#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <experimental/filesystem>
#include "include/geometry_and_functions.h" 
#include "src/geometry_and_functions.C"  // code with standard geometries and som other functions used here


namespace fs = std::experimental::filesystem;
using namespace std;

// written by Gabriela R. Araujo
// University of Zurich, May 2020
// Last update by G.R A. in March 2021 (include new calib folders)
// Check how to run and more info about the script in the README file

int analysis(string s_dir, string ana_dir, string data_dir, string background_dir, string calib_dir, string samplename, string bashrcfile, int n_isot_full, string full_isotopes[], string GATORDIR_summary);

int main()
{

//--------------------------------------------------------------------------------
// main directory for gator, this variable should be declared in the .bashrc file or exported
//-------------------------------------------------------------------------------
 string GATORDIR(getenv("GATORDIR"));
//--------------------------------------------------------------------------------
// central directory in ATP for all sample summary files. Don't
// write in this directory for other purposes.
//-------------------------------------------------------------------------------
 string GATORDIR_summary(getenv("GATORDIR_summary"));
//--------------------------------------------------------------------------------
// These paths are relative and should not be changed
//-------------------------------------------------------------------------------
 string data_dir="/home/atp/atp/GatorSC/Data/SAMPLE_REPORTS/SPE";// The SPE files at the DAQ machine at  LNGS are transferred to this directory by the automatic script in marmotx.
 string sim_dir=GATORDIR+"/simulations/gator_v2.0"; // simulation directory, version 2.0
 string ana_dir=GATORDIR+"/analysis"; // analysis directory with efficiency and analysis scripts
 string out_dir=GATORDIR+"/Sample_Sim_and_Analysis_Results"; // Results directory, it is created if it does not exist yet
 string calib_dir=GATORDIR+"/Calibrations/";// this value changes later to the specific calib folder chosen by the user
 string background_dir = GATORDIR+"/background"; // The SPE files used for background (with option to choose)
 string slurmlog_dir=GATORDIR+"/slurmlog";//log for jobs sent. Directory is created if it does not exist yet
 string bashrcfile=GATORDIR+"/.bashrc";//file for where all the variables and software version are defined
 string bin_dir=sim_dir+"/bin/Linux-g++";//path to the binary file
 string bin_name="gator_1.2"; //name of the binary file
//--------------------------------------------------------------------------------
 
 cout<<"*****************************************" <<endl;
 cout<<"*                                       *" <<endl;
 cout<<"*              EASY GATOR               *" <<endl;
 cout<<"*     simulation and analysis scripts   *" <<endl;
 cout<<"*        version 1.0 jun.2020           *" <<endl;
 cout<<"*                                       *" <<endl;
 cout<<"*****************************************" <<endl;

 // parameters used in a standard simulation
 int queue=5, nodes=100, n_beamOn=100000, n_totevents=1e+7, n_isot_std=8, n_isot_full=16, n_isot_full_sim=10;//These numbers are organized in such a way that the a queue of 2 and 50 nodes are enough for 10+6 events per macro (n_beamOn). if the total number of events change, then the number of jobs will change !!! Make sure that the number of jobs does not exceed the limit.. standard number of events: (currently e6 x 100 files). -> update: somehow a queue of 2 and 50 nodes is not enough anymore, so I changed values
 if (n_beamOn<10000) cout<<" min n_beamOn=10000"<<endl; //this is because of the output in the log files, which are later read to check whether the sim ran properly

 string std_isotopes[n_isot_std]={"238U","232Th","40K","60Co","137Cs","226Ra","235U","228Th"};
 string full_isotopes[n_isot_full]= {"238U","232Th","40K","60Co","137Cs", "226Ra","235U",  "54Mn", "58Co", "56Co","46Sc", "186keV", "1001keV","Pa", "7Be", "210Pb"};//Note: do not remove isotopes from the full list, since they need to be later read by EffCalcAll.cpp. If you add new isotopes, you need to write a new function for it in EffCalcAll.cpp as well and create macros.// isotopes that have macros but are not in the analysis: "228Th", "110mAg", "207Bi","57Co","134Cs". Isotope 56Co not working, but needs to be in the list.
 string full_isotopes_sim[n_isot_full_sim]= {"238U","232Th","40K","60Co","137Cs", "226Ra","235U", "54Mn", "58Co", "46Sc"};// Some isotopes are in the analysis (EffCalcAll.cpp) but have no macros: "Pa" (maybe it is the same to 1001Pa?), "7Be", "210Pb". 
//other lines \"1001keV\","186keV", \"605keV\", \"658keV\", \"885keV\", \"1064keV\", "186keV\", \"570keV\", \"796keV\", \"937keV\"]"; -> for these you may need EffCalcLine.cpp, not yet implemented in easygator

//----------------------------------------------------------------------------------
 char _key;
 while(_key!='c' && _key!='C') 
{
	 cout<<" Bash commands in this script are run in a fresh shell that sources from the .bashrc file located in "<<GATORDIR<<". \n Non-available versions of software and library paths can cause crashes. \n *** Press C to continue or B to check the .bashrc file first *** \n "<<endl;  cin>>_key; 
	if (_key=='b' || _key=='B') system(("vi "+bashrcfile).c_str());
}

 string samplename; 
 cout<<"Type the name of the sample:"<<endl;
 cin>>samplename;
 int n_vol=0; //number of volumes is initially set to 0 and changed when the geom. is built

 char an_sim; int break_anal=0; 
 cout<<" Type A to run the analysis of a sample or S for simulation"<<endl;
 cin>>an_sim;

 if(!itExists(out_dir)) system(("mkdir "+out_dir+" && mv Sample_standard "+out_dir+"/").c_str());

  string s_dir=out_dir+"/"+samplename;// Sample directory
 // first check whether the sample directory exists
 char cont_sim='g';
 if (itExists(s_dir)) // in case it exists and you want to run a simulation, show message
 {
	if(an_sim!='a' && an_sim!='A') {cout<<" \n The Sample Simulation/Results directory of this sample already exists. Type G to modify the geometry files for this sample or S to directly run the simulation.\n"; cin>>cont_sim;}
 }
 else if(!itExists(s_dir) && (an_sim=='a' || an_sim=='A'))
 {
	cout<<" \n The simulation directory of this sample does not exist. Type G to write a new geometry file for this sample or S to run the simulation. \n"; an_sim='x'; cin>>cont_sim; 
 }
 if (an_sim=='a' || an_sim=='A') {break_anal=analysis(s_dir, ana_dir, data_dir, background_dir, calib_dir, samplename, bashrcfile, n_isot_full, full_isotopes, GATORDIR_summary); return break_anal;}
 if (cont_sim=='g' || cont_sim=='G')//if you only want to re-run a simulation, this part is skipped
 { 
	
	 // Here the .icc and .ihh geometry files of the sample are created
	 n_vol=build_geo(samplename.c_str(), sim_dir);
	 if (n_vol<0) {cout<<" Error in building geometry"<<endl; return -1;}

	 //Now these files are linked the GeConstructor file, since these files contain #include "includesample.hh"
	 string s_incl_icc=sim_dir+"/src/includesample.hh"; 
	 system(("> "+s_incl_icc).c_str()); //emptying the file first
	 ofstream incl_icc(s_incl_icc.c_str(), std::ios_base::app);
	 incl_icc<<"#include \""+samplename+".icc\"\n";
	 incl_icc.close();

	 string s_incl_ihh=sim_dir+"/include/includesample.hh"; 
	 system(("> "+s_incl_ihh).c_str()); //emptying the file first
	 ofstream incl_ihh(s_incl_ihh.c_str(), std::ios_base::app);
	 incl_ihh<<"#include \""+samplename+".ihh\"\n";
	 incl_ihh.close();

	 //now the permission of these files are changed so that they can be modified by other users
	 //system(("chmod g+w "+s_incl_icc+"; chmod g+w "+s_incl_ihh+";").c_str());

	 // Now the geometry is made, the overlap check is run, previous wrl files are deleted and a new is created.
	 string comm_makegeo="bash --rcfile "+bashrcfile+" -ci 'cd "+sim_dir+"; make clean -f GlobGeom_makefile; make -f GlobGeom_makefile; make clean; make; chmod -R g+w tmp/Linux-g++; touch g4_trash.wrl; rm g4_*.wrl; cp  "+bin_dir+"/"+bin_name+" .; ./"+bin_name+";'";  //here a bash interactive shell is open which loads a specific rc file, then the commands are run.
	 system(comm_makegeo.c_str());

	//now we check wheter the new wrl file was created, if not, this indicates that the previous commands did not run as expected: show warning and break.
	 if (!itExists(sim_dir+"/g4_00.wrl")) 
	 {cout<<" \n \n The .wrl file was not created. Check whether the geometry was made in the previous step or if there were errors "<<endl; return -1;}
	 
	 // Now the the wrl file is open with freewrl 
	 string s_echo=" \n Opening .wrl file... \n\n *** Check wheter the geometry and position of the sample are right *** \n Click on the window first (to save a print of the geometry) and then close the freewrl window to continue \n\n";
	// int size=90; let str= String(format: "%.2f%%", size);
	 string comm_openwrl="bash --rcfile "+bashrcfile+" -ci 'cd "+sim_dir+" && echo \""+s_echo+"\" && sleep 3 && freewrl g4_00.wrl | import -window -94371852 -resize \"90%\" g4_00.pdf'"; //&& echo \"This is a screenshot of the geometry. If it is not good, save a new screenshot with the name g4_00.pdf before going to the analysis\" && sleep 4 && xdg-open g4_00.pdf
	 system(comm_openwrl.c_str());
 }//geometry part is finished

// Now, the isotopes and number of events used in the simulation are set. 
char c_inp;
int n_isot;
string isotopes[100];
cout<<"\n *************************************** \n\n ";
cout<<" To run the standard analysis (number of events: "<<n_totevents<<" and standard list of isotopes: "; for (int i=0; i<n_isot_std; ++i){cout<<std_isotopes[i]<<" ";} cout<<"), type S. To see the full list of isotopes, type L. To modify parameters and isotopes, type M \n"<<endl;
 cin>>c_inp;
 switch(c_inp)
 {
	case 's': 
	case 'S': 
		break;
	case 'L': 
	case 'l': 
		cout<<"\n Full list of isotopes: ";
		for (int i=0; i<n_isot_full_sim; i++){cout<<full_isotopes_sim[i]<<" ";}
		cout<<" \n Type M to modify the list and other parameters or S to continue with the standard one"<<endl;
		cin>>c_inp;
		if (c_inp=='S' || c_inp=='s') break;
	case 'M': 
	case 'm': 
		cout<<" Input the number of isotopes/macros to be simulated \n";
		cin>>n_isot;
		cout<<"\n Copy the isotopes below that should be included\n"; for (int i=0; i<n_isot_full_sim; ++i){cout<<full_isotopes_sim[i]<<" ";} cout<<"\n If the isotope is not on the list, create a macro for it in the Sample_standard folder in "+out_dir+", modify the full list of this script and run it again. You then also need to write new functions for the analysis in the EffCalcAll.cpp. \n";// 
		for (int i=0; i<n_isot; ++i) {cin>>isotopes[i];}
		cout<<" Input the number of events to be simulated \n";
		cin>>n_totevents;
 		if (n_totevents<n_beamOn) {cout<<" min number of events = n_beamOn ="+n_beamOn<<endl; cin>>n_totevents;}
		break;
	default: cout<<"invalid choice. Type either S, L or M"<<endl;
 }
 if (c_inp!='m' && c_inp!='M') {n_isot=n_isot_std; for (int i=0; i<n_isot; ++i) {isotopes[i]= std_isotopes[i];}}

 // Now the output directory is created and the macros of all isotopes are copied (regardless if they will be run in the simulation). To do: give the possibility to run isotopes in addition to a previous simulation
 string comm_mkdirs_mv; 
 if (itExists(s_dir)) // first check whether the directory already exists
 {
	cout<<" \n The simulation directory of this sample already exists. Do you want to overwrite it? Press C to continue and ctrl+c to stop.\n"; char cont; cin>>cont;
	comm_mkdirs_mv="mv "+s_dir+"/g4_* "+sim_dir+"/ ; mv "+s_dir+"/tmp_copy_of_the_iccfile "+GATORDIR+"/ ; cd "+out_dir+" && rm -rf "+samplename+" && cp -r Sample_standard "+samplename+" && mv "+sim_dir+"/g4_* "+samplename+" && mv "+GATORDIR+"/tmp_copy_of_the_iccfile "+samplename+"/"; // it forces the directory to be recreated, in case it already exists
 }
 else 
 {
	comm_mkdirs_mv="cd "+out_dir+" && cp -r Sample_standard "+samplename+" && mv "+sim_dir+"/g4_* "+samplename+" && mv "+GATORDIR+"/tmp_copy_of_the_iccfile "+samplename+"/";
 }
 system(comm_mkdirs_mv.c_str());

// now the macros of the isotopes are open and confine volume and number of events is written
string s_isolist="[ ";//ps: keep this space character here
string s_confinemorevolumes;

string sconfine;
if (n_vol>1 || n_vol==0) 
{
	cout<<"\n *** Check the volumes defined in the .ihh file below and input the physical volumes to be confined *** \n";
	system("sleep 2.");
	system(("cat "+sim_dir+"/include/"+samplename+".ihh").c_str());
	cout<<" \n\nInsert the volumes to be confined separated by space, and then press Enter\n";
	system("sleep 2.");
	cin.ignore(); getline(cin,sconfine);
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
 if (i==0)
 {
	cout<<"Check one of the macros, make sure that the physical volumes to be confined are right, otherwise start again"<<endl;
	system("sleep 3.");
	system(("vi "+out_dir+"/"+samplename+"/macros/"+isotopes[i]+".mac").c_str());
 }
}
 s_isolist.append("]"); //cout<<s_isolist<<endl;

// now the input necessary to send the jobs for the simulation is written (note that the $gatordir/.bashrc is sourced when submitting the jobs)
 string s_py_input=sim_dir+"/sim_input.py"; 
 system(("> "+s_py_input).c_str()); //emptying the file first
 ofstream py_input(s_py_input.c_str(), std::ios_base::app);
 py_input<<"gatordir=\""<<GATORDIR<<"\""<<endl;
 py_input<<"binary=\""<<bin_dir<<"/"<<bin_name<<"\""<<endl;
 py_input<<"datadir=\""<<out_dir.c_str()<<"\""<<endl;
 py_input<<"sample=\""<<samplename.c_str()<<"\""<<endl;
 py_input<<"queue=\""<<queue<<":00:00\"\nmaxnodes="<<nodes<<endl;
 py_input<<"totevents= "<<n_totevents<<endl;//space is important here to read integer later
 py_input<<"n_beamOn= "<<n_beamOn<<endl;
 py_input<<"isotope_list="<<s_isolist<<endl;

 py_input.close();



 //emptying the slurmlog folder for the new logfiles (moving old logs to archive) 
 if (!itExists(slurmlog_dir.c_str())) system(("mkdir "+slurmlog_dir+"; mkdir "+slurmlog_dir+"_archive;").c_str());
 system(("mv "+slurmlog_dir+"/* "+slurmlog_dir+"_archive/").c_str());

 //Now the jobs to run the simulation will be submitted 
 string s_submit="cd "+sim_dir+" && cp sim_input.py "+s_dir+"/ && screen  -S easygator_screen -dm bash -c 'python GatorSims.py;'"; // exec sh to keep the screen
 
 //ps: GatorSims.py is only a script to manage the jobs which are submitted using sbatch to pass parameter to the GatorSims.slurm script. This script runs the binary $binary "$macro" $gatordir/slurm_tmpfiles/$SLURM_JOB_ID/"$outfilename" > "$logfilename"

 system(s_submit.c_str());
 cout<<"\n\n ------------------------------------------- \n The jobs are being submitted in the easygator_screen. Type 'screen -r easygator_screen' if you want to check the screen. \n (ps: The screen is terminated once all jobs were submitted) \n\n Use 'qstat -u username' to check status of the jobs: make sure that they are running (check slurm log if they get immediately canceled). Use 'scancel -u username' to cancel the jobs if needed. \n\n Job submission errors are output in the log files in the slurmlog directory and script errors in the logs folder in the sample directory.\n";

}//end of main()

