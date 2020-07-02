#include "isotopes.h"
 
int EffCalcAll(Char_t s_dir[1000], Int_t NumInEvt)//("pathsimulateddata", total_N_simulated_evts)
{
	

	//gROOT->Reset(); -> this line was here, but it has a problem now: it does not let the variables from isotopes.h to be read (update 05.2020 by Gabriela)
	gStyle->SetPalette(1);
	gStyle->SetFuncColor(2);
  

	Char_t DataPath[1000];
	sprintf(DataPath,"%s/merged/",s_dir);
	
	string string_dir(s_dir); 
	string workdir= string_dir+"/effic/";

	string outfilename = "lines.list";
	outfilename = workdir + outfilename;
	
	Char_t description[1000];
  	Char_t FullFN1[1000], description1[1000];
  	Char_t tmpchar[1000], title[1000];

	//Switches are now in the header files (which should be rewritten for each sample, as done by easygator)	
	
	Bool_t writetxt = true;
	
	Int_t compbins = 10; //number of bins left and right of lines in which estimate the compton BG
	Int_t binx; //Bin corresponding to the line I want to determine the BRxEff
	Int_t leftcompbins, rightcompbins; //Used in non symmetric Compton estimation


//////    Define the branching ratio (BR) for the main lines  
	Float_t BR46 = 0.0425; // 46 keV of i_210Pb
	Float_t BR186 = 0.572; // 186 keV of 235U
	Float_t BR239 = 0.436;  // 239 keV of 212Pb
	Float_t BR339 = 0.114;  // 339 keV of 228Ac
	Float_t BR478 = 0.1052; // 478 of 7Be
	Float_t BR583 = 0.3054; // 583 keV of 208Tl (from nucleide.org)
	Float_t BR911 = 0.262;  // 911 keV of 228Ac
	Float_t BR969 = 0.159;  // 969 keV of 228Ac
	Float_t BR2615 = 0.3584; // 2615 keV of 208Tl
	Float_t BR295 = 0.184;  // 295 keV of 214Pb
	Float_t BR352 = 0.356;  // 352 keV of 214Pb
	Float_t BR609 = 0.4549;  // 609 keV of 214Bi
	Float_t BR803 = 0.0000121; // 803.1 keV of 210Po
	Float_t BR847 = 1.00; // 846.771 keV of 56Co
	Float_t BR1001 = 0.00846; // 1001 keV of 234mPa
	Float_t BR1120 = 0.1491; // 1120 keV of 214Bi
	Float_t BR1765 = 0.1531; // 1765 keV of 214Bi
	Float_t BR1173 = 0.9985; // 1173 keV of 60Co
	Float_t BR1238 = 0.676;  // 1238 of 56Co
	Float_t BR1332 = 0.9998; // 1332 keV of 60Co
	Float_t BR1460 = 0.1055; // 1460 keV of 40K
	Float_t BR835 = 0.999746; // 835 keV of 54Mn
	Float_t BR889 = 0.99984;  // 889 keV of 46Sc
	Float_t BR1120s = 0.99987;  // 1120 keV of 46Sc
	Float_t BR662 = 0.8499;  // 662 keV of 137Cs
	Float_t BR811 = 0.99;  // 811 keV of 58Co

// Use EffCalcLine.cpp for other individual isotopes (e.g. 110mAg)
//	Float_t BR658 = 0.940;  // 658 keV of 110mAg
//	Float_t BR885 = 0.722;  // 885 keV of 110mAg		
//	Float_t BR937 = 0.3413;  // 937.5 keV of 110mAg


Int_t point = 0;
TGraphErrors* g_effic = new TGraphErrors();


//-------- Starting with the 232Th chain --------------//
if(i_232Th){	
	
	TCanvas* c1 = new TCanvas("c1","Simulated Spectra",870,500);
	c1->SetLogy();
  
	TLegend* leg = new TLegend(0.6,0.7,0.9,0.9);
    
	sprintf(FullFN1,"%s232Th.root",DataPath);
	sprintf(description1," ^{232}Th Simulation");
	cout<<FullFN1<<endl;
    
	TChain* t1 = new TChain("t1");
	t1->Add(FullFN1);
    
	TH1F* h1 = new TH1F("h1",description1,27000,0,2700);
  
      
	h1->SetXTitle("Energy [keV]");
	h1->SetYTitle("counts");
	h1->SetStats(0);
	t1->Draw("GeEtot>>h1");
	
	Int_t NumInEvtTh = NumInEvt; //Number of simulated decays


// --------------- Calculate the efficiencies ------------------- \\

// ************  238.6 keV from 212Pb (44 % BR)  ************** \\
	binx = h1 -> FindBin(238.632);
	Float_t BRxEff239 = (h1->GetBinContent(binx) - (h1->Integral(binx-(compbins+1),binx-2)/compbins + h1->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvtTh;

	Float_t RealEff239 = BRxEff239 / BR239;
  
	cout<<"Efficiency x BR (239): "<<BRxEff239<<endl;
	cout<<"Real Efficiency (239): "<<RealEff239<<endl;
 
	g_effic -> SetPoint(point,238.632,RealEff239);
	g_effic -> SetPointError(point,0.0,0.1*RealEff239);
	point++;
 
// ************  338.32 keV from 228Ac (11 % BR)  ************** \\
	binx = h1 -> FindBin(338.320);
	
	Float_t BRxEff339 = (h1->GetBinContent(binx) - (h1->Integral(binx-(compbins+1),binx-2)/compbins + h1->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvtTh;
	
	//Float_t BRxEff339 = (h1->GetBinContent(339) - (h1->Integral(333,337)/5 + h1->Integral(341,355)/5)/2)/NumInEvtTh;
 
 	Float_t RealEff339 = BRxEff339 / BR339;

 	cout<<"Efficiency x BR (338): "<<BRxEff339<<endl;
 	cout<<"Real Efficiency (338): "<<RealEff339<<endl;
	
	g_effic -> SetPoint(point,338.320,RealEff339);
	g_effic -> SetPointError(point,0.0,0.1*RealEff339);
	point++;
	
// ************  583.2 keV from 208Tl (30.4 % BR)  ************** \\
//NOTE: At 583.4 there the peaks of 228Ac 228Pa (visible) ==> Bias on the left the Compton counting
	rightcompbins = 1;
	leftcompbins = 5;
	binx = h1 -> FindBin(583.187);
	
	Float_t BRxEff583 = (h1->Integral(binx,binx+1) - 2*(h1->Integral(binx-(leftcompbins+1),binx-2)/leftcompbins + h1->Integral(binx+2,binx+(rightcompbins+1))/rightcompbins)/2)/NumInEvtTh;
	
	//Float_t BRxEff583 = (h1->GetBinContent(584) - (h1->Integral(578,582)/5 + h1->Integral(586,590)/5)/2)/NumInEvtTh;
 
 	Float_t RealEff583 = BRxEff583 / BR583;

 	cout<<"Efficiency x BR (583): "<<BRxEff583<<endl;
 	cout<<"Real Efficiency (583): "<<RealEff583<<endl;
 	
 	g_effic -> SetPoint(point,583.187,RealEff583);
	g_effic -> SetPointError(point,0.0,0.1*RealEff583);
	point++;

// ************  911.196 keV from 228Ac (27 % BR)  **************/
	binx = h1 -> FindBin(911.2); //Geant4 for doesn't know exactly the energy of this line..... this should adjust the things
	
	Float_t BRxEff911 = (h1->GetBinContent(binx) - (h1->Integral(binx-(compbins+1),binx-2)/compbins + h1->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvtTh;
	
	//Float_t BRxEff911 = (h1->GetBinContent(912) - (h1->Integral(906,910)/5 + h1->Integral(914,918)/5)/2)/NumInEvtTh;

	Float_t RealEff911 = BRxEff911 / BR911;

	cout<<"Efficiency x BR (911): "<<BRxEff911<<endl;
	cout<<"Real Efficiency (911): "<<RealEff911<<endl;
	
	g_effic -> SetPoint(point,911.196,RealEff911);
	g_effic -> SetPointError(point,0.0,0.1*RealEff911);
	point++;

// ************  968.7 keV from 228Ac (16 % BR)  **************/
	binx = h1 -> FindBin(968.96);
	Float_t BRxEff969 = (h1->GetBinContent(binx) - (h1->Integral(binx-(compbins+1),binx-2)/compbins + h1->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvtTh;
	
	//Float_t BRxEff969 = (h1->GetBinContent(969) - (h1->Integral(963,967)/5 + h1->Integral(976,980)/5)/2)/NumInEvtTh;

	Float_t RealEff969 = BRxEff969 / BR969;
 
	cout<<"Efficiency x BR (969): "<<BRxEff969<<endl;
	cout<<"Real Efficiency (969): "<<RealEff969<<endl;
	
	g_effic -> SetPoint(point,968.96,RealEff969);
	g_effic -> SetPointError(point,0.0,0.1*RealEff969);
	point++;

// ************  2614.5 keV from 208Tl (35.6 % BR)  **************/
	binx = h1 -> FindBin(2614.511);
	Float_t BRxEff2615 = (h1->GetBinContent(binx) - (h1->Integral(binx-(compbins+1),binx-2)/compbins + h1->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvtTh;

	//Float_t BRxEff2615 = (h1->GetBinContent(2615) - (h1->Integral(2610,2614)/5 + h1->Integral(2617,2621)/5))/NumInEvtTh;

	Float_t RealEff2615 = BRxEff2615 / BR2615;
 
	cout<<"Efficiency x BR (2615): "<<BRxEff2615<<endl;
	cout<<"Real Efficiency (2615): "<<RealEff2615<<endl;
	
	g_effic -> SetPoint(point,2614.511,RealEff2615);
	g_effic -> SetPointError(point,0.0,0.1*RealEff2615);
	point++;

	sprintf(title,"%s232Th.C",workdir.c_str());
	c1->SaveAs(title);

	t1->Delete();//Finished with 232Th chain

} //End of the if(i_232Th)	
	
	
	
	

//------ Starting with the 238U chain --------------//
if(i_238U){

	TCanvas *c2 = new TCanvas("c2","Simulated Spectra",870,500);
	c2->SetLogy();

	sprintf(FullFN1,"%s238U.root",DataPath);
	sprintf(description1," ^{238}U Simulation");
	cout<<FullFN1<<endl;

  
	TChain *t1 = new TChain("t1");
	t1->Add(FullFN1);

	TH1F *h2 = new TH1F("h2",description1,27000,0,2700);

	h2->SetXTitle("Energy [keV]");
	h2->SetYTitle("counts");
	h2->SetStats(0);
	t1->Draw("GeEtot>>h2");
	
	Int_t NumInEvtU = NumInEvt;
	
	

// --------------- Calculate the efficiencies ------------------- \\

// ************  92.38keV and 92.80keV from 234Th (2.18% BR and 2.15% BR)  ************** \\
// Since in real data I don't resolve the two peaks, here I have to define a mean BRxEff for 92.6keV (weighted mean)
// All the variables used are defined in this sub-section.

	Int_t bin92a = h2 -> FindBin(92.38);
	Int_t bin92b = h2 -> FindBin(92.75); // the correct position should be 92.75 but sometimes from the simulations it is shifted a bit
	
	Float_t BR92a = 0.0218;
	Float_t BR92b = 0.0215;
	
	Float_t BR92 = BR92a + BR92b;
	
	//Here the stuff is a bit involved
	leftcompbins = 7;
	rightcompbins = 1;
	Float_t BRxEff92a = (h2->GetBinContent(bin92a) - (h2->Integral(bin92a-(leftcompbins+1),bin92a-2)/leftcompbins + h2->Integral(bin92a+2,bin92a+(rightcompbins+1))/rightcompbins)/2)/NumInEvtU;
	
	leftcompbins = 1;
	rightcompbins = 7;
	Float_t BRxEff92b = (h2->Integral(bin92b,bin92b+1) - 2*(h2->Integral(bin92b-(leftcompbins+1),bin92b-2)/leftcompbins + h2->Integral(bin92b+3,bin92b+(rightcompbins+2))/rightcompbins)/2)/NumInEvtU;
	
	Float_t BRxEff92 = BRxEff92a + BRxEff92b;
	
	Float_t RealEff92 = BRxEff92 / BR92;
	
	cout<<"Efficiency x BR (92): "<<BRxEff92<<endl;
	cout<<"Real Efficiency (92): "<<RealEff92<<endl;
	
	g_effic -> SetPoint(point,92.6,RealEff92);
	g_effic -> SetPointError(point,0.0,0.1*RealEff92);
	point++;
	
// ************  295.2 keV from 214Pb (19 % BR)  ************** \\
	binx = h2 -> FindBin(295.224);
	Float_t BRxEff295 = (h2->GetBinContent(binx) - (h2->Integral(binx-(compbins+1),binx-2)/compbins + h2->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvtU;
	
	//Float_t BRxEff295 = (h2->GetBinContent(296) - (h2->Integral(290,294)/5 + h2->Integral(298,302)/5)/2)/NumInEvtU;

	Float_t RealEff295 = BRxEff295 / BR295;

	cout<<"Efficiency x BR (295): "<<BRxEff295<<endl;
	cout<<"Real Efficiency (295): "<<RealEff295<<endl;
	
	g_effic -> SetPoint(point,295.224,RealEff295);
	g_effic -> SetPointError(point,0.0,0.1*RealEff295);
	point++;
	
	// ************  351.9 keV from 214Pb (37 % BR)  **************/
	binx = h2 -> FindBin(351.932);
	Float_t BRxEff352 = (h2->GetBinContent(binx) - (h2->Integral(binx-(compbins+1),binx-2)/compbins + h2->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvtU;
	
	//Float_t BRxEff352 = (h2->GetBinContent(352) - (h2->Integral(346,350)/5 + h2->Integral(354,358)/5)/2)/NumInEvtU;

	Float_t RealEff352 = BRxEff352 / BR352;

	cout<<"Efficiency x BR (352): "<<BRxEff352<<endl;
	cout<<"Real Efficiency (352): "<<RealEff352<<endl;
	
	g_effic -> SetPoint(point,351.932,RealEff352);
	g_effic -> SetPointError(point,0.0,0.1*RealEff352);
	point++;

// ************  609.3 keV from 214Bi (46 % BR)  **************/
	binx = h2 -> FindBin(609.312);
	Float_t BRxEff609 = (h2->GetBinContent(binx) - (h2->Integral(binx-(compbins+1),binx-2)/compbins + h2->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvtU;

	//Float_t BRxEff609 = (h2->GetBinContent(610) - (h2->Integral(604,608)/5 + h2->Integral(612,616)/5)/2)/NumInEvtU;

	Float_t RealEff609 = BRxEff609 / BR609;

	cout<<"Efficiency x BR (609): "<<BRxEff609<<endl;
	cout<<"Real Efficiency (609): "<<RealEff609<<endl;
	
	g_effic -> SetPoint(point,609.312,RealEff609);
	g_effic -> SetPointError(point,0.0,0.1*RealEff609);
	point++;
	
	
	// ************  1001 keV from 234mPa (0.59 % BR)  **************//
	// This fainty line is simulated alone if here cannot be determined (visual check of the spectrum)
	Float_t BRxEff1001, RealEff1001; //Otherwise it is not visible outside
	if((!i_1001keV)&&i_Pa){
		binx = h2 -> FindBin(1001.026);
		BRxEff1001 = (h2->GetBinContent(binx) - (h2->Integral(binx-(compbins+1),binx-2)/compbins + h2->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvtU;
	
	
		//Float_t BRxEff1001 = (h2->GetBinContent(1002) - (h2->Integral(996,1000)/5 + h2->Integral(1004,1008)/5)/2)/NumInEvtU;

		RealEff1001 = BRxEff1001 / BR1001;

		cout<<"Efficiency x BR (1001): "<<BRxEff1001<<endl;
		cout<<"Real Efficiency (1001): "<<RealEff1001<<endl;
	
		g_effic -> SetPoint(point,1001.026,RealEff1001);
		g_effic -> SetPointError(point,0.0,0.1*RealEff1001);
		point++;
	
	}
	
	
// ************  1120.3 keV from 214Bi (15 % BR)  **************/
	binx = h2 -> FindBin(1120.287);
	Float_t BRxEff1120 = (h2->GetBinContent(binx) - (h2->Integral(binx-(compbins+1),binx-2)/compbins + h2->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvtU;
	
	//Float_t BRxEff1120 = (h2->GetBinContent(1121) - (h2->Integral(1115,1119)/5 + h2->Integral(1123,1127)/5)/2)/NumInEvtU;

	Float_t RealEff1120 = BRxEff1120 / BR1120;

	cout<<"Efficiency x BR (1120): "<<BRxEff1120<<endl;
	cout<<"Real Efficiency (1120): "<<RealEff1120<<endl;
	
	g_effic -> SetPoint(point,1120.287,RealEff1120);
	g_effic -> SetPointError(point,0.0,0.1*RealEff1120);
	point++;
	
// ************  1764.5 keV from 214Bi (16 % BR)  **************/
	binx = h2 -> FindBin(1764.494);
	Float_t BRxEff1765 = (h2->GetBinContent(binx) - (h2->Integral(binx-(compbins+1),binx-2)/compbins + h2->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvtU;
	
	//Float_t BRxEff1765 = (h2->GetBinContent(1765) - (h2->Integral(1759,1763)/5 + h2->Integral(1767,1771)/5)/2)/NumInEvtU;

	Float_t RealEff1765 = BRxEff1765 / BR1765;

	cout<<"Efficiency x BR (1765): "<<BRxEff1765<<endl;
	cout<<"Real Efficiency (1765): "<<RealEff1765<<endl;
	
	g_effic -> SetPoint(point,1764.494,RealEff1765);
	g_effic -> SetPointError(point,0.0,0.1*RealEff1765);
	point++;
	
	sprintf(title,"%s238U.C",workdir.c_str());
	c2->SaveAs(title);

	t1->Delete();//Finisched with i_238U chain

} //End of if(i_238U)	




//------ 210Pb from  the 238U chain --------------//
if(i_210Pb){

	TCanvas *c210 = new TCanvas("c210","Simulated Spectra",870,500);
	c210->SetLogy();

	sprintf(FullFN1,"%s210Pb.root",DataPath);
	sprintf(description1," ^{210}Pb Simulation");
	cout<<FullFN1<<endl;

  
	TChain *t1 = new TChain("t1");
	t1->Add(FullFN1);

	TH1F *h210 = new TH1F("h210",description1,10000,0,1000);

	h210->SetXTitle("Energy [keV]");
	h210->SetYTitle("counts");
	h210->SetStats(0);
	t1->Draw("GeEtot>>h210");
	
	Int_t NumInEvtU = NumInEvt;
	
	

// --------------- Calculate the efficiencies ------------------- \\
// try for this low-energy line from Pb-210
//		if(i_210Pb) data_out << "210" << "\t" << "Pb" << "\t" << "46.539" << "\t" << BR46 << "\t" << RealEff46 << "\t" << BRxEff46 << endl;
// ************  46.539 keV from 210Pb (4 % BR)  ************** \\

	binx = h210 -> FindBin(46.5);
	Float_t BRxEff46 = (h210->GetBinContent(binx) - (h210->Integral(binx-(compbins+1),binx-2)/compbins + h210->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvtU;
	


	Float_t RealEff46 = BRxEff46 / BR46;

	cout<<"Efficiency x BR (46): "<<BRxEff46<<endl;
	cout<<"Real Efficiency (46): "<<RealEff46<<endl;
	
	g_effic -> SetPoint(point,46.5,RealEff46);
	g_effic -> SetPointError(point,0.0,0.1*RealEff46);
	point++;

// ************  83.1 keV from 210Po (0.0012 % BR)  ************** \\

	binx = h210 -> FindBin(803.1);
	Float_t BRxEff803 = (h210->GetBinContent(binx) - (h210->Integral(binx-(compbins+1),binx-2)/compbins + h210->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvtU;
	


	Float_t RealEff803 = BRxEff803 / BR803;

	cout<<"Efficiency x BR (803): "<<BRxEff803<<endl;
	cout<<"Real Efficiency (803): "<<RealEff803<<endl;
	
	g_effic -> SetPoint(point,803.1,RealEff803);
	g_effic -> SetPointError(point,0.0,0.1*RealEff803);
	point++;
		
	sprintf(title,"%s210Pb.C",workdir.c_str());
	c210->SaveAs(title);

	t1->Delete();//Finished with 210Pb chain

} //End of the if(i_210Pb)	
	
	
	
//------ Starting with the 40K --------------//
if(i_40K){

	TCanvas* c3 = new TCanvas("c3","Simulated Spectra",870,500);
	c3->SetLogy();
	sprintf(FullFN1,"%s40K.root",DataPath);
	sprintf(description1," ^{40}K Simulation");
	cout<<FullFN1<<endl;

	TChain *t1 = new TChain("t1");
	t1->Add(FullFN1);

	TH1F *h3 = new TH1F("h3",description1,27000,0,2700);

	h3->SetXTitle("Energy [keV]");
	h3->SetYTitle("counts");
	h3->SetStats(0);
	t1->Draw("GeEtot>>h3");
	
	Int_t NumInEvtK = NumInEvt;
	
	
// ------- Calculate the efficiencies (only the line at 1460.9 KeV) ------//
//NOTE: This is the highest energy line.... no Compton affects it.
	binx = h3 -> FindBin(1460.882);
	Float_t BRxEff1460 = h3->GetBinContent(binx)/NumInEvtK;
	
	//Float_t BRxEff1460 = h3->GetBinContent(1461)/NumInEvtK;

	Float_t RealEff1460 = BRxEff1460 / BR1460;

	cout<<"Efficiency x BR (1460): "<<BRxEff1460<<endl;
	cout<<"Real Efficiency (1460): "<<RealEff1460<<endl;
	
	g_effic -> SetPoint(point,1460.882,RealEff1460);
	g_effic -> SetPointError(point,0.0,0.1*RealEff1460);
	point++;
	
	sprintf(title,"%s40K.C",workdir.c_str());
	c3->SaveAs(title);
	
	
	t1->Delete(); //Finished with 40K element
	
} //End of if(i_40K)	
	
	
//------ Starting with the 7Be --------------//
if(i_7Be){

	TCanvas* c7Be = new TCanvas("c3","Simulated Spectra",870,500);
	c7Be->SetLogy();
	sprintf(FullFN1,"%s7Be.root",DataPath);
	sprintf(description1," ^{7}Be Simulation");
	cout<<FullFN1<<endl;

	TChain *t1 = new TChain("t1");
	t1->Add(FullFN1);

	TH1F *h7Be = new TH1F("h7Be",description1,27000,0,2700);

	h7Be->SetXTitle("Energy [keV]");
	h7Be->SetYTitle("counts");
	h7Be->SetStats(0);
	t1->Draw("GeEtot>>h7Be");
	
	Int_t NumInEvtK = NumInEvt;
	
	
// ------- Calculate the efficiencies (only the line at 477.595 KeV) ------//
	binx = h7Be -> FindBin(477.6);
	Float_t BRxEff478 = h7Be->GetBinContent(binx)/NumInEvtK;
	


	Float_t RealEff478 = BRxEff478 / BR478;

	cout<<"Efficiency x BR (478): "<<BRxEff478<<endl;
	cout<<"Real Efficiency (478): "<<RealEff478<<endl;
	
	g_effic -> SetPoint(point,477.595,RealEff478);
	g_effic -> SetPointError(point,0.0,0.1*RealEff478);
	point++;
	
	sprintf(title,"%s7Be.C",workdir.c_str());
	c7Be->SaveAs(title);
	
	
	t1->Delete(); //Finished with 7Be element
	
} //End of if(7Be)	
	
	
	
	
//------ Starting with the 60Co --------------//
if(i_60Co){

	sprintf(FullFN1,"%s60Co.root",DataPath);
	sprintf(description1," ^{60}Co Simulation");
	cout<<FullFN1<<endl;

	Int_t NumInEvtCo = NumInEvt;

	TChain* t1 = new TChain("t1");
	t1->Add(FullFN1);

	TCanvas* c4 = new TCanvas("c4","Simulated Spectra",870,500);
	c4->SetLogy();
 
	TH1F* h4 = new TH1F("h4",description1,5400,0,2700);
 
	h4->SetXTitle("Energy [keV]");
	h4->SetYTitle("counts");
	h4->SetStats(0);
	t1->Draw("GeEtot>>h4");


// --------------- Calculate the efficiencies -------------------/
// ************ 1173.2 keV from 60Co (99 % BR)  **************/
	binx = h4 -> FindBin(1173.228);
	Float_t BRxEff1173 = (h4->GetBinContent(binx) - (h4->Integral(binx-(compbins+1),binx-2)/compbins + h4->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvtCo;
	
	//Float_t BRxEff1173 = (h4->GetBinContent(1174) - (h4->Integral(1168,1172)/5 + h4->Integral(1176,1180)/5)/2)/NumInEvtCo;

	Float_t RealEff1173 = BRxEff1173 / BR1173;
 
	cout<<"Efficiency x BR (1173): "<<BRxEff1173<<endl;
	cout<<"Real Efficiency (1173): "<<RealEff1173<<endl;
	
	g_effic -> SetPoint(point,1173.228,RealEff1173);
	g_effic -> SetPointError(point,0.0,0.1*RealEff1173);
	point++;
	
// ************ 1332 keV from 60Co (99 % BR)  **************/
//NOTE: Is clearly visible his own Compton in the neibur bins.... shift the compton interval more to the right
	binx = h4 -> FindBin(1332.495); //It should be 1332.495 but G4.9.3 sometimes gives it at 1332.52
	
	rightcompbins = 5;
	leftcompbins = 3;
	
	Float_t BRxEff1332 = (h4->Integral(binx,binx+1) - 2*(h4->Integral(binx-(leftcompbins+1),binx-2)/leftcompbins + h4->Integral(binx+3,binx+(rightcompbins+2))/rightcompbins)/2)/NumInEvtCo;
	
	//Float_t BRxEff1332 = (h4->GetBinContent(1333) - (h4->Integral(1327,1331)/5 + h4->Integral(1335,1339)/5)/2)/NumInEvtCo;

	Float_t RealEff1332 = BRxEff1332 / BR1332;

	cout<<"Efficiency x BR (1332): "<<BRxEff1332<<endl;
	cout<<"Real Efficiency (1332): "<<RealEff1332<<endl;
	
	g_effic -> SetPoint(point,1332.495,RealEff1332);
	g_effic -> SetPointError(point,0.0,0.1*RealEff1332);
	point++;
	
	sprintf(title,"%s60Co.C",workdir.c_str());
	c4->SaveAs(title);
	

	t1->Delete(); //Finished with 60Co element
	
} //End of if(i_60Co)	
	
	


//------ Starting with the 58Co --------------//
if(i_58Co){

	sprintf(FullFN1,"%s58Co.root",DataPath);
	sprintf(description1," ^{58}Co Simulation");
	cout<<FullFN1<<endl;

	Int_t NumInEvti_58Co = NumInEvt;

	TChain* t1 = new TChain("t1");
	t1->Add(FullFN1);

	TCanvas* c58 = new TCanvas("c58","Simulated Spectra",870,500);
	c58->SetLogy();
 
	TH1F* h58 = new TH1F("h58",description1,5400,0,2700);
 
	h58->SetXTitle("Energy [keV]");
	h58->SetYTitle("counts");
	h58->SetStats(0);
	t1->Draw("GeEtot>>h58");
	
//--------------- Calculate the efficiencies -------------------//
	
// ************ 810.775 keV from 58Co (99 % BR)  ************** \\
//NOTE: This is the highest energy line.... no Compton affects it.
	binx = h58 -> FindBin(810.775);
	Float_t BRxEff811 = (h58->GetBinContent(binx) - (h58->Integral(binx-(compbins+1),binx-2)/compbins))/NumInEvti_58Co;
	
	
	Float_t RealEff811 = BRxEff811 / BR811;
	
	cout<<"Efficiency x BR (811): "<<BRxEff811<<endl;
	cout<<"Real Efficiency (811): "<<RealEff811<<endl;
	
	g_effic -> SetPoint(point,810.775,RealEff811);
	g_effic -> SetPointError(point,0.0,0.1*RealEff811);
	point++;
	
	sprintf(title,"%s58Co.C",workdir.c_str());
	c58->SaveAs(title);
	
	t1->Delete(); //Finished with 58Co element
	
} //End of if(58Co)


// 57Co
// 122.0614 4 	85.60 17 	e 
// 136.4743 5 	10.68 8 	e


//------ Starting with the 56Co --------------//
if(i_56Co){

	sprintf(FullFN1,"%s56Co.root",DataPath);
	sprintf(description1," ^{56}Co Simulation");
	cout<<FullFN1<<endl;

	Int_t NumInEvti_56Co = NumInEvt;

	TChain* t1 = new TChain("t1");
	t1->Add(FullFN1);

	TCanvas* c56 = new TCanvas("c56","Simulated Spectra",870,500);
	c56->SetLogy();
 
	TH1F* h56 = new TH1F("h56",description1,5400,0,2700);
 
	h56->SetXTitle("Energy [keV]");
	h56->SetYTitle("counts");
	h56->SetStats(0);
	t1->Draw("GeEtot>>h4");


// --------------- Calculate the efficiencies -------------------/
// ************  846.771 keV from 56Co ( 100% BR)  **************/
	binx = h56 -> FindBin(846.771);
	Float_t BRxEff847 = (h4->GetBinContent(binx) - (h56->Integral(binx-(compbins+1),binx-2)/compbins + h56->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvti_56Co;
	

	Float_t RealEff847 = BRxEff847 / BR847;
 
	cout<<"Efficiency x BR (847): "<<BRxEff847<<endl;
	cout<<"Real Efficiency (847): "<<RealEff847<<endl;
	
	g_effic -> SetPoint(point,846.771,RealEff847);
	g_effic -> SetPointError(point,0.0,0.1*RealEff847);
	point++;
	
// ************ 1238.282 keV from 56Co (67.6 % BR)  **************/
//NOTE: Is clearly visible his own Compton in the neibur bins.... shift the compton interval more to the right
	binx = h56 -> FindBin(1238.282); 
	
	rightcompbins = 5;
	leftcompbins = 3;
	
	Float_t BRxEff1238 = (h56->Integral(binx,binx+1) - 2*(h56->Integral(binx-(leftcompbins+1),binx-2)/leftcompbins + h56->Integral(binx+3,binx+(rightcompbins+2))/rightcompbins)/2)/NumInEvti_56Co;
	

	Float_t RealEff1238 = BRxEff1238 / BR1238;

	cout<<"Efficiency x BR (1238): "<<BRxEff1238<<endl;
	cout<<"Real Efficiency (1238): "<<RealEff1238<<endl;
	
	g_effic -> SetPoint(point,1238.282,RealEff1238);
	g_effic -> SetPointError(point,0.0,0.1*RealEff1238);
	point++;
	
	sprintf(title,"%s56Co.C",workdir.c_str());
	c56->SaveAs(title);
	

	t1->Delete(); //Finished with 56Co element
	
} //End of if(56Co)	
	
	

	
//------ Starting with the 46Sc --------------//
	
if(i_46Sc){
	
	sprintf(FullFN1,"%s46Sc.root",DataPath);
	sprintf(description1," ^{46}Sc Simulation");
	cout<<FullFN1<<endl;

	Int_t NumInEvtSc = NumInEvt;

	TChain* t1 = new TChain("t1");
	t1->Add(FullFN1);

	TCanvas* c5 = new TCanvas("c5","Simulated Spectra",870,500);
	c5->SetLogy();
 
 	TH1F* h5 = new TH1F("h5",description1,21000,0,2100);
 
	h5->SetXTitle("Energy [keV]");
	h5->SetYTitle("counts");
	h5->SetStats(0);
	t1->Draw("GeEtot>>h5");


// --------------- Calculate the efficiencies ------------------- \\

// ************ 889.3 keV from 46Sc (85 % BR)  ************** \\
	binx = h5 -> FindBin(889.271);
		
	rightcompbins = 5;
	leftcompbins = 3;
		
	Float_t BRxEff889 = (h5->GetBinContent(binx) - (h5->Integral(binx-(leftcompbins+1),binx-2)/leftcompbins + h5->Integral(binx+2,binx+(rightcompbins+1))/rightcompbins)/2)/NumInEvtSc;
		
		
	//Float_t BRxEff889 = (h5->GetBinContent(890) - (h5->Integral(884,888)/5 + h5->Integral(892,896)/5)/2)/NumInEvtSc;

	Float_t RealEff889 = BRxEff889 / BR889;
 
	cout<<"Efficiency x BR (889): "<<BRxEff889<<endl;
	cout<<"Real Efficiency (889): "<<RealEff889<<endl;
	
	g_effic -> SetPoint(point,889.271,RealEff889);
	g_effic -> SetPointError(point,0.0,0.1*RealEff889);
	point++;

// ************ 1120.5 keV from 46Sc (85 % BR)  ************** \\
//NOTE: Is clearly visible his own Compton in the neighbor bins.... shift the compton interval more to the right
	binx = h5 -> FindBin(1120.537);
	Float_t BRxEff1120s = (h5->GetBinContent(binx) - (h5->Integral(binx-(compbins+1),binx-2)/compbins + h5->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvtSc;
 		
	//Float_t BRxEff1120s = h5->GetBinContent(1121)/NumInEvtSc;

	Float_t RealEff1120s = BRxEff1120s / BR1120s;
 
	cout<<"Efficiency x BR (1120): "<<BRxEff1120s<<endl;
	cout<<"Real Efficiency (1120): "<<RealEff1120s<<endl;
	
	g_effic -> SetPoint(point,1120.537,RealEff1120s);
	g_effic -> SetPointError(point,0.0,0.1*RealEff1120s);
	point++;
	
	sprintf(title,"%s46Sc.C",workdir.c_str());
	c5->SaveAs(title);
  
	t1->Delete(); //Finished with 46Sc element
	
} //End of if(i_46Sc)
	
	
	
	
	
	
	
	
//------ Starting with the 137Cs --------------//
if(i_137Cs){

	sprintf(FullFN1,"%s137Cs.root",DataPath);
	sprintf(description1," ^{137}Cs Simulation");
	cout<<FullFN1<<endl;
	
	TChain* t1 = new TChain("t1");
	t1->Add(FullFN1);
	
	TCanvas* c6 = new TCanvas("c6","Simulated Spectra",870,500);
	c6->SetLogy();
	
	TH1F* h6 = new TH1F("h6",description1,21000,0,2100);
	
	h6->SetXTitle("Energy [keV]");
	h6->SetYTitle("counts");
	h6->SetStats(0);
	t1->Draw("GeEtot>>h6");
	
	
	Int_t NumInEvtCs = NumInEvt;
	
	
//--------------- Calculate the efficiencies -------------------//
	
// ************ 661.7 keV from 137Cs (84.99 % BR)  ************** \\
//NOTE: This is the highest energy line.... no Compton affects it.
	binx = h6 -> FindBin(661.657);
	Float_t BRxEff662 = (h6->GetBinContent(binx) - (h6->Integral(binx-(compbins+1),binx-2)/compbins))/NumInEvtCs;
	
	
	//Float_t BRxEff662 = (h6->GetBinContent(662) - (h6->Integral(656,660)/5 + h6->Integral(664,668)/5)/2)/NumInEvtCs;
	
	Float_t RealEff662 = BRxEff662 / BR662;
	
	cout<<"Efficiency x BR (662): "<<BRxEff662<<endl;
	cout<<"Real Efficiency (662): "<<RealEff662<<endl;
	
	g_effic -> SetPoint(point,661.657,RealEff662);
	g_effic -> SetPointError(point,0.0,0.1*RealEff662);
	point++;
	
	sprintf(title,"%s137Cs.C",workdir.c_str());
	c6->SaveAs(title);
	
	t1->Delete(); //Finished with 137Cs element
	
} //End of if(i_137Cs)
	
	
	
	
	
	
	
	
//------ Starting with the 235U (interested only to the 186 keV line)--------------//
if((!i_186keV)&&i_235U){
	
	sprintf(FullFN1,"%s235U.root",DataPath);
	sprintf(description1," ^{235}U Simulation");
	cout<<FullFN1<<endl;
	
	
	
	TChain* t1 = new TChain("t1");
	t1 -> Add(FullFN1);
	
	TCanvas* c8 = new TCanvas("c8","Simulated Spectra",870,500);
	c8 -> SetLogy();
	
	TH1F* h8 = new TH1F("h8",description1,21000,0,2100);
	
	h8 -> SetXTitle("Energy [keV]");
	h8 -> SetYTitle("counts");
	h8 -> SetStats(0);
	t1 -> Draw("GeEtot>>h8");
	
	
	Int_t NumInEvtU5 = NumInEvt;
	
	
//--------------- Calculate the efficiencies -------------------//
	
// ************ 185.712 keV from 235U (57.0 % BR)  **************/
// analysis note: this line also overlaps with the 186 keV line from 226Ra
	binx = h8 -> FindBin(185.712); //Sometimes Geant4 knows it as 185.6 keV ==> must be checked each time 
	Float_t BRxEff186 = (h8->GetBinContent(binx) - (h8->Integral(binx-(compbins+1),binx-2)/compbins))/NumInEvtU5;
	
	//Float_t BRxEff186 = (h8->GetBinContent(186) - (h8->Integral(180,184)/5 + h8->Integral(188,192)/5)/2)/NumInEvtU5;
	
	Float_t RealEff186 = BRxEff186 / BR186;
	
	cout<<"Efficiency x BR (186): "<<BRxEff186<<endl;
	cout<<"Real Efficiency (186): "<<RealEff186<<endl;
	
	g_effic -> SetPoint(point,185.712,RealEff186);
	g_effic -> SetPointError(point,0.0,0.1*RealEff186);
	point++;
	
	sprintf(title,"%s235U.C",workdir.c_str());
	c8->SaveAs(title);
	
	t1->Delete(); //Finished with 235U element
}
	
	
	
	
	
	
	
if(i_1001keV&&i_Pa){
//--------- Starting with the 1001 KeV 234m fainty line --------------//
//This is simulated only if and when it is necessary other wise from the 238U Chain it be taken
	
	sprintf(FullFN1,"%s1001keV.root",DataPath);
	sprintf(description1," 1001 KeV ^{234m}Pa Simulation");
	cout<<FullFN1<<endl;
	
	
	TChain* t1 = new TChain("t1");
	t1->Add(FullFN1);
	
	TCanvas* c7 = new TCanvas("c7","Simulated Spectra",870,500);
	c7->SetLogy();
	
	TH1F* h7 = new TH1F("h7",description1,21000,0,2100);
	
	h7->SetXTitle("Energy [keV]");
	h7->SetYTitle("counts");
	h7->SetStats(0);
	t1->Draw("GeEtot>>h7");
	
	
	Int_t NumInEvt1001 = NumInEvt;
	
	
//----------------- Calculate the efficiencies -------------------\\
// *************** 1001 KeV from 234mPa (no BR)  **************** \\
	
	RealEff1001 = h7->GetBinContent(h7->FindBin(1001.026))/NumInEvt1001;
	
	BRxEff1001 = RealEff1001 * BR1001;
	
	cout<<"Efficiency x BR (1001): "<<BRxEff1001<<endl;
	cout<<"Real Efficiency (1001): "<<RealEff1001<<endl;
	
	g_effic -> SetPoint(point,1001.026,RealEff1001);
	g_effic -> SetPointError(point,0.0,0.1*RealEff1001);
	point++;
	
	sprintf(title,"%s1001keV.C",workdir.c_str());
	c7->SaveAs(title);
	
	t1->Delete(); //Finished with 1001 KeV line from 234mPa
	
} //End of if(i_1001keV&&i_Pa)
	
	





	
if(i_186keV&&i_235U){
//------------ Starting with the 186 KeV 235U -------------------//
//This is simulated only if and when it is necessary, otherwise it can be used the 235U isotope decay simulation
	
	sprintf(FullFN1,"%s186keV.root",DataPath);
	sprintf(description1," 186 KeV ^{235}U Simulation");
	cout<<FullFN1<<endl;
	
	
	TChain* t1 = new TChain("t1");
	t1->Add(FullFN1);
	
	TCanvas* c8 = new TCanvas("c8","Simulated Spectra",870,500);
	c8->SetLogy();
	
	TH1F* h8 = new TH1F("h8",description1,21000,0,2100);
	
	h8->SetXTitle("Energy [keV]");
	h8->SetYTitle("counts");
	h8->SetStats(0);
	t1->Draw("GeEtot>>h8");
	
	
	Int_t NumInEvt186 = NumInEvt;
	
//------------------ Calculate the efficiencies -------------------//
	
//*************** 185.7 KeV from 235U (no BR)  ****************\\
	
	Float_t RealEff186 = h8->GetBinContent(h8->FindBin(185.720))/NumInEvt186;
	
	Float_t BRxEff186 = RealEff186 * BR186;
	
	cout<<"Efficiency x BR (186): "<<BRxEff186<<endl;
	cout<<"Real Efficiency (186): "<<RealEff186<<endl;
	
	g_effic -> SetPoint(point,185.720,RealEff186);
	g_effic -> SetPointError(point,0.0,0.1*RealEff186);
	point++;
	
	sprintf(title,"%s186keV.C",workdir.c_str());
	c8->SaveAs(title);
	
	t1->Delete(); //Finished with 186 KeV line from 235U
	
} //End of if(i_186keV&&i_235U)




if(i_54Mn){
	
	TCanvas* c9 = new TCanvas("c9","Simulated Spectra",870,500);
	c9->SetLogy();
	sprintf(FullFN1,"%s54Mn.root",DataPath);
	sprintf(description1," ^{54}Mn Simulation");
	cout<<FullFN1<<endl;

	TChain *t1 = new TChain("t1");
	t1->Add(FullFN1);

	TH1F *h9 = new TH1F("h9",description1,27000,0,2700);

	h9->SetXTitle("Energy [keV]");
	h9->SetYTitle("counts");
	h9->SetStats(0);
	t1->Draw("GeEtot>>h9");
	
	Int_t NumInEvtMn = NumInEvt;
	
	
// ------- Calculate the efficiencies ------//
	binx = h9 -> FindBin(834.838);
	Float_t BRxEff835 = (h9->GetBinContent(binx) - (h9->Integral(binx-(compbins+1),binx-2)/compbins))/NumInEvtMn;
	
	Float_t RealEff835 = BRxEff835 / BR835;

	cout<<"Efficiency x BR (835): "<<BRxEff835<<endl;
	cout<<"Real Efficiency (835): "<<RealEff835<<endl;
	
	g_effic -> SetPoint(point,834.838,RealEff835);
	g_effic -> SetPointError(point,0.0,0.1*RealEff835);
	point++;
	
	sprintf(title,"%s54Mn.C",workdir.c_str());
	c9->SaveAs(title);
	
	
	t1->Delete(); //Finished with 54Mn isotope
	
}	

TCanvas* effCanv = new TCanvas("effCanv","",870,500);
effCanv -> SetLogy();
g_effic -> SetMarkerStyle(20);
g_effic -> Draw("AP");
sprintf(title,"%sefficplot.root",workdir.c_str());
effCanv->SaveAs(title);


//---------- Print out a file with all the efficiences ------------//
if(writetxt){

	cout<<tmpchar<<endl;
	ofstream data_out(outfilename.c_str()); //This file will be the input of the sampleanalysis program
	if(data_out.fail()){
		cout<< "can't open file" <<endl; exit(1);
    } else {
    
		if(i_210Pb) data_out << "210" << "\t" << "Pb" << "\t" << "46.539" << "\t" << BR46 << "\t" << RealEff46 << "\t" << BRxEff46 << endl;
		if(i_238U) data_out << "234" << "\t" << "Th" << "\t" << "92.6" << "\t" << BR92 << "\t" << RealEff92 << "\t" << BRxEff92 << endl;
		if(i_235U) data_out << "235" << "\t" << "U" << "\t" << "185.720" << "\t" << BR186 << "\t" << RealEff186 << "\t" << BRxEff186 << endl;
		if(i_232Th) data_out << "212" << "\t" << "Pb" << "\t" << "238.632" << "\t" << BR239 << "\t" << RealEff239 << "\t" << BRxEff239 << endl;
		if(i_238U) data_out << "214" << "\t" << "Pb" << "\t" << "295.224" << "\t" << BR295 << "\t" << RealEff295 << "\t" << BRxEff295 << endl;
		if(i_232Th) data_out << "228" << "\t" << "Ac" << "\t" << "338.32" << "\t" << BR339 << "\t" << RealEff339 << "\t" << BRxEff339 << endl;
		if(i_238U) data_out << "214" << "\t" << "Pb" << "\t" << "351.932" << "\t" << BR352 << "\t" << RealEff352 << "\t" << BRxEff352 << endl;
		if(i_7Be) data_out << "7" << "\t" << "Be" << "\t" << "477.595" << "\t" << BR478 << "\t" << RealEff478 << "\t" << BRxEff478 << endl;
		if(i_232Th) data_out << "208" << "\t" << "Tl" << "\t" << "583.187" << "\t" << BR583 << "\t" << RealEff583 << "\t" << BRxEff583 << endl;
		if(i_238U) data_out << "214" << "\t" << "Bi" << "\t" << "609.312" << "\t" << BR609 << "\t" << RealEff609 << "\t" << BRxEff609 << endl;
		if(i_137Cs) data_out << "137" << "\t" << "Cs" << "\t" << "661.657" << "\t" << BR662 << "\t" << RealEff662 << "\t" << BRxEff662 << endl;
		if(i_210Pb) data_out << "210" << "\t" << "Pb" << "\t" << "803.1" << "\t" << BR803 << "\t" << RealEff803 << "\t" << BRxEff803 << endl;
		if(i_54Mn) data_out << "54" << "\t" << "Mn" << "\t" << "834.838" << "\t" << BR835 << "\t" << RealEff835 << "\t" << BRxEff835 << endl;
		if(i_46Sc)data_out << "46" << "\t" << "Sc" << "\t" << "889.271" << "\t" << BR889 << "\t" << RealEff889 << "\t" << BRxEff889 << endl;
		if(i_232Th) data_out << "228" << "\t" << "Ac" << "\t" << "911.196" << "\t" << BR911 << "\t" << RealEff911 << "\t" << BRxEff911 << endl;
		if(i_232Th) data_out << "228" << "\t" << "Ac" << "\t" << "968.96" << "\t" << BR969 << "\t" << RealEff969 << "\t" << BRxEff969 << endl;
		if(i_Pa) data_out << "234m" << "\t" << "Pa" << "\t" << "1001.026" << "\t" << BR1001 << "\t" << RealEff1001 << "\t" << BRxEff1001 << endl;
		if(i_238U) data_out << "214" << "\t" << "Bi" << "\t" << "1120.287" << "\t" << BR1120 << "\t" << RealEff1120 << "\t" << BRxEff1120 << endl;
		if(i_46Sc) data_out << "46" << "\t" << "Sc" << "\t" << "1120.537" << "\t" << BR1120s << "\t" << RealEff1120s << "\t" << BRxEff1120s << endl;
		if(i_60Co) data_out << "60" << "\t" << "Co" << "\t" << "1173.228" << "\t" << BR1173 << "\t" << RealEff1173 << "\t" << BRxEff1173 << endl;
		if(i_60Co) data_out << "60" << "\t" << "Co" << "\t" << "1332.492" << "\t" << BR1332 << "\t" << RealEff1332 << "\t" << BRxEff1332 << endl;
		if(i_58Co) data_out << "58" << "\t" << "Co" << "\t" << "810.775" << "\t" << BR811 << "\t" << RealEff811 << "\t" << BRxEff811 << endl;
		if(i_56Co) data_out << "56" << "\t" << "Co" << "\t" << "846.771" << "\t" << BR847 << "\t" << RealEff847 << "\t" << BRxEff847 << endl;
		if(i_56Co) data_out << "56" << "\t" << "Co" << "\t" << "1238.282" << "\t" << BR1238 << "\t" << RealEff1238 << "\t" << BRxEff1238 << endl;
		if(i_40K) data_out << "40" << "\t" << "K" << "\t" << "1460.882" << "\t" << BR1460 << "\t" << RealEff1460 << "\t" << BRxEff1460 << endl;
		if(i_238U) data_out << "214" << "\t" << "Bi" << "\t" << "1764.494" << "\t" << BR1765 << "\t" << RealEff1765 << "\t" << BRxEff1765 << endl;
		if(i_232Th) data_out << "208" << "\t" << "Tl" << "\t" << "2614.511" << "\t" << BR2615 << "\t" << RealEff2615 << "\t" << BRxEff2615 << endl;
		 
		data_out.close();
    }
	
}
 return 0;  
}
