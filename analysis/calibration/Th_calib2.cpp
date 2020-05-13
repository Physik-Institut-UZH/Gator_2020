#include <TROOT.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLegend.h>
#include <TCut.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TIterator.h>
#include <TList.h>
#include <TMultiGraph.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <TMath.h>
#include <TApplication.h>
#include <TSQLServer.h>
#include <TSQLResult.h>
#include <TSQLRow.h>
#include <TLatex.h>
#include <TTimeStamp.h>
#include <TLine.h>
#include <TVirtualFitter.h>
#include <TGaxis.h>
#include <TMarker.h>
#include <TFitResult.h>


using namespace std;

void Th_CalibScr();
void wait();

TH1F* loadTxt(string&, Double_t&);
TH1F* loadSpe(const char*, Double_t&);

Double_t peakFitFunc(Double_t* ,Double_t*);
Double_t initAmpl(TH1F*);
Double_t initCost(TH1F*);
Double_t initStep(TH1F*,Double_t,Double_t);

Double_t gausFunc (Double_t*,Double_t*);
Double_t tailFunc (Double_t*,Double_t*);
Double_t stepFunc (Double_t*,Double_t*);
Double_t resolFunc (Double_t*,Double_t*);

TH1F* convert_histo_ENR(TH1F*,const char*);
void ENRfitRoutine(TH1F*,TF1*,vector<Double_t>*,vector<Double_t>*,vector<Double_t>*,vector<Double_t>*,vector<Double_t>*,vector<Double_t>*);
TGraphErrors* plotResiduals(TF1*,vector<Double_t>*,vector<Double_t>*,vector<Double_t>*,vector<Double_t>*,TFitResultPtr&);
void ENRresolFncInit(TF1*,vector<Double_t>*,vector<Double_t>*);


TCanvas* c1;
TCanvas* c2;
TCanvas* c3;
TCanvas* c4;
TCanvas* c5;
TCanvas* c6;


int main()
{
	TApplication theApp("App",0,0);
	Th_CalibScr();
	
	theApp.Run();
	
	return 0;
}


void wait()
{
	c1 -> Update(); c1 -> WaitPrimitive();
}
//////////////////////////////////////////////////////////////////////////////////////////


