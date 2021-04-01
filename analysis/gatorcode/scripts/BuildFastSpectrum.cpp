// Script is for samples, scaled accurately by counts/keV/day

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
#include "TF1.h"
#include "TLegend.h"
//#include <TCut.h>
#include "TAxis.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TMath.h"
#include "TApplication.h"



using namespace std;

TH1F* loadSPE(const char* dir, Double_t& aqtime);
TH1F* convert_histo_ENR(TH1F* hADC, const char* calibdir);
TCanvas* c1;

void BuildFastSpectrum(string workdir, string backgroundSPEdir, string calibdir, string samplename)
{

    //cout<<workdir<<" "<<backgroundSPEdir<<" "<<backgroundSPEdir<<" "<<calibdir<<" "<<samplename<<endl;

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

	string SPEdir=workdir+"SPE/";
	string calibdir_bg = calibdir; // put as the same for now (Gabriela 06.20)

	string outfilename = workdir + string("spectrum.root");
	string spectrumfilename = workdir + string("spectrum.pdf");
	
	//int rebin =8;
	int rebin = 20;
	
	double minEn = 40;
	double maxEn = 2650;

//////////////////////////////////////////////////////////////////////////////////////////
	
	Double_t aqtime, aqtime_bg;
	
	TH1F* hADC = loadSPE(SPEdir.c_str(), aqtime);
	
	TH1F* hADC_bg = loadSPE(backgroundSPEdir.c_str(), aqtime_bg);	

	Double_t aqtime_days=aqtime/(24*3600); stringstream s_aqtime; s_aqtime<<aqtime_days;
	Double_t aqtimebg_days=aqtime_bg/(24*3600); stringstream s_aqtimebg; s_aqtimebg<<aqtimebg_days;
	
	string sampleLeg = samplename+" ("+s_aqtime.str()+"d)";
	string bgLeg = "Background ("+s_aqtimebg.str()+"d)";
	
	c1 = new TCanvas("c1","",1200,400);
	c1->SetLogy();
	
	TH1F* histoENR = convert_histo_ENR(hADC, calibdir.c_str());
	histoENR -> SetName("histoENR");
	histoENR -> SetTitle("");
	if(rebin>1) histoENR -> Rebin(rebin);
	histoENR -> Scale(1./(aqtime/(24*3600)),"width");
	histoENR -> SetLineWidth(1);
	histoENR -> SetLineColor(2);
	histoENR -> GetXaxis() -> SetRangeUser(minEn,maxEn);
	histoENR -> GetXaxis() -> SetTitle("Energy [keV]");
	histoENR -> GetYaxis() -> SetTitle("counts keV^{-1} day^{-1}");
        histoENR -> GetXaxis() -> CenterTitle();
        histoENR -> GetYaxis() -> CenterTitle();

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
	bg_histoENR -> Scale(1./(aqtime_bg/(24*3600)),"width");
	bg_histoENR -> SetLineWidth(1);
	bg_histoENR -> SetLineColor(1);
	bg_histoENR -> GetXaxis() -> SetRangeUser(minEn,maxEn);
	bg_histoENR -> GetXaxis() -> SetTitle("Energy [keV]");
	bg_histoENR -> GetYaxis() -> SetTitle("counts keV^{-1} day^{-1}");
        bg_histoENR -> GetXaxis() -> CenterTitle();
	bg_histoENR -> GetYaxis() -> CenterTitle();

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
	
	
	c1->SaveAs(spectrumfilename.c_str());
	system("sleep 6");
	gROOT->ProcessLine(".q");
			
}

#include "../source/src/loadSPE.cc"
#include "../source/src/convert_histo_ENR.cc"/ Scrip// Script is for samples, scaled accurately by counts/keV/day

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
#include "TF1.h"
#include "TLegend.h"
//#include <TCut.h>
#include "TAxis.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TMath.h"
#include "TApplication.h"



using namespace std;

TH1F* loadSPE(const char* dir, Double_t& aqtime);
TH1F* convert_histo_ENR(TH1F* hADC, const char* calibdir);
TCanvas* c1;

