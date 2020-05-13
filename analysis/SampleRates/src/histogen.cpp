#include <fstream>
#include <iostream>
#include <vector>

#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TFile.h>
//#include <TTree.h>
#include <TH1F.h>
//#include <TH1D.h>
//#include <TH2D.h>
#include <TF1.h>
#include <TLegend.h>
//#include <TCut.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
//#include <TIterator.h>
//#include <TList.h>
//#include <TMultiGraph.h>
#include <TMath.h>
#include <TApplication.h>
//#include <TSQLServer.h>
//#include <TSQLResult.h>
//#include <TSQLRow.h>
//#include <TLatex.h>
//#include <TTimeStamp.h>
#include <TLine.h>
//#include <TVirtualFitter.h>
//#include <TGaxis.h>
//#include <TMarker.h>
#include <TFitResult.h>


using namespace std;

TH1F* histogen(const Char_t* filename, Double_t& time){
	//This definition of histogen() is only for files.txt of Gator spectrum in which the first line is the acquisition time in seconds.
	
	ifstream datafile;
	
	Double_t counts, entries, ADCch;
	vector<Double_t>* ADCchVec = new vector<Double_t>;
	vector<Double_t>* entriesVec = new vector<Double_t>;
	
	cout << "Opening the file <" << filename << ">\n\n" << endl;
	
	datafile.open(filename);
	
	if(datafile.fail()){
		cout << "Can't open file <" << filename << endl;
		exit(1);
	}
	
	
	Char_t buffer[20];
	
	
	Int_t i=0;
	while(datafile.good()) {
		if(datafile.eof()){ 
			cout << "EOF at line " << (i+1) << "\n" << endl;
			break;
		}
		
		if(i == 0){
			datafile >> buffer; //The first line is the time in seconds
			time = atof(buffer);
			i++;
		}else{
			datafile >> buffer;
			ADCch = atof(buffer);
			datafile >> buffer;
			entries = atof(buffer);
			//cout << ADCch << "\t" << entries << endl;
			ADCchVec -> push_back(ADCch);
			entriesVec -> push_back(entries);
			i++;
		}
		
		if(datafile.eof()) break;
	}
	datafile.close();
	cout << "Number of channels = " << ADCchVec->size() << "\n\n" << endl;
	
	
	Int_t nbins = ADCchVec -> size();
	TH1F* histo = new TH1F("histo",filename,nbins,1,nbins);	
	
	for(Int_t i=0; i<ADCchVec->size(); i++){
		histo -> Fill(ADCchVec->at(i), entriesVec->at(i));
	}
	
	//histo -> Draw();
	
	delete ADCchVec;
	delete entriesVec;
	
	return histo;
	
}
///////////////////////////////////////////////////////////////////////////////////////////
