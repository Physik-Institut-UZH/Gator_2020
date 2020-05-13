#include <TSystem.h>
#include <TH1F.h>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

TH1F* loadSpe(const char* dir, Double_t& aqtime){

	//-------------------------------------------------\\	
	// Load of the sample histogram from the SPE files \\
	// this version is only for calibration files      \\
	//-------------------------------------------------\\

	string tmpstr("");
	stringstream tmpsstr;
	
	aqtime=0;
	
	Double_t time_tmp=0, entry=0; 
	Int_t channel=0;
	
	vector<Double_t>* entries_tmp = new vector<Double_t>;
	vector<Double_t>* entries = new vector<Double_t>;
	
	string dirname(dir);
	string command("ls ");
	vector<string> spelist;
	
	command += dirname;
	command += string("*.Spe > tmplist");
	
	system(command.c_str());
	ifstream tmplist("tmplist");
	
	while(getline(tmplist,tmpstr)){
		spelist.push_back(tmpstr);
	}
	
	int nSpe = spelist.size();
	
	system("rm -f tmplist");
	 
	ifstream spe;
	
	
	
	for(int iSpe=0; iSpe<nSpe; iSpe++){
		
		infilename = spelist.at(iSpe);
		cout << "\nLoading file <" << infilename << ">" << endl;
		
		spe.open(infilename.c_str());
		
		if (spe.fail()){
			cout << "Error: can't open the file <" << infilename.c_str() << ">\nSkipping the entry!	" << endl;
			continue;//Skip the loop
		}
		
		entries_tmp->clear();
		
		int channels;
		
		for (Int_t line = 0; line<=11; line++) {
			//Here I go ahead in the file discarding the header lines
			getline(spe,tmpstr);
			
			if (line==9){//Acquisition live time (the first of the two numbers)
				tmpsstr.str("");
				tmpsstr << tmpstr;
				spe >> tmpstr;
				time_tmp = atof(tmpstrc_str());
				cout << "Acquisition time: " << time_tmp << " secs" << endl;
			}
			
			if (line==11){//Info on how many channels are acquired (the second of the two numbers)
				tmpsstr.str("");
				tmpsstr << tmpstr;
				spe >> tmpstr;
				spe >> tmpstr;
				channels = atoi(tmpstr.c_str());
				channels++;//The number of channels is 1 more of the last channel number
				cout << "Number of channels: " << channels << endl;
			}
		}
		
		//Loading the ADC counts from the file and put them in the vector entry_tmp
		while (spe.good()) {
			spe >> tmpstr;
			entry = atof(tmpstr.c_str());
			if(iSpe==0){
				entries -> push_back(entry);
				if (entries->size()==channels) break;
			} else {
				entries_tmp -> push_back(entry);
				if (entries_tmp->size()==entries_tmp) break;
			}
				
			if (!spe.good()) break;
		}
		
		if(iSpe==0){
			cout << "Data vector size: " << entries->size() << endl;
		}else{
			cout << "Data vector size: " << entries_tmp->size() << endl;
			for(Int_t i=0; i<entries_tmp->size(); i++){
				(*entries)[i] += entries_tmp->at(i);
			}
		}
		
		spe.close();
		
		aqtime += time_tmp; //Stored total total acquisition time
		
	}
	
	//Create and fill the histogram
	TH1F* histoMCA = new TH1F("histoMCA","Spectrum ADC",entries->size(),1,entries_tmp->size());
	for(Int_t i=0; i<entries->size(); i++){
		histoMCA->Fill(i+1,entries->at(i));
	}
	
	//-------------------------------------------------------------//	
	// Finished to load of the sample histogram from the SPE files //
	//-------------------------------------------------------------//

	
	delete entries_tmp;
	delete entries;
	
	return histoMCA;

}
///////////////////////////////////////////////////////////////////////////////////////////