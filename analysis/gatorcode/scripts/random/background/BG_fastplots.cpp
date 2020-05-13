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
	gROOT -> ProcessLine(".L /Users/francesco/PhD/Gator/data_analysis/background/archive/GeMPI/loadgempi.cxx");
	gROOT -> ProcessLine(".L /Users/francesco/PhD/Gator/data_analysis/background/archive/GeMPI/get_gempi_ENR.cxx");
		
	
	const Double_t hour = 3600; //Seconds in an hour
	const Double_t day = 24*hour; //Seconds in a day
	const Double_t Mass = 2.2; //Mass of the sensitive Gator cristal in kg
	
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
	
	
	TH1F* histoENR = convert_histo_ENR(histoADC,"/Users/francesco/PhD/Gator/data_analysis/calibrations/archive/19-06-2012/");
	histoENR -> SetTitle("");
	
	
	TH1F* histoENR_old = conv_old_histo_ENR(histoADC_old);
	histoENR_old -> SetTitle("");
	
	TH1F* histoENR_vis = histoENR -> Clone("histoENR_vis");//Good to be drawn
	
	TH1F* histoENR_old_vis = histoENR_old -> Clone("histoENR_old_vis");//Good to be drawn
	
	
	histoENR_vis -> SetLineColor(kRed);
	histoENR_vis -> SetLineWidth(1);
	histoENR_vis -> Scale(1/tDay);
	histoENR_vis -> Rebin(16);
	histoENR_vis -> Scale(1./Mass,"width");
	histoENR_vis -> GetXaxis() -> SetTitle("Energy [keV]");
	histoENR_vis -> GetYaxis() -> SetTitle("Counts kg^{-1} keV^{-1} day^{-1}");
	
	
	histoENR_old_vis -> SetLineColor(kBlue);
	histoENR_old_vis -> SetLineWidth(1);
	histoENR_old_vis -> Scale(1./Mass/tDay_old);
	histoENR_old_vis -> Rebin(12);
	histoENR_old_vis -> Scale(1.,"width");
	
	
	TH1F* histoENR_GeMPI = get_gempi_ENR(); //Here the units are counts/days
	histoENR_GeMPI -> SetLineColor(kGreen);
	histoENR_GeMPI -> SetLineWidth(1);
	histoENR_GeMPI -> Rebin(4);
	histoENR_GeMPI -> Scale(1/Mass,"width");
	
	
	TCanvas* c1 = new TCanvas("c1","Backgrounds comparison");
	c1 -> cd() -> SetLogy();
	
	histoENR_vis -> Draw();
	histoENR_old_vis -> Draw("SAME");
	histoENR_GeMPI -> Draw("SAME");
	
	
	TLegend* leg = new TLegend(0.60,0.90,0.90,0.80);
	leg -> AddEntry(histoENR_vis,"Gator BG Feb 2012 (47.75 days)","L");
	leg -> AddEntry(histoENR_old_vis,"Gator BG Jun 2011 (46.43 days)","L");
	leg -> AddEntry(histoENR_GeMPI,"Gempi BG (100.5 days)","L");
	leg->Draw();
}
