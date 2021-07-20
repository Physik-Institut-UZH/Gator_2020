#include <fstream>
#include <iostream>
#include <vector>

#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMath.h>
#include <TApplication.h>
#include <TLine.h>
#include <TFitResult.h>

#include "GatorStructs.h"
#include "GatorCounter.hh"
#include "GatorDataLoader.hh"
#include "GatorSampleAnalysis.hh"
#include "screenfncs.h"


using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////

void sampleanalysis(string workdir, string backgroundSPEdir, string calibdir, double quantity);
// To run: ./sampleanalysis /disk/bulk_atp/gator/Sample_Sim_and_Analysis_Results/newmaytest /disk/bulk_atp/gator/background/bkg_2019_10 /disk/bulk_atp/gator/Calibrations/2015.08.07 1.06

void wait();

TCanvas* c1;

extern TApplication* theApp=NULL;
TApplication *myApp;

int main(int argc, char *argv[]){


	string workdir=argv[1];
	string backgroundSPEdir=argv[2];
	string calibdir=argv[3];
	string s_quantity=argv[4]; //This is the sample weight in kg!!! Or can even be the number of the pieces (PMTs e.g.)
	double quantity=atof(s_quantity.c_str()); 
	//cout<<workdir<<" "<<backgroundSPEdir<<" "<<calibdir<<" "<<quantity<<endl;
	

	
	if(!theApp) theApp = new TApplication("theApp",0,0);
	sampleanalysis(workdir, backgroundSPEdir, calibdir, quantity);
	
	return 0;
}


void wait()
{
	c1 -> Update(); c1 -> WaitPrimitive();
}
//////////////////////////////////////////////////////////////////////////////////////////


void sampleanalysis(string workdir, string backgroundSPEdir, string calibdir, double quantity)
{

	string spedatadir=workdir+"/SPE";
	string configdir = workdir+"/effic";
	string calibdir_bg = calibdir; // put as the same for now (Gabriela 06.20)

/////////////////////////////////////////
	
	gStyle->SetOptStat("");
	
	c1= new TCanvas("c1","");
	c1->cd();
	
	
	//The following lines are for closing the application when the canvas c1 is closed.

#ifndef __CINT__
	c1 -> Connect("TCanvas", "Closed()", "TApplication", gApplication,"Terminate()");
#endif


	// input files		
	string linesfilename = configdir + string("/lines.list"); //It doesn't matter if the "Eff_rootfile" switch is true. In such a case it is not used at all.
	string calfilename = calibdir + string("/calibration.root");
	string calfilename_bg = calibdir_bg + string("/calibration.root");
	
	// output files
	string outfilename = workdir + string("/output_sampleanalysis.txt");	
	string efftabfilename = workdir + string("/output_sampleanalysis_eff.txt");
	string activityplotfilename = workdir + string("/output_sampleanalysis_activity.pdf");
	string savefilename = workdir + string("/output_sampleanalysis.root"); //ps: this is not used (I do not know why)

	
	


	
	GatorSampleAnalysis analyser(workdir);	
	analyser.SetSampleCalib(calibdir);
	analyser.SetBackgroundCalib(calibdir_bg);
	
	if(!analyser.LoadData(spedatadir)){
		exit(-1);
	}	
	if(!analyser.LoadBackground(backgroundSPEdir)){
		exit(-1);
	}
	if(!analyser.LoadLines(linesfilename)){
		cout<<"ERROR: effic/lines.list file produced by the Effcalc script is empty for some reason - analysis cannot be continued !!! CHECK ISSUE FIRST"<<endl;
		return;//edit gabriela: I added these two lines to stop the script in case lines are not loaded
		exit(-1);

	}
	
	analyser.DefaultIntervals();	
	analyser.SetSampleQuntity(quantity);
	analyser.SetQuantityUnit("(kg or unit)");
	

	
	//Start the analysis here
	
	analyser.WriteEffTable(efftabfilename);
	analyser.WriteOutputTable(outfilename);
	
	
	analyser.DrawActivityPlots(c1);
	c1->SaveAs(activityplotfilename.c_str());
	

	
//	theApp -> Run(kTRUE);
		
	return;
}

// end
//////////////////////////////////////////////////////////////////

