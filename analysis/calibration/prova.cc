{

gROOT -> Reset();

gROOT -> ProcessLine(".L src/loadSpe.cpp");
gROOT -> ProcessLine(".L src/fit_funcs.cpp");
gROOT -> ProcessLine(".L src/convert_histo_ENR.cpp");
gROOT -> ProcessLine(".L sigmacalc.cxx");

TFile* f = new TFile("calibration.root","read");
TF1* calib_fcn_fw = (TF1*)f -> Get("calib_fcn_fw");
//vector<double>* v_saved_enr = (vector<double>*)f -> Get("v_saved_enr");
//vector<double>* v_saved_enr_err = (vector<double>*)f -> Get("v_saved_enr_err");
//vector<double>* v_enr_widths = (vector<double>*)f -> Get("v_enr_widths");
//vector<double>* v_enr_widths_err = (vector<double>*)f -> Get("v_enr_widths_err");
vector<double>* ADCcenters = (vector<double>*)f -> Get("ADCcenters");
vector<double>* ADCcenters_err = (vector<double>*)f -> Get("ADCcenters_err");
vector<double>* ADCwidths = (vector<double>*)f -> Get("ADCwidths");
vector<double>* ADCwidths_err = (vector<double>*)f -> Get("ADCwidths_err");
f -> Close();
delete f;

int nlines = ADCcenters->size();




vector<double>* v_ENR = new vector<double>;
vector<double>* v_ENR_err = new vector<double>;
vector<double>* v_ENR_width = new vector<double>;
vector<double>* v_ENR_width_err = new vector<double>;

Double_t ENRcenter, ENRcenter_err, ENRsigma, ENRsigma_err;

for (Int_t i=0; i<nlines; i++){
	
	sigmacalc(calib_fcn_fw, ADCcenters->at(i), ADCwidths->at(i), ADCwidths_err->at(i), ENRsigma, ENRsigma_err);
	
	ENRcenter = calib_fcn_fw(ADCcenters->at(i));
	ENRcenter_err = ENRcenter*(ADCcenters_err->at(i)/ADCcenters->at(i));
	
	v_ENR -> push_back(ENRcenter);
	v_ENR_err -> push_back(ENRcenter_err);
	
	v_ENR_width -> push_back(ENRsigma);
	v_ENR_width_err -> push_back(ENRsigma_err);
}

TGraphErrors* gr_resol_enr = new TGraphErrors(nlines,&(v_ENR->at(0)),&(v_ENR_width->at(0)),&(v_ENR_err->at(0)),&(v_ENR_width_err->at(0)));

gr_resol_enr -> SetTitle("Energy resolution");
gr_resol_enr -> GetXaxis() -> SetTitle("Energy [keV]");
gr_resol_enr -> GetYaxis() -> SetTitle("#sigma_{E} [keV]");

TCanvas* c1 = new TCanvas("c1");

gr_resol_enr -> Draw("AP");

TF1* resol_enr_fnc = new TF1("resol_enr_fnc",resolFunc,50.0,2700.0,3);

resolInit2(resol_enr_fnc, v_ENR, v_ENR_width);

cout << resol_enr_fnc->GetParameter(0) << "\t" << resol_enr_fnc->GetParameter(1) << "\t" << resol_enr_fnc->GetParameter(2) << endl;

gr_resol_enr -> Fit(resol_enr_fnc);



}