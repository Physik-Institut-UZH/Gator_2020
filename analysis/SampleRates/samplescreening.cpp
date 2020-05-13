{
	
	gROOT -> Reset();
	gROOT -> ProcessLine(".L ~/PhD/Gator/data_analysis/background/convert_histo_ENR.cxx");
	gROOT -> ProcessLine(".L detectline.cxx");
	
	const Double_t hour = 3600; //Seconds in an hour
	const Double_t day = 24*hour; //Seconds in a day
	
	string calibfilename("~/PhD/Gator/data_analysis/calibrations/calibration.root");
	
	//Loading from the file.root the BG histo
	TFile* bg_file = new TFile("~/PhD/Gator/data_analysis/background/background.root","read");
	TH1F* bg_histo_ADC = (TH1F*)bg_file->Get("bg_histo_ADC");
	bg_histo_ADC -> SetDirectory(0);//To make it usable also when the root file is closed!!!
	TH1F* bg_histo_ENR_vis = (TH1F*)bg_file->Get("bg_histo_ENR_vis");
	bg_histo_ENR_vis -> SetDirectory(0);//To make it usable also when the root file is closed!!!
	bg_file -> Close();
	delete bg_file;
	
	
	//Loading from the file.root the calibration functions
	TFile* cal_file = new TFile(calibfilename.c_str(),"read");
	TF1* calib_fcn_fw = (TF1*)cal_file->Get("calib_fcn_fw");
	TF1* calib_fcn_bw = (TF1*)cal_file->Get("calib_fcn_bw");
	TF1* resol_ADC_func = (TF1*)cal_file->Get("resol_ADC_func");
	cal_file -> Close();
	delete cal_file;
	
	
	//Vector of the lines in KeV on which work for the activities
	vector<Double_t>* linesENR = new vector<Double_t>; //In energy from litterature
	vector<Double_t>* linesBRxEff = new vector<Double_t>; //BR*Eff from simulations
	vector<Double_t>* linesADC = new vector<Double_t>; //Converted in ADC channel
	vector<Double_t>* sigmaADC = new vector<Double_t>;
	
	ifstream configfile("configscreening"); // Here inside there are the lines to be loaded and the BR*Eff
	
	if(configfile.fail()){
		cout<<"\nError can't open file <configscreening>"<<endl;
		exit(1);
	}
	
	Double_t storevar;
	while(configfile.good()){
		configfile >> (Double_t)storevar;
		linesENR -> push_back(storevar);
		configfile >> (Double_t)storevar;
		linesBRxEff -> push_back(storevar);
		if(configfile.eof()) break;
	}
	
	for(Int_t i=0; i<linesENR->size(); i++){
		storevar = calib_fcn_bw->Eval(linesENR->at(i));
		linesADC -> push_back(storevar);
		storevar = resol_ADC_func->Eval(storevar);
		sigmaADC -> push_back(storevar);
	}

//------------------------------------------------//	
// Load of the sample histogram from the SPE files//
//------------------------------------------------//

	Char_t buffer[100];
	
	Double_t time=0, time_tmp=0, entry=0; 
	Int_t channel=0;
	
	vector<Double_t>* entries_tmp = new vector<Double_t>;
	vector<Double_t>* entries = new vector<Double_t>;
	
	string infilename;
	
	ifstream spe;
	
	FILE* fpp = gSystem -> OpenPipe("ls ./TiCastle/*.SPE","r"); //Hard coded!!! Find a way to implement a simpler way to set the directory
	
	Int_t filenum =0; //Counts the files.SPE read
	
	while (!feof(fpp)){
		if (feof(fpp)){ break;}
		fgets(buffer,sizeof(buffer),fpp);
		infilename = buffer;
		infilename = infilename.substr(0,infilename.find("\n")); //Removed the carriage at the end of filename
		cout << "\nOpening file <" << infilename.c_str() << ">" << endl;
		
		spe.open(infilename.c_str());
		
		if (spe.fail()){
			cout << "Error: can't open the file <" << infilename.c_str() << ">" << endl;
			continue;//Skip the loop
		}
		for (Int_t i = 0; i<=11; i++) {
			if (i==9){
				spe >> (Double_t)time_tmp;
			}
			
			//Here I go ahead in the file discarding the header lines
			spe.getline(buffer,sizeof(buffer));
		}
		
		cout << "Acquisition time: " << time_tmp << " secs" << endl;
		
		entries_tmp->clear();
		
		//Loading the ADC counts from the file and put them in the vector entry_tmp
		while (spe.good()) {
			if (spe.eof()) break;
				channel++;
				spe >> (Double_t)entry;
				if(filenum==0){
					entries -> push_back(entry);
				} else {
					entries_tmp -> push_back(entry);
				}
			if (spe.eof()) break;
		}
		
		if(filenum==0){
			cout << "Number of channels: " << entries->size() << endl;
		}else{
			cout << "Number of channels: " << entries_tmp->size() << endl;
			for(Int_t i=0; i<entries_tmp->size(); i++){
				(*entries)[i] += entries_tmp->at(i);
			}
		}
		
		spe.close();
		
		filenum++;
		
		time += time_tmp; //Stored total total acquisition time
		
	}
	
	//-------------------------------------------------------------//	
	// Finished to load of the sample histogram from the SPE files //
	//-------------------------------------------------------------//
	
	TH1F* histoADC = new TH1F("histoADC","Spectrum ADC",entries_tmp->size(),1,entries_tmp->size());
	for(Int_t i=0; i<entries->size(); i++){
		histoADC->Fill(i+1,entries->at(i));
	}
	
	//Acquisition time in days
	Double_t tDay = time/day;
	
	bg_histo_ADC -> Scale(tDay); //The BG counts now are rescaled to the sample acquisition time
	
	//cout << "\nhistoENR creation" << endl;
	//Generate an histogram in energy domain for visualization (not working with)
	TH1F* histoENR = convert_histo_ENR(histoADC,"~/PhD/Gator/data_analysis/calibrations/");
	histoENR -> Rebin(15);
	histoENR -> Scale(1/tDay);
	histoENR -> Scale(1,"width");
	histoENR -> GetXaxis() -> SetTitle("Energy [KeV]");
	histoENR -> GetYaxis() -> SetTitle("Rate [KeV^{-1}d^{-1}]");
	
	histoADC -> Sumw2();
	histoADC -> Add(bg_histo_ADC,-1.); //This can now be used with the procedure detectline()
	
	//cout << "Output variables creation" << endl;
	
	//Input variables to be used with the procedure detectline()
	Double_t centerADC, widthADC;
	//Output variables to be used with the procedure detectline()
	Double_t TotLineCnts, TotCompCnts, LineCnts, LineCntsErr, DetectLim, rawActivity, rawActivityErr;
	
	//The results will be loaded in the following vectors
	vector<Double_t>* TotLineCnts_vec = new vector<Double_t>;
	vector<Double_t>* TotCompCnts_vec = new vector<Double_t>;
	vector<Double_t>* LineCnts_vec = new vector<Double_t>;
	vector<Double_t>* LineCntsErr_vec = new vector<Double_t>;
	vector<Double_t>* DetectLim_vec = new vector<Double_t>;
	vector<Double_t>* Activity_vec = new vector<Double_t>;
	vector<Double_t>* ActivityErr_vec = new vector<Double_t>;
	//vector<Double_t>* SpecActivity_vec = new vector<Double_t>; //Not yet used
	
	//cout << "Entering in the detectline 'for' loop." << endl;
	for(Int_t i=0; i<linesADC->size(); i++){
		centerADC = linesADC->at(i);
		widthADC = sigmaADC->at(i);
			detectline(histoADC,centerADC,widthADC,tDay,TotLineCnts,TotCompCnts,LineCnts,LineCntsErr,DetectLim,rawActivity,rawActivityErr);
		TotLineCnts_vec -> push_back(TotLineCnts);
		TotCompCnts_vec -> push_back(TotCompCnts);
		LineCnts_vec -> push_back(LineCnts);
		LineCntsErr_vec -> push_back(LineCntsErr);
		DetectLim_vec -> push_back(DetectLim);
		Activity_vec -> push_back(rawActivity);
		ActivityErr_vec -> push_back(rawActivityErr);
	}
	//cout << "Finished the detectline() 'for' loop." << endl;
	
	//Cycle to tranform raw activities in real activities dividing by the (Eff*BR)
	Double_t Mass = 28.53; //(Kg) Hardcoded value!!! Find a way to avoid this
	for(Int_t i=0; i<Activity_vec->size(); i++){
		(*Activity_vec)[i] = 1000*(*Activity_vec)[i]/(time*(*linesBRxEff)[i]*Mass);
		(*ActivityErr_vec)[i] = 1000*(*ActivityErr_vec)[i]/(time*(*linesBRxEff)[i]*Mass);
		if((*ActivityErr_vec)[i]!=0){
			cout << "\nLine at " << linesENR->at(i) << " KeV ==>" << " Activity = (" << Activity_vec->at(i) << " +- " << ActivityErr_vec->at(i) << ") mBq/Kg" << endl;
		} else {
			cout << "\nLine at " << linesENR->at(i) << " KeV ==>" << " Activity < " << Activity_vec->at(i) << " mBq/Kg" << endl;
		}
	}
	
	
	TCanvas* c1 = new TCanvas("c1","Sample spectrum");
	c1 -> SetLogy();
	
	histoENR -> Add(bg_histo_ENR_vis,-1);
	histoENR -> GetXaxis() -> SetUserRange(40.,histoENR->GetBinCenter(histoENR->GetXaxis()->GetLast()));
	histoENR -> Draw();
}