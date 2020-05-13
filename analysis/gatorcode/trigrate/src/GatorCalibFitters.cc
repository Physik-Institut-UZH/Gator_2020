#include <TF1.h>
#include <TH1F.h>
#include <TMath.h>
#include <TGraph.h>
#include <TGraphErrors.h>

#include "TH1D.h"

#ifndef SCRIPT
#include "GatorStructs.h"
#endif

using namespace std;

///////////Definitions of the functions for the plot//////////////
Double_t peakFitFuncA(Double_t* x,Double_t* par){
	
	Double_t E,P,T,A,sigma,beta,S,C;
	
	E = x[0];
	
	P = par[0];
	A = par[1];
	T = par[2];
	sigma = par[3];
	beta = par[4];
	S = par[5];
	C = par[6];
	
	double gauss = TMath::Exp( -pow((E-P)/sigma,2)/2 );
	//double tail = TMath::Exp( (pow(sigma/beta,2)/2) + ((E-P)/beta) ) * TMath::Erfc(  ( (E-P)*beta+pow(sigma,2) )/( sqrt(2)*sigma*beta )  );
	//double tail = TMath::Exp( ((E-P)/beta) ) * TMath::Erfc(  ( (E-P)*beta+pow(sigma,2) )/( sqrt(2)*sigma*beta )  );
	double tail = TMath::Exp( ((E-P)/beta) ) * TMath::Erfc( (((E-P)/sigma) + (sigma/beta))/sqrt(2) );
	double step = TMath::Erfc((E-P)/(sqrt(2)*sigma));
	
	return A*(gauss + T*tail) + S*step + C;
	
	//return A*( TMath::Gaus(E,P,sigma) + R * TMath::Exp(beta*(E-P))*TMath::Erfc((E-(P-beta*sigma*sigma))/(sqrt(2)*sigma)) ) + C;
	
}
//////////////////////////////////////////////////////////////////////////////////


Double_t peakFitFuncB(Double_t* x,Double_t* par){
	
	Double_t E,P,T,A,sigma,Gamma,S,C;
	
	E = x[0];
	
	P = par[0];
	A = par[1];
	T = par[2];
	sigma = par[3];
	Gamma = par[4];
	S = par[5];
	C = par[6];
	
	double gauss = TMath::Gaus( E,P,sigma );
	//double tail = TMath::Exp( (pow(sigma/beta,2)/2) + ((E-P)/beta) ) * TMath::Erfc(  ( (E-P)*beta+pow(sigma,2) )/( sqrt(2)*sigma*beta )  );
	//double tail = TMath::Exp( ((E-P)/beta) ) * TMath::Erfc(  ( (E-P)*beta+pow(sigma,2) )/( sqrt(2)*sigma*beta )  );
	double tail = TMath::Exp( ((E-P)*Gamma) ) * TMath::Erfc( ( E-(P-Gamma*sigma*sigma) )/(sqrt(2)*sigma) );
	double step = TMath::Erfc( (E-P)/(sqrt(2)*sigma) );
	
	//return A*((1-T)*gauss + T*tail) + S*step + C;
	return A*(gauss + T*tail) + S*step + C;
	
	//return A*( TMath::Gaus(E,P,sigma) + R * TMath::Exp(beta*(E-P))*TMath::Erfc((E-(P-beta*sigma*sigma))/(sqrt(2)*sigma)) ) + C;
	
}



//----------Initialization functions for parameters-----------//

void costInit(TH1D* histo, CalibLine& line){
	
	Double_t firstbin = histo->FindBin(line.MCAlowch); 
	Double_t lastbin = histo->FindBin(line.MCAupch);
	
	
	Double_t left_mean = 0.;
	Double_t right_mean = 0.;
	
	/*
	for(int bin=firstbin; bin<firstbin+10; bin++){
		left_mean += (histo->GetBinContent(bin))/10.;
	}
	for(int bin=lastbin-9; bin<=lastbin; bin++){
		right_mean += (histo->GetBinContent(bin))/10.;
	}
	
	line.cost = TMath::Min(left_mean,right_mean);
	*/
	
	right_mean = histo->GetBinContent(lastbin);
	
	line.cost = right_mean;
	
	return;
}
//////////////////////////////////////////////////////////////////////////////////////


void stepInit(TH1D* histo, CalibLine& line){
	
	Double_t firstbin = histo->FindBin(line.MCAlowch); 
	Double_t lastbin = histo->FindBin(line.MCAupch);
	
	int nBins = 3;
	
	Double_t left_mean = 0.;
	Double_t right_mean = 0.;
	
	for(int iBin=0; iBin<nBins; iBin++){
		left_mean += histo->GetBinContent(firstbin+iBin);
		right_mean += histo->GetBinContent(lastbin-iBin);
	}
	
	line.step = TMath::Max( 0.0, left_mean-right_mean );
	
	/*
	if((left_mean - right_mean)<=0){
		line.step = right_mean;
	}else{
		line.step = (left_mean - right_mean);
	}
	*/
	
	return;
}
/////////////////////////////////////////////////////////////////////////////////////


void amplInit(TH1D* histo, CalibLine& line){
	//This should always be run after the function "costInit"
	double max =0.;
	
	Double_t firstbin = histo->FindBin(line.MCAlowch); 
	Double_t lastbin = histo->FindBin(line.MCAupch);
	
	for(int bin=firstbin; bin<=lastbin; bin++){
		if(max < histo->GetBinContent(bin)) max = histo->GetBinContent(bin);
	}
	
	line.ampl = max-line.cost;
	//line.tail = 0.1*line.ampl;
	
	return;
}
//////////////////////////////////////////////////////////////////////////////////////


void sigmaInit(TH1D* histo, CalibLine& line){
	
	Double_t firstbin = histo->FindBin(line.MCAlowch); 
	Double_t lastbin = histo->FindBin(line.MCAupch);
	
	double max =0.;
	int maxbin;
	
	for(int bin=firstbin; bin<=lastbin; bin++){
		if(max < histo->GetBinContent(bin)){
			max = histo->GetBinContent(bin);
			maxbin = bin;
		}
	}
	
	/*
	int bin = maxbin;
	while(histo->GetBinContent(bin)>max/2.){
		bin--;
	}
	double lowval = histo->GetBinCenter(bin);
	
	bin = maxbin;
	while(histo->GetBinContent(bin)>max/2.){
		bin++;
	}
	double upval = histo->GetBinCenter(bin);
	
	line.sigma = (upval - lowval)/2; //This is not the sigma but a good starting point for the fit
	*/
	
	//line.sigma = 0.5*( histo->(GetBinCenter(histo->FindLastBinAbove(max*exp(-0.5)))) - histo->(GetBinCenter(histo->FindFirstBinAbove(max*exp(-0.5)))) );
	
	line.sigma = histo->GetBinCenter(histo->FindLastBinAbove(max*exp(-0.5) ) ) - histo->GetBinCenter(maxbin);
	
	return;
}
/////////////////////////////////////////////////////////////////////////////////////


Double_t resolFunc (Double_t* x,Double_t* par){
	
	Double_t E = x[0];
	
	Double_t A = par[0];
	Double_t B = par[1];
	Double_t C = par[2];
	
	return TMath::Sqrt(A*E*E + B*E + C);
}