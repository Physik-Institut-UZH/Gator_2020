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

#include "../source/src/loadSPE.cc"
#include "../source/src/convert_histo_ENR.cc"

using namespace std;

TH1F* loadSPE(const char* dir, Double_t& aqtime);
TH1F* convert_histo_ENR(TH1F* hADC, const char* calibdir);
TCanvas* c1;
	
//////////////////////////////////////////////////////////////////////////////////////////
// HARD-CODED VARIABLES
	
	string workdir = "/home/atp/galloway/Gator_Screening/Data/Samples/PTFE_nT_refl/";
	string outfilename = workdir + string("PTFE_nT_refl_activities.root");
	
	string SPEdir = "/home/atp/galloway/Gator_Screening/Data/Samples/PTFE_nT_refl/SPE/";
	
	
	string calibdir = "/home/atp/galloway/Gator_Screening/Calibrations/bkgrd_Cs_201410/";
	
	string backgroundSPEdir = "/home/atp/galloway/Gator_Screening/Data/Background/Background_20151002_to_20160107/SPE/";
	string calibdir_bg = "/home/atp/galloway/Gator_Screening/Calibrations/bkgrd_Cs_201410/";

	cout <<"hard-coded var loaded"<< endl;
//////////////////////////////////////////////////////////////////////////////////////////

void PlotActivityRatios(){


	if(pad) pad->cd();

	gr_ULActiv = new TGraphErrors();
	gr_ULActiv -> SetMarkerStyle(20);
	gr_ULActiv -> SetMarkerColor(kBlue);

    //Style

    gStyle  ->SetOptStat(0);
    gStyle  ->SetOptFit(0);
   
	
	if(pad) pad->cd();
	
	
	gr_DetActiv = new TGraphErrors();
	gr_DetActiv -> SetMarkerStyle(20);
	gr_DetActiv -> SetMarkerColor(kRed);
	gr_DetActiv -> SetLineColor(kRed);
		
	
	int nLines = GetNLines();
	
	int act_counter = 0;
	int lim_counter = 0;

	for(int iLine=0; iLine<nLines; iLine++){
		LineStruct *line = GetLine(iLine);
		cout <<"get lines"<< endl;
		
		if(line->Detected){
			gr_DetActiv -> SetPoint(act_counter,line->Energy,line->Activ);
			gr_DetActiv -> SetPointError(act_counter,0,line->Activ_err);
			act_counter++;
	 	}else{
			if(line->Activ<=0){
				gr_ULActiv -> SetPoint(lim_counter,line->Energy,line->LdActiv);
			lim_counter++;
			}else{
				gr_ULActiv -> SetPoint(lim_counter,line->Energy,line->LdActiv+line->Activ);
				lim_counter++;
			}
		}
		
	}
	
	TH2F* graphsupport;
	
	cout <<"graph support"<< endl;
	
	if(gr_DetActiv->GetN()==0){
		graphsupport = makeGraphSupport(0,0,TMath::MinElement(gr_ULActiv->GetN(),gr_ULActiv->GetY()),TMath::MaxElement(gr_ULActiv->GetN(),gr_ULActiv->GetY()));
	}else if(gr_ULActiv->GetN()==0){
		graphsupport = makeGraphSupport(TMath::MinElement(gr_DetActiv->GetN(),gr_DetActiv->GetY()),TMath::MaxElement(gr_DetActiv->GetN(),gr_DetActiv->GetY()),0,0);
	}else{
		graphsupport = makeGraphSupport( TMath::MinElement(gr_DetActiv->GetN(),gr_DetActiv->GetY()), TMath::MaxElement(gr_DetActiv->GetN(),gr_DetActiv->GetY()), TMath::MinElement(gr_ULActiv->GetN(),gr_ULActiv->GetY()), TMath::MaxElement(gr_ULActiv->GetN(),gr_ULActiv->GetY()) );
	}
	
	graphsupport -> GetXaxis() -> SetTitle( "Energy [keV]" );
	graphsupport -> GetYaxis() -> SetTitle( (string("mBq/")+m_unit).c_str() );
	graphsupport -> Draw();
	
	if(gr_DetActiv->GetN()>0)gr_DetActiv->Draw("P");
	if(gr_ULActiv->GetN()>0)gr_ULActiv->Draw("P");
	
	TLegend* leg2 = new TLegend(0.60,0.90,0.90,0.80);
	leg2 -> AddEntry(gr_DetActiv,"Detected","P");
	leg2 -> AddEntry(gr_ULActiv,"Upper Limits","P");
	leg2 -> Draw();

//}


		cout <<"end part 1"<< endl;
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
	histoENR -> Scale(1./(aqtime/24*3600),"width");
	histoENR -> SetLineWidth(1);
	histoENR -> SetLineColor(kRed);
	histoENR -> GetXaxis() -> SetRangeUser(minEn,maxEn);
	histoENR -> GetXaxis() -> SetTitle("Energy (keV)");
	histoENR -> GetYaxis() -> SetTitle("counts keV^{-1} day^{-1}");
	
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
	bg_histoENR -> Scale(1./(aqtime_bg/24*3600),"width");
	bg_histoENR -> SetLineWidth(1);
	bg_histoENR -> SetLineColor(kBlue);
	bg_histoENR -> GetXaxis() -> SetRangeUser(minEn,maxEn);
	bg_histoENR -> GetXaxis() -> SetTitle("Energy (keV)");
	bg_histoENR -> GetYaxis() -> SetTitle("counts keV^{-1} day^{-1}");
	
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
	
	
	c1->SaveAs(outfilename.c_str());
	
	//return 0;		
}

//#include "../source/src/loadSPE.cc"
//#include "../source/src/convert_histo_ENR.cc"
