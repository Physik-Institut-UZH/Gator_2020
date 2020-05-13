#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLegend.h>
#include <TCut.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TIterator.h>
#include <TList.h>
#include <TMultiGraph.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <TMath.h>
#include <TApplication.h>
#include <TSQLServer.h>
#include <TSQLResult.h>
#include <TSQLRow.h>
#include <TLatex.h>
#include <TTimeStamp.h>
#include <TLine.h>
#include <TVirtualFitter.h>
#include <TGaxis.h>
#include <TMarker.h>
#include <TFitResult.h>


using namespace std;


void wait();
void filechoice();
TH1F* loadSPE2(const char*);

TCanvas* c1;


int main()
{
	TApplication theApp("App",0,0);
	filechoice();
	
	theApp.Run();
	
	return 0;
}


void wait()
{
	c1 -> Update(); c1 -> WaitPrimitive();
}
//////////////////////////////////////////////////////////////////////////////////////////


////////////---------- SCRIPT FUNCTION ------------//////////////
void filechoice(){
	
	FILE* fpp = gSystem -> OpenPipe("ls *.SPE","r");
	
	TFile* calfile = new TFile("/Users/francesco/PhD/Gator/data_analysis/calibrations/calibration.root","read");
	TF1* calib_fcn_bw = (TF1*)calfile -> Get("calib_fcn_bw");
	calfile -> Close();
	delete calfile;
	
	TH1F* histoADC;
	
	TGraph* gr_rates = new TGraph();
	
	vector<Double_t>* ratevec = new vector<Double_t>;
	vector<string>* filenamevec = new vector<string>;
	
	Char_t buffer[100];
	string spename;
	
	Double_t integrstart,integrstop,cntrate;
	
	Int_t filenum=0;
	while(!feof(fpp)){
		if (feof(fpp)) break;
		
			fgets(buffer,sizeof(buffer),fpp);
			spename = buffer;
			spename = spename.substr(0,spename.find("\n")); //Removed the carriage at the end of filename
			filenamevec -> push_back(spename);
			cout << "\n\nOpening file <" << spename.c_str() << ">" << endl;
			
			histoADC = loadSPE2(spename.c_str());
			
			integrstart = calib_fcn_bw -> Eval(30); //Start to count from 40keV
			integrstop = histoADC -> GetXaxis() -> GetXmax();
			integrstop = calib_fcn_bw -> Eval(2750);
			
			
			cntrate = histoADC -> Integral(integrstart,integrstop);
			
			ratevec -> push_back(cntrate);
			
			gr_rates -> SetPoint(filenum+1,(Double_t)filenum,cntrate);
			
			filenum++;
		
			delete histoADC; //I don't need it anymore
			
		if (feof(fpp)) break;
	}
	
	fclose(fpp);
	
	
	//The following lines are for closing the application when the canvas c1 is closed.
	#ifndef __CINT__
	c1 -> Connect("TCanvas", "Closed()", "TApplication", gApplication,
				  "Terminate()");
	#endif
	
	
	c1 = new TCanvas("c1","");
	gr_rates -> SetTitle("Background file rates");
	gr_rates -> GetXaxis() -> SetTitle("File number");
	gr_rates -> GetYaxis() -> SetTitle("Rates [cnts/sec]");
	gr_rates -> SetMarkerStyle(7);
	gr_rates -> Draw("AP");
	
	Double_t xlow = gr_rates->GetXaxis()->GetXmin();
	Double_t xup = gr_rates->GetXaxis()->GetXmax();
	
	Double_t mean = 0;
	Double_t mean2 = 0;
	
	Int_t npoints = ratevec->size();
	
	for (Int_t i=0; i<npoints; i++){
		
		mean += ratevec->at(i)/npoints;
		mean2 += (ratevec->at(i))*(ratevec->at(i));
	}
	
	Double_t rms = TMath::Sqrt((mean2/(npoints-1))-((mean)*(mean)*npoints/(npoints-1)));
	
	cout << "\n\n\nMean = " << mean << endl;
	cout << "Low limit = " << mean - rms << endl;
	cout << "Up limit = " << mean + rms << endl;
	
	
	TLine* tl1 = new TLine(xlow,mean,xup,mean);
	tl1 -> SetLineStyle(3);
	tl1 -> SetLineColor(kBlue);
	tl1 -> Draw("SAME");
	
	
	TLine* tl2 = new TLine(xlow,mean+rms,xup,mean+rms);
	tl2 -> SetLineStyle(3);
	tl2 -> SetLineColor(kRed);
	tl2 -> Draw("SAME");
	
	wait();
	
	

	ofstream outfile;
	outfile.open("./acceptedfiles");
	
	for(Int_t i=0; i<ratevec->size(); i++){
		if(ratevec->at(i) < mean+2*rms){
			outfile << (*filenamevec)[i] << endl;
		}
	}
	
	outfile.close();
	
	outfile.open("./badfiles");
	
	for(Int_t i=0; i<ratevec->size(); i++){
		if(ratevec->at(i) > mean+2*rms){
			outfile << (*filenamevec)[i] << endl;
		}
	}
	
	outfile.close();
	
	
	delete filenamevec;
	delete ratevec;
	
	return;
	
}
////////////---------- SCRIPT FUNCTION FINISHED ------------//////////////



TH1F* loadSPE2(const char* filename){

	//---------------------------------------------------//	
	// Load of the sample histogram from the SPE files   //
	// This version is only to the histo for the routine //
	// filechoise.cpp                                    //
	//---------------------------------------------------//

	Char_t buffer[100];

	ifstream spe;
	
	spe.open(filename);
	
	vector<Double_t>* entries = new vector<Double_t>;
	
	Double_t entry, time;
	
	Int_t channel=0;
	
	
	if (spe.fail()){
		cout << "Error: can't open the file <" << filename << ">" << endl;
		exit(1);
	}
	
	Char_t timestr[100];
	for (Int_t i = 0; i<=11; i++) {
		if (i==9){
			spe >> timestr;
			time = atof(timestr);
		}
			
		//Here I go ahead in the file discarding the header lines
		spe.getline(buffer,sizeof(buffer));
	}
	
		
	cout << "Acquisition time: " << time << " secs" << endl;
	
		
	//Loading the ADC counts from the file and put them in the vector entry_tmp
	
	Char_t entrystr[100];
	while (spe.good()) {
		if (!spe.good()) break;
		
		channel++;
		spe >> entrystr;
		entry = atof(entrystr);
		entries -> push_back(entry);
		
		if (!spe.good()) break;
	}
	
		
		
	spe.close();
		
	
	cout << "Number of channels: " << entries->size() << endl;
	
	//Create and fill the histogram
	TH1F* histoADC = new TH1F("histoADC","",entries->size()-1,1,entries->size()-1);
	for(Int_t i=0; i<entries->size()-1; i++){
		histoADC->Fill(i+1,entries->at(i));
	}
	
	histoADC -> Scale(1/time);
	
	delete entries;
	
	return histoADC;

}