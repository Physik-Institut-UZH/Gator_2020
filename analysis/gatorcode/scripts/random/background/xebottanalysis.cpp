#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TFile.h>
//#include <TTree.h>
#include <TH1F.h>
//#include <TH1D.h>
//#include <TH2D.h>
//#include <TLegend.h>
//#include <TCut.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
//#include <TIterator.h>
//#include <TList.h>
#include <TMultiGraph.h>
#include <fstream>
#include <iostream>
#include <vector>
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


void xebottanalysis();
void wait();
//void filechoice();
TH1F* loadSPE(Char_t*, Double_t&);
//TH1F* loadSPE2(Char_t*, Double_t&);
void eff_est(const TF1*,const TFitResultPtr&,const Double_t,Double_t&,Double_t&);
void linecountsXeBot(const TH1F*, TCanvas*, const Double_t, const Double_t, Double_t&, Double_t&, Double_t&, Double_t&, Double_t&, Double_t&, Double_t&, Double_t&, Double_t&, const TH1F* bg_histoADC = 0, Double_t WidthScale = 3.0);
char* formatdigits(Double_t var, char* valuestr, Int_t dig = 3);

TCanvas* c1;


int main(){
	
	TApplication theApp("App",0,0);
	xebottanalysis();
	
	theApp.Run();
	
	return 0;
}


void wait()
{
	c1 -> Update(); c1 -> WaitPrimitive();
}
//////////////////////////////////////////////////////////////////////////////////////////



