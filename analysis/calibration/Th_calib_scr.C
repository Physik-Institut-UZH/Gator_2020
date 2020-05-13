{
	
	gROOT->Reset();
	
	gROOT->ProcessLine(".L prova.cc");
	
	//Creation of an histogram with the ASCII data of the Th228 source. Draw it in the second pad.
	
	Double_t time = 0; //Acquisition time of the source in seconds
	string filename("228Th-TF657_20120619.txt");
	TCanvas* c1 = new TCanvas("c1","228Th source calibration (ADC)");
	c1->SetLogy();
	TH1F* hADC = histogen(filename,time);
	c1->Modified();
	c1->Update();
	
	
	const Double_t hour = 3600; //For the conversion of seconds in to hours
	const Double_t day = 24*hour;
	
	//Acquisition time in days
	time = time/day;
	
	Int_t i=0; //General iterator index
	
	TFile* f = new TFile("calibration.root","read");
	
	TF1* calib_fcn_fw = (TF1*)f->Get("calib_fcn_fw");
	
	f -> Close();
	
	delete f;
	
	gROOT->ProcessLine("calib_fcn_fw");
	
	Double_t* xbinsENR = new Double_t[hADC->GetNbinsX()+1]; //Array of low energy bin edges (plus one more required by the contructor)
	
	for (i=0 ; i<hADC->GetNbinsX(); i++){
		xbinsENR[i] = calib_fcn_fw->Eval(hADC->GetXaxis()->GetBinLowEdge(i));
	}
	
	
	xbinsENR[hADC->GetNbinsX()] = calib_fcn_fw->Eval(hADC->GetXaxis()->GetBinUpEdge(i));// The upper edge of the last energy bin
	
	//Using this constructor for the new histogram
	TH1F* hENR = new TH1F("hENR","^{228}Th calibration",hADC->GetNbinsX(),xbinsENR);
	
	//Filling the histogram recalculating the errors
	Double_t tmp_ENR,tmp_bin,tmp_rate,tmp_rate_err,tmp_binwidth;
	for (i=hADC->GetXaxis()->GetFirst(); i<=hADC->GetXaxis()->GetLast(); i++){
		
		tmp_ENR = calib_fcn_fw->Eval(hADC->GetBinCenter(i));
		tmp_bin = hENR->FindBin(tmp_ENR);
		tmp_binwidth = hENR->GetBinWidth(tmp_bin); //Width of the bin in KeV
		tmp_rate = hADC->GetBinContent(i)/(tmp_binwidth*time);
		tmp_rate_err = hADC->GetBinError(i)/(tmp_binwidth*time);
		if (i>1500 && i<=1510){
			cout<<"\n"<<tmp_ENR<<"\t"<<tmp_bin<<"\t"<<tmp_binwidth<<"\t"<<tmp_rate<<endl;
		}
		hENR -> SetBinContent(tmp_bin,tmp_rate);
		hENR -> SetBinError(tmp_bin,tmp_rate_err);
		
	}
	
	hENR -> GetXaxis() -> SetTitle("Energy [KeV]");
	hENR -> GetYaxis() -> SetTitle("Rate [KeV^{-1} day^{-1}]");
	
	TCanvas* c2 = new TCanvas("c2","228Th source calibration (KeV)");
	hENR -> Draw();
}