////////////---------- SCRIPT FUNCTION ------------//////////////
void Th_CalibScr(){

//The following lines are for closing the application when the canvas c1 is closed.
#ifndef __CINT__
	c1 -> Connect("TCanvas", "Closed()", "TApplication", gApplication,
				  "Terminate()");
#endif

//-------------- HARD CODED STUFF: start ---------------\\

	string datadir = "/Users/francesco/PhD/Gator/data_analysis/calibrations/archive/temp/";//dir where input data files are
	
	string workdir = "/Users/francesco/PhD/Gator/data_analysis/calibrations/archive/temp/";//dir for the output

	Bool_t spe_data =  true; //If true the data is in Spe files and will be used loadSpe() routine to get the calibration histogram otherwise the calibration is in a txt file (old method) and the histogram will be loaded with loadTxt() routine.
	
	string txt_name = "228Th_supported_20110816Data.txt"; //This is taken into account only if the spe_data is false.
	txt_name = datadir + txt_name;
	
	
//-------------- HARD CODED STUFF: finish ---------------\\

	string filesavename = workdir;
	filesavename += "calibration.root";
	
	string conffilename = workdir;
	conffilename += "Th_calib.conf";
	
	
	
//Here follow the array of the litterature e corresponding energy lines (in KeV):
	
	//Loading from "Th_calib.conf"
	ifstream linesfile(conffilename.c_str());
	
	//vectors in which I load the parameters of lines for the calibration
	vector<string>* v_massN = new vector<string>;
	vector<string>* v_elemTag = new vector<string>;
	vector<Double_t>* litt_ENR = new vector<Double_t>;
	vector<Double_t>* litt_ENR_err = new vector<Double_t>;
	vector<Double_t>* ADC_low_range = new vector<Double_t>;
	vector<Double_t>* ADC_high_range = new vector<Double_t>;
	
	
	if (linesfile.fail()){
		cout << "Error: can't open <" << conffilename.c_str() << ">.... failure!" << endl;
		exit(1);
	}
	/*
	Char_t massN_str[100], elemTag_str[100], lit_enr_str[100], lit_enr_err_str[100], lowADCrange_str[100], upADCrange_str[100], width_str[100];
	*/
	
	string s_massN(""),s_elemTag(""),s_litenr(""),s_litenrerr(""),s_lowADCrange(""),s_upADCrange(""),s_ADCwidth("");
	Double_t d_lit_enr, d_lit_enr_err, d_lowADCrange, d_upADCrange, d_width;
	//Loading the configuration values for the fitting initialization
	while (linesfile.good()){

		linesfile >> s_massN;
		linesfile >> s_elemTag; 
		linesfile >> s_litenr;
		linesfile >> s_litenrerr;
		linesfile >> s_lowADCrange;
		linesfile >> s_upADCrange;
		//linesfile >> width_str; //Not yet implemented

		if(!linesfile.good()) break;

		d_lit_enr = atof(s_litenr.c_str());
		d_lit_enr_err = atof(s_litenrerr.c_str());
		d_lowADCrange = atof(s_lowADCrange.c_str());
		d_upADCrange = atof(s_upADCrange.c_str());
		//d_width = atof(s_ADCwidth.c_str()); //Not yet implemented
		
		v_massN -> push_back(s_massN);
		v_elemTag -> push_back(s_elemTag);
		litt_ENR -> push_back(d_lit_enr);
		litt_ENR_err -> push_back(d_lit_enr_err);
		ADC_low_range -> push_back(d_lowADCrange);
		ADC_high_range -> push_back(d_upADCrange);
		//v_initwidth  -> push_back(width_tmp); //Not yet implemented

		if(linesfile.eof()) break;
	}
	linesfile.close();
	
	
	c1 = new TCanvas("c1","228Th source Calibration (ADC)");
	c1 -> cd() -> SetLogy();
	
//Creation of an histogram with the ASCII data of the Th228 source. Draw it in the second pad.
	
	Double_t time = 0; //Acquisition time of the source in seconds
	
	TH1F* h = 0;
	
	if(spe_data) h = loadSpe(datadir.c_str(),time);
	else h = loadTxt(txt_name,time);
	
	h -> GetXaxis()->SetTitle("ADC channel");
	h -> GetYaxis()->SetTitle("Counts");
	
	
	
	//The full function used to fit the peaks. The range will changed each time I fit a new peak.
	TF1* ff_ADC = new TF1("ff_ADC",peakFitFunc,h->GetXaxis()->GetBinLowEdge(h->GetXaxis()->GetFirst()),h->GetXaxis()->GetBinUpEdge(h->GetXaxis()->GetLast()),7);
	ff_ADC->SetParNames("Mean","Ampl","A","Sigma","Beta","S","Constant");
	ff_ADC->SetLineColor(2);
	
	
//Vectors where I'll put all the parameters I want from the peaks
	vector<Double_t>* ADCcenters = new vector<Double_t>;
	vector<Double_t>* ADCcenters_err = new vector<Double_t>;
	vector<Double_t>* ADCwidths = new vector<Double_t>;
	vector<Double_t>* ADCwidths_err = new vector<Double_t>;
	//The follwing 4 vectors are used to save from the "litt_ENR" and "litt_ENR_err" vectors only the values relative to the peaks which are not discarded from the fit process.
	vector<Double_t>* litt_vec = new vector<Double_t>;
	vector<Double_t>* litt_err_vec = new vector<Double_t>;
	vector<Double_t>* ADClowRange_vec = new vector<Double_t>;
	vector<Double_t>* ADCupRange_vec = new vector<Double_t>;
	
	Int_t nlines = litt_ENR->size();
	
//Vectors of the functions summed together to build the general fit function of the peaks. This functions take only the parameters needed from the fit function "ff_ADC" and are used only to show in the canvas every single component and not to do the fit.
	vector<TF1*> gaus_fnc_vec(nlines);
	vector<TF1*> tail_fnc_vec(nlines);
	vector<TF1*> step_fnc_vec(nlines);
	//vector<TF1*> lin_fnc_vec(nlines); //Not more plotted
	
//String used in the for loop to give the name to the TF1 functions to be plotted
	char name_gaus_fnc [100];
	char name_tail_fnc [100];
	char name_step_fnc [100];
	//char name_lin_fnc [100]; //Not more plotted

	
	TFitResultPtr resFit; //Useful for the residuals plots
	Int_t fitStatus;


//Temporary variables used for the multistep fit.
	Double_t tmp_P=0,tmp_G=0,tmp_A=0,tmp_sig=0,tmp_beta=0,tmp_S=0,tmp_q=0;
	for (Int_t i=0;i<nlines;i++) {
		//Fit done in 4 steps to avoid to set boundaries to parameters.
		
		//ROI selection
		h -> GetXaxis() -> SetRangeUser(ADC_low_range->at(i),ADC_high_range->at(i));
		ff_ADC -> SetRange(ADC_low_range->at(i),ADC_high_range->at(i));
		c1 -> Modified();
//STEP1: only gaussian -> other functions switched off.
		cout << "\n1st Step" << endl;
		ff_ADC -> FixParameter(2,0.); //Low energy tail off
		ff_ADC -> FixParameter(4,0.); //'beta' parameter off
		ff_ADC -> FixParameter(5,0.); //Step function off
		ff_ADC -> SetParameter(0,h->GetBinCenter(h->GetMaximumBin())); //Gaussian Center initialization
		ff_ADC -> SetParameter(1,initAmpl(h)); //Amplitude
		ff_ADC -> SetParameter(3,5.); //Hardcoded sigma initialization!!! 
		ff_ADC -> SetParameter(6,initCost(h)); //Constant initialization
		h -> Fit(ff_ADC,"LRN"); 
		//Saving the temporary fit parameters
		tmp_P = ff_ADC -> GetParameter(0);
		tmp_G = ff_ADC -> GetParameter(1);
		tmp_sig = ff_ADC -> GetParameter(3);
		tmp_q = ff_ADC -> GetParameter(6);

//STEP2: fit of step functions with fixed gaussian and tail fnc switched off.
		cout << "\n2nd Step" << endl;
		ff_ADC -> FixParameter(2,0.); //Low energy tail off
		ff_ADC -> FixParameter(4,0.); //'beta' parameter off
		ff_ADC -> FixParameter(0,tmp_P); //From step before
		ff_ADC -> FixParameter(1,tmp_G); //From step before
		ff_ADC -> FixParameter(3,tmp_sig); //From step before
		ff_ADC -> SetParLimits(5,0,0); //Unfix this parameter
		ff_ADC -> SetParameter(5,initStep(h,tmp_sig,tmp_P));
		ff_ADC -> SetParameter(6,initCost(h));
		h -> Fit(ff_ADC,"RN");
		//Saving the temporary fit parameters
		tmp_S = ff_ADC -> GetParameter(5);
		tmp_q = ff_ADC -> GetParameter(6);
		
//STEP3: fit of low energy tail with fixed gaussian and step function
		cout << "\n3nd Step" << endl;
		ff_ADC -> FixParameter(0,tmp_P); //From step before
		ff_ADC -> FixParameter(3,tmp_sig); //From step before
		ff_ADC -> FixParameter(5,tmp_S); //From step before
		ff_ADC -> SetParameter(6,tmp_q);
		ff_ADC -> SetParameter(1,tmp_G);
		ff_ADC -> SetParLimits(2,0,1); //Unfix this parameter
		ff_ADC -> SetParameter(2,0.1); //Hardcoded A initialization!!!
		ff_ADC -> SetParLimits(4,0,1000./tmp_sig); //Unfix this parameter
		ff_ADC -> SetParameter(4,1./tmp_sig); //Beta initialization
		h -> Fit(ff_ADC,"RN");
		//Saving the temporary fit parameters
		tmp_A = ff_ADC -> GetParameter(2);
		tmp_beta = ff_ADC -> GetParameter(4);
		
//STEP4: all parameters initialized, start the global fit
		//ff_ADC -> SetRange(ADC_low_range->at(i),ADC_high_range->at(i));
		//initFitFuncADC(h,ff_ADC);
		
		cout << "\n4th Step" << endl;
		//Unfixing all the parameters. Give very large range at the parameters just to avoid negative parameters
		ff_ADC -> SetParLimits(0,0,0); //Unfixing
		ff_ADC -> SetParLimits(1,0,1000*tmp_G);
		ff_ADC -> SetParLimits(2,0,1);
		ff_ADC -> SetParLimits(3,0,100*tmp_sig);
		ff_ADC -> SetParLimits(4,0,1000/tmp_sig);
		ff_ADC -> SetParLimits(5,0,1000);
		ff_ADC -> SetParLimits(6,0,0); //Unfixing
		
		
		ff_ADC -> SetParameter(0,tmp_P);
		ff_ADC -> SetParameter(1,tmp_G);
		ff_ADC -> SetParameter(2,tmp_A);
		ff_ADC -> SetParameter(3,tmp_sig);
		ff_ADC -> SetParameter(4,tmp_beta);
		ff_ADC -> SetParameter(5,tmp_S);
		ff_ADC -> SetParameter(6,tmp_q);
		h -> Fit(ff_ADC,"MLBRN");
		
		for (Int_t k=0;k<7;k++) {
			ff_ADC -> SetParameter(k,ff_ADC->GetParameter(k));
		}
		
		//Fit without parameters limits using the last found.
		cout << "\nFinal Fit Step" << endl;
		resFit = h -> Fit(ff_ADC,"SR+"); //Used resFit to discard bad fitting peaks. Actually it is conceived for the residual plots.
		//ff_ADC -> Draw("same+");
		
		//Saving the values only if the fit converged
		fitStatus = resFit;
		if (fitStatus==0){
			ADCcenters -> push_back(ff_ADC->GetParameter(0));
			ADCcenters_err -> push_back(ff_ADC->GetParError(0));
			ADCwidths -> push_back(ff_ADC->GetParameter(3));
			ADCwidths_err -> push_back(ff_ADC->GetParError(3));
			litt_vec -> push_back(litt_ENR->at(i));
			litt_err_vec -> push_back(litt_ENR_err->at(i));
			ADClowRange_vec -> push_back(ADC_low_range->at(i));
			ADCupRange_vec -> push_back(ADC_high_range->at(i));
		}
		
		
		sprintf(name_gaus_fnc,"gausFunc%02d",i);
		gaus_fnc_vec[i] = new TF1(name_gaus_fnc,gausFunc,(Double_t)h->GetXaxis()->GetFirst(),(Double_t)h->GetXaxis()->GetLast(),4);
		gaus_fnc_vec[i] -> SetRange(ADC_low_range->at(i),ADC_high_range->at(i));
		gaus_fnc_vec[i] -> SetLineColor(3);
		gaus_fnc_vec[i] -> SetLineWidth(2);
		gaus_fnc_vec[i] -> SetParameters(ff_ADC->GetParameter(0),ff_ADC->GetParameter(3),ff_ADC->GetParameter(1)*(1-ff_ADC->GetParameter(2)),ff_ADC->GetParameter(6));
		gaus_fnc_vec[i] -> Draw("same");
		//c1 -> Update();
		
		sprintf(name_tail_fnc,"tailFunc%02d",i);
		tail_fnc_vec[i] = new TF1(name_tail_fnc,tailFunc,(Double_t)h->GetXaxis()->GetFirst(),(Double_t)h->GetXaxis()->GetLast(),5);
		tail_fnc_vec[i] -> SetRange(ADC_low_range->at(i),ADC_high_range->at(i));
		tail_fnc_vec[i] -> SetLineColor(4);
		tail_fnc_vec[i] -> SetLineWidth(2);
		tail_fnc_vec[i] -> SetParameters(ff_ADC->GetParameter(0),ff_ADC->GetParameter(3),ff_ADC->GetParameter(4),ff_ADC->GetParameter(1)*ff_ADC->GetParameter(2),ff_ADC->GetParameter(6));
		tail_fnc_vec[i] -> Draw("same");
		//c1 -> Update();
		
		sprintf(name_step_fnc,"stepFunc%02d",i);
		step_fnc_vec[i] = new TF1(name_step_fnc,tailFunc,(Double_t)h->GetXaxis()->GetFirst(),(Double_t)h->GetXaxis()->GetLast(),4);
		step_fnc_vec[i] -> SetRange(ADC_low_range->at(i),ADC_high_range->at(i));
		step_fnc_vec[i] -> SetLineColor(6);
		step_fnc_vec[i] -> SetLineWidth(2);
		step_fnc_vec[i] -> SetParameters(ff_ADC->GetParameter(0),ff_ADC->GetParameter(3),ff_ADC->GetParameter(5),ff_ADC->GetParameter(6));
		step_fnc_vec[i] -> Draw("same");
		//c1 -> Update();
		
		/*sprintf(name_lin_fnc,"linFunc%02d",i);
		lin_fnc_vec[i] = new TF1(name_lin_fnc,"pol1");
		lin_fnc_vec[i] -> SetRange(ADC_low_range->at(i),ADC_high_range->at(i));
		lin_fnc_vec[i] -> SetLineColor(7);
		lin_fnc_vec[i] -> SetLineWidth(2);
		lin_fnc_vec[i] -> SetParameters(ff_ADC->GetParameter(7),ff_ADC->GetParameter(6));
		lin_fnc_vec[i] -> Draw("same+");
		*/
		
		c1 -> Modified();
		c1 -> Update();
		wait();
	}
	
	for (Int_t i=0;i<nlines;i++) {
		gaus_fnc_vec[i] -> Draw("same+");
		tail_fnc_vec[i] -> Draw("same+");
		step_fnc_vec[i] -> Draw("same+");
		//lin_fnc_vec[i] -> Draw("same+");
	}
	

	h -> GetXaxis() -> UnZoom();
	
	
	c1 -> Modified();
	c1 -> Update();
	
/////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------FINISHED THE ADC FITTING PROCEDURE-------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////////////

	nlines = ADCcenters->size(); //Redefined since some lines are not more used due to fit failures
	
	c2 = new TCanvas("c2","ADC -> Energy conversion");
	c2 -> Divide(1,2);
	c2 -> cd(1);
	
	TGraphErrors* gr_cal_fw = new TGraphErrors(nlines,&(ADCcenters->at(0)),&(litt_vec->at(0)),&(ADCcenters_err->at(0)),&(litt_err_vec->at(0)));
	gr_cal_fw -> SetMarkerStyle(20);
	gr_cal_fw -> SetTitle("ADC --> keV calibration");
	gr_cal_fw -> GetXaxis()->SetTitle("ADC channel");
	gr_cal_fw -> GetXaxis()->SetTitleSize(0.06);
	gr_cal_fw -> GetYaxis()->SetTitle("Energy [KeV]");
	gr_cal_fw -> GetYaxis()->SetTitleSize(0.06);
	gr_cal_fw -> Draw("AP");
	
	TF1* calib_fcn_fw = new TF1("calib_fcn_fw","pol2");
	calib_fcn_fw -> SetLineColor(2);
	calib_fcn_fw -> SetLineWidth(2);
	
	
	resFit = gr_cal_fw -> Fit(calib_fcn_fw,"S");
	
	
	//To implement the residual plot
	c2 -> cd(2);
	
	//Using the function plotResiduals to generate the residual plot
	TGraphErrors* gr_cal_res_fw = plotResiduals(calib_fcn_fw,ADCcenters,ADCcenters_err,litt_vec,litt_err_vec,resFit);
	gr_cal_res_fw -> SetTitle("Residuals");
	gr_cal_res_fw -> GetXaxis() -> SetTitle("ADC");
	gr_cal_res_fw -> GetYaxis() -> SetTitle("Energy [KeV]");
	gr_cal_res_fw -> SetMarkerStyle(20);
	gr_cal_res_fw -> Draw("AP");
	
	TLine* zeroline_fw = new TLine(gr_cal_res_fw->GetXaxis()->GetXmin(),0,gr_cal_res_fw->GetXaxis()->GetXmax(),0);
	zeroline_fw -> SetLineColor(2);
	zeroline_fw -> SetLineWidth(2);
	zeroline_fw -> Draw("same");
	
	
	//Creating an "inverse calibration" from Energy to ADC (can be usefull).	
	c3 = new TCanvas("c3","Energy -> ADC conversion");
	c3 -> Divide(1,2);
	c3 -> cd(1);
	
	TGraphErrors* gr_cal_bw = new TGraphErrors(nlines,&(litt_vec->at(0)),&(ADCcenters->at(0)),&(litt_err_vec->at(0)),&(ADCcenters_err->at(0)));
	gr_cal_bw -> SetTitle("keV --> ADC calibration");
	gr_cal_bw -> GetXaxis()->SetTitle("Energy [KeV]");
	gr_cal_bw -> GetYaxis()->SetTitle("ADC");
	gr_cal_bw -> SetMarkerStyle(20);
	gr_cal_bw -> Draw("AP");
	
	
	TF1* calib_fcn_bw = new TF1("calib_fcn_bw","pol2");
	calib_fcn_bw -> SetLineColor(2);
	calib_fcn_bw -> SetLineWidth(2);
	
	resFit = gr_cal_bw -> Fit(calib_fcn_bw,"S");
	
	
	//To implement the residual plot
	c3 -> cd(2);
	
	//Using the function plotResiduals to generate the residual plot
	TGraphErrors* gr_cal_res_bw = plotResiduals(calib_fcn_bw,litt_vec,litt_err_vec,ADCcenters,ADCcenters_err,resFit);
	gr_cal_res_bw -> SetTitle("Residuals");
	gr_cal_res_bw -> GetXaxis() -> SetTitle("Energy [KeV]");
	gr_cal_res_bw -> GetYaxis() -> SetTitle("ADC");
	gr_cal_res_bw -> SetMarkerStyle(20);
	gr_cal_res_bw -> Draw("AP");
	
	TLine* zeroline_bw = new TLine(gr_cal_res_bw->GetXaxis()->GetXmin(),0,gr_cal_res_bw->GetXaxis()->GetXmax(),0);
	zeroline_bw -> SetLineColor(2);
	zeroline_bw -> SetLineWidth(2);
	zeroline_bw -> Draw("same");


	
//Resolution functions, in ADC and in Energy domains

	c4 = new TCanvas("c4","Resolution plots (ADC)");
	
	//c4 -> Divide(1,2);
	
	//ADC domain....
	c4 -> cd();
	
	TGraphErrors* gr_resol_ADC = new TGraphErrors(nlines,&(ADCcenters->at(0)),&(ADCwidths->at(0)),&(ADCcenters_err->at(0)),&(ADCwidths_err->at(0)));
	gr_resol_ADC -> SetTitle("ADC resolution");
	gr_resol_ADC -> SetMarkerStyle(20);
	gr_resol_ADC -> GetXaxis()->SetTitle("ADC channel");
	gr_resol_ADC -> GetYaxis()->SetTitle("Peak width [ADC]");
	gr_resol_ADC -> Draw("AP");
	
	TF1* resol_ADC_func = new TF1("resol_ADC_func",resolFunc,(Double_t)h->GetXaxis()->GetFirst(),(Double_t)h->GetXaxis()->GetLast(),3);
	resol_ADC_func -> SetParameters(1,1,1);
	resol_ADC_func -> SetLineColor(2);
	resol_ADC_func -> SetLineWidth(2);
	
	gr_resol_ADC -> Fit(resol_ADC_func);
	
	 
	cout << "\n\nGo ahead for saving the whole work!\n\n" << endl;
	wait();
	
	
	//Saving the whole work in a root file
	cout << "Saving in <" << filesavename.c_str() << ">" << endl;
	TFile* filesave = new TFile(filesavename.c_str(),"recreate");
	
	filesave -> WriteTObject(calib_fcn_fw,"calib_fcn_fw","Overwrite");
	filesave -> WriteTObject(calib_fcn_bw,"calib_fcn_bw","Overwrite");
	filesave -> WriteTObject(resol_ADC_func,"resol_ADC_func","Overwrite");
	filesave -> WriteTObject(gr_cal_res_fw,"gr_cal_res_fw","Overwrite");
	filesave -> WriteTObject(gr_cal_res_bw,"gr_cal_res_bw","Overwrite");
	
	
	//With the following vectors I can built again the plots without doing the calibration again
	filesave -> WriteObject(ADCcenters,"ADCcenters","overwrite");
	filesave -> WriteObject(ADCcenters_err,"ADCcenters_err","overwrite");
	filesave -> WriteObject(ADCwidths,"ADCwidths","overwrite");
	filesave -> WriteObject(ADCwidths_err,"ADCwidths_err","overwrite");
	filesave -> WriteObject(litt_vec,"litt_vec","overwrite");
	filesave -> WriteObject(litt_err_vec,"litt_err_vec","overwrite");
	
	filesave -> Close();
	delete filesave;	
	cout << "Data saved!\n\n" << endl;
	
	
	h -> GetXaxis() -> UnZoom(); //Needed to have the full domain range of "h" and to convert it in energy scale.
	
	
	
	
	
//---------------------------------------------------------------------------------------------------------------------\\	
//Working on the energy domain to produce a spectrum and a plot to show. For everything work only in ADC domain energy domain is only for showing.
	
	c5 = new TCanvas("c5","228Th source calibration (KeV)");
	c5 -> cd();
	c5 -> SetLogy();
	
	//Conversion of the histogram in energy domain
	TH1F* h_ENR = convert_histo_ENR(h,workdir.c_str());
	h_ENR -> Draw(); 
	
	
	return;
	
	/*
	TF1* ff_ENR = new TF1("ff_ENR",peakFitFunc,h_ENR->GetBinLowEdge(h_ENR->GetXaxis()->GetFirst()),h_ENR->GetBinLowEdge(h_ENR->GetXaxis()->GetLast())+h_ENR->GetBinWidth(h_ENR->GetXaxis()->GetLast()),7);
	ff_ENR->SetParNames("Mean","Ampl","A","Sigma","Beta","S","Constant");
	ff_ENR -> SetLineColor(2);
	
	
	vector<Double_t>* ENRcenters = new vector<Double_t>;
	vector<Double_t>* ENRcenters_err = new vector<Double_t>;
	vector<Double_t>* ENRwidths = new vector<Double_t>;
	vector<Double_t>* ENRwidths_err = new vector<Double_t>;
	
	
	//Same fitting process as the ADC case, but the whole procedure is in the function "ENRfitRoutine"
	ENRfitRoutine(h_ENR,ff_ENR,ENRcenters,ENRcenters_err,ENRwidths,ENRwidths_err,ADClowRange_vec,ADCupRange_vec);
	
	h_ENR -> GetXaxis() -> UnZoom();
	
	
	c5 -> Modified();
	c5 -> Update();
	
	
	return;
	*/
}
//////////////////////////////////////////////////////////////////
//--------------------------------------------------------------//
//                SCRIPT FUNCTION FINISHED                      //
//--------------------------------------------------------------//
//////////////////////////////////////////////////////////////////



