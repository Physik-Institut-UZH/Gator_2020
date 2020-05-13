#include <TF1.h>
#include <TH1F.h>
#include <TMath.h>
#include <TGraph.h>
#include <TGraphErrors.h>

using namespace std;

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
	
	
	Double_t firstval = histo->GetBinLowEdge(histo->GetXaxis()->GetFirst()); 
	Double_t lastval = histo->GetBinLowEdge(histo->GetXaxis()->GetLast()) + histo->GetBinWidth(histo->GetXaxis()->GetLast());
	
	Double_t ROIsize = lastval - firstval;
	
	Double_t low_mean = histo -> Integral(firstval,firstval+0.05*ROIsize)/(0.05*ROIsize);
	
	Double_t up_mean = histo -> Integral(lastval-0.05*ROIsize,lastval)/(0.05*ROIsize);
	
	return histo->GetMaximum() - 0.5*(low_mean+up_mean);
	
}
//////////////////////////////////////////////////////////////////////////////////////

Double_t initCost(TH1F* histo){
	
	Double_t firstval = histo->GetBinLowEdge(histo->GetXaxis()->GetFirst()); 
	Double_t lastval = histo->GetBinLowEdge(histo->GetXaxis()->GetLast()) + histo->GetBinWidth(histo->GetXaxis()->GetLast());
	
	Double_t ROIsize = lastval - firstval;
	
	Double_t low_mean = histo -> Integral(firstval,firstval+0.05*ROIsize)/(0.05*ROIsize);
	
	Double_t up_mean = histo -> Integral(lastval-0.05*ROIsize,lastval)/(0.05*ROIsize);
	
	return 0.5*(low_mean+up_mean);
}
//////////////////////////////////////////////////////////////////////////////////////

Double_t initStep(TH1F* histo, Double_t sigma, Double_t Center){
	
	Double_t firstval = histo->GetBinLowEdge(histo->GetXaxis()->GetFirst()); 
	Double_t lastval = histo->GetBinLowEdge(histo->GetXaxis()->GetLast()) + histo->GetBinWidth(histo->GetXaxis()->GetLast());
	
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
	
	return TMath::Sqrt(A*TMath::Power(E,2) + B*E + C);
}
//////////////////////////////////////////////////////////////////////////////////

void resolInit2(TF1* resolFnc, vector<Double_t>* v_x, vector<Double_t>* v_y){
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
	gr -> Fit(func);
	
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
