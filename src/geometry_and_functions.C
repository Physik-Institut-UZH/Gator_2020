#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

int build_geo(string samplename, string sim_dir) 
{

 string s_iccfile=sim_dir+"/src/"+samplename+".icc";
 string s_ihhfile=sim_dir+"/include/"+samplename+".ihh";

 int n_vol; cout<<" Type the number of volumes (n_vol) that were/will be constructed (if n_vol=1, its name will be the sample name) \n";
 cin>>n_vol;

 ifstream iccfile_check(s_iccfile.c_str()); 
 if (iccfile_check.good()) 
 {
	cout<<" The geometry file (.icc) of this sample already exists. If you continue, THE FILE WILL BE OVERWRITTEN. Type G to continue (overwrite), S to build the geometry and run the simulations without modifying/overwriting the geometry (.icc and .hh) files or  CTRL+C to restart the script with a new sample name \n"; //to do: give an option to visualize the current geometry (openin wrl file)
	char cont;
	cin>>cont;
	if (cont=='S' || cont=='s') return n_vol;
 }
 iccfile_check.close();
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

	 if (n_vol>1) {cout<<"Is the geometry of the samples/volumes like box, tube or other (type other in case you have different geometries)?"<<endl;}
	 else { cout<<"Is the geometry of the sample \""<<s_volumes[i]<<"\" a box, a tube or other?"<<endl;}
	 cin>>sgeo;

	 double dim[3];// x,y,z in mm for box or ID, OD and length for tubes.
	 int geom_ok; 
	 
	 do {
		 geom_ok=1;	
		 if (sgeo=="box")
		 {
			cout<<"type the x, y, z dimensions of the box \""<<s_volumes[i]<<"\" in mm separated by space or ENTER (note: very small samples can lead to confinement  errors!!) "<<endl;
			cin>>dim[0]>>dim[1]>>dim[2];
			string sdim[3]={"x","y","z"};
			iccfile<<"//Dimensions of the sample in box and definition of the geometry"<<endl;
			for (int j=0; j<3;j++)
			{iccfile<<" G4double box_"<<s_volumes[i]<<"_"<<sdim[j]<<"= "<<dim[j]<<"*mm;"<<endl;}
			iccfile<<" G4Box* "<<s_volumes[i]<<"= new G4Box(\""<<s_volumes[i]<<"\",0.5*"<<"box_"<<s_volumes[i]<<"_"<<sdim[0]<<",0.5*"<<"box_"<<s_volumes[i]<<"_"<<sdim[1]<<",0.5*"<<"box_"<<s_volumes[i]<<"_"<<sdim[2]<<");\n\n";
		 }
		 else if (sgeo=="tube") 
		 {
			/*cout<<"type the ID, OD, and length of the tube in mm and separated by ENTER  (note: very small samples can lead to confinement  errors!!)"<<endl;
			cin>>dim[0]>>dim[1]>>dim[2];
			string sdim[3]={"ID","OD","L"};
			iccfile<<"//Dimensions of the sample in tube and definition of the geometry"<<endl;*/
			cout<<" *** Sorry, tube geometry not yet completely implemented **** \n";
			sgeo="other";
			//** to do: implement tube geometry

		 } 
		 else if (sgeo=="other")
		 {
			cout<<" You can copy a file to use as basis for your new geometry. See the list below: \n"<<endl;
			string ls_src="cd "+sim_dir+"/src && ls *.icc"; 
			system("sleep 2.3"); system(ls_src.c_str());
			cout<<"\n Type the name of the file to be copied (without .icc):"<<endl;
			string s_copy;//sample copy
			cin>>s_copy;  string s_copy_iccfile=sim_dir+"/src/"+s_copy+".icc";

			ifstream f(s_copy_iccfile.c_str());
		   	if(f.good()) 
			{
				system(("cp "+sim_dir+"/src/"+s_copy+".icc "+s_iccfile+" && sed -i s/\""+s_copy+"\"/\""+samplename+"\"/g "+s_iccfile).c_str());
		 		cout<<"Now modify and save the .icc geometry file \n";
				system(("sleep 2.3 && vi "+s_iccfile).c_str());
				system(("cp "+sim_dir+"/include/"+s_copy+".ihh "+s_ihhfile+" && sed -i s/\""+s_copy+"\"/\""+samplename+"\"/g "+s_ihhfile).c_str());
				cout<<"Now modify and save the .ihh geometry file \n";
				system(("sleep 2.3 && vi "+s_ihhfile).c_str());
				
			}
			else {cout<<" The file you typed does not exist: "<<s_copy_iccfile<<endl; return -1;}	
			system(("cp "+s_iccfile+" tmp_copy_of_the_iccfile").c_str()); 
			return n_vol;
		 }
		 else 
		 {
			cout<<" invalid option, type box, tube or other"<<endl;
			cin>>sgeo; geom_ok=0;
		 }
		 if (n_vol>1 && sgeo=="other") break;
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

 system(("cp "+s_iccfile+" tmp_copy_of_the_iccfile").c_str()); //note, this is only a copy, the real file is int the sim_dir

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

string checkfunction(string data_dir, string samplefilename)
{
	system((" ls "+data_dir+"/"+samplefilename+"_20*.SPE > tmpfilelist").c_str());
	ifstream checktmp("tmpfilelist"); checktmp.seekg(0, ios::end); 
	if (checktmp.tellg()==0) {system(("echo '\n It seems that the name of the SPE files is different from the samplename used in the simulation and analysis, please check below the name of the file you want to read \n' && sleep 5.2 && ls -ltr "+data_dir+"/*.SPE && echo '\n\nNow, look for the correct name of the sample as written in the files above and type here only the part before _datum \n'").c_str()); cin>>samplefilename; system(("ls "+data_dir+"/"+samplefilename+"_20*.SPE > tmpfilelist").c_str()); ifstream checktmp2("tmpfilelist"); checktmp2.seekg(0, ios::end); 
	if (checktmp2.tellg()==0) {cout<<"The name is still wrong: "<<samplefilename<<" \nTry again"<<endl; return "N";}} //checkfunction(string data_dir, string samplefilename //To do: there is some bug here. If you have to type the samplefilename twice (by calling the function again) it returns to the main function the wrong samplefilename (the first one typed). Here is a temporary fix was to return -1 in this case so that people run the code again

	return samplefilename; 
}

bool itExists(string dirName_in)
{
  struct stat buffer;
  return (stat (dirName_in.c_str(), &buffer) == 0);
}
