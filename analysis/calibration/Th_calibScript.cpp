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

//Function used to plot every peak in the ADC domain.
	TF1* ff = new TF1("ff",peakFitFunc,(Double_t)h->GetXaxis()->GetFirst(),(Double_t)h->GetXaxis()->GetLast(),8);
	ff->SetParNames("Mean","Ampl","A","Sigma","Beta","S","Slope","Intercept");
	ff->SetLineColor(2);
	


//Vectors where I'll put all the parameters I want from the peaks
	vector<Double_t>* ADCcenters = new vector<Double_t>;
	vector<Double_t>* ADCcenters_err = new vector<Double_t>;
	vector<Double_t>* ADCwidths = new vector<Double_t>;
	vector<Double_t>* ADCwidths_err = new vector<Double_t>;
	//vector<Double_t>* ADCresol = new vector<Double_t>;
	//vector<Double_t>* ADCresol_err = new vector<Double_t>;
	//vector<Double_t>* ENRresol = new vector<Double_t>;
	//vector<Double_t>* ENRresol_err = new vector<Double_t>;
	
	

	
//The lines to be searched for the calibration are (in ascending energy order):
//===Pb239=== Range (1360,1490)//
//===Tl277=== Range (1610,1670)//
//===Pb300=== Range (1745,1800)//
//===Tl583=== Range (3380,3500)//
//===Bi727=== Range (4200,4340)//
//===Tl763=== Range (4350,4500) ==> NO//
//===Bi785=== Range (4500,4650) ==> NO//
//===Tl861=== Range (5000,5200)//
//===Bi1621=== Range (9300,9500)//
//===Tl2615=== Range (15200,15600)//


//Here follow the array of the litterature e corresponding energy lines (in KeV):

	Double_t ENR_litt[] = {238.632,277.37,300.089,583.187,727.33,860.53,1620.738,2614.511};
	Double_t ENR_litt_err[] = {0.002,0.02,0.012,0.002,0.01,0.02,0.010,0.010};
	
//ADC lower and upper limits of the ranges of the peaks
	Double_t ADC_low_range[] = {1360,1610,1745,3380,4200,5000,9300,15200};
	Double_t ADC_high_range[] = {1490,1670,1800,3500,4340,5200,9500,15600};
	
	Int_t nlines = sizeof(ENR_litt)/sizeof(Double_t);

//Vectors of the functions summed togeder to build the general fit function of the peaks. This functions take only the parameters needed from the fit function "ff" and are used only to show in the canvas every single component and not to do the fit.
	vector<TF1*> gaus_fnc_vec(nlines);
	vector<TF1*> tail_fnc_vec(nlines);
	vector<TF1*> step_fnc_vec(nlines);
	vector<TF1*> lin_fnc_vec(nlines);

