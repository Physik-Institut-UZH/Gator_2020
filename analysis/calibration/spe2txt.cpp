{
	gROOT -> Reset();
	
	gROOT -> ProcessLine(".L /Users/francesco/PhD/Gator/data_analysis/calibrations/src/loadSpe.cpp");
	
	Double_t time;
	TH1F* h1 = loadSpe("./",time);
	
	Int_t nbins = h1->GetNbinsX();
	
	cout << "Number of bins: " << nbins << endl;
	
	char tmpstr[100] = "";
	
	ofstream outxt("Th-calib-20121004.txt");
	
	sprintf(tmpstr,"%f",time);
	
	outxt << tmpstr << endl;
	
	for(Int_t i=1; i<nbins; i++){
		sprintf(tmpstr,"%d",(Int_t)h1->GetBinContent(i));
		outxt << i << "\t" << tmpstr << endl;
	}
	
	outxt.close();
}