int analysis(string s_dir, string ana_dir, string data_dir, string background_dir, string calib_dir, string samplename, string bashrcfile, int n_isot_full, string full_isotopes[], string GATORDIR_summary)
{
	int totevents, n_beamOn, sim_events, n_isot=0;
	string analysislogfile=s_dir+"/analysis_input.log";

//------// First: Check whether the analysis has already been run before and if so, from where to re-start it -------------------
	char r_ana;
	string message=" A: Simulation log checks\n B: Merge simulations root files\n C: Efficiency calculation (EffCalcAll.cpp script) from the simulation files\n D: Copy and selection of the SPE files \n E: Results: Spectrum plot & activity calculation (BuildFastSpectrum.cpp & sampleanalysis.cpp scripts) \n F: Merge main logs, plots and results into summary PDF \n or CTRL+C to exit the script\n";
	string runbf="The analysis of this sample was already run before";
	string stype="type one of the options below to start the simulation from: \n"+message;
	
	if (itExists(analysislogfile.c_str())) 
	{	
		string message_=runbf+". Type L to see the log file, or "+stype;
		cout<<message_<<endl; cin>>r_ana;
		if (r_ana=='l' || r_ana=='L') 
		{
			system ((" vi "+analysislogfile).c_str()); cout<<"ctrl+C to exit or "<<stype;
		}
	}
	else if (itExists((s_dir+"/output_sampleanalysis.txt").c_str()))
	{cout<<runbf<<", and the final resuts have already been calculated. If you want to repeat this step, press E, otherwise, "<<stype; cin>>r_ana;}
	else if (itExists((s_dir+"/SPE").c_str()))
	{cout<<runbf<<", the SPE files were already copied/selected. If you want to repeat this step, press D, otherwise, "<<stype; cin>>r_ana;}
	else if (itExists((s_dir+"/efficiency.log").c_str()))
	{cout<<runbf<<", the efficiency script was already run, If you want to do it again, press C, otherwise, "<<stype; cin>>r_ana;} 
	else if (itExists((s_dir+"/merged").c_str())) 
	{cout<<runbf<<", the log checks of the simulation were performed and the root files were merged, If you want to do it again, press B, otherwise, "<<stype; cin>>r_ana;}
	else {cout<<" This analysis is done in 6 steps: \n"<<message<<endl; r_ana='A';}
	while(r_ana!='A' && r_ana!='B' && r_ana!='C' && r_ana!='D' && r_ana!='E' && r_ana!='F') 
	{cout<<" Not a valid option (mind uppercase!). "<<stype<<endl; cin>>r_ana;}
//-------- End of check --------------------------------------------------------------------------------------------------


	// Before starting the analysis, we check whether the simulation worked as it should by comparing the input file of the simulation to the total of simulated events, scanning for errors in the log files, verifying the size of the root files and checking whether they merged properly
	if (r_ana=='A' || r_ana=='B' || r_ana=='C') //otherwise it skips diretly to copy SPE (D)
	{
		string readinput, line, readline, isotopes[100];
		string readinput_file=s_dir+"/sim_input.py";
		cout<<"\n *** Reading the inputs of the simulation for the analysis ***  "<<endl;
		ifstream readsim_input(readinput_file.c_str()); 
		if(!readsim_input.is_open()) cout<<" error in reading the simulation input file: "<<s_dir+"sim_input.py"<<" \n If there was no sim_input.py file for this simulation, please make one in order to run the analysis or re-run the simulation. "<<endl;

		while (readsim_input>>readinput) 
		{
			if (readinput=="totevents=") {readsim_input>>totevents; cout<<"totevents="<<totevents<<endl;}
			if (readinput=="n_beamOn=") {readsim_input>>n_beamOn; cout<<"n_beamOn="<<n_beamOn<<endl;}
			if (readinput=="isotope_list=[")
			{
				cout<<"isotope_list=";
				readsim_input>>line;
				istringstream iline(line);
				getline(iline, readline, '\"');
				while (readline!="]")
				{
					getline(iline, readline, '\"');
					if (readline!="," && readline!="]") 
					{
						isotopes[n_isot]=readline;
						cout<<isotopes[n_isot]<<",";
						n_isot++;
					}

				}
				cout<<"\n";
			} 


		}

		int totjobs=totevents/n_beamOn, n_errors=0;
		stringstream stotev; stotev<<totevents;
		string logdir=s_dir+"/logs/"; 
		string effscript=ana_dir+"/EffCalcAll.cpp"; // This script calculates the prob. of a gamma from the sample to reach the det.
	 	string isotvarh=ana_dir+"/isotopes.h", isotvarcpp=ana_dir+"/isotopes.cpp";// in this file we save a list of isotopes as variables to be read by EffcalcAll.cpp


		// Now we read the log files for each isotope and job
		system("sleep 2.8 && echo '\n\n *** Opening log files to check simulated events and errors *** \n Note: this is a simple check of simulated events and \"grep\" error scan. If something seems to be wrong, check the log files anyway. ' && sleep 3.0");  
		for (int t=0; t<n_isot; t++) 
		{
			for (int j=1; j<=totjobs; j++)
			{
				stringstream s_nbeam, sjob; s_nbeam<<n_beamOn;
				sjob<<j;
				string logfile=logdir+samplename+"_"+isotopes[t]+"_"+s_nbeam.str()+"_"+sjob.str()+".log";

				ifstream readlogfile(logfile.c_str(),ios::ate);
				if (!readlogfile.is_open()) cout<<"Error: logfile was not open: "<<logfile<<endl;
				for (int i=90; i<200; i++)//positioning the cursor at the end of the file
				{ 
					//it goes through the file (starting at the end, until if finds n_beamOn 
					readlogfile.seekg(-i, ios::end); 
					readlogfile>>sim_events;
					//cout<<sim_events<<endl;
					if (sim_events==n_beamOn) break;	

				}
				if (sim_events!=n_beamOn){ n_errors++; cout<<"Error: there was a problem with log file " <<logfile<<": the number of simulated events read from the log ("<<sim_events<<") does not seem to match n_beamOn ("<<n_beamOn<<"). Check the file for errors"<<endl;}
			}
		}
		system(("cd "+logdir+" && grep -iRl \"rror\" * > errors.log").c_str());
		ifstream errorlog(logdir+"errors.log"); if (!errorlog.is_open()) cout<<"error log file did not open: "+logdir+"errors.log"<<endl; 
		stringstream snerrors; snerrors<<n_errors;

		system(("sleep 2.4 && echo '---> Logfile check was completed. *** "+snerrors.str()+" errors or files with incomplete simulation were found  ***' && sleep 2.6").c_str());
		if (n_errors>0) {cout<<" \n Do you want to continue the analysis despite the errors? if yes, type C, if not, ctrl+C. The list of files that contain error messages is in "+logdir+"errors.log. Also check the messages above in case logfiles were not open. This indicates the simulation maybe crashed before it finished. If no log files were produced, maybe there was an error in submitting the jobs, so check for errors in the slurmlog directory in this folder. \n"; char cont; cin>>cont;}

		//Now log file checks were done, so we check the sizes of root files and merge them (the merge dir is recreated in case it existed before).
		if (r_ana!='C')// in this case, skip merge
		{
			string merge_dir=s_dir+"/merged"; system(("rm -rf "+merge_dir+" && mkdir "+merge_dir+" && echo '\n \n*** Merging root files for each isotope *** \n merge logs are in the merged directory and are scanned for errors, as well as file sizes are checked \n\n' && sleep 2.5").c_str()); 
			for (int t=0; t<n_isot; t++) 
			{

				string rootdir=s_dir+"/"+isotopes[t];
				string mergedroot=merge_dir+"/"+isotopes[t]+".root";
				string mergelog=merge_dir+"/merge_"+isotopes[t]+".log";
				string checkfilesizes="sleep 2.4 && cd "+rootdir+" && min=$(ls -l | gawk '{sum += $5; n++;} END {printf \"%i\", sum/(n-1)*.75;}') && max=$(ls -l | gawk '{sum += $5; n++;} END {printf \"%i\", sum/(n-1)*1.25;}') && nfiles=$(find . -type f -size +\"$min\"c -size -\"$max\"c | wc -l) && nfilestot=$(ls | wc -l) && if [ $nfiles -eq $nfilestot ]; then echo \"GOOD :-) all root files in the "+isotopes[t]+" folder are roughly the same size, files will be therefore merged\" && sleep 2.4; else echo \"*** ERROR: one or more root files have a significantly different size, check it below\" && ls -l && sleep 2.4 && echo \"press C to continue anyway or S to stop the script and check further what happened\" && read var && echo \"$var\" > ../tmpfile; fi"; char cont='C';
				system (checkfilesizes.c_str()); ifstream var((s_dir+"/tmpfile").c_str()); 
				if(var.good()) {var>>cont; system(("rm "+s_dir+"/tmpfile").c_str());}
				if (cont!='C' && cont!='c') {cout<<"script stopped by the user \n"; return -1;}
				system(("bash --rcfile "+bashrcfile+" -ci 'hadd "+mergedroot+" "+rootdir+"/*.root &> "+mergelog+"; cd "+merge_dir+" && grep -iRl \"error\" * > mergelog.err' &> /dev/null").c_str()); //hadd and then grep errors in the hadd log 
				ifstream checklog((merge_dir+"/mergelog.err").c_str()); checklog.seekg(0, ios::end);  
				if (checklog.tellg()!=0) // if it is not empty
				{
					cout<<"\n *** MERGER ERRORS were found in these merge: \n\n";
					system(("tail "+merge_dir+"/mergelog.err && echo \"press C to continue or S to stop the script and check further what happened\" && read var && echo \"$var\" > "+s_dir+"/tmpfile").c_str());
					ifstream var((s_dir+"/tmpfile").c_str()); var>>cont; 
					system(("rm "+s_dir+"/tmpfile").c_str());
					if (cont!='C' && cont!='c') {cout<<"script stopped by the user \n"; return -1;}
				} else { cout<<"\n No merge errors were found, but check the merge log "+mergelog+" in case something weird happens \n"<<endl;} 
			}
		}

	 	// Now we write the isotopes.h and isotopes.cpp header files of EffCalcAll.cpp.
		system(("> "+isotvarh).c_str()); //emptying the file first
		system(("> "+isotvarcpp).c_str()); //emptying the file first

		ofstream isoh(isotvarh.c_str(), std::ios_base::app);
		ofstream isocpp(isotvarcpp.c_str(), std::ios_base::app);
		isoh<<"#ifndef SIM_ISOTOPES\n#define SIM_ISOTOPES\n\n";
		isocpp<<"#include \"isotopes.h\"\n";
		for (int i=0; i<n_isot_full; i++)
		{
			bool isinthelist=false;
			for (int j=0; j<n_isot; j++)
			{if (full_isotopes[i]==isotopes[j]) {isinthelist=true; break;}}
			string strue; if (isinthelist) strue="true"; else strue="false";
			isocpp<<"bool i_"<<full_isotopes[i]<<" = "<<strue<<";\n";
			isoh<<"extern bool i_"<<full_isotopes[i]<<";\n";

		}
		isoh<<"\n#endif";
		isoh.close(); isocpp.close();
		
		cout<<"\n *** Running the efficiency script "+effscript+" *** \n\n";
		system(("sleep 3.8 && bash --rcfile "+bashrcfile+" -ci 'root -b -l <<EOF\n.L "+isotvarcpp+"++\n.x "+effscript+"(\""+s_dir+"\","+stotev.str()+") 2>  "+s_dir+"/efficiency.log\n.q\nEOF'").c_str()); // -b (no graphics) // 2> sends info and error message to a log file. Check this log file and display it

		// Now, check if there were errors
		system(("grep -i \"rror\" "+s_dir+"/efficiency.log > "+s_dir+"/efficiency.err").c_str());
		ifstream checkerr((s_dir+"/efficiency.err").c_str()); checkerr.seekg(0, ios::end); 
		if (checkerr.tellg()!=0) {cout<<"\n*** ERRORS were found when running the efficiency script, as shown in the log:\n";}
		else {cout<<"\nNo errors were found while running the efficiency script\nYet, please check the log: \n\n";}
		system(("sleep 4. && vi "+s_dir+"/efficiency.log").c_str()); 
		if (checkerr.tellg()!=0) {cout<<"Now ctrl+c in case you want to stop the analysis or type C to continue despite errors.\n\n"; char s_cont; cin>>s_cont; if (s_cont!='c' && s_cont!='C') return -1;}
	}// end of r_ana if A, B, C

	// Now, we copy the SPE files to the s_dir 
	if (r_ana!='E' && r_ana!='F') // In these cases, skip these parts
	{
		string samplefilename_tmp=samplename; //we initialize it like this
		string samplefilename=checkfunction(data_dir, samplefilename_tmp);
		if (samplefilename=="N") return -1;

		system(("rm tmpfilelist; cd "+s_dir+" && rm -rf SPE && mkdir SPE && cp "+data_dir+"/"+samplefilename+"_20* SPE/").c_str()); 

		
		system(("echo 'The list of SPE files in the sample folder now is:\n' && sleep 4.3 && cd "+s_dir+" && ls SPE/ && echo '\nDo you want to exclude a file from the analysis? (Type y or n)\n '").c_str());
		char exc; cin>>exc;

		while (exc!='y' && exc!='Y' && exc!='n' && exc!='N')  {cout<<"Invalid option. Type it again"<<endl; cin>>exc;}
		if (exc=='y' || exc=='Y')
		{
			cout<<"Type the complete name of the files you want to exclude separated by enter and then type 'stop' when done\n"; 
			system (("cd "+s_dir+"/SPE && mkdir excluded").c_str());
			string s_excl; 
			while (cin>>s_excl) {if (s_excl=="stop") break; system(("cd "+s_dir+"/SPE && mv "+s_excl+" excluded/").c_str());}
		}
	}	

	if (r_ana!='F') // If F, skip this part
	{
		// now we indeed start with the analysis codes (part E)
		string ana_sourcecode=ana_dir+"/gatorcode/source";
		// First, we choose the calibration and background folders
 		system (("echo 'Chose one one of the calibration folders below to be used for this analysis/simulation: ' && sleep 3.0 && ls -ltr "+calib_dir+" && echo '\nType the name of the calibration folder here\n'").c_str());
		 string calfolder; cin>>calfolder; 
		 while (!itExists((calib_dir+calfolder).c_str())) { cout<<" Wrong directory: "+calib_dir+calfolder+" does not exist, type it again. \n"; cin>>calfolder; } 
 calib_dir=calib_dir+calfolder; cout<<" using calibration folder: "<<calib_dir<<endl;
		
 		system (("echo 'Choose one of the background folders below to be used in the analysis:' && sleep 3.0 && ls -ltr "+background_dir+"/ && echo '\nType the name of the background folder here\n'").c_str());
		string bkfolder; cin>>bkfolder; 
		while (!itExists((background_dir+"/"+bkfolder).c_str())) { cout<<" Wrong directory, type it again. \n"; cin>>bkfolder; } 
		string backgroundSPEdir = background_dir+"/"+bkfolder;

		cout<<" \nType the quantity (in units or kg) of the material to be analysed\n";
		string s_quantity; cin>>s_quantity;
		
		string ana_scriptcode=ana_dir+"/gatorcode/scripts"; //here you find the BuildFastSpectrum.cpp code
		// Then, we plot the spectrum using BuildFastSpectrum.cpp
		string run_buildfastspectrum="root -l 'BuildFastSpectrum.cpp(\""+s_dir+"/\", \""+backgroundSPEdir+"/\",\""+calib_dir+"/\",\""+samplename+"\")'"; cout<<run_buildfastspectrum<<endl;
		system(("source "+bashrcfile+" && cd "+ana_scriptcode+" && "+run_buildfastspectrum).c_str());

		//Then we re-compile and run the analysis code 
		system(("bash --rcfile "+bashrcfile+" -ci 'cd "+ana_sourcecode+" && make clean && make && ./sampleanalysis "+s_dir+" "+backgroundSPEdir+" "+calib_dir+" "+s_quantity+"'").c_str());

		ofstream ana_log(analysislogfile.c_str());
		ana_log<<"\nBackground folder: "<<backgroundSPEdir<<endl;
		ana_log<<"Calibration folder: "<<calib_dir<<endl;
		ana_log<<"Amount of material (kg or pieces): "<<s_quantity<<endl;	
		ana_log<<"\n === List of SPE files used for the analysis ==="<<endl;
		ana_log.close();
		system(("cd "+s_dir+"/SPE && ls -p | grep -v / >> "+s_dir+"/analysis_input.log").c_str());
		ana_log.open((s_dir+"/analysis_input.log").c_str(), ofstream::app);
		ana_log<<"\n === List of SPE files excluded from the analysis === "<<endl;
		ana_log.close();
		system(("ls "+s_dir+"/SPE/excluded >> "+s_dir+"/analysis_input.log").c_str());
	}

	printsummary(s_dir, samplename, GATORDIR_summary);
	
	return 0;
}

