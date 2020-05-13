// Script is for samples, scaled accurately by counts/keV/day
// Uses regular (long 2015-2016) background run

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

void BuildFastSpectrum_Sample(){

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
	
//	string workdir = "/home/atp/galloway/Gator_Screening/Data/Samples/Copper_nT_FS/";
string workdir = "/home/atp/atp/GatorSC/Data/SAMPLE_REPORTS/SPE/KarlsPMTs/";

//string workdir = "/home/atp/galloway/Gator_Screening/Data/Background/Background_201802_4slpm/";
//string workdir = "/home/atp/galloway/Gator_calib/Data/2017/228Th/"

//string workdir = "/home/atp/galloway/Gator_calib/Data/2014/228Th_10102014/";


//	string outfilename = workdir + string("PTFE_nT_refl.root");
//string outfilename = workdir + string("Copper_nT_FS.root");
string outfilename = workdir + string("KarlsPMTs.root");
	
//	string SPEdir = "/home/atp/galloway/Gator_Screening/Data/Samples/PTFE_nT_refl/SPE/";
//  string SPEdir = workdir + "SPE/";
	string SPEdir = workdir;
	
	
//	string calibdir = "/home/atp/galloway/Gator_Screening/Calibrations/bkgrd_Cs_201410/";
	string calibdir = "/home/atp/galloway/Gator_Screening/Calibrations/2015.08.07/";
	
// below is for sample	
//	string backgroundSPEdir = "/home/atp/galloway/Gator_Screening/Data/Background/Background_20131130/SPE/";
//	string calibdir_bg = "/home/atp/galloway/Gator_Screening/Calibrations/bkgrd_all_201407/";
	
	string backgroundSPEdir = "/home/atp/galloway/Gator_Screening/Data/Background/Background_20151002_to_20160107/SPE/";
	string calibdir_bg = "/home/atp/galloway/Gator_Screening/Calibrations/bkgrd_Cs_201410/";

//below includes PMT holders
//	string backgroundSPEdir = "/home/atp/galloway/Gator_Screening/Data/Background_PMTs/PTFE_holders_Feb2017/SPE/";
//	string calibdir_bg = "/home/atp/galloway/Gator_Screening/Calibrations/bkgrd_all_201407/";	
//	string calibdir_bg = "/home/atp/galloway/Gator_Screening/Calibrations/bkgrd_Cs_201410/";
	string calibdir_bg = "/home/atp/galloway/Gator_Screening/Calibrations/2015.08.07/";
	
//	int rebin =8;
	int rebin =8;
	
	double minEn = 0;
	double maxEn = 3000;
	
//	string sampleLeg = "PTFE, July 2017 (35.5 d)";
//	string sampleLeg = "Copper for FS Rings (32.5 d)";
	string sampleLeg = "Karl's PMTs (22 d)";
	string bgLeg = "Background 2015 (107.5 d)";
	
	//////////////////////////////////////////////////////////////////////////////////////////
	
	Double_t aqtime, aqtime_bg;
	
	TH1F* hADC = loadSPE(SPEdir.c_str(), aqtime);
	
	TH1F* hADC_bg = loadSPE(backgroundSPEdir.c_str(), aqtime_bg);
	
	
	
	c1 = new TCanvas("c1","",1200,400);
	c1->SetLogy();
	
	TH1F* histoENR = convert_histo_ENR(hADC, calibdir.c_str());
	histoENR -> SetName("histoENR");
	histoENR -> SetTitle("");
	if(rebin>1) histoENR -> Rebin(rebin);
	// line below scales to counts per day
	histoENR -> Scale(1./(aqtime/(24*3600)),"width");
	//line below scales by time, sample time longer
//	histoENR -> Scale((aqtime_bg/aqtime),"width");
	// belwo is if bkgrd time is longer
//	histoENR -> Scale(1,"width");
//	histoENR -> Scale(1,"width");
	histoENR -> SetLineWidth(1);
	histoENR -> SetLineColor(2);
	histoENR -> GetXaxis() -> SetRangeUser(minEn,maxEn);
	histoENR -> GetXaxis() -> SetTitle("Energy (keV)");
	histoENR -> GetYaxis() -> SetTitle("counts keV^{-1} day^{-1}");
//	histoENR -> GetYaxis() -> SetTitle("counts keV^{-1}");
//	histoENR -> GetYaxis() -> SetTitle("counts keV^{-1} T_{current}^{-1}");
	
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
	
	
	
	
	TH1F* bg_histoENR = convert_histo_ENR(hADC_bg,calibdir_bg.c_str());
	bg_histoENR -> SetName("bg_histoENR");
	bg_histoENR -> SetTitle("");
	if(rebin>1) bg_histoENR -> Rebin(rebin);
	// line below scales to counts per day
	bg_histoENR -> Scale(1./(aqtime_bg/(24*3600)),"width");
	//line below scales by time, sample acquisition time longer
//	bg_histoENR -> Scale(1,"width");
	// below is if bkgrd time is longer
//	bg_histoENR -> Scale((aqtime/aqtime_bg),"width");
	bg_histoENR -> SetLineWidth(1);
	bg_histoENR -> SetLineColor(1);
	bg_histoENR -> GetXaxis() -> SetRangeUser(minEn,maxEn);
	bg_histoENR -> GetXaxis() -> SetTitle("Energy (keV)");
	bg_histoENR -> GetYaxis() -> SetTitle("counts keV^{-1} day^{-1}");
//	bg_histoENR -> GetYaxis() -> SetTitle("counts keV^{-1} T_{current}^{-1}");
	
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
	
	
	
	
	TLegend* leg = new TLegend(0.60,0.90,0.90,0.80);
	leg -> AddEntry(histoENR,sampleLeg.c_str(),"L");
	leg -> AddEntry(bg_histoENR,bgLeg.c_str(),"L");
	leg -> SetFillColor(kWhite);
	leg -> SetBorderSize(0);
	leg -> SetTextFont(62);
	leg -> Draw();
	
	
	//c1->SaveAs(outfilename.c_str());
	
	//return 0;		
}

#include "../source/src/loadSPE.cc"
#include "../source/src/convert_histo_ENR.cc"
