// below file is just Gator background spectrum, scaled by 2.2 kg detector mass

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "TROOT.h"
#include "TSystem.h"
#include <TStyle.h>
#include "TFile.h"
//#include <TTree.h>
#include "TH1F.h"
//#include <TH2F.h>
//#include <TH1D.h>
//#include <TH2D.h>
#include "TF1.h"
#include "TLegend.h"
//#include <TCut.h>
#include "TAxis.h"
#include "TCanvas.h"
#include "TColor.h"
//#include <TGraph.h>
//#include <TGraphErrors.h>
//#include <TIterator.h>
//#include <TList.h>
//#include <TMultiGraph.h>
#include "TMath.h"
#include "TApplication.h"
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


using namespace std;

TH1F* loadSPE(const char* dir, Double_t& aqtime);
TH1F* convert_histo_ENR(TH1F* hADC, const char* calibdir);
TCanvas* c1;

void GatorBkgrd_perkeVday_ADC(){

	//Style

	gStyle  ->SetOptStat(0);
    gStyle  ->SetOptFit(0);

    //------ define color gradient
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
    //gStyle->SetNumberContours(30);
    //--------------------------------------------------------------------------
	gStyle->SetStatBorderSize(0);
    gStyle->SetTitleBorderSize(0);
    gStyle->SetTitleFillColor(10);
    gStyle->SetStatColor(10);
    gStyle->SetStatFont(42);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetPadTopMargin(0.01);
	gStyle->SetPadBottomMargin(0.11);
	gStyle->SetPadRightMargin(0.01);
	gStyle->SetPadLeftMargin(0.05);
	//Finish of ATP common makeup
	
	
	
//////////////////////////////////////////////////////////////////////////////////////////
// HARD-CODED VARIABLES
	
	string workdir = "/home/atp/galloway/Gator_Screening/Data/Background/Background_20151002_to_20160107/";
	string outfilename = workdir + string("bkgrd_2016_ADC.root");	
	string SPEdir = "/home/atp/galloway/Gator_Screening/Data/Background/BBackground_20151002_to_20160107/SPE/";

//	string calibdir = "/home/atp/galloway/Gator_Screening/Calibrations/bkgrd_all_201407/";


	string backgroundSPEdir = "/home/atp/galloway/Gator_Screening/Data/Background/Background_20151002_to_20160107/SPE/";	
//	string calibdir_bg = "/home/atp/galloway/Gator_Screening/Calibrations/bkgrd_Cs_201410/";


	int rebin =1;
	
	double minEn = 0;
	double maxEn = 4000;
	
	string sampleLeg = "Nov. 2017 (19.5 d)";
	string bgLeg = "2015-2016 (107.5 d)";

//////////////////////////////////////////////////////////////////////////////////////////
	
	
	
	Double_t aqtime, aqtime_bg;
	
	// Gator
//	TH1F* hADC = loadSPE(SPEdir.c_str(), aqtime);
        TH1F* histoENR = loadSPE(SPEdir.c_str(), aqtime);


//below removed for not calibrated spectrum
//	TH1F* hADC_bg = loadSPE(backgroundSPEdir.c_str(), aqtime_bg);
//uncalibrated	
        TH1F* bg_histoENR = loadSPE(backgroundSPEdir.c_str(), aqtime_bg);

	
	c1 = new TCanvas("c1","",1200,400);
	c1->SetLogy();


// calibration removed below
//        TH1F* histoENR = convert_histo_ENR(hADC, calibdir.c_str());	
//	TH1F* histoENR ;// = convert_histo_ENR(hADC, calibdir.c_str());
	histoENR -> SetName("histoENR");
	histoENR -> SetTitle("");
	if(rebin>1) histoENR -> Rebin(rebin);
	histoENR -> Scale(1./(2.2*aqtime/(24*3600)),"width");
	histoENR -> SetLineWidth(1);
	histoENR -> SetLineColor(38);
//	histoENR -> GetXaxis() -> SetRangeUser(minEn,maxEn);
	histoENR -> GetXaxis() -> SetTitle("ADC");
	histoENR -> GetYaxis() -> SetTitle("counts kg^{-1} keV^{-1} day^{-1}");
	cout << "aqtime: " << (aqtime/(24*3600)) << "day" <<endl;
	
	//MAKEUP
	histoENR->GetXaxis()->SetLabelFont(132); //Times New Roman
	histoENR->GetXaxis()->SetLabelSize(0.045);
	histoENR->GetXaxis()->SetTitleFont(132); //Times New Roman
	histoENR->GetXaxis()->SetTitleSize(0.045);
	histoENR->GetXaxis()->SetTitleOffset(1.1);
	
	histoENR->GetYaxis()->SetLabelFont(132); //Times New Roman
	histoENR->GetYaxis()->SetLabelSize(0.045);
	histoENR->GetYaxis()->SetTitleFont(132); //Times New Roman
	histoENR->GetYaxis()->SetTitleSize(0.045);
	histoENR->GetYaxis()->SetTitleOffset(0.55);
	

	
// remove calibration below	
//	TH1F* bg_histoENR = convert_histo_ENR(hADC_bg,calibdir_bg.c_str());

	bg_histoENR -> SetName("bg_histoENR");
	bg_histoENR -> SetTitle("");
	bg_histoENR -> Rebin(rebin);
// below scales with detector mass (2.2 kg)
	bg_histoENR -> Scale(1./(2.2*aqtime_bg/(24*3600)),"width");
// below scales by time only
//        bg_histoENR -> Scale(1./(aqtime_bg/(24*3600)),"width");
	bg_histoENR -> SetLineWidth(1);
	bg_histoENR -> SetLineColor(46);
//	bg_histoENR -> GetXaxis() -> SetRangeUser(minEn,maxEn);
//below for calibrated
//	bg_histoENR -> GetXaxis() -> SetTitle("Energy (keV)");
        bg_histoENR -> GetXaxis() -> SetTitle("ADC");


// below by mass and aq. time
	bg_histoENR -> GetYaxis() -> SetTitle("counts kg^{-1} keV^{-1} day^{-1}");
// below by time only
//        bg_histoENR -> GetYaxis() -> SetTitle("counts keV^{-1} day^{-1}");
	cout << "aqtime_bg: " <<  (aqtime_bg/(24*3600)) << "day"  << endl;
	cout << "integral cross-check: " <<  bg_histoENR ->Integral(500, maxEn) << endl;
	cout << "integral counts times bin width: " <<  bg_histoENR ->Integral(500, maxEn, "width") << endl;
//	cout << "number of bins: " << bg_histoENR -> GetNBinsX() << endl;
//	cout << "bin width: " << bg_histoENR -> GetXaxis() -> GetBinWidth(50) << endl;


	
	//MAKEUP
	bg_histoENR->GetXaxis()->SetLabelFont(132); //Times New Roman
	bg_histoENR->GetXaxis()->SetLabelSize(0.045);
	bg_histoENR->GetXaxis()->SetTitleFont(132); //Times New Roman
	bg_histoENR->GetXaxis()->SetTitleSize(0.045);
	bg_histoENR->GetXaxis()->SetTitleOffset(1.1);
	
	bg_histoENR->GetYaxis()->SetLabelFont(132); //Times New Roman
	bg_histoENR->GetYaxis()->SetLabelSize(0.045);
	bg_histoENR->GetYaxis()->SetTitleFont(132); //Times New Roman
	bg_histoENR->GetYaxis()->SetTitleSize(0.045);
	bg_histoENR->GetYaxis()->SetTitleOffset(0.55);
	
	histoENR -> Draw();
	bg_histoENR -> Draw("same");
//	bg_histoENR -> Draw();
	
	
	
	
	TLegend* leg = new TLegend(0.60,0.90,0.90,0.80);
	leg -> AddEntry(histoENR,sampleLeg.c_str(),"L");
	leg -> AddEntry(bg_histoENR,bgLeg.c_str(),"L");
//	leg->SetHeader("scaled by 2017 aquisition time");
	leg -> SetFillColor(kWhite);
	leg -> SetBorderSize(0);
	leg -> SetTextFont(62);
	leg -> Draw();
	
	
	//c1->SaveAs(outfilename.c_str());
	
	//return 0;		
}

#include "../source/src/loadSPE.cc"
#include "../source/src/convert_histo_ENR.cc"
