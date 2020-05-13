Double_t peakFitFunc(Double_t* x,Double_t* par){
	
	Double_t E,P,Gamma,A,sigma,beta,S,m,q;
	
	E = x[0];
	
	P = par[0];
	Gamma = par[1];
	A = par[2];
	sigma = par[3];
	beta = par[4];
	S = par[5];
	m = par[6];
	q = par[7];
	
	
	
	Double_t result = Gamma*//General amlitude of the peak
	((1-A)*TMath::Gaus(E,P,sigma)+//Gaussian peak (normalized)
	 A*TMath::Exp((E-P)/beta)*TMath::Erfc(((E-P)/beta)+(sigma/(sqrt(2)*beta))))+//Low eff collecting charge tail
	 S*TMath::Erfc((E-P)/(sqrt(2)*sigma))+//Step modelled background
	 m*E+q;//Linear modelled background
	
	return result;
}
//////////////////////////////////////////////////////////////////////////////////


void initFitFunc(TH1F* histo,TF1* lineFit){
	
	Int_t first_bin = histo -> GetXaxis() -> GetFirst();
	Int_t last_bin = histo -> GetXaxis() -> GetLast();
	
	cout << "\nFirst bin: " << first_bin << endl;
	cout << "Last bin: " << last_bin << endl;
	
	
	//Take the means in two windows wide 10% of the whole histo showed "x range"
	Double_t low_mean=0,high_mean=0;
	
	for (Int_t i=first_bin; i<first_bin+(Int_t)(0.1*(last_bin-first_bin)); i++) {
		low_mean += histo->GetBinContent(i)/((Int_t)(0.1*(last_bin-first_bin)));
	}
	
	for (Int_t i=last_bin;i>last_bin-(Int_t)(0.1*(last_bin-first_bin));i--){
		high_mean += histo->GetBinContent(i)/((Int_t)(0.1*(last_bin-first_bin)));
	}
	
	cout << "\nLow mean value: " << low_mean << endl;
	cout << "High mean value: " << high_mean << endl;
	
	cout << "Line center init: " << (Double_t)histo->GetMaximumBin() << endl;
	
	Double_t Gamma = histo->GetMaximum() - 0.5*(low_mean+high_mean);
	
	lineFit -> SetParameter(0,(Double_t)histo->GetMaximumBin());
	
	lineFit -> SetParameter(1,Gamma); //
	lineFit -> SetParLimits(1,0.,histo->GetMaximum());
	
	lineFit -> SetParameter(2,0.05); //This parameter should be from 0 to 1
	lineFit -> SetParLimits(2,0.,1.);
	
	lineFit -> SetParameter(3,10.); //Generally this value allow the fit to converge
	lineFit -> SetParLimits(3,0.,100); //Good interval, largge enough for fit converging
	
	lineFit -> SetParameter(4,4.); //It seems that this parameter make the fit converging => No idea how to inizialize in a cleaner way this parameter
	lineFit -> SetParLimits(4,0.,(Double_t)(last_bin-first_bin));
	
	lineFit -> SetParameter(5,TMath::Abs(low_mean-high_mean)); //Starting amplitude of the erfc
	lineFit -> SetParLimits(5,0.,10*TMath::Abs(low_mean-high_mean));
	
	lineFit -> SetParameter(6,(high_mean-low_mean)/(last_bin-first_bin));
	
	lineFit -> SetParameter(7,low_mean-first_bin*(high_mean-low_mean)/(last_bin-first_bin));
	
	return;
	
}
//////////////////////////////////////////////////////////////////////////////////


Double_t gausFunc (Double_t* x,Double_t* par){
	
	Double_t E = x[0];
	
	Double_t P = par[0];
	Double_t sigma = par[1];
	Double_t A = par[2];
	
	return A*TMath::Gaus(E,P,sigma);
	
}

Double_t tailFunc (Double_t* x,Double_t* par){
	
	Double_t E = x[0];
	
	Double_t P = par[0];
	Double_t sigma = par[1];
	Double_t beta = par[2];
	Double_t A = par[3];
	
	return A*TMath::Exp((E-P)/beta)*TMath::Erfc(((E-P)/beta)+(sigma/(sqrt(2)*beta)));
}

Double_t stepFunc (Double_t* x,Double_t* par){
	
	Double_t E = x[0];
	
	Double_t P = par[0];
	Double_t sigma = par[1];
	Double_t S = par[2];
	
	return S*TMath::Erfc((E-P)/(sqrt(2)*sigma));
}
//////////////////////////////////////////////////////////////////////////////////


Double_t resolError(TF1* ff,TFitResultPtr& resFit){
	
	Double_t c = ff->GetParameter(0);
	Double_t ce = ff->GetParError(0);
	Double_t w = ff->GetParameter(3);
	Double_t we = ff->GetParError(3);
	Double_t cw_cov = resFit -> CovMatrix(0,3);
	
	return TMath::Sqrt(TMath::Power(ce/c,2)+TMath::Power(we/w,2)+2*cw_cov*(-w/TMath::Power(c,3)));
}