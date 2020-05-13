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
	
	TH1F* histoENR_vis = histoENR -> Clone("histoENR_vis");//Good to be drawn
	
	TH1F* histoENR_old_vis = histoENR_old -> Clone("histoENR_old_vis");//Good to be drawn
	
	
	histoENR_vis -> SetLineColor(2);
	histoENR_vis -> SetLineWidth(1);
	histoENR_vis -> Scale(1/tDay);
	histoENR_vis -> Rebin(5);
	histoENR_vis -> Scale(1/Mass,"width");
	histoENR_vis -> GetXaxis() -> SetTitle("Energy [keV]");
	histoENR_vis -> GetYaxis() -> SetTitle("Counts kg^{-1} keV^{-1} day^{-1}");
	
	
	histoENR_old_vis -> SetLineColor(4);
	histoENR_old_vis -> SetLineWidth(1);
	histoENR_old_vis -> Scale(1/tDay_old);
	histoENR_old_vis -> Rebin(5);
	histoENR_old_vis -> Scale(1/Mass,"width");
	
	
	histoENR -> SetLineColor(2);
	histoENR -> SetLineWidth(1);
	histoENR -> GetXaxis() -> SetTitle("Energy [keV]");
	histoENR -> GetYaxis() -> SetTitle("Counts kg^{-1} keV^{-1} day^{-1}");
	histoENR -> Scale(1/tDay,"width");
	
	
	histoENR_old -> SetLineColor(4);
	histoENR_old -> SetLineWidth(1);
	histoENR_old -> Scale(1/tDay_old,"width");
	
	
	TCanvas* c1 = new TCanvas("c1","Backgrounds comparison");
	c1 -> cd() -> SetLogy();
	
	histoENR_vis -> Draw();
	histoENR_old_vis -> Draw("SAME");
	
	
	TLegend* leg = new TLegend(0.60,0.90,0.90,0.80);
	leg -> AddEntry(histoENR_vis,"BG Feb 2012 (47.75 days)","L");
	leg -> AddEntry(histoENR_old_vis,"BG Jun 2011 (46.43 days)","L");
	leg->Draw();
	

//Loading the lines for which calculate the difference of counts and compton. The lines are stored in the file "comparelines"
	vector<Double_t>* vlitENR = new vector<Double_t>;
	
	ifstream linesfile("comparelines");
	
	Double_t tempd;
	while(linesfile.good()){
		if(linesfile.eof()) break;
		
		linesfile >> tempd;
		vlitENR -> push_back(tempd);
		
		if(linesfile.eof()) break;
	}
	
	
	TCanvas* c2 = new TCanvas("c2","Background not rebinned");
	histoENR -> Draw();
	histoENR_old -> Draw("SAME");
	
	
	TLegend* leg2 = new TLegend(0.60,0.90,0.90,0.80);
	leg2 -> AddEntry(histoENR_vis,"BG Feb 2012 (47.75 days)","L");
	leg2 -> AddEntry(histoENR_old_vis,"BG Jun 2011 (46.43 days)","L");
	leg2 -> Draw();
	
