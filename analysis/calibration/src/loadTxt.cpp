#include <TROOT.h>
#include <TH1F.h>
#include <TCanvas.h>

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;


TH1F* loadTxt(string& filename, Double_t& time){
	//This definition of loadTxt() is only for files of Gator spectrum in which the first line is the acquisition time in secons.
	
	ifstream datafile;
	
	Double_t counts, entries, ADCch;
	vector<Double_t>* ADCchVec = new vector<Double_t>;
	vector<Double_t>* entriesVec = new vector<Double_t>;
	
	cout << "Opening the file <" << filename.c_str() << ">" << endl;
	
	string timeStr, ADCchStr, entriesStr;
	
	datafile.open(filename.c_str());
	Int_t i = 0;
	while(!datafile.eof()) {
		if(i==0){
			datafile >> timeStr;
			time = atof(timeStr.c_str());
		}else{
			datafile >> ADCchStr;
			datafile >> entriesStr;
			ADCch = atof(ADCchStr.c_str());
			entries = atof(entriesStr.c_str());
			ADCchVec -> push_back(ADCch);
			entriesVec -> push_back(entries);
		}
		i++;
	}
	datafile.close();
	cout << "Number of channels = " << ADCchVec->size() << "\n\n" << endl;
	
	
	Int_t nlines = ADCchVec -> size();
	TH1F* histo = new TH1F("histo",filename.c_str(),nlines,1,nlines); //nlines take into account also the first line which is the data acquisition time
	
	
	for(Int_t i=0; i<ADCchVec->size(); i++){
		histo -> Fill(ADCchVec->at(i), entriesVec->at(i));
	}
	
	histo -> Draw();
	
	return histo;
	
}

///////////////////////////////////////////////////////////////////////////////////////////