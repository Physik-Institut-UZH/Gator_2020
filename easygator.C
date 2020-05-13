#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace std;

// written by G. R. Araujo
//
// Last update by ... in ...
// Check how to run and more info about the script in the README file in the same folder

void check_matlist(string sim_dir);
int build_geo(string samplename,string sim_dir);
bool itExists(string dirName_in);
int analysis();

int main()
{

//--------------------------------------------------------------------------------
 string GATORDIR="/disk/bulk_atp/gator"; //main directory for gator
 string sim_dir=GATORDIR+"/simulations/gator_v2.0"; // simulation directory, version 2.0
 string out_dir=GATORDIR+"/Simulation_Results"; // Results directory
 string slurmlog_dir=GATORDIR+"/slurmlog";
 string bashrcfile=GATORDIR+"/.bashrc";
//--------------------------------------------------------------------------------

 cout<<"*****************************************" <<endl;
 cout<<"*                                       *" <<endl;
 cout<<"*              EASY GATOR               *" <<endl;
 cout<<"*     simulation and analysis scripts   *" <<endl;
 cout<<"*        version 1.0 feb.2020           *" <<endl;
 cout<<"*                                       *" <<endl;
 cout<<"*****************************************" <<endl;

 // parameters used in a standard simulation
 int queue=2, nodes=50, n_beamOn=1000000, n_totevents=1e+5, n_isot_std=8, n_isot_full=16;//These numbers are organized in such a way that the a queue of 2 and 50 nodes are enough for 10+6 events per macro (n_beamOn). if the total number of events change, then the number of jobs will change !!! Make sure that the number of jobs do not exceed the limit.. standard number of events: (currently e6 x 100 files).

 string std_isotopes[n_isot_std]={"238U","232Th","40K","60Co","137Cs","226Ra","235U","228Th"};
 string full_isotopes[n_isot_full]= {"238U","232Th","40K","60Co","137Cs", "226Ra","235U", "228Th", "110mAg", "207Bi", "54Mn", "58Co", "56Co", "57Co","134Cs", "46Sc"};
 //other lines \"1001keV\","186keV", \"605keV\", \"658keV\", \"885keV\", \"1064keV\", "186keV\", \"570keV\", \"796keV\", \"937keV\"]";

// !!! note, other enviroments and library paths are set in the .bashrc file in the GATORDIR folder
//----------------------------------------------------------------------------------
 cout<<" Bash commands in this script are run in a fresh shell that sources from the .bashrc file located in "<<GATORDIR<<". \n Non-available versions of software and library paths can cause crashes. \n *** Press C to continue or B to check the .bashrc file first *** \n "<<endl; 
 char _key;
 cin>>_key;
 if (_key=='b' || _key=='B') system(("vi "+bashrcfile).c_str());

 string samplename; 
 cout<<"Type the name of the sample:"<<endl;
 cin>>samplename;
 int n_vol=0; //number of volumes is initially set to 0 and changed when the geom. is built

 char an_sim; int break_anal=0; 
 cout<<" Type A to run the analysis of a sample or S for simulation"<<endl;
 cin>>an_sim;
 
 // first check whether the simulation directory exists
 string s_dir=out_dir+"/"+samplename;
 char cont_sim='g';
 if (itExists(s_dir)) // in case it exists and you want to run a simulation, show message
 {
	if(an_sim!='a' && an_sim!='A') {cout<<" \n The simulation directory of this sample already exists. Type G to build a new geometry for this sample or S to directly run the simulation."; cin>>cont_sim;}
 }
 else if(!itExists(s_dir) && (an_sim=='a' || an_sim=='A'))
 {
	cout<<" \n The simulation directory of this sample does not exist. Type G to build a new geometry for this sample or S to run the simulation."; cin>>cont_sim; //to do: but here I need to check that the included geometry files are indeed from this sample
 }
 if (an_sim=='a' || an_sim=='A') break_anal=analysis();
 if (break_anal!=0) return 0;
 if (cont_sim!='s' && cont_sim!='S')//it does not build the geometry, if you only want to re-run a simulation
 { 
	 // Here the .icc and .ihh geometry files of the sample are created
	 n_vol=build_geo(samplename.c_str(), sim_dir);

	 //Now these files are linked the GeConstructor file, since these files contain #include "includesample.hh"
	 string s_incl_icc=sim_dir+"/src/includesample.hh";
	 ofstream incl_icc(s_incl_icc.c_str());
	 incl_icc<<"#include \""+samplename+".icc\"\n";
	 incl_icc.close();

	 string s_incl_ihh=sim_dir+"/include/includesample.hh";
	 ofstream incl_ihh(s_incl_ihh.c_str());
	 incl_ihh<<"#include \""+samplename+".ihh\"\n";
	 incl_ihh.close();

	 // Now the geometry is made, the overlap check is run, previous wrl files are deleted and a new is created.
	 string comm_makegeo="bash --rcfile "+GATORDIR+"/.bashrc -ci 'cd "+sim_dir+"; make clean -f GlobGeom_makefile; make -f GlobGeom_makefile; make clean; make; touch g4_trash.wrl; rm g4_*.wrl; cp bin/Linux-g++/gator_1.2 .; ./gator_1.2;'";  //here a bash interactive shell is open which loads a specific rc file, then the commands are run.
	 system(comm_makegeo.c_str());

	//now we check wheter the new wrl file was created, if not, this indicates that the previous commands did not run as expected: show warning and break.
	 if (!itExists(sim_dir+"/g4_00.wrl")) 
	 {cout<<" \n \n The .wrl file was not created. Check whether the geometry was made in the previous step or if there were errors "<<endl; return -1;}
	 
	 // Now the the wrl file is open with freewrl 
	 string s_echo="\n Opening .wrl file... \n\n *** Check wheter the geometry and position of the sample are right *** \n Then close the freewrl window to continue \n\n";
	 string comm_openwrl="bash --rcfile "+GATORDIR+"/.bashrc -ci 'cd "+sim_dir+"; echo \""+s_echo+"\"; freewrl g4_*.wrl'"; 
	 system(comm_openwrl.c_str());
 }//geometry part is finished

// Now, the isotopes and number of events used in the simulation are set. 
char c_inp;
int n_isot;
string isotopes[100];
cout<<"\n *************************************** \n\n ";
cout<<" To run the standard analysis (number of events: :"<<n_totevents<<" and standard list of isotopes: "; for (int i=0; i<n_isot_std; ++i){cout<<std_isotopes[i]<<" ";} cout<<"), type S. To see the full list of isotopes, type L. To modify parameters and isotopes, type M \n"<<endl;
 cin>>c_inp;
 switch(c_inp)
 {
	case 's': 
	case 'S': 
		break;
	case 'L': 
	case 'l': 
		cout<<"\n Full list of isotopes: ";
		for (int i=0; i<n_isot_full; i++){cout<<full_isotopes[i]<<" ";}
		cout<<" \n Type M to modify the list and other parameters or S to continue with the standard one"<<endl;
		cin>>c_inp;
		if (c_inp=='S' || c_inp=='s') break;
	case 'M': 
	case 'm': 
		cout<<" Input the number of isotopes/macros to be simulated \n";
		cin>>n_isot;
		cout<<"\n Copy the isotopes below that should be included\n";for (int i=0; i<n_isot_full; ++i){cout<<full_isotopes[i]<<" ";} cout<<"\n (if the isotope is not on the list, create a macro for it in the Sample_standard folder in "+out_dir+", modify the full list of this script and run it again)\n";
		for (int i=0; i<n_isot; ++i) {cin>>isotopes[i];}
		cout<<" Input the number of events to be simulated \n";
		cin>>n_totevents;
		break;
	default: cout<<"invalid choice. Type either S, L or M"<<endl;
 }
 if (c_inp!='m' && c_inp!='M') {n_isot=n_isot_std; for (int i=0; i<n_isot; ++i) {isotopes[i]= std_isotopes[i];}}

 // Now the output directory is created and the macros of all isotopes are copied (regardless if they will be run in the simulation). To do: give the possibility to run isotopes in addition to a previous simulation
 string comm_mkdirs_mv; 
 if (itExists(s_dir)) // first check whether the directory already exists
 {
	cout<<" \n The simulation directory of this sample already exists. Do you want to overwrite it? Press C to continue and ctrl+c to stop.\n"; char cont; cin>>cont;
	comm_mkdirs_mv="cd "+out_dir+" && rm -rf "+samplename+" && cp -r Sample_standard "+samplename+" && mv "+sim_dir+"/g4_*.wrl "+samplename; // it forces the directory to be recreated, in case it already exists
 }
 else 
 {
	comm_mkdirs_mv="cd "+out_dir+" && cp -r Sample_standard "+samplename+" && mv "+sim_dir+"/g4_*.wrl "+samplename;
 }
 system(comm_mkdirs_mv.c_str());

// now the macros of the isotopes are open and confine volume and number of events is written
string s_isolist="[";
string s_confinemorevolumes;

string sconfine;
if (n_vol>1) 
{
	cout<<" *** Check the volumes defined in the .ihh file below and input the _phys volumes to be confined *** \n";
	system("sleep 2.");
	system(("cat "+sim_dir+"/include/"+samplename+".ihh").c_str());
	cout<<" \n\nInsert them with the _phys extension and separated by space: \n";
	cin>>sconfine;
} 
else
{sconfine=samplename+"_phys";}


for (int i=0; i<n_isot; i++)
{
  ofstream append_macros(out_dir+"/"+samplename+"/macros/"+isotopes[i]+".mac", std::ios_base::app); // append instead of overwrite
  append_macros << "/xe/gun/confine "<<sconfine.c_str()<<"\n"; 
  append_macros<< "/run/beamOn "<<n_beamOn<<endl;
 string s_iso; if (i<n_isot-1) {s_iso="\""+isotopes[i]+"\",";} else {s_iso="\""+isotopes[i]+"\"";}
 s_isolist.append(s_iso);
}
 s_isolist.append("]"); //cout<<s_isolist<<endl;

// now the input necessary to send the jobs for the simulation is written (note that the $gatordir/.bashrc is sourced when submitting the jobs)
 string s_py_input=sim_dir+"/sim_input.py"; 
 ofstream py_input(s_py_input.c_str());
 py_input<<"gatordir=\""<<GATORDIR<<"\""<<endl;
 py_input<<"binary=\""<<sim_dir<<"/bin/Linux-g++/gator_1.2\""<<endl;
 py_input<<"datadir=\""<<out_dir.c_str()<<"\""<<endl;
 py_input<<"sample=\""<<samplename.c_str()<<"\""<<endl;
 py_input<<"queue=\""<<queue<<":00:00\"\nmaxnodes ="<<nodes<<endl;
 py_input<<"totevents="<<n_totevents<<endl;
 py_input<<"eventsxjob_str = \""<<n_beamOn<<"\""<<endl;
 py_input<<"isotope_list="<<s_isolist<<endl;

 py_input.close();

 //check whether there was any problem with simulations: whether there are files in the tmp_files (this did not work, it seems it was not compiled by the current gcc version)
 //string spath="/disk/bulk_atp/gator/slurm_tmpfiles/"; fs::path dirpath(spath.c_str()); if (dirpath.empty()) 

 //emptying the slurmlog folder for the new logfiles (moving old logs to archive)
 system(("mv "+slurmlog_dir+"/* "+slurmlog_dir+"_archive/").c_str());

 //Now the jobs to run the simulation will be submitted 
 string s_submit="cd "+sim_dir+" && screen  -S easygator_screen -dm bash -c 'python GatorSims.py;'"; // exec sh to keep the screen
 //ps: GatorSims.py is only a script to manage the jobs which are submitted using sbatch to pass parameter to the GatorSims.slurm script. This script runs the binary $binary "$macro" $gatordir/slurm_tmpfiles/$SLURM_JOB_ID/"$outfilename" > "$logfilename"
 system(s_submit.c_str());
 cout<<" ------------------------------------------- \n The jobs are being submitted in the easygator_screen. Type 'screen -r easygator_screen' if you want to check the screen. \n (ps: The screen is terminated once all jobs were submitted) \n\n use 'qstat -u username' to check status of the jobs and 'scancel -u username' to cancel the jobs. \n\n Check the log files in the slurmlog directory and in the logs folder in the sample directory.\n";

}

