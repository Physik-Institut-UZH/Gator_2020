// Code to create the calibration root files inside a new calibration folder  (dont run it in folders with existing calibration.root files, since they will be overwritten!)

// Before running the code, make sure that the gr_cal_res_fw.txt, gr_cal_res_bw.txt, and errorgraph_resolutionfile.txt files exist

// to run it, run the following command inside the calibration folder:
//$ root -l make_calib_files.C

#include "TF1.h"

void make_calib_files()
{

//#### vary parameters here ! #####
//current values set for 2021.02.04 calibration folder

// calib_fcn_fw: f = a * x + b
double a_fw= 0.16485455420310968;
double b_fw = 0.5881101870063857;

//calib_fcn_bw: f = a * x + b
double a_bw = 6.065953135683144;
double b_bw = -3.567448832998586;

int max_x_fw = 3000;//TODO: Check whether these values make sense
int max_x_bw=1;
int max_x_resol=20000;

//resol_ADC_func: Sqrt([0]*x*x+[1]*x+[2]) -> f = sqrt(a(E**2) + bE + c)
double a_res=1.4966736860366046e-08;
double b_res=0.0024618435283309563;
double c_res=6.949079284547924;
//###################################


 TFile *calibrootfile = new TFile ("calibration.root", "RECREATE");

 TF1 *calib_fcn_fw = new TF1 ("calib_fcn_fw","[0]*x+[1]", 0, max_x_fw);
 calib_fcn_fw->SetParameter(0, a_fw);
 calib_fcn_fw->SetParameter(1, b_fw);

 TF1 *calib_fcn_bw = new TF1 ("calib_fcn_bw","[0]*x+[1]", 0, max_x_bw);
 calib_fcn_bw->SetParameter(0, a_bw);
 calib_fcn_bw->SetParameter(1, b_bw);

 TF1 *resol_ADC_func = new TF1 ("resol_ADC_func","sqrt([0]*x*x+[1]*x+[2])", 0, max_x_resol);
 resol_ADC_func->SetParameter(0, a_res);
 resol_ADC_func->SetParameter(1, b_res);
 resol_ADC_func->SetParameter(2, c_res);

 calib_fcn_fw->Write();
 calib_fcn_bw->Write();
 resol_ADC_func->Write();
 
 TGraphErrors *gr_cal_res_fw = new TGraphErrors("gr_cal_res_fw.txt");
 gr_cal_res_fw->SetName("gr_cal_res_fw");  //gr_cal_res_fw->SetTitle("gr_cal_res_fw");
 gr_cal_res_fw->GetYaxis()->SetTitle("Energy reconstruction residuals [keV]");
 gr_cal_res_fw->GetXaxis()->SetTitle("MCA channel");
 gr_cal_res_fw->SetMarkerStyle(20);
 gr_cal_res_fw->Write();

 TGraphErrors *gr_cal_res_bw = new TGraphErrors("gr_cal_res_bw.txt");
 gr_cal_res_bw->SetName("gr_cal_res_bw");  //gr_cal_res_bw->SetTitle("gr_cal_res_bw");
 gr_cal_res_bw->GetYaxis()->SetTitle("MCA channels reconstruction residuals");
 gr_cal_res_bw->GetXaxis()->SetTitle("Energy [keV]");
 gr_cal_res_bw->SetMarkerStyle(20);
 gr_cal_res_bw->Write();

 calibrootfile->Close();

 TFile *resolutionrootfile = new TFile ("resolution.root", "RECREATE");
 resol_ADC_func->Write();

 TGraphErrors *resolution_error_graph = new TGraphErrors("resolution_file.txt");
 //resolution_error_graph->GetYaxis()->SetTitle("?"); resolution_error_graph->GetXaxis()->SetTitle("MCA channel");
 resolution_error_graph->SetMarkerStyle(20);
 resolution_error_graph->Write();



}
