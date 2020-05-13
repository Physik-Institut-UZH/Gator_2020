//========This script should be used as the first part of a wider script for each data taking========//
// For this script is required the header: header_Th_lines.h
//
// To run this script are required the functions contained in the following libraries:
// - myFuncs.cpp
// - myFitFunctions.c

{
	TCanvas* c1 = new TCanvas("Canv1","228Th source Calibration");
	
	gROOT -> ProcessLine(".L myFuncs.cpp");//All the functions used here
	gROOT -> ProcessLine(".L myFitFunctions.c");//for the function "peakFitFunc" and "initFitFunc"


//Creation of an histogram with the ASCII data of the Th228 source. Draw it in the second pad.

	Double_t time = 0; //Acquisition time in seconds of the source
	string filename("228Th-TF656_20120316_FT.txt");
	TH1F* h = histogen(filename,time);

	
	TF1* ff = new TF1("ff",peakFitFunc,(Double_t)h->GetXaxis()->GetFirst(),(Double_t)h->GetXaxis()->GetLast(),8);
	ff->SetParNames("Mean","Ampl","A","Sigma","Beta","S","Slope","Intercept");
	ff->SetLineColor(2);
	


//Vectors where I'll put all the parameters I want from the peaks
	vector<Double_t>* ADCcenters = new vector<Double_t>;
	vector<Double_t>* ADCcenters_err = new vector<Double_t>;
	vector<Double_t>* ADCwidths = new vector<Double_t>;
	vector<Double_t>* ADCwidths_err = new vector<Double_t>;
	vector<Double_t>* ADCresol = new vector<Double_t>;
	//vector<Double_t>* ADCresol_err = new vector<Double_t>;
	vector<Double_t>* ENRresol = new vector<Double_t>;
	//vector<Double_t>* ENRresol_err = new vector<Double_t>;
	
	

	
//The lines to be searched for the calibration are (in ascending energy order):
//===Pb239=== Range (1360,1440)//
//===Tl277=== Range (1610,1670)//
//===Pb300=== Range (1745,1800)//
//===Tl583=== Range (3380,3500)//
//===Bi727=== Range (4200,4340)//
//===Tl763=== Range (4350,4500) ==> NO//
//===Bi785=== Range (4500,4650) ==> NO//
//===Tl861=== Range (5000,5200)//
//===Bi1621=== Range (9340,9480)//
//===Tl2615=== Range (15200,15600)//


//Here follow the array of the litterature e corresponding energy lines (in KeV):

	Double_t ENR_litt[] = {238.632,277.37,300.089,583.187,727.33,860.53,1620.738,2614.511};
	Double_t ENR_litt_err[] = {0.002,0.02,0.012,0.002,0.01,0.02,0.010,0.010};
	
	
	Int_t nlines = sizeof(ENR_litt)/sizeof(Double_t);

	TFitResultPtr resFit;

	h -> GetXaxis() -> SetRangeUser(1360,1490);
	//ff -> SetRange(1360,1490);
	initFitFunc(h,ff);
	resFit = h -> Fit(ff,"BS+");
	ADCcenters -> push_back(ff->GetParameter(0));
	ADCcenters_err -> push_back(ff->GetParError(0));
	ADCwidths -> push_back(ff->GetParameter(3));
	ADCwidths_err -> push_back(ff->GetParError(3));
	ADCresol -> push_back((ff->GetParameter(3))/(ff->GetParameter(0)));
	//ADCresol_err -> push_back(resolError(ff,resFit));
	
	
	 
	 


	h -> GetXaxis() -> SetRangeUser(1610,1670);
	//ff -> SetRange(1610,1670);
	initFitFunc(h,ff);
	resFit = h -> Fit(ff,"BS+");
	ADCcenters -> push_back(ff->GetParameter(0));
	ADCcenters_err -> push_back(ff->GetParError(0));
	ADCwidths -> push_back(ff->GetParameter(3));
	ADCwidths_err -> push_back(ff->GetParError(3));
	ADCresol -> push_back((ff->GetParameter(3))/(ff->GetParameter(0)));
	//ADCresol_err -> push_back(resolError(ff,resFit));


	h -> GetXaxis() -> SetRangeUser(1745,1800);
	//ff -> SetRange(1745,1800);
	initFitFunc(h,ff);
	resFit = h -> Fit(ff,"BS+");
	ADCcenters -> push_back(ff->GetParameter(0));
	ADCcenters_err -> push_back(ff->GetParError(0));
	ADCwidths -> push_back(ff->GetParameter(3));
	ADCwidths_err -> push_back(ff->GetParError(3));
	ADCresol -> push_back((ff->GetParameter(3))/(ff->GetParameter(0)));
	//ADCresol_err -> push_back(resolError(ff,resFit));



//===ee511===//
//Range (2850,3050) --> Use line analisys functions.....
//h2->SetAxisRange(2220,2320);
//ff->SetParameters(2274,5,4500,150,-0.01);
//ff->SetRange(2220,2320);
//h2->Fit(ff,"R+");
//linesADC[ee511]=ff->GetParameter(0);
//linesADCerr[ee511]=ff->GetParError(0);



	h -> GetXaxis() -> SetRangeUser(3380,3500);
	//ff->SetRange(3380,3500);
	initFitFunc(h,ff);
	resFit = h -> Fit(ff,"BS+");
	ADCcenters -> push_back(ff->GetParameter(0));
	ADCcenters_err -> push_back(ff->GetParError(0));
	ADCwidths -> push_back(ff->GetParameter(3));
	ADCwidths_err -> push_back(ff->GetParError(3));
	ADCresol -> push_back((ff->GetParameter(3))/(ff->GetParameter(0)));
	//ADCresol_err -> push_back(resolError(ff,resFit));


	h -> GetXaxis() -> SetRangeUser(4200,4340);
	//ff->SetRange(4200,4340);
	initFitFunc(h,ff);
	resFit = h -> Fit(ff,"BS+");
	ADCcenters -> push_back(ff->GetParameter(0));
	ADCcenters_err -> push_back(ff->GetParError(0));
	ADCwidths -> push_back(ff->GetParameter(3));
	ADCwidths_err -> push_back(ff->GetParError(3));
	ADCresol -> push_back((ff->GetParameter(3))/(ff->GetParameter(0)));
	//ADCresol_err -> push_back(resolError(ff,resFit));


	h -> GetXaxis() -> SetRangeUser(5000,5200);
	//ff->SetRange(5000,5200);
	initFitFunc(h,ff);
	resFit = h -> Fit(ff,"BS+");
	ADCcenters -> push_back(ff->GetParameter(0));
	ADCcenters_err -> push_back(ff->GetParError(0));
	ADCwidths -> push_back(ff->GetParameter(3));
	ADCwidths_err -> push_back(ff->GetParError(3));
	ADCresol -> push_back((ff->GetParameter(3))/(ff->GetParameter(0)));
	//ADCresol_err -> push_back(resolError(ff,resFit));


	h -> GetXaxis() -> SetRangeUser(9300,9500);
	//ff->SetRange(9300,9500);
	initFitFunc(h,ff);
	resFit = h -> Fit(ff,"BS+");
	ADCcenters -> push_back(ff->GetParameter(0));
	ADCcenters_err -> push_back(ff->GetParError(0));
	ADCwidths -> push_back(ff->GetParameter(3));
	ADCwidths_err -> push_back(ff->GetParError(3));
	ADCresol -> push_back((ff->GetParameter(3))/(ff->GetParameter(0)));
	//ADCresol_err -> push_back(resolError(ff,resFit));


	h -> GetXaxis() -> SetRangeUser(15200,15600);
	//ff->SetRange(15200,15600);
	initFitFunc(h,ff);
	resFit = h -> Fit(ff,"BS+");
	ADCcenters -> push_back(ff->GetParameter(0));
	ADCcenters_err -> push_back(ff->GetParError(0));
	ADCwidths -> push_back(ff->GetParameter(3));
	ADCwidths_err -> push_back(ff->GetParError(3));
	ADCresol -> push_back((ff->GetParameter(3))/(ff->GetParameter(0)));
	//ADCresol_err -> push_back(resolError(ff,resFit));
	

	TF1* gausFunc = new TF1("gausFunc",gausFunc,(Double_t)h->GetXaxis()->GetFirst(),(Double_t)h->GetXaxis()->GetLast(),3);
	gausFunc -> SetRange(15200,15600);
	gausFunc -> SetLineColor(3);
	gausFunc -> SetLineWidth(1);
	gausFunc -> SetParameters(ff->GetParameter(0),ff->GetParameter(3),ff->GetParameter(1)*(1-ff->GetParameter(2)));
	gausFunc -> Draw("same");
	
	
	
	TF1* tailFunc = new TF1("tailFunc",tailFunc,(Double_t)h->GetXaxis()->GetFirst(),(Double_t)h->GetXaxis()->GetLast(),4);
	tailFunc -> SetRange(15200,15600);
	tailFunc -> SetLineColor(4);
	tailFunc -> SetLineWidth(1);
	tailFunc -> SetParameters(ff->GetParameter(0),ff->GetParameter(3),ff->GetParameter(4),ff->GetParameter(1)*ff->GetParameter(2));
	tailFunc -> Draw("same");
	
	
	TF1* stepFunc = new TF1("stepFunc",tailFunc,(Double_t)h->GetXaxis()->GetFirst(),(Double_t)h->GetXaxis()->GetLast(),3);
	stepFunc -> SetRange(15200,15600);
	stepFunc -> SetLineColor(6);
	stepFunc -> SetLineWidth(1);
	stepFunc -> SetParameters(ff->GetParameter(0),ff->GetParameter(3),ff->GetParameter(5));
	stepFunc -> Draw("same");
	
	
	TF1* linFunc = new TF1("linFunc","pol1");
	linFunc -> SetRange(15200,15600);
	linFunc -> SetLineColor(7);
	linFunc -> SetLineWidth(1);
	linFunc -> SetParameters(ff->GetParameter(7),ff->GetParameter(6));
	linFunc -> Draw("same");
	
	h -> GetXaxis()->SetTitle("ADC channel");
	h -> GetYaxis()->SetTitle("Entries");
	

	
	
	

// ADC => Energy conversion
	TCanvas* c2 = new TCanvas("c2","ADC -> Energy conversion");
	
	c2 -> cd();

	TGraphErrors* gr_cal_fw = new TGraphErrors(nlines,&(ADCcenters->at(0)),ENR_litt,&(ADCcenters_err->at(0)),ENR_litt_err);
	gr_cal_fw -> Draw("AP");

	TF1* calib_fcn_fw = new TF1("calib_fcn_fw","pol2");
	calib_fcn_fw -> SetLineColor(2);
	calib_fcn_fw -> SetLineWidth(1);
	
	
	gr_cal_fw -> Fit(calib_fcn_fw,"F");
	
	gr_cal_fw -> GetXaxis()->SetTitle("ADC channel");
	gr_cal_fw -> GetYaxis()->SetTitle("Energy [KeV]");
	

//Creating an "inverse calibration" from Energy to ADC (can be usefull).	

	TCanvas* c3 = new TCanvas("c3","Energy -> ADC conversion");
	
	c3 -> cd();
	
	TGraphErrors* gr_cal_bw = new TGraphErrors(nlines,ENR_litt,&(ADCcenters->at(0)),ENR_litt_err,&(ADCcenters_err->at(0)));
	gr_cal_bw -> Draw("AP");
	
	
	TF1* calib_fcn_bw = new TF1("calib_fcn_bw","pol2");
	calib_fcn_bw -> SetLineColor(2);
	calib_fcn_bw -> SetLineWidth(1);
	
	gr_cal_bw -> Fit(calib_fcn_bw,"F");
	
	gr_cal_bw -> GetXaxis()->SetTitle("Energy [KeV]");
	gr_cal_bw -> GetYaxis()->SetTitle("ADC channel");
	
	
	
/*	
// Contruction of the ADC resolution function (errors still missing)
	TCanvas* c3 = new TCanvas("c3","ADC line resolution");
	
	c3 -> cd();
	
	TGraphErrors* gr_resol_ADC = new TGraphErrors(nlines,&(ADCcenters->at(0)),&(ADCresol->at(0)),&(ADCcenters_err->at(0)),&(ADCresol_err->at(0)));
	gr_resol_ADC -> SetMarkerStyle(7);
	gr_resol_ADC -> Draw("AP");
	
	TF1* resol_ADC_fnc = new TF1("resol_ADC_fnc","pol2");
	resol_ADC_fnc -> SetRange(1500,16000);
	resol_ADC_fnc -> SetLineColor(2);
	resol_ADC_fnc -> SetLineWidth(1);
	
	gr_resol_ADC -> Fit(resol_ADC_fnc,"M");
	
	gr_resol_ADC -> GetXaxis()->SetTitle("ADC channel");
	gr_resol_ADC -> GetYaxis()->SetTitle("Resolution");
 */
	


	
	
	

 
//====== Here a new Canvas with the scatter plot of the residuals is generated ======//
//====== Here the errors for the poins are not taken in account and a manual ========//
//====== manual procedure is required ===============================================//

	/*
	TCanvas* canv3 = new TCanvas("Canv3","Calibration residuals",1);
	canv3 -> cd();
	Double_t residuals[NLINES];
	//Double_t* xbins = new Double_t[1+h2 -> GetNbinsX()];
	
	
	for (i=0; i<NLINES; i++){
		residuals[i] = linesThEn[i] - (ff2->Eval(linesADC[i]));		
	}
	

	for(i = 0; i < h2 -> GetNbinsX(); i++){
		xbins[i] = 0;		
	}
	
	
	for(i = 0; i < h2 -> GetNbinsX(); i++){
		xbins[i] = (Double_t)((ff2 -> GetParameter(0)) + i*(ff2 -> GetParameter(1)))-(ff2 -> GetParameter(1))/2;
		
	}
	*/
	
	/*	
	TGraph* gr2 = new TGraph(NLINES,linesADC,residuals);
	gr2 -> Draw("AP");
	TF1* zeroln = new TF1("ZeroLine",linearFit,0,h2->GetNbinsX(),2);
	zeroln -> SetParameters(0,0);
	zeroln -> SetLineColor(2);
	zeroln -> Draw("SAME");

	*/
	
	/*
	TH1F* hcal = new TH1F(h2->GetNbinsX());
	hcal -> SetName("hcal");
	hcal -> SetNameTitle("Calibrated Histogram");
	
	//hcal -> SetBins(h2 -> GetNbinsX(),xbins);
	
		
	cout << "ch" << "\t" << "xbins[i]" << "\t" << "BinCenter" << "\t" << "BinContent\t" << "BinContent (cal)" << endl; 
	for(i = 0; i < h2 -> GetNbinsX(); i++){
		hcal -> SetBinContent(i,h2->GetBinContent(i));
		if (i < 16 || i >  h2 -> GetNbinsX()-16) {
		cout << i << "\t" << xbins[i] << "\t" << hcal->GetBinCenter(i) << "\t" << h2->GetBinContent(i) << "\t" << hcal->GetBinContent(i) << endl;
		}
	}
	

	TCanvas* canv4 = new TCanvas("Canv4","Calibrated histogram");
	canv4 -> cd();
	
//There is a problem in drawing the histogram
	//hcal -> Draw();

*/
	 
}  //end of the script