////////////---------- SCRIPT FUNCTION ------------//////////////
void xebottanalysis(){
	
	c1= new TCanvas("c1","");
	c1->cd();
	//The following lines are for closing the application when the canvas c1 is closed.
#ifndef __CINT__
	c1 -> Connect("TCanvas", "Closed()", "TApplication", gApplication,"Terminate()");
#endif
	
	
	TFile* calfile = new TFile("/Users/francesco/PhD/Gator/data_analysis/calibrations/calibration.root","read");
	TF1* calib_fcn_bw = (TF1*)calfile -> Get("calib_fcn_bw");
	TF1* resol_ADC_func = (TF1*)calfile -> Get("resol_ADC_func");
	calfile -> Close();
	delete calfile;
	
	
//Loading the features of the lines that have to be analyzed. From the file lines.list
	ifstream linesfile("linesSS.list");
	
	if (linesfile.fail()){
			cout << "Error: can't open <lines.list>" << endl;
			exit(1);
		}
	
	
	vector<string>* v_massN = new vector<string>;
	vector<string>* v_elemTag = new vector<string>;
	vector<Double_t>* v_litENR = new vector<Double_t>;
	vector<Double_t>* v_BR = new vector<Double_t>;
	
	
	
	Char_t massNstr[100], elemTagstr[100], litENRstr[100], BRstr[100];
	Double_t litENRtmp, BRtmp;
	while (linesfile.good()){
		if(linesfile.eof()) break;
		
		linesfile >> massNstr;
		linesfile >> elemTagstr; 
		linesfile >> litENRstr;
		linesfile >> BRstr;
		
		if(linesfile.eof()) break;
		
		litENRtmp = atof(litENRstr);
		BRtmp = atof(BRstr);
		
		v_massN -> push_back(massNstr);
		v_elemTag -> push_back(elemTagstr);
		v_litENR -> push_back(litENRtmp);
		v_BR -> push_back(BRtmp);
		
		if(linesfile.eof()) break;
	}
	linesfile.close();
	
	
//Loading the root file with the efficiences. The efficiency will be found through a polinomial fitting of simulated data in a proper range about the energy value I'm interested in.
	TFile* eff_file = new TFile("/Users/francesco/PhD/Gator/XeActivation/effic.root","read");
	TGraphErrors* gr_eff = (TGraphErrors*)eff_file->Get("gr_eff");
	eff_file -> Close();
	delete eff_file;
	
	
	//TCanvas* c2 = new TCanvas("c2","");
	c1 -> cd();
	
	gr_eff -> Draw("AP");
	
	
	TF1* eff_func1 = new TF1("eff_func1","pol2",30,240); //Low energy fitting function => used up to 225 keV
	eff_func1 -> SetLineWidth(1);
	eff_func1 -> SetLineColor(2);
	
	TF1* eff_func2 = new TF1("eff_func2","pol2",215,1980); //High energy fitting function => from 225 keV
	eff_func2 -> SetLineWidth(1);
	eff_func2 -> SetLineColor(2);
	
	TFitResultPtr resFit1, resFit2;
	resFit1 = gr_eff -> Fit(eff_func1,"SR+");
	resFit2 = gr_eff -> Fit(eff_func2,"SR+");
	
	vector<Double_t>* v_effic = new vector<Double_t>;
	vector<Double_t>* v_effic_err = new vector<Double_t>;
	
	//Extrapolation of the efficiences for each line through a fitting procedure of the "efficience curve"
	Double_t lowrange, uprange, efftmp, efferrtmp;
	for (Int_t i=0; i<v_litENR->size(); i++){
		
		litENRtmp = v_litENR->at(i);
		cout << "\n\nEnergy = " << litENRtmp << " keV" << endl;
		
		if (litENRtmp <= 225){
			eff_est(eff_func1,resFit1,v_litENR->at(i),efftmp,efferrtmp);
		} else {
			eff_est(eff_func2,resFit2,v_litENR->at(i),efftmp,efferrtmp);
		}
		v_effic -> push_back(efftmp);
		v_effic_err -> push_back(efferrtmp);
	}
	

	
	
//Load the histogram in ADC domain of the acquisition from the files.SPE
	
	TCanvas* c3 = new TCanvas("c3","");
	c3 -> cd() -> SetLogy();
	Double_t aqtime; //Acquisition time
	TH1F* histoADC = loadSPE("./SPE/", aqtime);
	histoADC -> SetLineWidth(1);
	histoADC -> SetLineColor(kBlue);
	histoADC -> GetXaxis() -> SetTitle("ADC");
	histoADC -> GetYaxis() -> SetTitle("counts/day");
	histoADC -> Draw();
	
	
//Load the background in ACD domain from the proper root file. Here there is an hardcoded switch from the modality with BG or without BG (just changing a switch).
	
	Bool_t BGswitch = true;
	
	TH1F* bg_histo_ADC = 0; //Becomes different from 0 only if the switch changes
	
	if(BGswitch){
		
		TFile* bg_file = new TFile("~/PhD/Gator/data_analysis/background/background.root","read");
		bg_histo_ADC = (TH1F*)bg_file -> Get("bg_histo_ADC_vis"); //From here I get it in counts/day
		bg_histo_ADC -> SetDirectory(0);
		bg_file -> Close();
		delete bg_file;
		bg_histo_ADC -> Scale(aqtime/(24*3600)); //Proper rescaling for the acquisition time (is saved in counts/days). Now it's in counts/sec!!!
		bg_histo_ADC -> SetLineWidth(1);
		bg_histo_ADC -> SetLineColor(kRed);
		bg_histo_ADC -> GetXaxis() -> SetTitle("ADC");
		bg_histo_ADC -> GetYaxis() -> SetTitle("counts/day");
		bg_histo_ADC -> Draw("SAME");
		
	}
		
	
	vector<Double_t>* v_linecnts = new vector<Double_t>;
	vector<Double_t>* v_linecnts_err = new vector<Double_t>;
	vector<Double_t>* v_compcnts = new vector<Double_t>;
	vector<Double_t>* v_compcnts_err = new vector<Double_t>;
	vector<Double_t>* v_det_lim = new vector<Double_t>; //Detection limit in counts
	vector<Double_t>* v_peakcnts = new vector<Double_t>;
	vector<Double_t>* v_peakcnts_err = new vector<Double_t>;
	vector<Double_t>* v_bgcnts = new vector<Double_t>;
	vector<Double_t>* v_bgcnts_err = new vector<Double_t>;
	
	
	Double_t center,sigma,linecnts, linecnts_err, compcnts, compcnts_err, peakcnt, peakcnts_err, bgcnts, bgcnts_err, det_lim;
	for(Int_t i=0; i<v_litENR->size(); i++){
		
		center = calib_fcn_bw -> Eval(v_litENR->at(i));
		sigma = resol_ADC_func -> Eval(center);	
		
		cout << "Line energy = " << v_litENR->at(i) << endl;
		
		linecountsXeBot(histoADC,c3,center,sigma,linecnts,linecnts_err,compcnts,compcnts_err,peakcnt,peakcnts_err,bgcnts, bgcnts_err,det_lim,bg_histo_ADC);
		
		v_peakcnts -> push_back(peakcnt);
		v_peakcnts_err -> push_back(peakcnts_err);
		v_linecnts -> push_back(linecnts);
		v_linecnts_err -> push_back(linecnts_err);
		v_compcnts -> push_back(compcnts);
		v_compcnts_err -> push_back(compcnts_err);
		v_bgcnts -> push_back(bgcnts);
		v_bgcnts_err -> push_back(bgcnts_err);
		v_det_lim -> push_back(det_lim);
		
		//wait();
		
	}
	
	
//Put all together and find the specific activities
	//const Double_t XeMass = 1.85; //In kg (hard coded, be care!!!)
	
	const Double_t XeMass = 2.9; //This is the SS bottle weight!!!
	
	//Activities calculated even though we are under the limit
	vector<Double_t>* v_activity = new vector<Double_t>; 
	vector<Double_t>* v_activity_err = new vector<Double_t>;
	
	if(BGswitch){//Evaluate activities only if there is a BG histogram
		Double_t activity, activity_err;
		for(Int_t i=0; i<v_litENR->size(); i++){
		
			activity = 1000 * v_linecnts->at(i) / (v_BR->at(i) * v_effic->at(i) * aqtime * XeMass); // mBq/kg
			
			activity_err = activity * TMath::Sqrt(TMath::Power(v_linecnts_err->at(i)/v_linecnts->at(i),2) + TMath::Power(v_effic_err->at(i)/v_effic->at(i),2));
		
			v_activity -> push_back(activity);
			v_activity_err -> push_back(activity_err);
		
		}
	}
	
	
	
	//Save in a TFile everything
	TFile* savefile = new TFile("savefileSS.root","recreate");
	//savefile -> Writeobject(aqtime,"aqtime","overwrite");
	savefile -> WriteObject(v_massN,"v_massN","overwrite");
	savefile -> WriteObject(elemTagstr,"elemTagstr","overwrite");
	savefile -> WriteObject(v_litENR,"v_litENR","overwrite");
	savefile -> WriteObject(v_BR,"v_BR","overwrite");
	savefile -> WriteObject(v_effic,"v_effic","overwrite");
	savefile -> WriteObject(v_effic_err,"v_effic_err","overwrite");
	savefile -> WriteObject(v_linecnts,"v_linecnts","overwrite");
	savefile -> WriteObject(v_linecnts_err,"v_linecnts_err","overwrite");
	savefile -> WriteObject(v_peakcnts,"v_peakcnts","overwrite");
	savefile -> WriteObject(v_peakcnts_err,"v_peakcnts_err","overwrite");
	savefile -> WriteObject(v_compcnts,"v_compcnts","overwrite");
	savefile -> WriteObject(v_compcnts_err,"v_compcnts_err","overwrite");
	savefile -> WriteObject(v_bgcnts,"v_bgcnts","overwrite");
	savefile -> WriteObject(v_bgcnts_err,"v_bgcnts_err","overwrite");
	savefile -> WriteObject(v_activity,"v_activity","overwrite");
	savefile -> WriteObject(v_activity_err,"v_activity_err","overwrite");
	savefile -> WriteObject(v_det_lim,"v_det_lim","overwrite");
	savefile -> WriteObject(histoADC,"histoADC","overwrite");
	savefile -> Close();
	delete savefile;
	
	
//Output section 
	ofstream outfile;
	
	if(BGswitch){
		
		outfile.open("xe_act.txt");
		
	}else{
	
		outfile.open("xe_act_before.txt");
	
	}
	
	Double_t det_lim_act, var, varerr;
	
	char valuestr[100]; //Using this to get a formatted output from 'formatdigits' function
	
	for (Int_t i=0; i<v_litENR->size(); i++){
	
		det_lim_act = 1000 * v_det_lim->at(i) / (v_BR->at(i) * v_effic->at(i) * aqtime * XeMass); //Detection limit in specific activity units
		
		//cout << "Detection limit = " << formatdigits(det_lim_act,valuestr) << "mBq/kg" << endl;
		
		outfile<<"|  <sup>"<<v_massN->at(i)<<"</sup>"<<v_elemTag->at(i)<<"  |  "<<v_litENR->at(i)<<"  |  "<<formatdigits(var=v_peakcnts->at(i),valuestr)<<" +- ";
		outfile<<formatdigits(varerr=v_peakcnts_err->at(i),valuestr); //Up to here is common for output with and without BG
		
		if(BGswitch){//Output for data with BG
		outfile<<"  |  "<<formatdigits(var=v_compcnts->at(i),valuestr)<<" +- ";
		outfile<<formatdigits(varerr=v_compcnts_err->at(i),valuestr)<<"  |  ";
		outfile<<formatdigits(var=v_bgcnts->at(i),valuestr)<<" +- ";
		outfile<<formatdigits(varerr=v_bgcnts_err->at(i),valuestr)<<"  |  ";
		outfile<<formatdigits(var=v_linecnts->at(i),valuestr)<<" +- ";
		outfile<<formatdigits(varerr=v_linecnts_err->at(i),valuestr)<<"  |  ";
		outfile<<formatdigits(var=v_det_lim->at(i),valuestr)<<"  |  ";
		outfile<<formatdigits(var=v_effic->at(i),valuestr)<<" +- ";
		outfile<<formatdigits(varerr=v_effic_err->at(i),valuestr)<<"  |  ";
		outfile<<formatdigits(var=v_BR->at(i),valuestr)<<"  |  ";
		outfile<<formatdigits(var=det_lim_act,valuestr)<<"  |  ";
			if(v_linecnts->at(i) <= 0){
				
				outfile<<"<"<<formatdigits(var=det_lim_act,valuestr)<<"  |"<<endl;
				
			}else if((v_linecnts->at(i) > 0)&&(v_linecnts->at(i) <= v_det_lim->at(i))){
				
				outfile<<"<"<<formatdigits(var=(det_lim_act + v_activity->at(i)),valuestr)<<"  |"<<endl;
				
			}else{
			
				outfile<<formatdigits(var=v_activity->at(i),valuestr)<<" +- ";
				outfile<<formatdigits(varerr=v_activity_err->at(i),valuestr)<<"  |"<<endl;
				
			}
		
		}else{//Output for data without BG
			//The values we have are relative to a "BG acquisition" ==> only detection limit activities are printed in the output file (for each line under investigation).
			outfile<<formatdigits(var=v_det_lim->at(i),valuestr)<<"  |  ";
			outfile<<formatdigits(var=v_effic->at(i),valuestr)<<" +- ";
			outfile<<formatdigits(varerr=v_effic_err->at(i),valuestr)<<"  |  ";
			outfile<<formatdigits(var=v_BR->at(i),valuestr)<<"  |  ";
			outfile<<formatdigits(var=det_lim_act,valuestr)<<"  |"<<endl;
			
		}
		
	}
	outfile.close();
	
	cout << "\n\n\nTotal time = " << formatdigits(aqtime,valuestr,8) << " sec ==> " << aqtime/(24*3600) << " days"<<endl;
	
	
	
	return;
}
//////////////////////////////////////////////////////////////////
//--------------------------------------------------------------//
//                SCRIPT FUNCTION FINISHED                      //
//--------------------------------------------------------------//
//////////////////////////////////////////////////////////////////




