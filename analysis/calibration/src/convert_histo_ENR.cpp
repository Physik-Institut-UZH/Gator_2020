#include <TFile.h>
#include <TF1.h>
#include <TH1F.h>

using namespace std;


TH1F* convert_histo_ENR(TH1F* hADC, const char* calibdir){
	//This function converts the histogram from ADC domain to KeV domain. This is the version 2.0 in which can be chosen also the directory where there is the calibration.root to be used for the proper sample or BG run.
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
	
	
	
	Double_t* xbinsENR = new Double_t[hADC->GetNbinsX()+1]; //Array of low energy bin edges (plus one more required by the contructor)
	
	for (i=0 ; i<hADC->GetNbinsX(); i++){
		xbinsENR[i] = calib_fcn_fw->Eval(hADC->GetXaxis()->GetBinLowEdge(i));
	}
	
	
	xbinsENR[hADC->GetNbinsX()] = calib_fcn_fw->Eval(hADC->GetXaxis()->GetBinUpEdge(i));// The upper edge of the last energy bin
	
	//Using this constructor for the new histogram
	TH1F* hENR = new TH1F("hENR","",hADC->GetNbinsX(),xbinsENR);
	
	//Filling the new histogram
	for (i=hADC->GetXaxis()->GetFirst(); i<=hADC->GetXaxis()->GetLast(); i++){
				
		hENR -> Fill(calib_fcn_fw->Eval(hADC->GetBinCenter(i)),hADC->GetBinContent(i));
		//hENR -> SetBinError(hENR->FindBin(calib_fcn_fw->Eval(hADC->GetBinCenter(i))),tmp_rate_err);
		
	}
	
	//cout << "VACCA!" << endl;
	
	delete xbinsENR;
	
	return hENR; //The histogram which comes out must be rescaled for bin width -> do it outside this function
}
