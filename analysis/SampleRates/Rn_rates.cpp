//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo//
// Michelle, May 2018
//
// This file picks out the radon lines and plots the trigger rate as function of time.
// note! the lines are currently specified by channel number, so depends on gain settings:
// need to use correct calibration file to get the correct energy ROIs
// the energies of interest are:
// U-238 bot (Ra-226 to Pb-206)		
// line1	Pb-214	295.22
// line2	Pb-214	351.93
// line3	Bi-214	609.31
// line4	Bi-214	1120.29
// line5	Bi-214	1764.49	
//
// for future need to select multiple lines to plot together
// would also be nice (and less prone to error) also to just specify energies 
// and the relevant calibration file
//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo//

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

#include <TROOT.h>
#include <TH1F.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMath.h>
#include <TApplication.h>
#include "trigrate.hh"
#include "loadSPE.cc"
#include "convert_histo_ENR.cc"


using namespace std;


int main(int argc, char** argv){
	
	string SPEdir;
	string OutDir;
	string OutFile;
	stringstream StartEnrStr("");
	stringstream EndEnrStr("");
	Double_t StartCh, EndCh;
	
	//Read the options and set the flags and filenames
	//string sourceName;
	//string outFileName;
	bool flag_setSPEDir = false;
	bool flag_setOutDir = false;
	bool flag_setOutFile = false;
	bool flag_setStartCh = false;
	bool flag_setEndCh = false;
	char c=0;
	while((c=getopt(argc,argv,"i:o:s:e:f:"))!=-1){
		switch(c)
		{
			case 'i':
				SPEdir = optarg;
				flag_setSPEDir = true;
				break;
			case 'o':
				OutDir = optarg;
				flag_setOutDir = true;
				break;
			case 's':
				StartEnrStr << optarg;
				if(!(StartEnrStr>>StartCh)){
					cout << endl << "ERROR:: You should plug in a numeric value for the start channel" << endl;
					return -1;
				}else{
					flag_setStartCh = true;
				}
				break;
			case 'e':
				EndEnrStr << optarg;
				if(!(EndEnrStr>>EndCh)){
					cout << endl << "ERROR:: You should plug in a numeric value for the end channel" << endl;
					return -1;
				}else{
					flag_setEndCh = true;
				}
				break;
			case 'f':
				OutFile = optarg;
				flag_setOutFile = true;
				break;
			default:
				cout << "Unrecognized option: " << c << endl;
				return -1;
		};
	};
	
	if(!flag_setSPEDir){
		cout << "ERROR:: SPE directory was not set." << endl;
		cout << endl << "Usage: sample_rate -i <SPEdir> [-o <outputdir>|-h <ADC start counting>]" << endl << endl;
	}else{
		if(SPEdir.substr(SPEdir.size()-1,1)!=string("/")) SPEdir = SPEdir + string("/");
	}
	
	if(!flag_setOutDir){
		OutDir = SPEdir + string("../");
	}else{
		if(OutDir.substr(OutDir.size()-1,1)!=string("/")) OutDir = OutDir + string("/");
	}
	
	cout << "SPE directory: <" << SPEdir << ">\n\n" << endl;
	
	trigrate* pTrigRate = new trigrate();
	
	if(flag_setStartCh&&flag_setEndCh){
		pTrigRate->FindSPE(SPEdir.c_str(), StartCh, EndCh, true);
	}else{
		pTrigRate->FindSPE(SPEdir.c_str(),true);
	}
	
	TGraphErrors* gr_rates = pTrigRate->MakeFullPlot();
	
	TCanvas* c1 = new TCanvas("c1");
	
	gr_rates->Draw("ap*");
	
	if(flag_setOutFile){
		OutFile = OutFile + string(".root");
		c1->SaveAs((OutDir+OutFile).c_str());
	}else{
		c1->SaveAs((OutDir+string("trigrate_plot.root")).c_str());
	}
	
//	return 0;		
}