TH1F* loadSPE(Char_t* dir, Double_t& aqtime){

	//-------------------------------------------------//	
	// Load of the sample histogram from the SPE files //
	//-------------------------------------------------//

	Char_t buffer[100];
	
	aqtime=0;
	
	Double_t time_tmp=0, entry=0; 
	Int_t channel=0;
	
	vector<Double_t>* entries_tmp = new vector<Double_t>;
	vector<Double_t>* entries = new vector<Double_t>;
	
	string dirname(dir);
	string command("ls ");
	string infilename;
	
	command += dirname;
	command += "*.SPE";
	
	ifstream spe;
	
	FILE* fpp = gSystem -> OpenPipe(command.c_str(),"r"); //Hard coded!!! Find a way to implement a simpler way to set the directory
	
	Int_t filenum =0; //Counts the files.SPE read
	
	Char_t time_tmp_str[100], entry_str[100];
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
				spe >> time_tmp_str;
				time_tmp = atof(time_tmp_str);
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
				spe >> entry_str;
				entry = atof(entry_str);
				if(filenum==0){
					if (entries->size()>=16385) break; //According to calibration... hard coded ==> be care!!!
					entries -> push_back(entry);
				} else {
					if (entries_tmp->size()>=16385) break;
					entries_tmp -> push_back(entry);
				}
				
			if (!spe.good()) break;
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
///////////////////////////////////////////////////////////////////////////////////////////


void eff_est(const TF1* fit_pol2,
			const TFitResultPtr& resFit,
			const Double_t x, //The energy value
			Double_t& y, //The efficiency value
			Double_t& yerr){ //Error on the efficiency value

	
	y = fit_pol2 -> Eval(x);
	
	//Double_t a = fit_pol3->GetParameter(0);
	//Double_t b = fit_pol3->GetParameter(1);
	//Double_t c = fit_pol3->GetParameter(2);
	//Double_t d = fit_pol3->GetParameter(3);
	
	Double_t cov_aa = resFit->CovMatrix(0,0);
	Double_t cov_bb = resFit->CovMatrix(1,1);
	Double_t cov_cc = resFit->CovMatrix(2,2);
	
	
	Double_t cov_ab = resFit->CovMatrix(0,1);
	Double_t cov_ac = resFit->CovMatrix(0,2);
	Double_t cov_bc = resFit->CovMatrix(1,2);
	
	Double_t var = cov_aa + cov_bb*TMath::Power(x,2) + cov_cc*TMath::Power(x,4) + 2*(cov_ab*x + cov_ac*TMath::Power(x,2) + cov_bc*TMath::Power(x,3));
	
	yerr = TMath::Sqrt(var);
	
	return;
}
///////////////////////////////////////////////////////////////////////////////////////////


void linecountsXeBot(const TH1F* histoADC, //The units must be only in counts
				TCanvas* workcanv,
				const Double_t center,
				const Double_t sigma,
				Double_t& linecnts,
				Double_t& linecnts_err,
				Double_t& compcnts,
				Double_t& compcnts_err,
				Double_t& peakcnts,
				Double_t& peakcnts_err,
				Double_t& bgcnts,
				Double_t& bgcnts_err,
				Double_t& det_lim,
				const TH1F* bg_histoADC,//This is by default 0 ==> means that we working with the BG only.
				Double_t WidthScale){
	
	//NOTE: here the bg_histoADC must enter in the routine with a properly rescaled for different time acquisitions.
	
	compcnts = 0;
	peakcnts = 0;
	bgcnts = 0;
	
	Double_t line_low = center - WidthScale*sigma;
	Double_t line_up = center + WidthScale*sigma;
	Double_t line_intrv = line_up - line_low;
	
	Double_t compt_low = center - 2*WidthScale*sigma;
	Double_t compt_up = center + 2*WidthScale*sigma;
	Double_t compt_intrv = (line_low-compt_low) + (compt_up-line_up);
	
	
	//All the limits in general finish not on a bin border ==> 4 different bin fraction must be taken.
	//The fraction is relative to the lower section cut from the 4 lines
	Int_t bin1 = histoADC -> GetXaxis() -> FindBin(compt_low);
	Int_t bin2 = histoADC -> GetXaxis() -> FindBin(line_low);
	Int_t bin3 = histoADC -> GetXaxis() -> FindBin(line_up);
	Int_t bin4 = histoADC -> GetXaxis() -> FindBin(compt_up);
	
	
	Double_t frac1 = (compt_low-histoADC->GetXaxis()->GetBinLowEdge(bin1))/(histoADC->GetXaxis()->GetBinUpEdge(bin1)-histoADC->GetXaxis()->GetBinLowEdge(bin1));
	
	Double_t frac2 = (line_low-histoADC->GetXaxis()->GetBinLowEdge(bin2))/(histoADC->GetXaxis()->GetBinUpEdge(bin2)-histoADC->GetXaxis()->GetBinLowEdge(bin2));
	
	Double_t frac3 = (line_up-histoADC->GetXaxis()->GetBinLowEdge(bin3))/(histoADC->GetXaxis()->GetBinUpEdge(bin3)-histoADC->GetXaxis()->GetBinLowEdge(bin3));
	
	Double_t frac4 = (compt_up-histoADC->GetXaxis()->GetBinLowEdge(bin4))/(histoADC->GetXaxis()->GetBinUpEdge(bin4)-histoADC->GetXaxis()->GetBinLowEdge(bin4));
	
	
	compcnts += (1-frac1)*histoADC->GetBinContent(bin1);
	for (Int_t i=bin1+1; i<bin2; i++){
		compcnts += histoADC->GetBinContent(i);
	}
	compcnts += frac2*histoADC->GetBinContent(bin2);
	
	compcnts += (1-frac3)*histoADC->GetBinContent(bin3);
	for (Int_t i=bin3+1; i<bin4; i++){
		compcnts += histoADC->GetBinContent(i);
	}
	compcnts += frac4*histoADC->GetBinContent(bin4);
	
	peakcnts += (1-frac2)*histoADC->GetBinContent(bin2);
	for (Int_t i=bin2+1; i<bin3; i++){
		peakcnts += histoADC->GetBinContent(i);
	}
	peakcnts += frac3*histoADC->GetBinContent(bin3);
	
	
	if(bg_histoADC){//For the BG counts reuse the code above and the same variables
		
		
		bin2 = bg_histoADC -> GetXaxis() -> FindBin(line_low);
		bin3 = bg_histoADC -> GetXaxis() -> FindBin(line_up);
		
		frac2 = (line_low - bg_histoADC->GetXaxis()->GetBinLowEdge(bin2)) / (bg_histoADC->GetXaxis()->GetBinUpEdge(bin2) - bg_histoADC->GetXaxis()->GetBinLowEdge(bin2));
	
		frac3 = (line_up - bg_histoADC->GetXaxis()->GetBinLowEdge(bin3)) / (bg_histoADC->GetXaxis()->GetBinUpEdge(bin3) - bg_histoADC->GetXaxis()->GetBinLowEdge(bin3));
	
		bgcnts += (1-frac2)*bg_histoADC->GetBinContent(bin2);
		for (Int_t i=bin2+1; i<bin3; i++){
			bgcnts += bg_histoADC->GetBinContent(i);
		}
		bgcnts += frac3*bg_histoADC->GetBinContent(bin3);
		
		bgcnts_err = TMath::Sqrt(bgcnts);
	}
	
	
	cout << "\ncenter = " << center << endl;
	cout << "sigma = " << sigma << endl;
	cout << "comptLow start = " << compt_low << endl;
	cout << "lineLow start = " << line_low << endl;
	cout << "lineUp stop = " << line_up << endl;
	cout << "comptUp stop = " << compt_up << endl;
	cout << "line_nbins = " << line_intrv << endl;
	cout << "compt_mbins = " << compt_intrv << endl;
	cout << "peakcnts = " << peakcnts << endl;
	cout << "peakcnts err = " << sqrt(peakcnts) << endl;
	cout << "raw comptcnts = " << compcnts << endl;
	cout << "raw comptcnts err = " << sqrt(compcnts) << endl;
	
	peakcnts_err = TMath::Sqrt(peakcnts);
	Double_t est_compcnts = (line_intrv/compt_intrv)*compcnts;
	Double_t est_compcnts_err = (line_intrv/compt_intrv)*sqrt(compcnts);
	
	
	if(bg_histoADC){
		
		cout << "bg counts = " << bgcnts << endl;
		cout << "bg counts err = " << bgcnts_err << endl;
		
	}
	
	
	cout << "est comptcnts = " << est_compcnts << endl;
	cout << "est comptcnts err = " << est_compcnts_err << endl;
	
	compcnts = est_compcnts;
	compcnts_err = est_compcnts_err;
	
	if (bg_histoADC==0){
	//We are working with a general BG acquired with the "signal" and it is used only to estimate a detection limit
	bgcnts = 0;
	bgcnts_err = 0;
	
	//In this situation the peak-counts are the BG itself
	det_lim = 2.86 + 4.87*TMath::Sqrt(1.36 + peakcnts); //From the Gator paper
	
	linecnts = peakcnts - est_compcnts;
	linecnts_err = TMath::Sqrt(peakcnts+(line_intrv/compt_intrv)*(line_intrv/compt_intrv)*compcnts); 
	
	
	cout << "linecnts = " << linecnts << endl;
	cout << "linecnts err = " << linecnts_err << endl;
	} else {
	//Here I have also the acquired "blanck" BG (properly rescaled)
		
		det_lim = 2.86 + 4.87*TMath::Sqrt(1.36 + (line_intrv/compt_intrv)*(line_intrv/compt_intrv)*compcnts + bgcnts); //From the Gator paper
		
		linecnts = peakcnts - est_compcnts - bgcnts;
		linecnts_err = TMath::Sqrt(peakcnts + (line_intrv/compt_intrv)*(line_intrv/compt_intrv)*compcnts + bgcnts);
		
		cout << "linecnts = " << linecnts << endl;
		cout << "linecnts err = " << linecnts_err << endl;
		
	}
	cout << "detect limit = " << det_lim << "\n\n\n" << endl;
	
	
	TLine* tlinecenter = new TLine(center,workcanv->cd()->GetUymin(),center,workcanv->cd()->GetUymax());
	tlinecenter -> SetLineStyle(3);
	tlinecenter -> SetLineColor(kGreen+1);
	tlinecenter -> Draw("SAME");
	
	TLine* tline1 = new TLine(line_low,workcanv->cd()->GetUymin(),line_low,workcanv->cd()->GetUymax());
	tline1 -> SetLineStyle(3);
	tline1 -> SetLineColor(kRed);
	tline1 -> Draw("SAME");
	
	TLine* tline2 = new TLine(line_up,workcanv->cd()->GetUymin(),line_up,workcanv->cd()->GetUymax());
	tline2 -> SetLineStyle(3);
	tline2 -> SetLineColor(kRed);
	tline2 -> Draw("SAME");
	
	TLine* tline3 = new TLine(compt_low,workcanv->cd()->GetUymin(),compt_low,workcanv->cd()->GetUymax());
	tline3 -> SetLineStyle(3);
	tline3 -> SetLineColor(kBlue);
	tline3 -> Draw("SAME");
	
	TLine* tline4 = new TLine(compt_up,workcanv->cd()->GetUymin(),compt_up,workcanv->cd()->GetUymax());
	tline4 -> SetLineStyle(3);
	tline4 -> SetLineColor(kBlue);
	tline4 -> Draw("SAME");
	
	
	
	return;
}
///////////////////////////////////////////////////////////////////////////////////////////


char* formatdigits(Double_t var, char* valuestr, Int_t dig){//By default the digits right to the zeros are 2
	
	
	Int_t nse = dig - ((int)log10(var)+1);
	
	if ((int)log10(var) < 0) nse++;//In this way works fine always
	
	Char_t tmpchar[20];
	
	sprintf(tmpchar,"%%.%df",nse);
	
	sprintf(valuestr,""); //Initialization
	
	sprintf(valuestr,tmpchar,var);

	//cout<<value<<endl;
	
	return valuestr;
}
