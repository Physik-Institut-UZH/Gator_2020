{	//Script della puttana.... mi serviva da fare un po' di roba al volo!!!
	gROOT -> Reset();
	
	gROOT-> SetStyle("Plain");
	
	/*
	TFile* eff_file = new TFile("/Users/francesco/PhD/Gator/XeActivation/effic.root","read");
	TGraphErrors* gr_eff = (TGraphErrors*)eff_file->Get("gr_eff");
	eff_file -> Close();
	delete eff_file;
	
	TCanvas* c1 = new TCanvas("c1","");
	
	gr_eff -> SetTitle("");
	gr_eff -> GetXaxis() -> SetTitle("Energy [keV]");
	gr_eff -> GetYaxis() -> SetTitle("Efficiences");
	gr_eff -> Draw("AP");
	
	TF1* eff_func1 = new TF1("eff_func1","pol2",45,230);
	eff_func1 -> SetLineWidth(1);
	eff_func1 -> SetLineColor(2);
	
	TF1* eff_func2 = new TF1("eff_func2","pol2",220,1970);
	eff_func2 -> SetLineWidth(1);
	eff_func2 -> SetLineColor(2);
	
	gr_eff -> Fit(eff_func1,"R+");
	gr_eff -> Fit(eff_func2,"R+");
	
	TLine* borderline = new TLine(225,0,225,c1->cd()->GetUymax());
	borderline -> SetLineStyle(3);
	borderline -> SetLineColor(kBlue);
	borderline -> Draw("SAME");
	*/
	
	TFile* f = new TFile("./unitiTiGr1/unitiTiGr1_prelim.root","read");
	vector<Double_t>* v_bgcnts = (vector<Double_t>*)f->Get("v_bgcnts");
	vector<Double_t>* v_compcnts = (vector<Double_t>*)f->Get("v_compcnts");
	vector<Double_t>* v_effic = (vector<Double_t>*)f->Get("v_effic");
	vector<Double_t>* v_BRxEff = (vector<Double_t>*)f->Get("v_BRxEff");
	//TH1F* histoADC = (TH1F*)f->Get("histoADC");
	//histoADC -> SetDirectory(0);
	f -> Close();
	delete f;
	
	const Double_t tDay = 24*3600;
	const Double_t t0 = 6;
	const Double_t Mass= 14.250;
	
	Double_t times[] = {10,20,30};
	
	Int_t nlines = v_compcnts->size();
	Int_t npoints = sizeof(times)/sizeof(Double_t);
	
	Double_t Ld;
	
	cout << "\n\n" << endl;
	for(Int_t i=0; i<nlines; i++){
		cout << "|";
		for (Int_t k=0; k<npoints; k++){
			
			Ld = 1000*(2.86 + 4.87*TMath::Sqrt(1.36 + (v_compcnts->at(i) + v_bgcnts->at(i))*(times[k]/t0)))/(v_BRxEff->at(i)*Mass*times[k]*tDay); //In units of mBq/kg
			
			cout << "  " << Ld <<"  |";
		}
		cout << endl;
		
	}
	
	/*
	gROOT -> ProcessLine(".L ~../convert_histo_ENR.cxx");
	
	TH1F* histoENR = convert_histo_ENR(histoADC);
	
	const Double_t actimeDay = 6;
	const Double_t actime = actimeDay*tDay;
	
	
	histoENR -> Scale(1/actimeDay);
	histoENR -> GetXaxis() -> SetTitle("Energy [keV]");
	
	TCanvas* c2 = new TCanvas("c2","");
	c2 -> Divide(1,2);
	c2 -> cd(1) -> SetLogy();
	histoENR -> GetYaxis() -> SetTitle("Rate [counts/sec]");
	histoENR -> Draw();
	c2 -> cd(2) -> SetLogy();
	
	TH1F* histoENR2 = histoENR -> Clone("histoENR2");
	histoENR2 -> GetYaxis() -> SetTitle("Rate [counts/(keV sec)]");
	histoENR2 -> Draw();
	*/
	
}