void printsummary(string s_dir, string samplename, string GATORDIR_summary)
{


	string tmptxt="tmp.txt";
	ofstream pdf_file(tmptxt.c_str());
	pdf_file<<" Sample directory: "<<s_dir<<endl;
	pdf_file<<"\n ========= Simulation input ========= \n (See geometry below)"<<endl;
	pdf_file.close();
	system(("cat "+s_dir+"/sim_input.py >> "+tmptxt).c_str());

	pdf_file.open(tmptxt.c_str(), ofstream::app);
	pdf_file<<"\n ========= Line efficiency ========= "<<endl;
	pdf_file<<"See values in Table 1.\n"<<endl;

	pdf_file<<"\n ========= Livetime and inputs for the analysis ========= \n"<<endl;
	pdf_file.close();
	system(("tail -2 "+s_dir+"/SampleAnalysis.log >> "+tmptxt).c_str());
	system(("cat "+s_dir+"/analysis_input.log >> "+tmptxt).c_str());

	pdf_file.open(tmptxt.c_str(), ofstream::app);
	pdf_file<<"\n ========= Geometry of the sample ========="<<endl; //to do: put figure here
	pdf_file<<"See figure of the geometry below.\n The .wrl file is also saved in the sample directory. And the dimensions/material and position are specified in the code below.\n\n"<<endl;
	pdf_file<<"----------------------- icc file code ---------------- \n"<<endl;
	pdf_file.close();
	system(("cat "+s_dir+"/tmp_copy_of_the_iccfile >> "+tmptxt).c_str());


	system(("libreoffice --convert-to \"pdf\" "+tmptxt).c_str()); 
	system(("cat "+s_dir+"/output_sampleanalysis_eff.txt "+s_dir+"/output_sampleanalysis.txt > tmp2.txt; pandoc tmp2.txt -o tmp2.pdf").c_str());
	system(("pdfunite tmp.pdf "+s_dir+"/g4_00.pdf tmp2.pdf "+s_dir+"/spectrum.pdf "+s_dir+"/output_sampleanalysis_activity.pdf "+s_dir+"/simulation_analysis_summary.pdf").c_str());
        system(("cp "+s_dir+"/simulation_analysis_summary.pdf "+GATORDIR_summary+"/"+samplename+"_simulation_analysis_summary.pdf").c_str());
	system("rm tmp*.txt; rm tmp*.pdf;");

}