/*
///////////Definitions of the functions for the plot//////////////
Double_t peakFitFunc(Double_t* x,Double_t* par){
	
	Double_t E,P,Gamma,A,sigma,beta,S,C;
	
	E = x[0];
	
	P = par[0];
	Gamma = par[1];
	A = par[2];
	sigma = par[3];
	beta = par[4];
	S = par[5];
	C = par[6];
	
	
	
	return Gamma* //General amlitude of the peak
	((1-A)*TMath::Gaus(E,P,sigma)+//Gaussian peak
	A*TMath::Exp(beta*(E-P))*TMath::Erfc((beta*(E-P))+(beta*sigma/sqrt(2))))+ //Low efficiency collecting charge tail
	S*TMath::Erfc((E-P)/(sqrt(2)*sigma))+ //Step modelled background
	+C; //Constant
	
}

//////////////////////////////////////////////////////////////////////////////////


//----------Initialization functions-----------//
Double_t initAmpl(TH1F* histo){
	
	
	Double_t firstval = histo->GetXaxis()->GetBinLowEdge(histo->GetXaxis()->GetFirst()); 
	Double_t lastval = histo->GetXaxis()->GetBinUpEdge(histo->GetXaxis()->GetLast());
	
	Double_t ROIsize = lastval - firstval;
	
	Double_t low_mean = histo -> Integral(firstval,firstval+0.05*ROIsize)/(0.05*ROIsize);
	
	Double_t up_mean = histo -> Integral(lastval-0.05*ROIsize,lastval)/(0.05*ROIsize);
	
	return histo->GetMaximum() - 0.5*(low_mean+up_mean);
	
}

//////////////////////////////////////////////////////////////////////////////////////


Double_t initCost(TH1F* histo){
	
	Double_t firstval = histo->GetXaxis()->GetBinLowEdge(histo->GetXaxis()->GetFirst()); 
	Double_t lastval = histo->GetXaxis()->GetBinUpEdge(histo->GetXaxis()->GetLast());
	
	Double_t ROIsize = lastval - firstval;
	
	Double_t low_mean = histo -> Integral(firstval,firstval+0.05*ROIsize)/(0.05*ROIsize);
	
	Double_t up_mean = histo -> Integral(lastval-0.05*ROIsize,lastval)/(0.05*ROIsize);
	
	return 0.5*(low_mean+up_mean);
}

//////////////////////////////////////////////////////////////////////////////////////


Double_t initStep(TH1F* histo, Double_t sigma, Double_t Center){
	
	Double_t firstval = histo->GetXaxis()->GetBinLowEdge(histo->GetXaxis()->GetFirst()); 
	Double_t lastval = histo->GetXaxis()->GetBinUpEdge(histo->GetXaxis()->GetLast());
	
	Double_t ROIsize = lastval - firstval;
	
	Double_t low_mean = histo -> Integral(Center-10*sigma,(Center-10*sigma)+(0.05*ROIsize))/(0.05*ROIsize);
	Double_t up_mean = histo -> Integral((Center+10*sigma)-(0.05*ROIsize),Center+10*sigma)/(0.05*ROIsize);
	
	return TMath::Abs(low_mean-up_mean);
}

/////////////////////////////////////////////////////////////////////////////////////


//---------Definition of the single function for the peak fitting------------//
Double_t gausFunc (Double_t* x,Double_t* par){
	
	Double_t E = x[0];
	
	Double_t P = par[0];
	Double_t sigma = par[1];
	Double_t A = par[2];
	Double_t C = par[3];
	
	
	return A*TMath::Gaus(E,P,sigma)+C;
	
}
//////////////////////////////////////////////////////////////////////////////////////

Double_t tailFunc (Double_t* x,Double_t* par){
	
	Double_t E = x[0];
	
	Double_t P = par[0];
	Double_t sigma = par[1];
	Double_t beta = par[2];
	Double_t A = par[3];
	Double_t C = par[4];
	
	return A*TMath::Exp(beta*(E-P))*TMath::Erfc((beta*(E-P))+(beta*sigma/sqrt(2)))+C;
}
//////////////////////////////////////////////////////////////////////////////////////

Double_t stepFunc (Double_t* x,Double_t* par){
	
	Double_t E = x[0];
	
	Double_t P = par[0];
	Double_t sigma = par[1];
	Double_t S = par[2];
	Double_t C = par[3];
	
	return S*TMath::Erfc((E-P)/(sqrt(2)*sigma))+C;
}
//////////////////////////////////////////////////////////////////////////////////////


Double_t resolFunc (Double_t* x,Double_t* par){
	
	Double_t E = x[0];
	
	Double_t A = par[0];
	Double_t B = par[1];
	Double_t C = par[2];
	
	return TMath::Sqrt(A*E*E + B*E + C);
}

//////////////////////////////////////////////////////////////////////////////////


TH1F* convert_histo_ENR2(TH1F* hADC, const char* calibdir){
	//This function gives the energy histogram with a constant binning. It is less accurate than convert_histo_ENR(...) routine but it is useful when I want build up the resolution function in energy domain.
	//cout <<"\nAcquisition time: " << time << " sec" << endl;
	
	TF1* calib_fcn_fw = 0;
	
	Int_t i=0; //General iterator index
	
	string calibfilename = calibdir;
	calibfilename += "calibration.root"; //Hardcoded but this function would be used for stuff referring to this.
	
	TFile* f = new TFile(calibfilename.c_str(),"read");
	
	calib_fcn_fw = (TF1*)f->Get("calib_fcn_fw");
	
	
	if (calib_fcn_fw == 0){
		cout << "Calibration not still done. Run ./Th_calib before!!!" << endl;
		exit(1);
	}
	
	f -> Close();
	
	delete f;
	
	
	//Using this constructor for the new histogram
	TH1F* hENR = new TH1F("hENR","",27500,0,2750); //each bin is 0.1 keV wide
	
	//Filling the new histogram
	Double_t enr_cent, counts;
	for (i=hADC->GetXaxis()->GetFirst(); i<=hADC->GetXaxis()->GetLast(); i++){
		
		enr_cent = calib_fcn_fw->Eval(hADC->GetBinCenter(i));
		counts = hADC->GetBinContent(i);
		hENR -> Fill(enr_cent,counts);
		//hENR -> SetBinError(hENR->FindBin(calib_fcn_fw->Eval(hADC->GetBinCenter(i))),tmp_rate_err);
		
	}
	
	//cout << "VACCA!" << endl;
	
	return hENR; //The histogram which comes out must be rescaled for bin width -> do it outside this function
}
*/
//////////////////////////////////////////////////////////////////////////////////


