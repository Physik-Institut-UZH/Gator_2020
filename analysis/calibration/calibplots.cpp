{
	gROOT->Reset();

	/*
	TFile* calfile = new TFile("archive/04-10-2012/calibration.root","read");
	
	TF1* calib_fcn_fw = (TF1*)calfile->Get("calib_fcn_fw");
	TF1* calib_fcn_bw = (TF1*)calfile->Get("calib_fcn_bw");
	TF1* resol_ADC_func = (TF1*)calfile->Get("resol_ADC_func");
	TGraphErrors* gr_cal_res_fw = (TGraphErrors*)calfile->Get("gr_cal_res_fw");
	TGraphErrors* gr_cal_res_bw = (TGraphErrors*)calfile->Get("gr_cal_res_bw");
	
	vector<Double_t>* ADCcenters = (vector<Double_t>*)calfile->Get("ADCcenters");
	vector<Double_t>* ADCcenters_err = (vector<Double_t>*)calfile->Get("ADCcenters_err");
	vector<Double_t>* ADCwidths = (vector<Double_t>*)calfile->Get("ADCwidths");
	vector<Double_t>* ADCwidths_err = (vector<Double_t>*)calfile->Get("ADCwidths_err");
	vector<Double_t>* litt_vec = (vector<Double_t>*)calfile->Get("litt_vec");
	vector<Double_t>* litt_err_vec = (vector<Double_t>*)calfile->Get("litt_err_vec");
	
	calfile->Close();
	delete calfile;
	
	//--------------------------------------------------------------------------------------------//
	TCanvas* c1 = new TCanvas("c1","Forward Calibration");
	c1 -> Divide(1,2);
	c1 -> cd(1);
	
	TGraphErrors* gr_cal_fw = new TGraphErrors(ADCcenters->size(),&(ADCcenters->at(0)),&(litt_vec->at(0)),&(ADCcenters_err->at(0)),&(litt_err_vec->at(0)));
	gr_cal_fw -> SetTitle("Calibration ADC -> Energy");
	gr_cal_fw -> GetXaxis()->SetTitle("ADC channel");
	gr_cal_fw -> GetYaxis()->SetTitle("Energy [KeV]");
	gr_cal_fw -> Draw("AP");
	
	TF1* calib_fcn_fw = new TF1("calib_fcn_fw","pol2");
	calib_fcn_fw -> SetLineColor(2);
	calib_fcn_fw -> SetLineWidth(1);
	gr_cal_fw -> Fit(calib_fcn_fw);
	
	
	
	c1 -> cd(2);
	
	gr_cal_res_fw -> SetTitle("Residuals");
	gr_cal_res_fw -> Draw("AP");
	
	TLine* zeroline_fw = new TLine(gr_cal_res_fw->GetXaxis()->GetXmin(),0,gr_cal_res_fw->GetXaxis()->GetXmax(),0);
	zeroline_fw -> SetLineColor(2);
	zeroline_fw -> SetLineWidth(2);
	zeroline_fw -> Draw("same");
	
	
	//------------------------------------------------------------------------------------------------//
	TCanvas* c2 = new TCanvas("c2","Backward Calibration");
	c2 -> Divide(1,2);
	c2 -> cd(1);
	
	TGraphErrors* gr_cal_bw = new TGraphErrors(ADCcenters->size(),&(litt_vec->at(0)),&(ADCcenters->at(0)),&(litt_err_vec->at(0)),&(ADCcenters_err->at(0)));
	gr_cal_bw -> SetTitle("Calibration ADC -> Energy");
	gr_cal_bw -> GetXaxis()->SetTitle("Energy [KeV]");
	gr_cal_bw -> GetYaxis()->SetTitle("ADC channel");
	gr_cal_bw -> Draw("AP");
	
	TF1* calib_fcn_bw = new TF1("calib_fcn_bw","pol2");
	calib_fcn_bw -> SetLineColor(2);
	calib_fcn_bw -> SetLineWidth(1);
	gr_cal_bw -> Fit(calib_fcn_bw);
	
	
	c2 -> cd(2);
	
	gr_cal_res_bw -> SetTitle("Residuals");
	gr_cal_res_bw -> Draw("AP");
	
	TLine* zeroline_bw = new TLine(gr_cal_res_bw->GetXaxis()->GetXmin(),0,gr_cal_res_bw->GetXaxis()->GetXmax(),0);
	zeroline_bw -> SetLineColor(2);
	zeroline_bw -> SetLineWidth(2);
	zeroline_bw -> Draw("same");
	
	
	//------------------------------------------------------------------------------------------------//
	TCanvas* c3 = new TCanvas("c3","ADC Resolution");
	
	gr_resol_ADC = new TGraphErrors(ADCcenters->size(),&(ADCcenters->at(0)),&(ADCwidths->at(0)),&(ADCcenters_err->at(0)),&(ADCwidths_err->at(0)));
	gr_resol_ADC -> SetTitle("ADC resolution");
	gr_resol_ADC -> GetXaxis() -> SetTitle("ADC channel");
	gr_resol_ADC -> GetYaxis() -> SetTitle("Widths (ADC) ");
	gr_resol_ADC -> Draw("AP");
	
	resol_ADC_func -> Draw("same");
	
	
	//------------------------------------------------------------------------------------------------//
	TCanvas* c4 = new TCanvas("c4","Energy resolution");
	
	TGraphErrors* gr_resol_ENR = new TGraphErrors();
	
	for (Int_t i=0; i<ADCcenters->size(); i++){
		valENR = calib_fcn_fw->Eval(ADCcenters->at(i));
		
		sigmaENR = sigmacalc(	,ADCcenters->at(i),ADCwidths->at(i));
		
		valENR_err = 0.5*(calib_fcn_fw->Eval(ADCcenters->at(i)+ADCcenters_err->at(i)) - calib_fcn_fw->Eval(ADCcenters->at(i)-ADCcenters_err->at(i)));
		
		sigmaENR_err = (sigmacalc()-sigmacalc())/2;
	}
	*/
	
	//------------------------------------------------------------------------------------------------//
	// Comparison of energy resolutions
	TCanvas* c5 = new TCanvas("c5","Resolution comparison");
	
	TFile* resolfile_new = new TFile("archive/04-10-2012/resolution.root","read");
	
	TGraphErrors* gr_resol_new = (TGraphErrors*)resolfile_new -> Get("gr_resol_enr");
	gr_resol_new -> SetName("gr_resol_new");
	TF1* resol_enr_fnc_new = (TF1*)resolfile_new -> Get("resol_enr_fnc");
	resol_enr_fnc_new -> SetName("resol_enr_fnc_new");
	
	resolfile_new -> Close();
	delete resolfile_new;
	
	gr_resol_new -> SetMarkerStyle(20);
	gr_resol_new -> SetMarkerColor(kRed);
	gr_resol_new -> SetLineColor(kRed);
	gr_resol_new -> SetLineWidth(2);
	gr_resol_new -> SetTitle("");
	gr_resol_new -> GetXaxis() -> SetTitle("Energy [keV]");
	gr_resol_new -> GetYaxis() -> SetTitle("#sigma_{E} [keV]");
	resol_enr_fnc_new -> SetLineColor(kRed);
	resol_enr_fnc_new -> SetLineWidth(2);
	
	
	
	TFile* resolfile_old = new TFile("archive/19-06-2012/resolution.root","read");
	
	vector<Double_t>* v_saved_enr_old = (vector<Double_t>*)resolfile_old -> Get("v_saved_enr");
	vector<Double_t>* v_saved_enr_err_old = (vector<Double_t>*)resolfile_old -> Get("v_saved_enr_err");
	vector<Double_t>* v_enr_widths_old = (vector<Double_t>*)resolfile_old -> Get("v_enr_widths");
	vector<Double_t>* v_enr_widths_err_old = (vector<Double_t>*)resolfile_old -> Get("v_enr_widths_err");
	
	/*
	TGraphErrors* gr_resol_old = (TGraphErrors*)resolfile_old -> Get("gr_resol_enr");
	gr_resol_old -> SetName("gr_resol_old");
	TF1* resol_enr_fnc_old = (TF1*)resolfile_old -> Get("resol_enr_fnc");
	resol_enr_fnc_old -> SetName("resol_enr_fnc_old");
	*/
	
	resolfile_old -> Close();
	delete resolfile_old;
	
	
	TGraphErrors* gr_resol_old = new TGraphErrors(v_saved_enr_old->size(),(&v_saved_enr_old->at(0)),(&v_enr_widths_old->at(0)),(&v_saved_enr_err_old->at(0)),(&v_enr_widths_err_old->at(0)));
	gr_resol_old -> SetName("gr_resol_old");
	
	TF1* resol_enr_fnc_old = new TF1("resol_enr_fnc_old","sqrt([0]*x*x+[1]*x+[2])");
	
	
	gr_resol_old -> SetMarkerStyle(20);
	gr_resol_old -> SetMarkerColor(kBlue);
	gr_resol_old -> SetLineColor(kBlue);
	gr_resol_old -> SetLineWidth(2);
	
	//gr_resol_old -> SetTitle("Energy resolutions");
	//gr_resol_old -> GetXaxis() -> SetTitle("Energy [keV]");
	//gr_resol_old -> GetYaxis() -> SetTitle("#sigma_{E} [keV]");
	//resol_enr_fnc_old -> SetRange(30.,2700.);
	//resol_enr_fnc_old -> SetParameters(resol_enr_fnc_new->GetParameter(0),resol_enr_fnc_new->GetParameter(1),resol_enr_fnc_new->GetParameter(2));
	resol_enr_fnc_old -> SetLineColor(kBlue);
	resol_enr_fnc_old -> SetLineWidth(2);
	
	gr_resol_old -> Fit(resol_enr_fnc_old);
	
	
	c5 -> cd();
	
	gr_resol_new -> Draw("AP");
	
	gr_resol_old -> Draw("P");
	
	
	//------------------------------------------------------------------------------------------------//
	// Energy Spectrum plotting
	TCanvas* c6 = new TCanvas("c6","Th source spectrum");
	c6 -> SetLogy();
	
	string calibdir = "/Users/francesco/PhD/Gator/data_analysis/calibrations/archive/04-10-2012/";
	
	string rootinfilename = calibdir;
	rootinfilename += "calibration.root";
	
	gROOT -> ProcessLine(".L /Users/francesco/PhD/Gator/data_analysis/calibrations/src/convert_histo_ENR.cpp");
	gROOT -> ProcessLine(".L /Users/francesco/PhD/Gator/data_analysis/calibrations/src/loadSpe.cpp");
	
	Double_t time;
	TH1F* hADC = loadSpe(calibdir.c_str(),time);
	
	/*
	TFile* rootinfile = new TFile(rootinfilename.c_str(),"read");
	
	TF1* calib_fcn_fw = (TF1*)rootinfile -> Get("calib_fcn_fw");
	//vector<Double_t>* v_ADCcenters = (vector<Double_t>*)rootinfile -> Get("ADCcenters");
	//vector<Double_t>* v_ADCwidths = (vector<Double_t>*)rootinfile -> Get("ADCwidths");
	
	rootinfile -> Close();
	delete rootinfile;
	*/
	
	TH1F* hENR = convert_histo_ENR(hADC,calibdir.c_str());
	
	hENR -> Rebin(5);
	hENR -> Scale(1.,"width");
	hENR -> SetTitle("Th source spectrum");
	hENR -> GetXaxis() -> SetTitle("Energy [keV]");
	hENR -> GetYaxis() -> SetTitle("Counts");
	
	hENR -> Draw();

}
