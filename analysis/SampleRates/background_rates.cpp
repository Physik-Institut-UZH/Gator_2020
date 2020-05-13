#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

#include <TROOT.h>
//#include <TSystem.h>
//#include <TStyle.h>
//#include <TFile.h>
//#include <TTree.h>
#include <TH1F.h>
//#include <TH2F.h>
//#include <TH1D.h>
//#include <TH2D.h>
//#include <TF1.h>
//#include <TLegend.h>
//#include <TCut.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
//#include <TIterator.h>
//#include <TList.h>
//#include <TMultiGraph.h>
#include <TMath.h>
#include <TApplication.h>
//#include <TSQLServer.h>
//#include <TSQLResult.h>
//#include <TSQLRow.h>
//#include <TLatex.h>
//#include <TTimeStamp.h>
//#include <TLine.h>
//#include <TVirtualFitter.h>
//#include <TGaxis.h>
//#include <TMarker.h>
//#include <TFitResult.h>
#include "trigrate.hh"

using namespace std;


int main(int argc, char** argv){
	
	string SPEdir;
	string OutDir;
	string OutFile;
	stringstream StChStr("");
	stringstream EndChStr("");
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
				StChStr << optarg;
				if(false){
					cout << endl << "ERROR:: You should plug in a numeric value for the starting channel" << endl;
					return -1;
				}else{
					StartCh=atof(StChStr.str().c_str());
					flag_setStartCh = true;
				}
				break;
			case 'e':
				EndChStr << optarg;
				if(false){
					cout << endl << "ERROR:: You should plug in a numeric value for the ending channel" << endl;
					return -1;
				}else{
					EndCh=atof(EndChStr.str().c_str());
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
	
	if(!(flag_setSPEDir&&flag_setOutDir&&flag_setStartCh&&flag_setEndCh&&flag_setOutFile)){
		cout << "ERROR!!!" << endl;
		cout << endl << "Usage: " << argv[0] << " -i <SPEdir> -o <outputdir> -s <Start counting chan> -e <End counting chan> -f <outfilename>" << endl;
		cout << "All the options are mandatory!!!" << endl;
		exit(0);
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
	
	if(flag_setStartCh){
		pTrigRate->FindSPE(SPEdir.c_str(), StartCh, EndCh, true);
	}
	
	TGraphErrors* gr_rates = pTrigRate->MakeFullPlot();
	gr_rates->GetYaxis()->SetTitle("Rate [counts/sec]");
	
	TCanvas* c1 = new TCanvas("c1");
	
	gr_rates->Draw("ap*");
	
	
	OutFile = OutFile + string(".C");
	c1->SaveAs((OutDir+OutFile).c_str());
	
		
	return 0;
}