int analysis()
{
	cout<<" Analysis Mode "<<endl;
	return 1;
}
int build_geo(string samplename, string sim_dir) 
{

 string s_iccfile=sim_dir+"/src/"+samplename+".icc";
 string s_ihhfile=sim_dir+"/include/"+samplename+".ihh";

 int n_vol; cout<<" Type the number of volumes (n_vol) that were/will be constructed (if n_vol=1, its name will be the sample name) \n";
 cin>>n_vol;

 ifstream iccfile_check(s_iccfile.c_str()); 
 if (iccfile_check.good()) 
 {
	cout<<" The geometry file (.icc) of this sample already exists. If you continue, THE FILE WILL BE OVERWRITTEN. Type C to continue (overwrite), M  to modify the sample name or G to build the geometry and run the simulations without modifying/overwriting the geometry (.icc and .hh) files\n"; //to do: give an option to visualize the current geometry (openin wrl file)
	char cont;
	cin>>cont;
        if (cont=='M' || cont=='m') main();
	if (cont=='G' || cont=='g') return n_vol;
 }
 if (n_vol>20) {cout<<"n_vol is too large, max =20. Change max in the script \n"; return -1;}
 

  
 string s_volumes[20];
 if (n_vol>1)
 { 
	cout<<" Type the names of the volumes separated by space \n";
	for (int i=0; i<n_vol; i++) {cout<<"volume "<<i+1<<endl; cin>>s_volumes[i];}
 } 
 else
 { s_volumes[0]=samplename;}

 ofstream ihhfile(s_ihhfile.c_str()); //creates a new ihh file 
 ofstream iccfile(s_iccfile.c_str()); //creates a new .icc geometry file
 string sgeo;
 int break_buildgeo=0;

 iccfile<<"// Set visibility properties for all the samples \nG4VisAttributes* sample_vis = new G4VisAttributes(red);\nsample_vis -> SetVisibility(true); \nsample_vis -> SetForceSolid(false);\n";

 for (int i=0; i<n_vol; i++)
 {

	 ihhfile<<"\n// ---------- volume "<<s_volumes[i]<<" ---------- //\n\n";
	 ihhfile<<"//---------------   logical and physical volumes definitions \n";
	 ihhfile<<" G4LogicalVolume* "<<s_volumes[i]<<"_log;\n";
	 ihhfile<<" G4VPhysicalVolume* "<<s_volumes[i]<<"_phys;\n";

	 iccfile<<"\n//---------- volume "<<s_volumes[i]<<" ---------- \n\n";

	 cout<<"Is the geometry of the sample/volume \""<<s_volumes[i]<<"\" a box, a tube or other?"<<endl;
	 cin>>sgeo;

	 double dim[3];// x,y,z in mm for box or ID, OD and length for tubes.
	 int geom_ok; 
	 
	 do {
		 geom_ok=1;	
		 if (sgeo=="box")
		 {
			cout<<"type the x, y, z dimensions of the box in mm separated by space or ENTER (note: very small samples can lead to confinement  errors!!) "<<endl;
			cin>>dim[0]>>dim[1]>>dim[2];
			string sdim[3]={"x","y","z"};
			iccfile<<"//Dimensions of the sample in box and definition of the geometry"<<endl;
			for (int j=0; j<3;j++)
			{iccfile<<" G4double box_"<<s_volumes[i]<<"_"<<sdim[j]<<"= "<<dim[j]<<"*mm;"<<endl;}
			iccfile<<" G4Box* "<<s_volumes[i]<<"= new G4Box(\""<<s_volumes[i]<<"\",0.5*"<<"box_"<<s_volumes[i]<<"_"<<sdim[0]<<",0.5*"<<"box_"<<s_volumes[i]<<"_"<<sdim[1]<<",0.5*"<<"box_"<<s_volumes[i]<<"_"<<sdim[2]<<");\n\n";
		 }
		 else if (sgeo=="tube") 
		 {
			cout<<"type the ID, OD, and length of the tube in mm and separated by ENTER  (note: very small samples can lead to confinement  errors!!)"<<endl;
			cin>>dim[0]>>dim[1]>>dim[2];
			string sdim[3]={"ID","OD","L"};
			iccfile<<"//Dimensions of the sample in tube and definition of the geometry"<<endl;
			cout<<" *** Sorry, tube geometry not yet completely implemented **** \n";
			//** to do: implement tube geometry

		 } 
		 else if (sgeo=="other")
		 {
			cout<<" You can copy a file to use as basis for your new geometry. See the list below: \n"<<endl;
			string ls_src="cd "+sim_dir+"/src && ls *.icc"; 
			system("sleep 2.3"); system(ls_src.c_str());
			cout<<"\n Type the name of the file to be copied:"<<endl;
			string s_copy;
			cin>>s_copy; s_copy=sim_dir+"/src/"+s_copy;
			ifstream f(s_copy.c_str());
		   	if(f.good()) 
			{
				string copy_comm="cp "+s_copy+" "+s_iccfile;
				system(copy_comm.c_str());
		 		cout<<"Now modify and save the .icc geometry file \n";
				system("sleep 2.3"); 
				system(("vi "+s_iccfile).c_str());
				cout<<"Now modify and save the .ihh geometry file \n";
				system("sleep 2.3"); 
				system(("vi "+s_ihhfile).c_str());
				
			}
			else {cout<<" The file you typed does not exist. Maybe you forgot to type the .icc extension?"<<endl;}	
			return n_vol;
		 }
		 else 
		 {
			cout<<" invalid option, type box, tube or other"<<endl;
			cin>>sgeo; geom_ok=0;
		 }
	 } while (geom_ok==0);

	 string material;
	 check_matlist(sim_dir); //checks whether the material of the sample is already in the list.
	 cin>>material; 
	 
	 //Construct the logical volume
	 iccfile<<"//Construct the logical volume \n G4LogicalVolume* "<<s_volumes[i]<<"_log = new G4LogicalVolume("<<s_volumes[i]<<","<<material.c_str()<<",\""<<s_volumes[i]<<"_log\");\n"<<endl;

	 // Set visibility properties
	 iccfile<<"// Set visibility for the sample (all are set to the same color, change it if necessary) \n" <<s_volumes[i]<<"_log -> SetVisAttributes(sample_vis);\n\n";

	 // Set the position of the sample
	 double pos[3]; //coordinates x, y, z;
	 char Pos;
	 cout<<"If the sample is placed at the top and center of the detector (x=y=0), type D. If it is somewhere touching the bottom and the wall of the cavity (z=0, x=-cavity1_x/2+sample_size_x/2, y=0), type C. To set another position, type other\n";
	 cin>>Pos;
	 if (Pos=='D'||Pos=='d') //it positions the sample at the top of the detector.
	 {
		 iccfile<<"// Set coordinates for the position of the sample at the top of the detector\n";
		 iccfile<<"G4double "<<s_volumes[i]<<"_Pos_x =0*mm;\n";
		 iccfile<<"G4double "<<s_volumes[i]<<"_Pos_y =0*mm;\n";
		 if (sgeo=="box") iccfile<<"G4double "<<s_volumes[i]<<"_Pos_z= endcapPos_z+0.5*endcapHeight1+0.5*box_"<<s_volumes[i]<<"_z+0.01*mm;\n\n";
		 if (sgeo=="tube") 
		 {
			cout<<"the base of the tube is being positioned at the top of the detector. If this is not the case, rotate the tube\n";
			iccfile<<"G4double "<<s_volumes[i]<<"_Pos_z= endcapPos_z+ 0.5*endcapHeight1+ 0.5*tube_"<<s_volumes[i]<<"_L +0.01*mm;\n\n";
		}
	 }		
	 else // it simply writes some geometry that can be then changed (Pos=='C'|| Pos=='c') //To do: fix positions
	 {
		 iccfile<<"// Set coordinates for the position of the sample and the position vector touching the bottom and left wall of the cavity *** currently not working *** Check the positions againg \n";
		if (sgeo=="box")  
		{
			iccfile<<"G4double "<<s_volumes[i]<<"_Pos_y =-mylarOD-0.5*box_"<<s_volumes[i]<<"_y;\n";
			iccfile<<"G4double "<<s_volumes[i]<<"_Pos_z= 0.5*box_"<<s_volumes[i]<<"_z+0.01*mm-heightOfTheCrystal;\n";
		}
		if (sgeo=="tube") 
		{
			cout<<"the tube is being positioned parallel to the detector. If this is not the case, rotate the tube\n";
			iccfile<<"G4double "<<s_volumes[i]<<"_Pos_y =-mylarOD-0.5*tube_OD;\n";
			iccfile<<"G4double "<<s_volumes[i]<<"_Pos_z=0.5*tube_L +0.01*mm-heightOfTheCrystal;\n";
		}
		iccfile<<"G4double "<<s_volumes[i]<<"_Pos_x =0*mm;\n\n";
	 }


	 iccfile<<"// Define the position vector \n";
	 iccfile<<"G4ThreeVector "<<s_volumes[i]<<"_Pos("<<s_volumes[i]<<"_Pos_x,"<<s_volumes[i]<<"_Pos_y,"<<s_volumes[i]<<"_Pos_z); \n\n";

	 iccfile<<"// Define the physical volume \n";
	 iccfile<<"G4VPhysicalVolume* "<<s_volumes[i]<<"_phys = new  G4PVPlacement(0,"<<s_volumes[i]<<"_Pos,"<<s_volumes[i]<<"_log,\""<<s_volumes[i]<< "_phys\",cavity1_log,false,0,true);\n";
  }

 iccfile.close();
 ihhfile.close();

 cout<<"Check or modify the .icc geometry file \n";
 system("sleep 2.1"); 
 system(("vi "+s_iccfile).c_str());

 cout<<"Check or modify the .ihh geometry file \n";
 system("sleep 2.1"); 
 system(("vi "+s_ihhfile).c_str());

 return n_vol;

}

// This function asks the user whether the material of the sample is already in the list. If it is not, it asks the user to include it. 
void check_matlist(string sim_dir)
{
 string material_list=sim_dir+"/src/includematerials.hh"; 
 string s_comm_matlist="vi "+material_list;
 char is_mat;
 cout<<" Is the material of the sample already included in the material list? Press Y if the material is included, N if not or L to see the list."<<endl;
 cin>>is_mat; 
 switch(is_mat)
 {
	case 'L': 
	case 'l': 
		system(s_comm_matlist.c_str()); 
		check_matlist(sim_dir);
		break;
	case 'N': 
	case 'n': 
		cout<<" Insert the new material in the list"<<endl; 
		system("sleep 2.3"); system(s_comm_matlist.c_str()); 
		is_mat='Y';
	case 'Y': 
	case 'y': 
		cout<<"Type the name of the material as shown in the list: "<<endl; 
		break;
	default: cout<<"invalid choice. Type either L, N or Y"<<endl;
 }

}

bool itExists(string dirName_in)
{
  struct stat buffer;
  return (stat (dirName_in.c_str(), &buffer) == 0);
}



