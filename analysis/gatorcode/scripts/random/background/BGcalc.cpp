/*
 *  BGcalc.cpp
 *  
 *
 *  Created by Francesco on 7/3/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

{
	gROOT -> Reset();
	gROOT -> SetStyle("Plain");
	
	/*
    //display styles
    gStyle->SetOptStat(0);
    gStyle->SetTitleFillColor(0);
    gStyle->SetTitleBorderSize(0);
    gStyle->SetStatColor(0);
    gStyle->SetCanvasBorderMode(0);
    TGaxis::SetMaxDigits(3);
	*/
	
	gROOT -> ProcessLine(".L ~/PhD/Gator/data_analysis/convert_histo_ENR.cxx"); //To convert current BG
	//gSystem -> Sleep(1000);
	gROOT -> ProcessLine(".L ~/PhD/Gator/data_analysis/background/archive/conv_old_histo_ENR.cxx"); //To convert old BG
	//gSystem -> Sleep(1000);
	gROOT -> ProcessLine(".L ~/PhD/Gator/data_analysis/histogen.cxx");
	//gSystem -> Sleep(1000);
	gROOT -> ProcessLine(".L ~/PhD/Gator/data_analysis/loadSPE.cxx");
	gROOT -> ProcessLine(".L ~/PhD/Gator/data_analysis/loadSPE3.cxx");
	//gSystem -> Sleep(1000);
	gROOT -> ProcessLine(".L ~/PhD/Gator/data_analysis/background/archive/tlinedraw.cxx");
	//gSystem -> Sleep(1000);
	//gROOT -> ProcessLine(".L /Users/francesco/PhD/Gator/data_analysis/background/linecounts.cxx");
	gROOT -> ProcessLine(".L /Users/francesco/PhD/Gator/data_analysis/linecounts2.cxx");
	gROOT -> ProcessLine(".L /Users/francesco/PhD/Gator/data_analysis/formatdigits.cpp");
	
	
	const Double_t hour = 3600; //Seconds in an hour
	const Double_t day = 24*hour; //Seconds in a day
	const Double_t Mass = 2.2; //Mass of the sensitive cristal in kg
	
	
	Double_t time, time_old;
	
//Loading the histo of current BG and convert it in Counts/(KeV days)
	TH1F* histoADC = loadSPE("/Users/francesco/Phd/Gator/data_analysis/background/",time);
	//gSystem -> Sleep(1000);

	
	//TH1F* histoADC_old = loadSPE("~/PhD/Gator/data_analysis/background/archive/",time_old);
	TH1F* histoADC_old = histogen("/Users/francesco/PhD/Gator/data_analysis/background/archive/BG20110625Data.txt",time_old);
	histoADC_old -> SetName("histoADC_old");

	
	//Acquisition time in days
	Double_t tDay = time/day;
	Double_t tDay_old = time_old/day;
	
	
	TH1F* histoENR = convert_histo_ENR(histoADC);
	histoENR -> SetTitle("");
	
	
	TH1F* histoENR_old = conv_old_histo_ENR(histoADC_old);
	histoENR_old -> SetTitle("");
	
	
	histoENR -> SetLineColor(2);
	histoENR -> SetLineWidth(2);
	histoENR -> GetXaxis() -> SetTitle("Energy [keV]");
	histoENR -> GetYaxis() -> SetTitle("Count rate [Counts kg^{-1} keV^{-1} day^{-1}]");
	histoENR -> Scale(1/(Mass*tDay));
	
	
	histoENR_old -> SetLineColor(4);
	histoENR_old -> SetLineWidth(2);
	histoENR_old -> Scale(1/(Mass*tDay_old));
	
	
	
}
