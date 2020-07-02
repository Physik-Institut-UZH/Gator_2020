#include <fstream>
#include <iostream>
#include <vector>

#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TFile.h>
//#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TLegend.h>
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
#include <TLine.h>
//#include <TVirtualFitter.h>
//#include <TGaxis.h>
//#include <TMarker.h>
#include <TFitResult.h>

#include "GatorStructs.h"
#include "GatorCounter.hh"
#include "GatorDataLoader.hh"
#include "GatorSampleAnalysis.hh"
#include "screenfncs.h"


using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////

void sampleanalysis();
void wait();

TCanvas* c1;

extern TApplication* theApp=NULL;
TApplication *myApp;

int main(){
		
	
	if(!theApp) theApp = new TApplication("theApp",0,0);
    sampleanalysis();
	
	return 0;
}


void wait()
{
	c1 -> Update(); c1 -> WaitPrimitive();
}
//////////////////////////////////////////////////////////////////////////////////////////


void sampleanalysis(){
	
	gStyle->SetOptStat("");
	
	c1= new TCanvas("c1","");
	c1->cd();
	
	
	//The following lines are for closing the application when the canvas c1 is closed.

#ifndef __CINT__
	c1 -> Connect("TCanvas", "Closed()", "TApplication", gApplication,"Terminate()");
#endif

	
//////////////////////////////////////////////////////////////////////////////////////////		
// hard-coded input variables:
	string sample = "Copper_nT_FS";
	
	string datadir = "/disk/bulk_atp/shayne/Gator/Gator_analysis/gatorcode/Data/Samples/Karl_PMTs/SPE"; // This could be BG SPE dir if "BGswitch" is false	
	string workdir = "/disk/bulk_atp/shayne/Gator/Gator_analysis/gatorcode/Data/Samples/Karl_PMTs/"; // output files directory
	
	// For all isotopes except Cs, bkgrd is from before Oct 2014
	string backgroundSPEdir = "/disk/bulk_atp/shayne/Gator/Gator_analysis/gatorcode/Data/Background_PMTs/bkgd/SPE/";
//	string backgroundSPEdir = "/home/atp/galloway/Gator_Screening/Data/Background/Background_20131130/SPE"; // old bkgrd
	
	//calibration data
//	string calibdir = "/home/atp/galloway/Gator_Screening/Calibrations/bkgrd_Cs_201410/"; // detector recalibrated Nov 1, 2014
//	string calibdir_bg = "/home/atp/galloway/Gator_Screening/Calibrations/bkgrd_Cs_201410/"; // calibration file for bkgrd data taken between July 2014 and Oct 2014
//	string calibdir_bg = "/home/atp/galloway/Gator_Screening/Calibrations/bkgrd_all_201407/"; // calibration file for bkgrd data taken between July 2014 and Oct 2014

	string calibdir = "/home/atp/galloway/Gator_Screening/Calibrations/2015.08.07/";
	string calibdir_bg = "/home/atp/galloway/Gator_Screening/Calibrations/2015.08.07/";
	

	// below depends on number of PMTs
//	string configdir = "/home/atp/galloway/Gator_sims/Screening/Copper_nT_FS/effic/"; // location of lines.list generated from sim	
	string configdir = "/disk/bulk_atp/shayne/Gator_sims/Screening/PMT_R12699/for_Karl/effic/";

//	Double_t quantity = 1; //This is the sample weight in kg!!!	
	Double_t quantity = 2; //This is the sample weight in kg!!! Or can even be the number of the pieces (PMTs e.g.)



//////////////////////////////////////////////////////////////////////////////////////////	


	// input files		
	string linesfilename = configdir + string("/lines.list"); //It doesn't matter if the "Eff_rootfile" switch is true. In such a case it is not used at all.
	string calfilename = calibdir + string("calibration.root");
	string calfilename_bg = calibdir_bg + string("calibration.root");
	
	// output files
	string outfilename = workdir + sample + string(".txt");	
	string efftabfilename = workdir + sample + string("_eff.txt");
	string activityplotfilename = workdir + sample + string("_act.png");
	string savefilename = workdir + sample + string(".root");

	
// end hard-coded variables
//////////////////////////////////////////////////////////////////////////////////////////	


	
	GatorSampleAnalysis analyser(workdir);	
	analyser.SetSampleCalib(calibdir);
	analyser.SetBackgroundCalib(calibdir_bg);
	
	if(!analyser.LoadData(datadir)){
		exit(-1);
	}	
	if(!analyser.LoadBackground(backgroundSPEdir)){
		exit(-1);
	}
	if(!analyser.LoadLines(linesfilename)){
		exit(-1);

	}
	
	analyser.DefaultIntervals();	
	analyser.SetSampleQuntity(quantity);
	analyser.SetQuantityUnit("kg");
	

	
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