TGraphErrors* plotResiduals(TF1* fit_pol2,
							vector<Double_t>* x,
							vector<Double_t>* x_err,
							vector<Double_t>* yTh_vec,
							vector<Double_t>* yTh_err_vec,
							TFitResultPtr& resFit){
	
	//vector<Double_t>* y = new vector<Double_t>*;
	//vector<Double_t>* y_err = new vector<Double_t>*;
	
	TGraphErrors* residual_gr = new TGraphErrors(x->size());
	
	Double_t y, y_err, calc_val, calc_val_err;
	
	Double_t a, a_err, b, b_err, c, c_err, cov_ab, cov_ac, cov_bc;
	
	a = fit_pol2->GetParameter(0);
	a_err = fit_pol2->GetParError(0);
	b = fit_pol2->GetParameter(1);
	b_err = fit_pol2->GetParError(1);
	c = fit_pol2->GetParameter(2);
	c_err = fit_pol2->GetParError(2);
	
	cov_ab = resFit -> CovMatrix(0,1);
	cov_ac = resFit -> CovMatrix(0,2);
	cov_bc = resFit -> CovMatrix(1,2);
	
	
	for (Int_t i=0; i<x->size(); i++){
		
		calc_val = fit_pol2 -> Eval(x->at(i));
		
		calc_val_err = TMath::Sqrt(a_err*a_err + b_err*x->at(i)*b_err*x->at(i) + ((c_err*x->at(i)*x->at(i)))*((c_err*x->at(i)*x->at(i))) + ((b+2*c*x->at(i))*x_err->at(i))*((b+2*c*x->at(i))*x_err->at(i)) + 2*(x->at(i))*(cov_ab + cov_ac*x->at(i) + cov_bc*x->at(i)*x->at(i)));
		
		y = calc_val - yTh_vec->at(i);
		
		y_err = TMath::Sqrt((calc_val_err*calc_val_err)+(yTh_err_vec->at(i)*yTh_err_vec->at(i)));
		
		residual_gr -> SetPoint(i,x->at(i),y);
		residual_gr -> SetPointError(i,x_err->at(i),y_err);
		
	}
		
	
	return residual_gr;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////


void ENRfitRoutine(TH1F* h_ENR,
				TF1* ff_ENR,
				vector<Double_t>* ENRcenters,
				vector<Double_t>* ENRcenters_err,
				vector<Double_t>* ENRwidths,
				vector<Double_t>* ENRwidths_err,
				vector<Double_t>* ADClowRange_vec,
				vector<Double_t>* ADCupRange_vec){
	
	//Temporary variables used for the multistep fit.
	Double_t tmp_P=0,tmp_G=0,tmp_A=0,tmp_sig=0,tmp_beta=0,tmp_S=0,tmp_q=0;
	
	//Some of the saved objects are needed for the initialization process
	TFile* f = new TFile("calibration.root","read");
	
	TF1* calib_fcn_fw = (TF1*)f->Get("calib_fcn_fw");
	
	vector<Double_t>* ADCcenters = (vector<Double_t>*)f->Get("ADCcenters");
	
	vector<Double_t>* ADCwidths = (vector<Double_t>*)f->Get("ADCwidths");
	
	f->Close();
	delete f;
	
//When I enter in this routine I lose the trace of the peak index I'm fitting.... using the size of ENRcenters can be retrieved ---> When no peaks are yet fitted, the size of this vector is 0 => load the values of ADCcenters and ADCwidths with the index 0 and so on. 
	Int_t nlines = ADCcenters->size();
	
	TFitResultPtr fitRes;
	Int_t fitStatus;
	
	
	for (Int_t i=0; i<nlines; i++){
	
		Double_t initCenter = calib_fcn_fw->Eval(ADCcenters->at(i));
	
		Double_t initSigma = 0.5*(calib_fcn_fw->Eval(ADCcenters->at(i) + ADCwidths->at(i)) - calib_fcn_fw->Eval(ADCcenters->at(i) - ADCwidths->at(i)));

		
		h_ENR -> GetXaxis() -> SetRangeUser(calib_fcn_fw->Eval(ADClowRange_vec->at(i)),calib_fcn_fw->Eval(ADCupRange_vec->at(i)));
		ff_ENR -> SetRange(calib_fcn_fw->Eval(ADClowRange_vec->at(i)),calib_fcn_fw->Eval(ADCupRange_vec->at(i)));
		
		
//STEP1: only gaussian -> other functions switched off.
		cout << "\nFitting Step 1" << endl;
		cout<<"ROI from " << calib_fcn_fw->Eval(ADClowRange_vec->at(i)) << " KeV  " << " to " << calib_fcn_fw->Eval(ADCupRange_vec->at(i)) << " KeV" << endl;
		ff_ENR -> FixParameter(2,0.); //Low energy tail off
		ff_ENR -> FixParameter(4,0.); //'beta' parameter off
		ff_ENR -> FixParameter(5,0.); //Step function off
		ff_ENR -> SetParameter(0,initCenter); 
		ff_ENR -> SetParameter(1,initAmpl(h_ENR)); //Amplitude
		ff_ENR -> SetParameter(3,initSigma);  
		ff_ENR -> SetParameter(6,initCost(h_ENR)); //Constant initialization
		h_ENR -> Fit(ff_ENR,"RN"); 
		//Saving the temporary fit parameters
		tmp_P = ff_ENR -> GetParameter(0);
		tmp_G = ff_ENR -> GetParameter(1);
		tmp_sig = ff_ENR -> GetParameter(3);
		tmp_q = ff_ENR -> GetParameter(6);
		
		
//STEP2: fit of step functions with fixed gaussian and tail fnc switched off.
		cout << "\nFitting Step 2" << endl;
		ff_ENR -> FixParameter(2,0.); //Low energy tail off
		ff_ENR -> FixParameter(4,0.); //'beta' parameter off
		ff_ENR -> FixParameter(0,tmp_P); //From step before
		ff_ENR -> FixParameter(1,tmp_G); //From step before
		ff_ENR -> FixParameter(3,tmp_sig); //From step before
		ff_ENR -> SetParLimits(5,0,0); //Unfix this parameter
		ff_ENR -> SetParameter(5,initStep(h_ENR,tmp_sig,tmp_P));
		ff_ENR -> SetParameter(6,initCost(h_ENR));
		h_ENR -> Fit(ff_ENR,"RN");
		//Saving the temporary fit parameters
		tmp_S = ff_ENR -> GetParameter(5);
		tmp_q = ff_ENR -> GetParameter(6);
		
		
//STEP3: fit of low energy tail with fixed gaussian and step fnc
		cout << "\nFitting Step 3" << endl;
		ff_ENR -> FixParameter(0,tmp_P); //From step before
		ff_ENR -> FixParameter(3,tmp_sig); //From step before
		ff_ENR -> FixParameter(5,tmp_S); //From step before
		ff_ENR -> SetParameter(6,tmp_q);
		ff_ENR -> SetParameter(1,tmp_G);
		ff_ENR -> SetParLimits(2,0,1); //Unfix this parameter
		ff_ENR -> SetParameter(2,0.05); //Hardcoded A initialization!!!
		ff_ENR -> SetParLimits(4,0,1000./tmp_sig); //Unfix this parameter
		ff_ENR -> SetParameter(4,1./tmp_sig); //Beta initialization
		h_ENR -> Fit(ff_ENR,"RN");
		//Saving the temporary fit parameters
		tmp_A = ff_ENR -> GetParameter(2);
		tmp_beta = ff_ENR -> GetParameter(4);
		
		
//STEP4: all parameters initialized, start the global fit
		cout << "\nFitting Step 4" << endl;
		//Unfixing all the parameters. Give very large range at the parameters just to avoid negative parameters
		ff_ENR -> SetParLimits(0,0,0); //Unfixing
		ff_ENR -> SetParLimits(1,0,1000*tmp_G);
		ff_ENR -> SetParLimits(2,0,1);
		ff_ENR -> SetParLimits(3,0,1000*tmp_sig);
		ff_ENR -> SetParLimits(4,0,1000/tmp_sig);
		ff_ENR -> SetParLimits(5,0,1000*tmp_S);
		ff_ENR -> SetParLimits(6,0,0); //Unfixing
		
		
		ff_ENR -> SetParameter(0,tmp_P);
		ff_ENR -> SetParameter(1,tmp_G);
		ff_ENR -> SetParameter(2,tmp_A);
		ff_ENR -> SetParameter(3,tmp_sig);
		ff_ENR -> SetParameter(4,tmp_beta);
		ff_ENR -> SetParameter(5,tmp_S);
		ff_ENR -> SetParameter(6,tmp_q);
		h_ENR -> Fit(ff_ENR,"LBRN");
		
		
		for (Int_t k=0;k<7;k++) {
			ff_ENR -> SetParameter(k,ff_ENR->GetParameter(k));
		}
		
		
		//Fit without parameters limits using the last found.
		cout<<"\nFinal Fit"<<endl;
		fitRes = h_ENR-> Fit(ff_ENR,"SR+");
		
		
		//Saving the parameters to be used in the resolution plot if the fit converged
		fitStatus = fitRes;
		if(fitStatus==0){
			ENRcenters -> push_back(ff_ENR->GetParameter(0));
			ENRcenters_err -> push_back(ff_ENR->GetParError(0));
			ENRwidths -> push_back(ff_ENR->GetParameter(3));
			ENRwidths_err -> push_back(ff_ENR->GetParError(3));
		}
	}	
	
	c5 -> Modified();
	c5 -> Update();
	
	delete ADCcenters;
	delete ADCwidths;
	return;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

/*
TH1F* loadSpe(const char* dir, Double_t& aqtime){

	//-------------------------------------------------\\	
	// Load of the sample histogram from the SPE files \\
	// this version is only for calibration files      \\
	//-------------------------------------------------\\

	Char_t buffer[300];
	
	aqtime=0;
	
	Double_t time_tmp=0, entry=0; 
	Int_t channel=0;
	
	vector<Double_t>* entries_tmp = new vector<Double_t>;
	vector<Double_t>* entries = new vector<Double_t>;
	
	string dirname(dir);
	string command("ls ");
	string infilename;
	
	command += dirname;
	command += "*.Spe";
	
	ifstream spe;
	
	FILE* fpp = gSystem -> OpenPipe(command.c_str(),"r"); //Hard coded!!! Find a way to implement a simpler way to set the directory
	
	Int_t filenum =0; //Counts the files.SPE read
	
	Char_t time_tmp_str[100], entry_str[100];
	while (!feof(fpp)){
		if (feof(fpp)){ break;}
		fgets(buffer,sizeof(buffer),fpp);
		infilename = buffer;
		infilename = infilename.substr(0,infilename.find("\n")); //Removed the carriage at the end of filename
		cout << "\nOpening file <" << infilename.c_str() << ">" << endl;
		
		spe.open(infilename.c_str());
		
		if (spe.fail()){
			cout << "Error: can't open the file <" << infilename.c_str() << ">" << endl;
			continue;//Skip the loop
		}
		for (Int_t i = 0; i<=11; i++) {
			if (i==9){
				spe >> time_tmp_str;
				time_tmp = atof(time_tmp_str);
			}
			
			//Here I go ahead in the file discarding the header lines
			spe.getline(buffer,sizeof(buffer));
		}
		
		cout << "Acquisition time: " << time_tmp << " secs" << endl;
		
		entries_tmp->clear();
		
		//Loading the ADC counts from the file and put them in the vector entry_tmp
		while (spe.good()) {
			if (spe.eof()) break;
				channel++;
				spe >> entry_str;
				entry = atof(entry_str);
				if(filenum==0){
					if (entries->size()>=16385) break; //According to calibration... hard coded ==> be care!!!
					entries -> push_back(entry);
				} else {
					if (entries_tmp->size()>=16385) break;
					entries_tmp -> push_back(entry);
				}
				
			if (!spe.good()) break;
		}
		
		if(filenum==0){
			cout << "Number of channels: " << entries->size() << endl;
		}else{
			cout << "Number of channels: " << entries_tmp->size() << endl;
			for(Int_t i=0; i<entries_tmp->size(); i++){
				(*entries)[i] += entries_tmp->at(i);
			}
		}
		
		spe.close();
		
		filenum++;
		
		aqtime += time_tmp; //Stored total total acquisition time
		
	}
	
	//Create and fill the histogram
	TH1F* histoADC = new TH1F("histoADC","Spectrum ADC",entries_tmp->size(),1,entries_tmp->size());
	for(Int_t i=0; i<entries->size(); i++){
		histoADC->Fill(i+1,entries->at(i));
	}
	
	//-------------------------------------------------------------//	
	// Finished to load of the sample histogram from the SPE files //
	//-------------------------------------------------------------//

	
	delete entries_tmp;
	delete entries;
	
	return histoADC;

}
*/
///////////////////////////////////////////////////////////////////////////////////////////


/*
TH1F* loadTxt(string& filename, Double_t& time){
	//This definition of loadTxt() is only for files of Gator spectrum in which the first line is the acquisition time in secons.
	
	ifstream datafile;
	
	Double_t counts, entries, ADCch;
	vector<Double_t>* ADCchVec = new vector<Double_t>;
	vector<Double_t>* entriesVec = new vector<Double_t>;
	
	cout << "Opening the file <" << filename.c_str() << ">" << endl;
	
	string timeStr, ADCchStr, entriesStr;
	
	datafile.open(filename.c_str());
	Int_t i = 0;
	while(!datafile.eof()) {
		if(i==0){
			datafile >> timeStr;
			time = atof(timeStr.c_str());
		}else{
			datafile >> ADCchStr;
			datafile >> entriesStr;
			ADCch = atof(ADCchStr.c_str());
			entries = atof(entriesStr.c_str());
			ADCchVec -> push_back(ADCch);
			entriesVec -> push_back(entries);
		}
		i++;
	}
	datafile.close();
	cout << "Number of channels = " << ADCchVec->size() << "\n\n" << endl;
	
	
	Int_t nlines = ADCchVec -> size();
	TH1F* histo = new TH1F("histo",filename.c_str(),nlines,1,nlines); //nlines take into account also the first line which is the data acquisition time
	
	
	for(Int_t i=0; i<ADCchVec->size(); i++){
		histo -> Fill(ADCchVec->at(i), entriesVec->at(i));
	}
	
	histo -> Draw();
	
	return histo;
	
}
*/
///////////////////////////////////////////////////////////////////////////////////////////