//Section where I compare the BG of the two spectra through a scan of the ratio of the integral	
	
	TFile* calfile = new TFile("/Users/francesco/PhD/Gator/data_analysis/calibrations/calibration.root","read");
	TF1* calib_fcn_fw = (TF1*)calfile -> Get("calib_fcn_fw");
	TF1* calib_fcn_bw = (TF1*)calfile -> Get("calib_fcn_bw");
	TF1* resol_ADC_func = (TF1*)calfile -> Get("resol_ADC_func");
	calfile -> Close();
	delete calfile;
	
	
	TFile* calfile_old = new TFile("~/PhD/Gator/data_analysis/calibrations/archive/calib_old.root","read");
	TF1* calib_old_fcn_fw = (TF1*)calfile_old -> Get("calib_old_fcn_fw");
	TF1* calib_old_fcn_bw = (TF1*)calfile_old -> Get("calib_old_fcn_bw");
	TF1* resol_old_ADC_func = (TF1*)calfile_old -> Get("resol_ADC_func");
	calfile_old -> Close();
	delete calfile_old;
	
	
	TH1F* histoADC_vis = histoADC -> Clone("histoADC_vis");
	histoADC -> Sumw2();
	//histoADC -> Scale(1/tDay);
	
	
	TH1F* histoADC_old_vis = histoADC_old -> Clone("histoADC_old_vis");
	histoADC_old -> Sumw2();
	//histoADC_old -> Scale(tDay/tDay_old);//Don't rescale now!!!
	
	
	TCanvas* c3 = new TCanvas("c3","BG Ratios");
	c3 -> Divide(1,2);
	
	
	//The following should be loaded from a file
	
	Double_t step = 50; //Energy step for the "ratio plots"
	Int_t nratiopnts = 1 + (2650 - step)/step; //The last edge will be 1650 keV
	
	//Double_t ratio_x[] = {50,100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400,1450,1500,1550,1600,1650,1700,1750,1800,1850,1900,1950,2000};
	
	//Int_t nratiopnts = sizeof(ratio_x)/sizeof(Double_t);
	
	Double_t* ratio_x = new Double_t[nratiopnts];
	Double_t* ratio_x_err = new Double_t[nratiopnts];
	Double_t* ratio_y = new Double_t[nratiopnts];
	Double_t* ratio_y_err = new Double_t[nratiopnts];
	
	for (Int_t i=0; i<nratiopnts; i++) ratio_x[i] = step + i*step;
	
	Double_t ingralstop_new = calib_fcn_bw -> Eval(nratiopnts*step);
	Double_t ingralstop_old = calib_old_fcn_bw -> Eval(nratiopnts*step);
	Double_t ingralstart_new, ingralstart_old; //Start values for the integral calculation (in ADC).
	
	Double_t integr_new, integr_err_new, integr_old, integr_err_old;
	for (Int_t i=0; i<nratiopnts; i++){
		
		ingralstart_new = calib_fcn_bw->Eval(ratio_x[i]);
		ingralstart_old = calib_old_fcn_bw -> Eval(ratio_x[i]);
		
		integr_new = histoADC->Integral(ingralstart_new,ingralstop_new);
		integr_err_new = TMath::Sqrt(integr_new);
		
		integr_old = histoADC_old->Integral(ingralstart_old,ingralstop_old);
		integr_err_old = TMath::Sqrt(integr_old)*(tDay/tDay_old);
		integr_old *= (tDay/tDay_old);
		
		ratio_y[i] = integr_new/integr_old;
		ratio_y_err[i] = ratio_y[i]*TMath::Sqrt(TMath::Power(integr_err_new/integr_new,2) + TMath::Power(integr_err_old/integr_old,2));
		ratio_x_err[i] = 0; //It's a fake!!! Just to fill the errors in the graph.
		//cout << "\n\nEnergy threshold = " << ratio_x[i] << " keV" << endl;
		//cout << "Tot counts new = " << integr_new << endl;
		//cout << "Tot counts old = " << integr_old << endl;
	}
	
	c3 -> cd(1);
	TGraphErrors* ratiocumul_gr = new TGraphErrors(nratiopnts,ratio_x,ratio_y,ratio_x_err,ratio_y_err);
	ratiocumul_gr -> SetTitle("BG - cumulated ratios");
	ratiocumul_gr -> GetXaxis() -> SetTitle("Energy thr [keV]");
	ratiocumul_gr -> GetXaxis() -> SetRangeUser(0,2700);
	ratiocumul_gr -> GetYaxis() -> SetTitle("Ratio (2012/2011)");
	ratiocumul_gr -> SetMarkerStyle(9);
	ratiocumul_gr -> Draw("AP");
	
	
	TLine* rcumulrefline = new TLine(0,1,2700,1);
	rcumulrefline -> SetLineColor(kRed);
	rcumulrefline -> SetLineWidth(1);
	rcumulrefline -> Draw("same");
	
	
	
	//Since the cumulative distribution doesn't give so much info try to compare the 50 keV wide bands of the 2 BGs
	
	Double_t* ratioband_x = new Double_t[nratiopnts-1];
	Double_t* ratiobands_x_err = new Double_t[nratiopnts-1];
	Double_t* ratiobands_y = new Double_t[nratiopnts-1];
	Double_t* ratiobands_y_err = new Double_t[nratiopnts-1];
	
	//I will reuse some of the variables used for the cumulative ratios
	for(Int_t i=0; i<nratiopnts-1; i++){
	
		ingralstart_new = calib_fcn_bw->Eval(ratio_x[i]);
		ingralstop_new = calib_fcn_bw -> Eval(ratio_x[i+1]);
		
		ingralstart_old = calib_old_fcn_bw -> Eval(ratio_x[i]);
		ingralstop_old = calib_old_fcn_bw -> Eval(ratio_x[i+1]);
		
		integr_new = histoADC->Integral(ingralstart_new,ingralstop_new);
		integr_err_new = TMath::Sqrt(integr_new);
		
		integr_old = histoADC_old->Integral(ingralstart_old,ingralstop_old);
		integr_err_old = TMath::Sqrt(integr_old*(tDay/tDay_old));
		
		ratiobands_y[i] = (integr_new/integr_old) - 1;
		ratiobands_y_err[i] = TMath::Abs(ratio_y[i])*TMath::Sqrt(TMath::Power(integr_err_new/integr_new,2) + TMath::Power(integr_err_old/integr_old,2));
		
		ratioband_x[i] = (ratio_x[i+1] + ratio_x[i])/2;
		ratiobands_x_err[i] = (ratio_x[i+1] - ratio_x[i])/2; //It's not en error but the width of the "bin"
		
	}
	
	//TCanvas* c7 = new TCanvas("c7","");
	//c7 -> cd();
	
	c3 -> cd(2);
	TGraphErrors* ratiobands_gr = new TGraphErrors(nratiopnts,ratioband_x,ratiobands_y,ratiobands_x_err,ratiobands_y_err);
	ratiobands_gr -> SetTitle("BG - 50 keV bins ratios");
	ratiobands_gr -> GetXaxis() -> SetTitle("Energy [keV]");
	ratiobands_gr -> GetXaxis() -> SetRangeUser(0,2700);
	ratiobands_gr -> GetYaxis() -> SetTitle("Relative variation (2012/2011)");
	ratiobands_gr -> SetMarkerStyle(20);
	ratiobands_gr -> SetMarkerSize(0.8);
	ratiobands_gr -> Draw("AP");
	
	
	
	TLine* rbandsrefline = new TLine(0,0,2700,0);
	rbandsrefline -> SetLineColor(kRed);
	rbandsrefline -> SetLineWidth(1);
	rbandsrefline -> Draw("same");
	
	
	
	
	
	
	resol_old_ADC_func -> SetName("resol_old_ADC_func");
	
	
	TCanvas* c4 = new TCanvas("c4","Counts analysis in ADC domain (BG2012)");
	c4 -> cd();
	
	//Create the rebinned ADC histograms to see if the energy lines are well linked with the lines in ADC domain
	
	histoADC_vis -> Scale(1/tDay);
	histoADC_vis -> GetXaxis() -> SetTitle("ADC");
	histoADC_vis -> GetYaxis() -> SetTitle("Counts/day");
	histoADC_vis -> SetTitle("");
	//histoADC_vis -> Rebin(8);
	//histoADC_vis -> Scale(1./8);
	histoADC_vis -> Draw();
	
	
	TCanvas* c5 = new TCanvas("c5","Counts analysis in ADC domain (BG2011)");
	c5 -> cd();
	
	histoADC_old_vis -> Scale(1/tDay_old);
	histoADC_old_vis -> GetXaxis() -> SetTitle("ADC");
	histoADC_old_vis -> GetYaxis() -> SetTitle("Counts/day");
	histoADC_old_vis -> SetTitle("");
	//histoADC_old_vis -> Rebin(8);
	//histoADC_old_vis -> Scale(1./8);
	histoADC_old_vis -> Draw();
	
	
	//Here drawing the vertical line to see how accurately the peaks are selected (for both the new and old BG)
	Double_t xpos, xpos_old;
	for(Int_t i=0; i<vlitENR->size(); i++){
		xpos = calib_fcn_bw->Eval(vlitENR->at(i));
		xpos_old = calib_old_fcn_bw->Eval(vlitENR->at(i));
		tlinedraw(c4,xpos);
		tlinedraw(c5,xpos_old);
	}
	
	
	//Vectors used to store info about the counts for each line.
	vector<Double_t>* vpeakcnts = new vector<Double_t>;
	vector<Double_t>* vpeakcnts_err = new vector<Double_t>;
	vector<Double_t>* vlinecnts = new vector<Double_t>;
	vector<Double_t>* vlinecnts_err = new vector<Double_t>;
	vector<Double_t>* vcompcnts = new vector<Double_t>;
	vector<Double_t>* vcompcnts_err = new vector<Double_t>;
	vector<Double_t>* vdetlim = new vector<Double_t>; //Detection limit in counts
	vector<Int_t>* linedetflag = new vector<Int_t>;
	
	vector<Double_t>* vpeakcnts_old = new vector<Double_t>;
	vector<Double_t>* vpeakcnts_old_err = new vector<Double_t>;
	vector<Double_t>* vlinecnts_old = new vector<Double_t>;
	vector<Double_t>* vlinecnts_old_err = new vector<Double_t>;
	vector<Double_t>* vcompcnts_old = new vector<Double_t>;
	vector<Double_t>* vcompcnts_old_err = new vector<Double_t>;
	vector<Double_t>* vdetlim_old = new vector<Double_t>; //Detection limit in counts
	vector<Int_t>* linedetflag_old = new vector<Int_t>;
	
	
	vector<Double_t>* vlineratio = new vector<Double_t>;
	vector<Double_t>* vlineratio_err = new vector<Double_t>;
	vector<Double_t>* vcompratio = new vector<Double_t>;
	vector<Double_t>* vcompratio_err = new vector<Double_t>;
	
	
	histoADC -> GetXaxis() -> UnZoom();
	histoADC_old -> GetXaxis() -> UnZoom();
	
	//Variables used temporarily and needed for linescounts2() routine
	Double_t center,sigma,linecnts, linecnts_err, compcnts, compcnts_err, peakcnt, peakcnts_err, bgcnts, bgcnts_err, det_lim, ratio, ratio_err;
	for (Int_t i=0; i<vlitENR->size(); i++){
		
		center = calib_fcn_bw->Eval(vlitENR->at(i));
		sigma = resol_ADC_func->Eval(center);
		
		cout << "\n\n\nLine energy = " << vlitENR->at(i) << endl;
		
linecounts2(histoADC,c4,center,sigma,linecnts,linecnts_err,compcnts,compcnts_err,peakcnt,peakcnts_err,bgcnts, bgcnts_err,det_lim,0,3.0);
		
		vpeakcnts -> push_back(peakcnt/tDay);
		vpeakcnts_err -> push_back(peakcnts_err/tDay);
		
		vlinecnts -> push_back(linecnts/tDay);
		vlinecnts_err -> push_back(linecnts_err/tDay);
		
		vcompcnts -> push_back(compcnts/tDay);
		vcompcnts_err -> push_back(compcnts_err/tDay);
		
		vdetlim -> push_back(det_lim/tDay);
		
		if(linecnts > det_lim){
			linedetflag -> push_back(1);
		} else {
			linedetflag -> push_back(0);
		}
		
		c4 -> Modified();
		
		//Using the variables defined above and the 'linecounts()' function for the old BG
		center = calib_old_fcn_bw->Eval(vlitENR->at(i));
		sigma = resol_old_ADC_func->Eval(center);
		linecounts2(histoADC_old,c5,center,sigma,linecnts,linecnts_err,compcnts,compcnts_err,peakcnt,peakcnts_err,bgcnts, bgcnts_err,det_lim,0,3.0);
		
		vpeakcnts_old -> push_back(peakcnt/tDay_old);
		vpeakcnts_old_err -> push_back(peakcnts_err/tDay_old);
		
		vlinecnts_old -> push_back(linecnts/tDay_old);
		vlinecnts_old_err -> push_back(linecnts_err/tDay_old);
		
		vcompcnts_old -> push_back(compcnts/tDay_old);
		vcompcnts_old_err -> push_back(compcnts_err/tDay_old);
		
		vdetlim_old -> push_back(det_lim/tDay_old);
		
		if(linecnts > det_lim){
			linedetflag_old -> push_back(1);
		} else {
			linedetflag_old -> push_back(0);
		}
		
		c5 -> Modified();
		
		//Calculating the ratios for Line and Compton counts between new and old data
		ratio = vlinecnts->at(i)/vlinecnts_old->at(i);
		//ratio_err = ratio*TMath::Sqrt((vpeakcnts_err->at(i)/vpeakcnts->at(i))*(vpeakcnts_err->at(i)/vpeakcnts->at(i))+(vpeakcnts_old_err->at(i)/vpeakcnts_old->at(i))*(vpeakcnts_old_err->at(i)/vpeakcnts_old->at(i)));
		
		ratio_err = TMath::Abs(ratio-1)*TMath::Sqrt(TMath::Power(vlinecnts_err->at(i)/vlinecnts->at(i),2) + TMath::Power(vlinecnts_old_err->at(i)/vlinecnts_old->at(i),2)); //Here there is the variation error of line counting and not the error on the ratio (old lines are commented)
		
		vlineratio -> push_back(ratio); //Actually there is the "peak ratio"
		vlineratio_err -> push_back(ratio_err); //Actually there is the "peak variation" error
		
		//Ratio for Compton Counts
		ratio = vcompcnts->at(i)/vcompcnts_old->at(i);
		//ratio_err = ratio*TMath::Sqrt((vcompcnts_err->at(i)/vcompcnts->at(i))*(vcompcnts_err->at(i)/vcompcnts->at(i))+(vcompcnts_old_err->at(i)/vcompcnts_old->at(i))*(vcompcnts_old_err->at(i)/vcompcnts_old->at(i))); 
		
		ratio_err = TMath::Abs(ratio-1)*TMath::Sqrt(TMath::Power(vcompcnts_err->at(i)/vcompcnts->at(i),2)+TMath::Power(vcompcnts_old_err->at(i)/vcompcnts_old->at(i),2)); //Here there is the variation error of compton counting and not the error on the ratio (old lines commented)
		
		vcompratio -> push_back(ratio);
		vcompratio_err -> push_back(ratio_err); //Actually there is the "compton variation" error
		
	}
	
	
	//Here in the vectors there are all the info needed to do a comparison table
	//All this information will be put in an ASCII file and formatted for a table
	ofstream outfile("comp_table.txt");
	
	char valuestr[100]; //Using this to get a formatted output from 'formatdigits' function
	Int_t digits =2;
	
	for (Int_t i=0; i<vlitENR->size(); i++){
		//New BG columns
		outfile << "|  " << vlitENR->at(i) << "  |  ";
		outfile << vpeakcnts->at(i) << " +- ";
		outfile << vpeakcnts_err->at(i) << "  |  ";
		outfile << vcompcnts->at(i) << " +- ";
		outfile << vcompcnts_err->at(i) << "  |  ";
		outfile << vdetlim->at(i) << "  |  ";
		if (linedetflag->at(i)==1){
			outfile << vlinecnts->at(i) << " +- ";
			outfile << vlinecnts_err->at(i) << "  |  ";
		} else {
			if (vlinecnts->at(i) < 0){
				outfile << "< " << vdetlim->at(i) << "  |  ";
			} else {
				outfile << "< " << vdetlim->at(i)+vlinecnts->at(i) << "  |  ";
			}
		}
		//Old BG columns
		outfile << vpeakcnts_old->at(i) << " +- ";
		outfile << vpeakcnts_old_err->at(i) << "  |  ";
		outfile << vcompcnts_old->at(i) << " +- ";
		outfile << vcompcnts_old_err->at(i) << "  |  ";
		outfile << vdetlim_old->at(i) << "  |  ";
		if (linedetflag_old->at(i)==1){
			outfile << vlinecnts_old->at(i) << " +- ";
			outfile << vlinecnts_old_err->at(i) << "  |  ";
		} else {
			if (vlinecnts_old->at(i) < 0){
				outfile << "< " << vdetlim_old->at(i) << "  |  ";
			} else {
				outfile << "< " << vdetlim_old->at(i)+vlinecnts_old->at(i) << "  |  ";
			}
		}
		//Variation Columns
		if ((linedetflag->at(i)==1)&&(linedetflag_old->at(i)==1)){
			//outfile << vlineratio->at(i) << " +- ";
			//outfile << vlineratio_err->at(i) << "  |  ";
			outfile << vlineratio->at(i)-1 << " +- "; //Relative variation
			outfile << vlineratio_err->at(i) << "  |  ";
		} else {
			//outfile << "---" << "  |  "; //This line for the "line ratio"
			outfile << vlineratio->at(i)-1 << " +- "; //Relative variation
			outfile << vlineratio_err->at(i) << "  |  ";
		}
		if (vcompcnts_old->at(i)>0){
			//outfile << vcompratio->at(i) << " +- ";
			//outfile << vcompratio_err->at(i) << "  |" << endl;
			outfile << vcompratio->at(i)-1 << " +- "; //Relative variation
			outfile << vcompratio_err->at(i) << "  |" << endl;
		} else {
			outfile << "---" << "  |" << endl;
		}
	}
	
	outfile.close();
	
	
	TGraphErrors* gr_linecnts_vars = new TGraphErrors();
	gr_linecnts_vars -> SetMarkerStyle(20);
	gr_linecnts_vars -> SetMarkerSize(0.8);
	gr_linecnts_vars -> SetMarkerColor(kBlue);
	gr_linecnts_vars -> SetLineColor(kBlue);
	gr_linecnts_vars -> SetFillStyle(0);
	
	TGraphErrors* gr_compcnts_vars = new TGraphErrors();
	gr_compcnts_vars -> SetMarkerStyle(20);
	gr_compcnts_vars -> SetMarkerSize(0.8);
	gr_compcnts_vars -> SetMarkerColor(kRed);
	gr_compcnts_vars -> SetLineColor(kRed);
	gr_compcnts_vars -> SetFillStyle(0);
	
	Double_t enr, val, err;
	Int_t point = 0;
	for (Int_t i=0; i<vlitENR->size(); i++){
		if (vcompcnts_old->at(i)>0){
			
			//cout << "\ni = " << i << "\t" << "point = " << point << endl;
			enr = vlitENR->at(i);
			val = vlineratio->at(i)-1;
			err = vlineratio_err->at(i);
			//cout << "val = " << val << "\t" << "err = " << err << endl;
			gr_linecnts_vars -> SetPoint(point,enr,val);
			gr_linecnts_vars -> SetPointError(point,0,err);
			
			point++;
		}
		
	}
	
	
	point = 0;
	for (Int_t i=0; i<vlitENR->size(); i++){
		if (vcompcnts_old->at(i)>0){
			enr = vlitENR->at(i);
			val = vcompratio->at(i)-1;
			err = vcompratio_err->at(i);
			gr_compcnts_vars -> SetPoint(point,enr,val);
			gr_compcnts_vars -> SetPointError(point,0,err);
			
			point++;
		}
		
	}
	
	
	
	TCanvas* c6 = new TCanvas("c6","Spectra counts ratios (2012/2011)");
	c6 -> cd();
	
	gr_linecnts_vars -> SetTitle("Counts relative variation");
	gr_linecnts_vars -> GetXaxis() -> SetTitle("Energy [keV]");
	gr_linecnts_vars -> Draw("AP");
	
	
	gr_compcnts_vars -> SetTitle("Counts relative variation");
	gr_compcnts_vars -> GetXaxis() -> SetTitle("Energy [keV]");
	gr_compcnts_vars -> Draw("P");
	
	
	TLegend* leg3 = new TLegend(0.60,0.90,0.90,0.80);
	leg3 -> AddEntry(gr_linecnts_vars,"Line Counts","L");
	leg3 -> AddEntry(gr_compcnts_vars,"Compton Counts","L");
	leg3 -> Draw();
	
	
	TLine* refline = new TLine(gr_linecnts_vars->GetXaxis()->GetXmin(),0,gr_linecnts_vars->GetXaxis()->GetXmax(),0);
	refline -> SetLineColor(kBlack);
	refline -> SetLineWidth(1);
	refline -> Draw("same");
	
	
	
	TCanvas* c7 = new TCanvas("c7","");
	c7 -> cd();
	
	TGraph* correl_gr = new TGraph(gr_compcnts_vars->GetN(),gr_compcnts_vars->GetY(),gr_linecnts_vars->GetY());
	correl_gr -> GetXaxis() -> SetTitle("Compton counts relative variation");
	correl_gr -> GetYaxis() -> SetTitle("Line counts relative variation");
	correl_gr -> SetMarkerStyle(20);
	correl_gr -> SetMarkerSize(0.8);
	correl_gr -> Draw("AP");
	
	
	TCanvas* c8 = new TCanvas("c8","");
	ratiobands_gr -> Draw("AP");
	gr_linecnts_vars -> Draw("P");
	gr_compcnts_vars -> Draw("P");
	leg3 -> Draw();
	refline -> Draw("same");
	
}
