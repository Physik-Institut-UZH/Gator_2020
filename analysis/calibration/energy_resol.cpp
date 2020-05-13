#include <TROOT.h>
#include <TStyle.h>
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

void wait();
void energy_resol();
Double_t peakFitFunc(Double_t* ,Double_t*);
Double_t initAmpl(TH1F*);
Double_t initCost(TH1F*);
Double_t initStep(TH1F*,Double_t,Double_t);
Double_t gausFunc (Double_t*,Double_t*);
Double_t tailFunc (Double_t*,Double_t*);
Double_t stepFunc (Double_t*,Double_t*);
Double_t resolFunc (Double_t*,Double_t*);
TH1F* convert_histo_ENR(TH1F*,const char*);
TH1F* convert_histo_ENR2(TH1F*,const char*);
void resolInit(TF1*, vector<Double_t>*, vector<Double_t>*);

TH1F* loadSpe(const char*, Double_t&);


TCanvas* c1;

int main()
{
	TApplication theApp("App",0,0);
	energy_resol();
	
	theApp.Run();
	
	return 0;
}




////////////---------- SCRIPT FUNCTION ------------//////////////
void energy_resol(){
	
	c1 = new TCanvas("c1");
	
	//The following lines are for closing the application when the canvas c1 is closed.
#ifndef __CINT__
	c1 -> Connect("TCanvas", "Closed()", "TApplication", gApplication,"Terminate()");
#endif

//-------------- HARD CODED STUFF: start ---------------\\

	string workdir = "/Users/francesco/PhD/Gator/data_analysis/calibrations/archive/temp/";


//-------------- HARD CODED STUFF: finish ---------------\\

	string rootinfilename = workdir;
	rootinfilename += "calibration.root";
	
	string resolfilename = workdir;
	resolfilename += "resolution.root";
	
	
//Load the spectrum in ADC domain from SPE files
	Double_t time;
	
	TH1F* hADC = loadSpe(workdir.c_str(),time);
	
	TF1* resol_enr_fnc; //The aim of this script
	TF1* calib_fcn_fw = 0;
	
//Defining vectors for lines configuration and fill them from the file "Th_res_enr.conf"
	//vector<string>* v_massN = new vector<string>;//not useful
	//vector<string>* v_elemTag = new vector<string>;//not useful
	vector<Double_t>* v_lit_enr = new vector<Double_t>;
	vector<Double_t>* v_saved_enr = new vector<Double_t>;
	vector<Double_t>* v_saved_enr_err = new vector<Double_t>; //This will be a vector with only 0s
	vector<Double_t>* v_enr_widths = new vector<Double_t>;
	vector<Double_t>* v_enr_widths_err = new vector<Double_t>;
	vector<Double_t>* v_enr_beta = new vector<Double_t>; //Maybe I will use it once
	vector<Double_t>* v_lowENRrange = new vector<Double_t>;
	vector<Double_t>* v_highENRrange = new vector<Double_t>;
	vector<Double_t>* v_initwidth = new vector<Double_t>;
	vector<Double_t>* v_cal_enr= new vector<Double_t>;
	vector<Double_t>* v_cal_enr_err = new vector<Double_t>;

//Load from calibration.root the useful things
	TFile* f = new TFile(rootinfilename.c_str(),"read");
	
	calib_fcn_fw = (TF1*)f->Get("calib_fcn_fw");
	vector<Double_t>* v_ADCcenters = (vector<Double_t>*)f -> Get("ADCcenters");
	vector<Double_t>* v_ADCwidths = (vector<Double_t>*)f -> Get("ADCwidths");
	
	f -> Close();
	delete f;
	
	
	if (calib_fcn_fw == 0){
		cout << "Calibration not still done. Run ./Th_calib before!!!" << endl;
		exit(1);
	}
	
	//Loading from "Th_res_enr.conf"
	ifstream linesfile("Th_res_enr.conf");
	
	Char_t massN_str[100], elemTag_str[100], lit_enr_str[100], lowADCrange_str[100], highADCrange_str[100], width_str[100];
	Double_t lit_enr_tmp, lowADCrange_tmp, highADCrange_tmp, width_tmp;
	
	if (linesfile.fail()){
		cout << "Error: can't open <" << "Th_res_enr.conf" << ">.... failure!" << endl;
		exit(1);
	}
	
	while (linesfile.good()){
		if(linesfile.eof()) break;

		linesfile >> massN_str;
		linesfile >> elemTag_str; 
		linesfile >> lit_enr_str;
		linesfile >> lowADCrange_str;
		linesfile >> highADCrange_str;
		linesfile >> width_str;

		if(linesfile.eof()) break;

		lit_enr_tmp = atof(lit_enr_str);
		lowADCrange_tmp = atof(lowADCrange_str);
		highADCrange_tmp = atof(highADCrange_str);
		width_tmp = atof(width_str);

		//v_massN -> push_back(massN_str);
		//v_elemTag -> push_back(elemTag_str);
		v_lit_enr -> push_back(lit_enr_tmp);
		v_lowENRrange -> push_back((Double_t)calib_fcn_fw->Eval(lowADCrange_tmp));
		v_highENRrange -> push_back((Double_t)calib_fcn_fw->Eval(highADCrange_tmp));
		v_initwidth  -> push_back(width_tmp);

		if(linesfile.eof()) break;
	}
	linesfile.close();
	
	
	TH1F* hENR = convert_histo_ENR2(hADC,workdir.c_str());
	//hENR -> Rebin(3);
	//hENR -> Scale(1.,"width");
	
	hENR -> Draw();
	
	Int_t nlines = v_lit_enr->size();
	
	
	//Vectors of the functions summed together to build the general fit function of the peaks. This functions take only the parameters needed from the fit function "ff_ENR" and are used only to show in the canvas every single component and not to do the fit.
	vector<TF1*> gaus_fnc_vec(nlines);
	vector<TF1*> tail_fnc_vec(nlines);
	vector<TF1*> step_fnc_vec(nlines);
	
	//String used in the for loop to give the name to th TF1 functions to be plotted
	char name_gaus_fnc [100];
	char name_tail_fnc [100];
	char name_step_fnc [100];
	
	//cout << "VACCA!" << endl;
	TF1* ff_ENR = new TF1("ff_ENR",peakFitFunc,hENR->GetBinLowEdge(hENR->GetXaxis()->GetFirst()),hENR->GetBinLowEdge(hENR->GetXaxis()->GetLast()),7);
	ff_ENR->SetParNames("Mean","Ampl","A","Sigma","Beta","S","Constant");
	ff_ENR->SetLineColor(2);
	
	//return;
	
	TFitResultPtr resFit; //Useful for the residuals plots
	Int_t fitStatus;
	
	//Temporary variables used for the multistep fit.
	Double_t tmp_P=0,tmp_G=0,tmp_A=0,tmp_sig=0,tmp_beta=0,tmp_S=0,tmp_q=0;
	Double_t lowRng, upRng;
	for (Int_t i=0;i<nlines;i++) {
		//Fit done in 4 steps to avoid to set boundaries to parameters.
		
		lowRng = v_lowENRrange->at(i);
		upRng = v_highENRrange->at(i);
		
		//ROI selection
		hENR -> GetXaxis() -> SetRangeUser(lowRng,upRng);
		ff_ENR -> SetRange(lowRng,upRng);
		c1 -> Modified();
		
//STEP1: only gaussian -> other functions switched off.
		cout << "\n1st Step" << endl;
		ff_ENR -> FixParameter(2,0.); //Low energy tail off
		ff_ENR -> FixParameter(4,0.); //'beta' parameter off
		ff_ENR -> FixParameter(5,0.); //Step function off
		ff_ENR -> SetParameter(0,v_lit_enr->at(i)); //Gaussian Center initialization
		ff_ENR -> SetParameter(1,initAmpl(hENR)); //Amplitude
		ff_ENR -> SetParameter(3,v_initwidth->at(i));
		ff_ENR -> SetParameter(6,initCost(hENR)); //Constant initialization
		hENR -> Fit(ff_ENR,"RN"); 
		//Saving the temporary fit parameters
		tmp_P = ff_ENR -> GetParameter(0);
		tmp_G = ff_ENR -> GetParameter(1);
		tmp_sig = ff_ENR -> GetParameter(3);
		tmp_q = ff_ENR -> GetParameter(6);
		
//STEP2: fit of step functions with fixed gaussian and tail fnc switched off.
		cout << "\n2nd Step" << endl;
		ff_ENR -> FixParameter(2,0.); //Low energy tail off
		ff_ENR -> FixParameter(4,0.); //'beta' parameter off
		ff_ENR -> FixParameter(0,tmp_P); //From step before
		ff_ENR -> FixParameter(1,tmp_G); //From step before
		ff_ENR -> FixParameter(3,tmp_sig); //From step before
		ff_ENR -> SetParLimits(5,0,0); //Unfix this parameter
		ff_ENR -> SetParameter(5,initStep(hENR,tmp_sig,tmp_P));
		ff_ENR -> SetParameter(6,initCost(hENR));
		hENR -> Fit(ff_ENR,"RN");
		//Saving the temporary fit parameters
		tmp_S = ff_ENR -> GetParameter(5);
		tmp_q = ff_ENR -> GetParameter(6);
		
//STEP3: fit of low energy tail with fixed gaussian and step function
		cout << "\n3nd Step" << endl;
		ff_ENR -> FixParameter(0,tmp_P); //From step before
		ff_ENR -> FixParameter(3,tmp_sig); //From step before
		ff_ENR -> FixParameter(5,tmp_S); //From step before
		ff_ENR -> SetParameter(6,tmp_q);
		ff_ENR -> SetParameter(1,tmp_G);
		ff_ENR -> SetParLimits(2,0,1.); //Unfix this parameter (and put true limits to its
		ff_ENR -> SetParameter(2,0.1); //Hardcoded A initialization --> BE CARE!!!!
		ff_ENR -> SetParLimits(4,0,1000./tmp_sig); //Unfix this parameter ????
		ff_ENR -> SetParameter(4,1./tmp_sig); //Beta initialization
		hENR -> Fit(ff_ENR,"LRN");
		//Saving the temporary fit parameters
		tmp_A = ff_ENR -> GetParameter(2);
		tmp_beta = ff_ENR -> GetParameter(4);
		
//STEP4: all parameters initialized, start the global fit
		//ff_ENR -> SetRange(ADC_low_range[i],ADC_high_range[i]);
		//initFitFuncADC(h,ff_ENR);
		
		cout << "\n4th Step" << endl;
		//Unfixing all the parameters. Give very large range at the parameters just to avoid negative parameters
		ff_ENR -> SetParLimits(0,0,0); //Unfixing
		ff_ENR -> SetParLimits(1,0,1000*tmp_G);
		ff_ENR -> SetParLimits(2,0,1);
		ff_ENR -> SetParLimits(3,0,100*tmp_sig);
		ff_ENR -> SetParLimits(4,0,1000/tmp_sig);
		ff_ENR -> SetParLimits(5,0,1000);
		ff_ENR -> SetParLimits(6,0,0); //Unfixing
		
		
		ff_ENR -> SetParameter(0,tmp_P);
		ff_ENR -> SetParameter(1,tmp_G);
		ff_ENR -> SetParameter(2,tmp_A);
		ff_ENR -> SetParameter(3,tmp_sig);
		ff_ENR -> SetParameter(4,tmp_beta);
		ff_ENR -> SetParameter(5,tmp_S);
		ff_ENR -> SetParameter(6,tmp_q);
		hENR -> Fit(ff_ENR,"MBRN");
		
		for (Int_t k=0;k<7;k++) {
			ff_ENR -> SetParameter(k,ff_ENR->GetParameter(k));
		}
		
		//Fit without parameters limits using the last found.
		cout << "\nFinal Fit Step" << endl;
		resFit = hENR -> Fit(ff_ENR,"SR+"); //Used resFit to discard bad fitting peaks. Actually it is conceived for the residual plots.
		//ff_ENR -> Draw("same+");
		
		//Saving the values only if the fit converged
		fitStatus = resFit;
		cout << "PROB = " << resFit->Prob() << endl;
		if (fitStatus==0){
			cout << "PEAK SAVED" << endl;
			v_cal_enr -> push_back(ff_ENR->GetParameter(0));
			v_cal_enr_err -> push_back(ff_ENR->GetParError(0));
			v_saved_enr -> push_back(v_lit_enr->at(i));
			v_saved_enr_err -> push_back(0); //Just a trick
			v_enr_widths -> push_back(ff_ENR->GetParameter(3));
			v_enr_widths_err -> push_back(ff_ENR->GetParError(3));
			v_enr_beta -> push_back(ff_ENR->GetParameter(4));
		} else {
			cout << "PEAK NOT SAVED" << endl;
		}
		
		sprintf(name_gaus_fnc,"gausFunc%02d",i);
		gaus_fnc_vec[i] = new TF1(name_gaus_fnc,gausFunc,(Double_t)hENR->GetXaxis()->GetFirst(),(Double_t)hENR->GetXaxis()->GetLast(),4);
		gaus_fnc_vec[i] -> SetRange(v_lowENRrange->at(i),v_highENRrange->at(i));
		gaus_fnc_vec[i] -> SetLineColor(3);
		gaus_fnc_vec[i] -> SetLineWidth(2);
		gaus_fnc_vec[i] -> SetParameters(ff_ENR->GetParameter(0),ff_ENR->GetParameter(3),ff_ENR->GetParameter(1)*(1-ff_ENR->GetParameter(2)),ff_ENR->GetParameter(6));
		gaus_fnc_vec[i] -> Draw("same");
		
		sprintf(name_tail_fnc,"tailFunc%02d",i);
		tail_fnc_vec[i] = new TF1(name_tail_fnc,tailFunc,(Double_t)hENR->GetXaxis()->GetFirst(),(Double_t)hENR->GetXaxis()->GetLast(),5);
		tail_fnc_vec[i] -> SetRange(v_lowENRrange->at(i),v_highENRrange->at(i));
		tail_fnc_vec[i] -> SetLineColor(4);
		tail_fnc_vec[i] -> SetLineWidth(2);
		tail_fnc_vec[i] -> SetParameters(ff_ENR->GetParameter(0),ff_ENR->GetParameter(3),ff_ENR->GetParameter(4),ff_ENR->GetParameter(1)*ff_ENR->GetParameter(2),ff_ENR->GetParameter(6));
		tail_fnc_vec[i] -> Draw("same");
		
		sprintf(name_step_fnc,"stepFunc%02d",i);
		step_fnc_vec[i] = new TF1(name_step_fnc,tailFunc,(Double_t)hENR->GetXaxis()->GetFirst(),(Double_t)hENR->GetXaxis()->GetLast(),4);
		step_fnc_vec[i] -> SetRange(v_lowENRrange->at(i),v_highENRrange->at(i));
		step_fnc_vec[i] -> SetLineColor(6);
		step_fnc_vec[i] -> SetLineWidth(2);
		step_fnc_vec[i] -> SetParameters(ff_ENR->GetParameter(0),ff_ENR->GetParameter(3),ff_ENR->GetParameter(5),ff_ENR->GetParameter(6));
		step_fnc_vec[i] -> Draw("same");
		
		
		c1 -> Modified();
		wait();

	}
	
	hENR -> GetXaxis() -> UnZoom();
	
	for (Int_t i=0;i<nlines;i++) {
		gaus_fnc_vec[i] -> Draw("same+");
		tail_fnc_vec[i] -> Draw("same+");
		step_fnc_vec[i] -> Draw("same+");
	}
	

	c1 -> Modified();
	 
	
	
/////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------FINISHED THE ENERGY FITTING PROCEDURE-------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////////////////

	nlines = v_saved_enr -> size();

	cout << "\n\n\nLit En" << "\t" << "Cal En" << "\t" << "Cal En Err" << "\t" << "Sigma" << "\t" << "Sigma Err" << endl;
	for(Int_t i=0;i<nlines;i++){
		cout << v_saved_enr->at(i) << "\t" << v_cal_enr->at(i) << "\t" << v_cal_enr_err->at(i) << "\t" << v_enr_widths->at(i) << "\t" << v_enr_widths_err->at(i) << endl;
	}
	cout << "\n\n\n" << endl;
	
	TCanvas* c2 = new TCanvas("c2","Resolution plot (energy)");
	c2 -> cd();
	TGraphErrors* gr_resol_enr = new TGraphErrors(nlines,&(v_saved_enr->at(0)),&(v_enr_widths->at(0)),&(v_saved_enr_err->at(0)),&(v_enr_widths_err->at(0)));
	gr_resol_enr -> SetTitle("Energy resolution");
	gr_resol_enr -> GetXaxis()->SetTitle("keV");
	gr_resol_enr -> GetYaxis()->SetTitle("#sigma_{E} [keV]");
	gr_resol_enr -> SetMarkerStyle(20);
	gr_resol_enr -> Draw("AP");
	
	
	resol_enr_fnc = new TF1("resol_enr_fnc",resolFunc,50.0,2700.0,3);
	
	//TCanvas* c3 = new TCanvas("c3");
	//c3 -> cd();
	//resolInit(resol_enr_fnc, v_saved_enr, v_enr_widths);
	resol_enr_fnc -> SetParameters(1e-05,1e-05,1e-05);
	resol_enr_fnc -> SetLineColor(2);
	resol_enr_fnc -> SetLineWidth(2);
	
	c2 -> cd();
	
	gr_resol_enr -> Fit(resol_enr_fnc);
	
	
	//Saving the whole work in a root file
	
	TFile* filesave = new TFile(resolfilename.c_str(),"update");
	
	filesave -> WriteObject(v_saved_enr,"v_saved_enr","Overwrite");
	filesave -> WriteObject(v_saved_enr_err,"v_saved_enr_err","Overwrite");
	filesave -> WriteObject(v_enr_widths,"v_enr_widths","Overwrite");
	filesave -> WriteObject(v_enr_widths_err,"v_enr_widths_err","Overwrite");
	filesave -> WriteTObject(resol_enr_fnc,"resol_enr_fnc","Overwrite");
	filesave -> WriteTObject(gr_resol_enr,"gr_resol_enr","Overwrite");

	filesave -> Close();
	delete filesave;
	
	wait(); //Before closing the canvases
	return;
	
}//SCRIPT FINISH!!!


void wait()
{
	c1 -> Update(); c1 -> WaitPrimitive();
}
//////////////////////////////////////////////////////////////////////////////////////////


void resolInit(TF1* resolFnc, vector<Double_t>* v_x, vector<Double_t>* v_y){
	//To initalize the resolution function
	
	
	TF1* func = new TF1("func","pol2");
	
	Int_t npoints = v_x -> size();
	
	Double_t* x = new Double_t[npoints];
	Double_t* y = new Double_t[npoints];
	
	for (Int_t i=0; i<npoints; i++){
		x[i] = v_x->at(i);
		y[i] = TMath::Power(v_y->at(i),2);
	}
	
	TGraph* gr = new TGraph(npoints,x,y);
	gr -> Fit(func,"F");
	
	resolFnc -> SetParameters(func->GetParameter(0),func->GetParameter(1),func->GetParameter(2));
	
	
	/*
	gr -> Draw("AP");
	func -> Draw("SAME+");
	
	wait();
	*/
	delete func;
	delete gr;
	delete [] x;
	delete [] y;
	return;
}