void BuildFastSpectrum(string workdir, string backgroundSPEdir, string calibdir, string samplename)
{

    //cout<<workdir<<" "<<backgroundSPEdir<<" "<<backgroundSPEdir<<" "<<calibdir<<" "<<samplename<<endl;

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

	string SPEdir=workdir+"SPE/";
	string calibdir_bg = calibdir; // put as the same for now (Gabriela 06.20)

	string outfilename = workdir + string("spectrum.root");
	string spectrumfilename = workdir + string("spectrum.pdf");
	
	//int rebin =8;
	int rebin = 20;
	
	double minEn = 40;
	double maxEn = 2650;

//////////////////////////////////////////////////////////////////////////////////////////
	
	Double_t aqtime, aqtime_bg;
	
	TH1F* hADC = loadSPE(SPEdir.c_str(), aqtime);
	
	TH1F* hADC_bg = loadSPE(backgroundSPEdir.c_str(), aqtime_bg);	

	Double_t aqtime_days=aqtime/(24*3600); stringstream s_aqtime; s_aqtime<<aqtime_days;
	Double_t aqtimebg_days=aqtime_bg/(24*3600); stringstream s_aqtimebg; s_aqtimebg<<aqtimebg_days;
	
	string sampleLeg = samplename+" ("+s_aqtime.str()+"d)";
	string bgLeg = "Background ("+s_aqtimebg.str()+"d)";
	
	c1 = new TCanvas("c1","",1200,400);
	c1->SetLogy();
	
	TH1F* histoENR = convert_histo_ENR(hADC, calibdir.c_str());
	histoENR -> SetName("histoENR");
	histoENR -> SetTitle("");
	if(rebin>1) histoENR -> Rebin(rebin);
	histoENR -> Scale(1./(aqtime/(24*3600)),"width");
	histoENR -> SetLineWidth(1);
	histoENR -> SetLineColor(2);
	histoENR -> GetXaxis() -> SetRangeUser(minEn,maxEn);
	histoENR -> GetXaxis() -> SetTitle("Energy [keV]");
	histoENR -> GetYaxis() -> SetTitle("counts keV^{-1} day^{-1}");
        histoENR -> GetXaxis() -> CenterTitle();
        histoENR -> GetYaxis() -> CenterTitle();

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
	bg_histoENR -> Scale(1./(aqtime_bg/(24*3600)),"width");
	bg_histoENR -> SetLineWidth(1);
	bg_histoENR -> SetLineColor(1);
	bg_histoENR -> GetXaxis() -> SetRangeUser(minEn,maxEn);
	bg_histoENR -> GetXaxis() -> SetTitle("Energy [keV]");
	bg_histoENR -> GetYaxis() -> SetTitle("counts keV^{-1} day^{-1}");
        bg_histoENR -> GetXaxis() -> CenterTitle();
	bg_histoENR -> GetYaxis() -> CenterTitle();

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
	
	
	c1->SaveAs(spectrumfilename.c_str());
	system("sleep 6");
	gROOT->ProcessLine(".q");
			
}

#include "../source/src/loadSPE.cc"
#include "../source/src/convert_histo_ENR.cc" is for samples, scaled accurately by counts/keV/day

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "TROOT.h"
#include "TSystem.h"
//#include <TStyle.h>
#include "TFile.h"
//#include <TTree.h>
#include "TH1F.h"
#include "TF1.h"
#include "TLegend.h"
//#include <TCut.h>
#include "TAxis.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TMath.h"
#include "TApplication.h"



using namespace std;

TH1F* loadSPE(const char* dir, Double_t& aqtime);
TH1F* convert_histo_ENR(TH1F* hADC, const char* calibdir);
TCanvas* c1;

