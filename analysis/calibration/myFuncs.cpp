TH1F* histogen(const string& filename){
//This definition of histogen() is only for files like "sample.dat" that doesn't contain the acquisition time.


ifstream datafile;
//string dataline, str_counts; //Not more usefull. Just for the smart example below.
Double_t ADCch, entries;
vector<Double_t>* ADCchVec = new vector<Double_t>;
vector<Double_t>* entriesVec = new vector<Double_t>;

cout << "Opening the file \'" << filename.c_str() << "\'" << endl;

datafile.open(filename.c_str());

//ofstream outf("Control.txt"); //Only to debug code

while(!datafile.eof()) {
	datafile >> (Double_t)ADCch;
	datafile >> (Double_t)entries;
	ADCchVec -> push_back(ADCch);
	entriesVec -> push_back(entries);
}
datafile.close();

cout << "Num of channels= " << ADCchVec->size() << "\n\n" << endl;

TH1F* histo = new TH1F("histo",filename.c_str(),ADCchVec->size(),1,ADCchVec->size());

for(Int_t i=0; i<ADCchVec->size(); i++){
	histo -> Fill(ADCchVec->at(i), entriesVec->at(i));
}




//DON'T CANCEL THE FOLLOWING LOOP BECAUSE IT'S A SMART EXAMPLE TO MANAGE WITH STRINGS. JUST COMMENT THE WHOLE BLOCK!!!
/*
Int_t nlines=0;
while (!datafile.eof()){
   //cout <<"Start loop num: " << nlines << "\n" << endl; //Only for debug.
   getline(datafile,dataline);
   if(nlines==0) {
   	histo->SetBinContent(0,0); //0 is the index of the underflow bin, which I set to 0 for safety   
   }

   str_counts = dataline.substr(dataline.find_first_of("\t")+1); // I want to get only the second column, 
                                                                 // in which are the counts for each channel.
                                                                 // This values are after the TAB character.
   counts = atof(str_counts.c_str()); // Converts the counts from char to float.
   
   if(nlines!=0  && nlines < 15){
   cout << "Line: " << nlines << "\t" << "Counts = " << counts << "\n" << endl; //Just to debug
   }
   histo->Fill((Double_t)nlines,counts); //Fill each bin with the correnponding counts rate
   nlines++;

}
*/

histo -> Draw();

return histo;

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////



TH1F* histogen(const string& filename, Double_t& time){
//This definition of histogen() is only for files of Gator spectrum in which the first line is the acquisition 
//time in secons.

ifstream datafile;

Double_t counts, entries;
vector<Double_t>* ADCchVec = new vector<Double_t>;
vector<Double_t>* entriesVec = new vector<Double_t>;

cout << "Opening the file <" << filename.c_str() << ">" << endl;

	Double_t time, ADCch, entries;
	
datafile.open(filename.c_str());
Int_t i = 0;
while(!datafile.eof()) {
	if(i==0){
	datafile >> (Double_t)time;
	}else{
	datafile >> (Double_t)ADCch;
	datafile >> (Double_t)entries;
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
/////////////////////////////////////////////////////////////////////////////


void sortPeaks(Double_t* xArr,Double_t* yArr,Int_t arrSize){

   Bool_t ordinato=false;
   Int_t aux;

   for (Int_t i=0;i<arrSize;i++){
      if (ordinato==true){return;}
      ordinato=true;
      for (Int_t j=(arrSize-1);j>i;j--){
         if (xArr[j]<xArr[j-1]){
            ordinato=false;
            aux=xArr[j-1];
            xArr[j-1]=xArr[j];
            xArr[j]=aux;
            aux=yArr[j-1];
            yArr[j-1]=yArr[j];
            yArr[j]=aux;
         }
      }
   }
   return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void lineAnalisys(TH1F* histo,
                  TF1* fitfunc,
						Double_t pos,// = fitfunc->GetParameter(1), 
                  Option_t* option = "IB",
						Double_t amp = 0,// = fitfunc->GetParameter(2),
						Double_t sigma = 5
                  ){
	
	//This function can be used only manually and is thought to fit the lines with a gaussian + a linear funct.
	//After the fit is shown and if is ok the values of line position and width can be "pusched back" in the 
	//external vectors "positions" and "widths".	
	
	Double_t minrange = pos-50;
	Double_t maxrange = pos+50;
	
	if(amp == 0){
		amp = 0.55*workHisto->GetMaximum();
	}
	
	
	if(minrange < histo->GetBinCenter(histo->GetXaxis()->GetFirst())) {
		minrange = histo->GetBinCenter(histo->GetXaxis()->GetFirst());
	}
	
	if(maxrange >	histo->GetBinCenter(histo->GetXaxis()->GetLast())) {
		maxrange = histo->GetBinCenter(histo->GetXaxis()->GetLast());
	}
	
	fitfunc -> SetParameters(amp,pos,sigma,10,0.01);
	fitfunc -> SetRange(minrange,maxrange);
	fitfunc -> SetParLimits(0,0,2*amp);
	fitfunc -> SetParLimits(2,0,5*sigma);
	fitfunc -> SetParLimits(3,0,amp);
	histo -> Fit(fitfunc,option);
	
	return;
	
}
/////////////////////////////////////////////////////////////////////////////////////////




TH1F* lineHisto(TCanvas* workCanv,
					 Double_t linesADC_raw,
					 Double_t low_ADC_win,
					 Double_t high_ADC_win,
					 string filename = "sample.dat"){
	
	
	workCanv -> cd();
	
	Double_t ADCch, entries;
	vector<Double_t>* ADCchVec = new vector<Double_t>;
	vector<Double_t>* entriesVec = new vector<Double_t>;
	
	
	Double_t lowbin = (Int_t)(low_ADC_win+0.5);
	Double_t highbin = (Int_t)(high_ADC_win+0.5);
	
	ifstream datafile;
	datafile.open(filename.c_str());
	
	while(datafile.good()) {
		datafile >> (Double_t)ADCch;
		datafile >> (Double_t)entries;
		ADCchVec -> push_back(ADCch);
		entriesVec -> push_back(entries);
		if (datafile.eof()) break;
	}
	datafile.close();
	
	Int_t nbins;
	
	for(Int_t i=0; i<ADCchVec->size(); i++){ 
		if((ADCchVec->at(i) >= lowbin)&&(ADCchVec->at(i) <= highbin)) nbins++;
	}
	
	
	TH1F* histo = new TH1F("workHisto","workHisto",nbins,lowbin,highbin);
	
	
	for(Int_t i=0; i<ADCchVec->size(); i++){
		if((ADCchVec->at(i) >= lowbin)&&(ADCchVec->at(i) <= highbin)) histo -> Fill(ADCchVec->at(i), entriesVec->at(i));
	}
	
	histo -> Draw();
	
	TLine* linec = new TLine(linesADC_raw,workCanv->GetUymin(),linesADC_raw,workCanv->GetUymax());
	linec -> SetLineStyle(2);
	linec -> SetLineColor(4);
	linec -> Draw("SAME");
	
	workCanv -> Update();
	
	delete ADCchVec;
	delete entriesVec;
	
	return histo;
	
}
////////////////////////////////////////////////////////////////////////////////////




void linesCountsFunc(TCanvas* workCanv,  //The canvas where the procedure is shown
							Double_t LineCenter, //Input line center from a previously saved vector in a file.root
							Double_t LineWidth, //Input line width from a previously saved vector in a file.root
							Double_t& LineTotCounts, //Output variable for the line total counts (Signal + Compton)
							Double_t& LineCompton, //Output variable for the line Compton counts
							Double_t& LineCounts, //Output variable for the line counts without the Compton
							Double_t& LineCounts_err, //Output variable for the error on line counts
							Double_t& det_lim, //Output for the "Detection Limit" for the line
							Double_t WidthScale = 3.0,
							const Char_t* filename = "sample.dat" //Input file name, where the raw data is stored
							){
	
	
	
	Double_t line_low = LineCenter - WidthScale*LineWidth;
	Double_t line_high = LineCenter + WidthScale*LineWidth;
	
	Double_t bg_low = line_low - 2*WidthScale*LineWidth;
	Double_t bg_high = line_high + 2*WidthScale*LineWidth;
	
	workCanv -> cd();
	
	Double_t ADCch, entries;
	vector<Double_t>* ADCchVec = new vector<Double_t>;
	vector<Double_t>* entriesVec = new vector<Double_t>;
	
	
	//Standard code to generate an histogram from 2 columns ASCII file
	Double_t ADCch, entries;
	
	ifstream datafile;
	datafile.open(filename);
	while(datafile.good()) {
		datafile >> (Double_t)ADCch;
		datafile >> (Double_t)entries;
		ADCchVec -> push_back(ADCch);
		entriesVec -> push_back(entries);
		if (datafile.eof()) break;
	}
	datafile.close();
	
	
	TH1F* histo = new TH1F("histo","",ADCchVec->size(),ADCchVec->at(0),ADCchVec->at(ADCchVec->size()-1));
	
	for(Int_t i=0; i<ADCchVec->size(); i++){
		histo -> Fill(ADCchVec->at(i), entriesVec->at(i));
	}
	
	
	Int_t line_low_bin = histo -> FindBin(line_low);
	Int_t line_high_bin = histo -> FindBin(line_high);
	
		
	Int_t bg_low_bin = histo -> FindBin(bg_low);
	Int_t bg_high_bin = histo -> FindBin(bg_high);
	
	cout << "\nCompton low limit bin: " << bg_low_bin << "  ->  " << "ADC channel: " << bg_low << endl;
	cout << "Line low limit bin: " << line_low_bin << "  ->  " << "ADC channel: " << line_low << endl;
	cout << "Line center bin: " << histo -> FindBin(LineCenter) << "  ->  " << "ADC channel: " << LineCenter << endl;
	cout << "Line high limit bin: " << line_high_bin << "  ->  " << "ADC channel: " << line_high << endl;
	cout << "Compton high limit bin: " << bg_high_bin << "  ->  " << "ADC channel: " << bg_high << endl;

	
	Double_t line_counts_raw=0, compt_left=0, compt_right=0;
	
	
	for(Int_t i=bg_low_bin; i<=line_low_bin; i++){
		compt_left += histo -> GetBinContent(i);
	}
	
	cout << "\nLow Compton counts: " << compt_left <<endl;
	
	for(Int_t i=line_low_bin; i<=line_high_bin; i++){
		line_counts_raw += histo -> GetBinContent(i);
	}
	
	
	for(Int_t i=line_high_bin; i<=bg_high_bin; i++){
		compt_right += histo -> GetBinContent(i);
	}
	
	cout << "High Compton counts: " << compt_right <<endl;
	
	LineCounts = line_counts_raw - (compt_left+compt_right)/2; //Here is assigned an output variable
	
	
	//Section for the error calculus
	Double_t bg_low_err, bg_high_err, tot_counts_err, var_counts;
	
	
	//Poissonian error estimation. It could be changed;
	bg_low_err = TMath::Sqrt(compt_left);
	bg_high_err = TMath::Sqrt(compt_right);
	tot_counts_err = TMath::Sqrt(line_counts_raw);
	LineCounts_err = TMath::Sqrt(line_counts_raw + (compt_left+compt_right)/2); //Here is assigned an output variable
	
	cout << "\n\nTotal line counts: " << line_counts_raw << endl;
	cout << "Tot line counts error: " << tot_counts_err << endl;
	cout << "Estimated Compton counts: " << (compt_left+compt_right)/2 << endl;
	cout << "Compton counts error: " << TMath::Sqrt((compt_left+compt_right)/2) << endl;
	cout << "Net line counts: " << LineCounts << endl;
	cout << "Line counts error: " << LineCounts_err << endl;
	
	
	//Determine if the signal can be condered detected or not
	det_lim = 2.86 + 4.87*TMath::Sqrt(1.36 + (compt_left+compt_right)/2); //From the Gator paper
	
	cout << "\nDetection limit: " << det_lim << endl;
	
	if (LineCounts <= 0) {
		cout << "\nLine activity not detected!" << endl;
		cout << "Upper limit of activity is set to detection limit: " << det_lim << " counts" << endl;
	} else if ((LineCounts > 0) && (LineCounts <= det_lim)) {
		cout << "\nLine activity detected but not determinable.\nUpper limit set to: " <<  (det_lim + LineCounts) << endl;
	} else if (LineCounts > det_lim) {
		cout << "Line activity detected" << endl;
	}
	
	
	//OUTPUT SECTION
	LineTotCounts = line_counts_raw;
	LineCompton = (compt_left+compt_right)/2;
	
	
	//Draw lines to show the method on each line
	TLine* tline_central = new TLine(LineCenter,workCanv->GetUymin(),LineCenter,workCanv->GetUymax());
	tline_central -> SetLineStyle(2);
	tline_central -> SetLineColor(4);
	tline_central -> Draw("SAME");
	
	TLine* tline_low1 = new TLine(line_low,workCanv->GetUymin(),line_low,workCanv->GetUymax());
	tline_low1 -> SetLineStyle(2);
	tline_low1 -> SetLineColor(2);
	tline_low1 -> Draw("SAME");
	
	TLine* tline_high1 = new TLine(line_high,workCanv->GetUymin(),line_high,workCanv->GetUymax());
	tline_high1 -> SetLineStyle(2);
	tline_high1 -> SetLineColor(2);
	tline_high1 -> Draw("SAME");
	
	TLine* tline_low2 = new TLine(bg_low,workCanv->GetUymin(),bg_low,workCanv->GetUymax());
	tline_low2 -> SetLineStyle(2);
	tline_low2 -> SetLineColor(3);
	tline_low2 -> Draw("SAME");
	
	TLine* tline_high2 = new TLine(bg_high,workCanv->GetUymin(),bg_high,workCanv->GetUymax());
	tline_high2 -> SetLineStyle(2);
	tline_high2 -> SetLineColor(kGreen);
	tline_high2 -> Draw("SAME");
	
	workCanv -> Update();
	
	return;
	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
TH1F* find_peak_RMS(){
	
}*/




////////////////////////////////////////////////
// The following functions come from Giovanni //
////////////////////////////////////////////////

TSpectrum* FindPeak( TH1D *hdev, Int_t nPeaks ){
    Int_t maxNPeaks = 50; // Maximum number of peaks
    Float_t resolution = 1.; // Determines resolution of the neighboring peaks 
    // default value is 1 correspond to 3 sigma distance 
    // between peaks. Higher values allow higher resolution
    // (smaller distance between peaks.
    // May be set later through SetResolution. 
    TSpectrum *first_cal_peaks = new TSpectrum( maxNPeaks, resolution );
    Double_t sigma = 1.;
    Double_t threshold = 0.5;
    first_cal_peaks->Search( hdev, sigma, "goff", threshold );
    
    Int_t size = first_cal_peaks->GetNPeaks();
    Int_t iterations = 1;
    Double_t increment = 0.03;
    Double_t decrement = 0.02;
    
    while( size != nPeaks ){
      if( size > nPeaks && threshold < ( 1- increment ) ){
			threshold += increment;
			first_cal_peaks->Search( hdev, sigma, "goff", threshold );
      }else if( size < nPeaks && threshold > decrement){
			threshold -= decrement;
			first_cal_peaks->Search( hdev, sigma, "goff", threshold );
      }else{
			increment /= 2.;
			decrement /=2.;
      }
      iterations ++;
      size = first_cal_peaks->GetNPeaks();
      if( iterations > 100 ){
			return 0;
      }
    }

    return first_cal_peaks;
}
///////////////////////////////////////////////////////////////////////////////////////////////////


TFitResultPtr Calibrate( vector<double> *peaks,
			 vector<double> *peaks_error,
			 vector<double> *literature,
			 vector<double> *literature_error,
			 TF1 * fit_func,
			 TFile *rootout ){

  int nPeaks = peaks->size();

  TGraphErrors* position_graph = new TGraphErrors( nPeaks,
																	&(peaks->at(0)),
																	&(literature->at(0)),
																	&(peaks_error->at(0)),
																	&(literature_error->at(0)));

  TFitResultPtr fitresult = position_graph->Fit(fit_func->GetName(),"N");

  rootout->cd();
  fit_func->Write();
    
  return fitresult;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////



void Draw_Calibration( vector<double>* peaks,
		                 vector<double>* peaks_error,
		                 vector<double>* literature,
		                 vector<double>* literature_error,
		                 TF1* fit_func,
		                 string *outpath_string,
		                 string *outfile_name,
		                 TFile *file ){

  TCanvas *canvas = new TCanvas();
  canvas->cd();
  gPad->SetFillColor(10);

  int nPeaks = peaks->size();
  TGraphErrors *position_graph = 
    new TGraphErrors( nPeaks,
		      &(peaks->at(0)),
		      &(literature->at(0)),
		      &(peaks_error->at(0)),
		      &(literature_error->at(0)) );

  if( fit_func->GetParameter(2) == 0. ){
    position_graph->SetTitle("Linear Calibration");
  }else{
    position_graph->SetTitle("Quadratic Calibration");
  }
  position_graph->SetName( outfile_name->c_str() );

  position_graph->GetXaxis()->SetTitle("Uncalibrated Energy");
  position_graph->GetYaxis()->SetTitle("LiteratureEnergy [keV]");

  position_graph->SetMarkerStyle(21);
  position_graph->SetMarkerColor(kBlue);

  position_graph->Draw("AP");

  fit_func->SetLineColor(2);
  fit_func->SetLineWidth(1);
  position_graph->Fit(fit_func->GetName(),"Q");
  fit_func->Draw("same");
  
  string *outfile_string = new string( outpath_string->c_str() );
  outfile_string->append( outfile_name->c_str() );
  outfile_string->append(".png");
  canvas->Print( outfile_string->c_str() );
  
  file->cd();
  position_graph->Write();

  return;  
}
/////////////////////////////////////////////////////////////////////////////////////////////////////



void Residuals( vector<double> *peaks,
		vector<double> *peaks_error,
		vector<double> *literature,
		vector<double> *literature_error,
		vector<double> *diff,
		vector<double> *diff_error ){

  int nPeaks = peaks->size();
  for( int i=0; i<nPeaks; i++ ){
    diff->push_back( peaks->at(i) - literature->at(i) );
    diff_error->push_back( sqrt( pow(peaks_error->at(i), 2. ) + 
				 pow( literature_error->at(i), 2. ) ) );
  }

  return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////


void Draw_Calibration_Deviation( vector<double> *diff,
				   vector<double> *diff_error,
				   vector<double> *literature,
				   vector<double> *literature_error,
				   string *outpath_string,
				 string *outfile_name,
				 string *title,
				 TFile *file ){

  TCanvas *canvas = new TCanvas();
  canvas->cd();
  gPad->SetFillColor(10);

  int nPeaks = diff->size();
  TGraphErrors *diff_graph = 
    new TGraphErrors( nPeaks, 
		      &( literature->at(0) ),
		      &( diff->at(0) ),
		      &( literature_error->at(0) ),
		      &( diff_error->at(0) ) );
  diff_graph->SetTitle( title->c_str() );
  diff_graph->SetName( outfile_name->c_str() );
  diff_graph->GetXaxis()->SetTitle("Energy [keV]");
  diff_graph->GetYaxis()->SetTitle("Deviation [keV]");

  diff_graph->SetMarkerStyle(21);
  diff_graph->SetMarkerColor(kBlue);

  diff_graph->Draw("AP");

  string *func_name = new string( "" );
  func_name->append( outfile_name->c_str() );
  func_name->append( "_func" );
  TF1 *p0 = new TF1( func_name->c_str(), "pol0" );
  p0->SetLineColor(2);
  p0->SetLineWidth(2);
  TFitResultPtr fitresult = diff_graph->Fit(p0);
  string *fitresult_name = new string("");
  fitresult_name->append( outfile_name->c_str() );
  fitresult_name->append( "_fitresult" );
  fitresult->SetName( fitresult_name->c_str() );

  string *outfile_string = new string( outpath_string->c_str() );
  outfile_string->append( outfile_name->c_str() );
  outfile_string->append(".png");
  canvas->Print( outfile_string->c_str() );

  outfile_string = new string( outpath_string->c_str() );
  outfile_string->append( outfile_name->c_str() );
  outfile_string->append(".txt");
  ofstream printResults( outfile_string->c_str() );
  printResults << p0->GetParameter(0) << "\t" << p0->GetParError(0) << endl; 
  printResults << p0->GetChisquare() << "\t" << p0->GetNDF() << endl;

  file->cd();
  diff_graph->Write();
  p0->Write();
 //fitresult->Write();

  return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