//String used in the for loop to give the name to th TF1 functions to be plotted
	char name_gaus_fnc [100];
	char name_tail_fnc [100];
	char name_step_fnc [100];
	char name_lin_fnc [100];
	
	
	TFitResultPtr resFit; //For the moment not used --> will be used for the residuals plots
	
	for (Int_t i=0;i<nlines;i++) {

		h -> GetXaxis() -> SetRangeUser(ADC_low_range[i],ADC_high_range[i]);
		//ff -> SetRange(ADC_low_range[i],ADC_high_range[i]);
		initFitFunc(h,ff);
		resFit = h -> Fit(ff,"BS+");
		ADCcenters -> push_back(ff->GetParameter(0));
		ADCcenters_err -> push_back(ff->GetParError(0));
		ADCwidths -> push_back(ff->GetParameter(3));
		ADCwidths_err -> push_back(ff->GetParError(3));
		//ADCresol -> push_back((ff->GetParameter(3))/(ff->GetParameter(0)));
		//ADCresol_err -> push_back(resolError(ff,resFit));
		
		sprintf(name_gaus_fnc,"gausFunc%02d",i);
		gaus_fnc_vec[i] = new TF1(name_gaus_fnc,gausFunc,(Double_t)h->GetXaxis()->GetFirst(),(Double_t)h->GetXaxis()->GetLast(),3);
	   //gaus_fnc_vec[i] -> SetRange(ADC_low_range[i],ADC_high_range[i]);
	   gaus_fnc_vec[i] -> SetLineColor(3);
	   gaus_fnc_vec[i] -> SetLineWidth(1);
	   gaus_fnc_vec[i] -> SetParameters(ff->GetParameter(0),ff->GetParameter(3),ff->GetParameter(1)*(1-ff->GetParameter(2)));
		gaus_fnc_vec[i] -> Draw("same");
		
		sprintf(name_tail_fnc,"tailFunc%02d",i);
		tail_fnc_vec[i] = new TF1(name_tail_fnc,tailFunc,(Double_t)h->GetXaxis()->GetFirst(),(Double_t)h->GetXaxis()->GetLast(),4);
		//tail_fnc_vec[i] -> SetRange(ADC_low_range[i],ADC_high_range[i]);
		tail_fnc_vec[i] -> SetLineColor(4);
		tail_fnc_vec[i] -> SetLineWidth(1);
		tail_fnc_vec[i] -> SetParameters(ff->GetParameter(0),ff->GetParameter(3),ff->GetParameter(4),ff->GetParameter(1)*ff->GetParameter(2));
		tail_fnc_vec[i] -> Draw("same");
		
		sprintf(name_step_fnc,"stepFunc%02d",i);
		step_fnc_vec[i] = new TF1(name_step_fnc,tailFunc,(Double_t)h->GetXaxis()->GetFirst(),(Double_t)h->GetXaxis()->GetLast(),3);
		//step_fnc_vec[i] -> SetRange(ADC_low_range[i],ADC_high_range[i]);
		step_fnc_vec[i] -> SetLineColor(6);
		step_fnc_vec[i] -> SetLineWidth(1);
		step_fnc_vec[i] -> SetParameters(ff->GetParameter(0),ff->GetParameter(3),ff->GetParameter(5));
		step_fnc_vec[i] -> Draw("same");
		
		sprintf(name_lin_fnc,"linFunc%02d",i);
		lin_fnc_vec[i] = new TF1(name_lin_fnc,"pol1");
		//lin_fnc_vec[i] -> SetRange(ADC_low_range[i],ADC_high_range[i]);
		lin_fnc_vec[i] -> SetLineColor(7);
		lin_fnc_vec[i] -> SetLineWidth(1);
		lin_fnc_vec[i] -> SetParameters(ff->GetParameter(7),ff->GetParameter(6));
		lin_fnc_vec[i] -> Draw("same");
	}
		

//===ee511===//
//Range (2850,3050) --> Use line analisys functions.....
//h2->SetAxisRange(2220,2320);
//ff->SetParameters(2274,5,4500,150,-0.01);
//ff->SetRange(2220,2320);
//h2->Fit(ff,"R+");
//linesADC[ee511]=ff->GetParameter(0);
//linesADCerr[ee511]=ff->GetParError(0);

	
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
	
	
	
	
//Saving the whole work in a root file
	
	TFile* filesave = new TFile("calibration.root","update");
	
	filesave -> WriteTObject(calib_fcn_fw,"calib_fcn_fw","Overwrite");
	filesave -> WriteTObject(calib_fcn_bw,"calib_fcn_bw","Overwrite");
	
	filesave -> WriteObject(ADCcenters,"ADCcenters","overwrite");
	filesave -> WriteObject(ADCcenters_err,"ADCcenters_err","overwrite");
	filesave -> WriteObject(ADCwidths,"ADCwidths","overwrite");
	filesave -> WriteObject(ADCwidths_err,"ADCwidths_err","overwrite");
	
	filesave -> Close();
	delete filesave;
	
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
	

}  //end of the script