void BuildFastSpectrum(string workdir, string backgroundSPEdir, string calibdir, string samplename)
{

    //cout<<workdir<<" "<<backgroundSPEdir<<" "<<backgroundSPEdir<<" "<<calibdir<<" "<<samplename<<endl;

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

	string SPEdir=workdir+"SPE/";
	string calibdir_bg = calibdir; // put as the same for now (Gabriela 06.20)

	string outfilename = workdir + string("spectrum.root");
	string spectrumfilename = workdir + string("spectrum.pdf");
	string spectrumfilename2 = workdir + string("spectrum.png");
	
	//int rebin =8; // Note that bin=1 does not mean 1 keV, but rather one hADC bins. Check convert_histo_ENR.cc for details. There you have: Double_t* xbinsENR = new Double_t[hADC->GetNbinsX()+1]; (Gabriela 07.20)
	int rebin = 20;
	
	double minEn = 100;
	double maxEn = 2700;

//////////////////////////////////////////////////////////////////////////////////////////
	
	Double_t aqtime, aqtime_bg;
	
	TH1F* hADC = loadSPE(SPEdir.c_str(), aqtime);
	
	TH1F* hADC_bg = loadSPE(backgroundSPEdir.c_str(), aqtime_bg);	

	Double_t aqtime_days=aqtime/(24*3600); stringstream s_aqtime; s_aqtime<<aqtime_days;
	Double_t aqtimebg_days=aqtime_bg/(24*3600); stringstream s_aqtimebg; s_aqtimebg<<aqtimebg_days;
	
	string sampleLeg = samplename+" ("+s_aqtime.str()+"d)";
	string bgLeg = "Background ("+s_aqtimebg.str()+"d)";
	
	c1 = new TCanvas("c1","",1200,400);
	c1->SetLogy();
	
	TH1F* histoENR = convert_histo_ENR(hADC, calibdir.c_str());
	histoENR -> SetName("histoENR");
	histoENR -> SetTitle("");
	if(rebin>1) histoENR -> Rebin(rebin);
	histoENR -> Scale(1./(aqtime/(24*3600)),"width");
	histoENR -> SetLineWidth(1);
	histoENR -> SetLineColor(2);
	histoENR -> GetXaxis() -> SetRangeUser(minEn,maxEn);
	histoENR -> GetXaxis() -> SetTitle("Energy (keV)");
	histoENR -> GetYaxis() -> SetTitle("Counts keV^{-1} day^{-1}");
        histoENR -> GetXaxis() -> CenterTitle();
       // histoENR -> GetYaxis() -> CenterTitle();

	//MAKEUP
	histoENR->GetXaxis()->SetLabelFont(132); //Times New Roman
	histoENR->GetXaxis()->SetLabelSize(0.045);
	histoENR->GetXaxis()->SetTitleFont(132); //Times New Roman
	histoENR->GetXaxis()->SetTitleSize(0.06);
	histoENR->GetXaxis()->SetTitleOffset(0.7);
	
	histoENR->GetYaxis()->SetLabelFont(132); //Times New Roman
	histoENR->GetYaxis()->SetLabelSize(0.045);
	histoENR->GetYaxis()->SetTitleFont(132); //Times New Roman
	histoENR->GetYaxis()->SetTitleSize(0.06);
	histoENR->GetYaxis()->SetTitleOffset(0.35);
	histoENR ->SetFillStyle(3001);
	histoENR ->SetMaximum(18);
	
	
	
	
	TH1F* bg_histoENR = convert_histo_ENR(hADC_bg,calibdir_bg.c_str());
	bg_histoENR -> SetName("bg_histoENR");
	bg_histoENR -> SetTitle("");
	if(rebin>1) bg_histoENR -> Rebin(rebin);
	bg_histoENR -> Scale(1./(aqtime_bg/(24*3600)),"width");
	bg_histoENR -> SetLineWidth(1);
	bg_histoENR -> SetLineColor(1);
	bg_histoENR -> GetXaxis() -> SetRangeUser(minEn,maxEn);
	bg_histoENR -> GetXaxis() -> SetTitle("Energy (keV)");
	bg_histoENR -> GetYaxis() -> SetTitle("counts keV^{-1} day^{-1}");
        bg_histoENR -> GetXaxis() -> CenterTitle();
	bg_histoENR -> GetYaxis() -> CenterTitle();

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

	TColor *col622 = gROOT->GetColor(622);
	col622->SetAlpha(0.001);
	TColor *col590 = gROOT->GetColor(590);
	col590->SetAlpha(0.001);


	histoENR -> SetFillColor(622);
	histoENR -> SetLineColor(625);
	
	histoENR -> Draw();
	bg_histoENR -> Draw("FHISTsame");
		
	//bg_histoENR -> SetFillColorAlpha(590, 0.0001);
	bg_histoENR -> SetFillColor(590);
	bg_histoENR ->SetFillStyle(3001);
	bg_histoENR -> SetLineColor(871);
	
	histoENR -> Draw("AXISSAME");

	TLegend* leg = new TLegend(0.65,0.8,0.83,0.60);
	leg -> AddEntry(histoENR,sampleLeg.c_str(),"LF");
	leg -> AddEntry(bg_histoENR,bgLeg.c_str(),"LF");
	leg -> SetFillColor(kWhite);
	leg -> SetBorderSize(0);
	leg -> SetTextFont(132);
	leg -> SetTextSize(0.052);
	leg -> Draw();
	
	const Int_t n_lines = 16;

    	Double_t E_lines[n_lines]={295.22, 351.93, 609.31, 1120.29,1238.11,1729.595, 1764.49,2204.21, 338.32,911.196,968.96,238.63,583.187,2614.51, 1460.88, 661.657};
	string  l_text[n_lines]={"Pb-214","Pb-214","Bi-214","Bi-214","Bi-214","Bi-214","Bi-214","Bi-214", "", "Ac-228","Ac-228", "Pb-212","Tl-208","Tl-208", "K-40", "Cs-137"};
	Int_t color_lines[n_lines]={601, 601, 603, 603,603,603,603,603, 805,805,805,619, 800, 800, 632, 434};
	for (int l=0; l<n_lines; l++)
	{
		if (E_lines[l]==338.32) continue; // skiping Ac-228 line that is barely seen
		string stext= l_text[l];
		TLine *l_en=new TLine(E_lines[l],histoENR->GetMinimum(),E_lines[l],0.15*histoENR->GetMaximum());
		TText *t_en=new TText(E_lines[l]-3.,0.16*histoENR->GetMaximum(),stext.c_str());
		l_en->SetLineColor(922);//color_lines[l]);
		l_en->SetLineStyle(2);// l_en->SetLineWidth(2);
		l_en->Draw();
		t_en->SetTextColor(color_lines[l]); 
		t_en->SetTextFont(132);
		t_en->SetTextAngle(90); t_en->SetTextSize(0.045);
		t_en->Draw();
	}

	
	c1->SaveAs(spectrumfilename.c_str());
	c1->SaveAs(spectrumfilename2.c_str());
	system("sleep 6");
	gROOT->ProcessLine(".q");
			
}

#include "../source/src/loadSPE.cc"
#include "../source/src/convert_histo_ENR.cc"
