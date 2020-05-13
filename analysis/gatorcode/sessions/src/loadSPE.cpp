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

TH1F* loadSPE(const char* dir, Double_t& aqtime){

	//-------------------------------------------------//	
	// Load of the sample histogram from the SPE files //
	//-------------------------------------------------//

	Char_t buffer[1000];
	
	aqtime=0;
	
	Double_t time_tmp=0, entry=0; 
	Int_t channel=0;
	
	vector<Double_t>* entries_tmp = new vector<Double_t>;
	vector<Double_t>* entries = new vector<Double_t>;
	
	string dirname = dir;
	string command("ls ");
	string infilename;
	
	command += dirname;
	command += "*.SPE";
	
	ifstream spe;
	
	FILE* fpp = gSystem -> OpenPipe(command.c_str(),"r"); //Hard coded!!! Find a way to implement a simpler way to set the directory
	
	Int_t filenum =0; //Counts the files.SPE read
	
	Char_t time_tmp_str[100], entry_str[100];
	while (!feof(fpp)){
		fgets(buffer,sizeof(buffer),fpp);
		if (feof(fpp)){ break;}
		infilename = buffer;
		infilename = infilename.substr(0,infilename.find("\n")); //Removed the carriage at the end of filename
		cout << "\nOpening file <" << infilename.c_str() << ">" << endl;
		
		spe.open(infilename.c_str());
		
		if (spe.fail()){
			cout << "Error: can't open the file <" << infilename.c_str() << ">\nSkipping the entry!" << endl;
			continue;//Skip the loop
		}
		for (Int_t i = 0; i<=11; i++) {
			if (i==9){
				spe >> time_tmp_str;
				time_tmp = atof(time_tmp_str);
			}
			
			//Here I go ahead in the file discarding the header lines
			spe.getline(buffer,sizeof(buffer));
		}
		
		//cout << "Acquisition time: " << time_tmp << " secs" << endl;
		
		entries_tmp->clear();
		
		//Loading the ADC counts from the file and put them in the vector entry_tmp
		while (spe.good()) {
			if (spe.eof()) break;
				channel++;
				spe >> entry_str;
				entry = atof(entry_str);
				if(filenum==0){
					if (entries->size()>=16384) break; //According to calibration... hard coded ==> be care!!!
					entries -> push_back(entry);
				} else {
					if (entries_tmp->size()>=16384) break;
					entries_tmp -> push_back(entry);
				}
				
			if (!spe.good()) break;
		}
		
		if(filenum==0){
			//cout << "Number of channels: " << entries->size() << endl;
		}else{
			//cout << "Number of channels: " << entries_tmp->size() << endl;
			for(Int_t i=0; i<entries_tmp->size(); i++){
				(*entries)[i] += entries_tmp->at(i);
			}
		}
		
		spe.close();
		
		filenum++;
		
		aqtime += time_tmp; //Stored total total acquisition time
		
	}
	
	//Create and fill the histogram
	TH1F* histoADC = new TH1F("histoADC","Spectrum ADC",entries_tmp->size(),1,entries_tmp->size());
	for(Int_t i=0; i<entries->size(); i++){
		histoADC->Fill(i+1,entries->at(i));
	}
	
	//-------------------------------------------------------------//	
	// Finished to load of the sample histogram from the SPE files //
	//-------------------------------------------------------------//

	
	delete entries_tmp;
	delete entries;
	
	return histoADC;

}