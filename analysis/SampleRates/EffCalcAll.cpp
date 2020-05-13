{
	
	gROOT->Reset();
	gStyle->SetPalette(1);
	gStyle->SetFuncColor(2);
  
//Here are the setup and initialization stuff to be changed manually
	Char_t* file = "merged_10PMTs-R11410";
  Char_t* events = "1e8";
	Char_t DataPath[1000];

	sprintf(DataPath,"/Users/francesco/PhD/Gator/data_analysis/samples/PMTs/10xR11410-20/sim_root_files/");
	
	string workdir = "/Users/francesco/PhD/Gator/data_analysis/samples/PMTs/10xR11410-20/";
	
	string outfilename = "lines.list";
	outfilename = workdir + outfilename;
	
	Char_t description[1000];
  
	Char_t FullFN1[1000], description1[1000];
  
	Char_t tmpchar[1000], title[1000];
	
	//Switches
	Bool_t U238 = true; //If the 238U chain is simulated
	Bool_t Th232 = true; //If the 232Th chain is simulated
	Bool_t U235 = true; //If want or not the 235U info
	Bool_t U186 = true; //To calculate the 186 keV BRxEff from direct gamma simulation and not from the 235U decay
	Bool_t K40 = true;
	Bool_t Co60 = true;
	Bool_t Cs137 = true;
	Bool_t sc = true; //If 46Sc is simulated
	Bool_t Pa1001 = false; //To calculate the 1001 keV BRxEff from direct gamma simulation and not from the 238U decay chain
	Bool_t Pa = true; //If want or not the 234mPa info
	Bool_t Mn54 = true; //If I want Mn54 info
	
	Bool_t writetxt = true;
	
	Int_t compbins = 10; //number of bins left and right of lines in which estimate the compton BG
	Int_t binx; //Bin corresponding to the line I want to determine the BRxEff
	Int_t leftcompbins, rightcompbins; //Used in non simmetric Compton estimation


//////    Define the branching ratio (BR) for the main lines  
	Float_t BR186 = 0.570; // 186 keV of 235U
	Float_t BR239 = 0.436;  // 239 keV of 212Pb
	Float_t BR339 = 0.114;  // 339 keV of 228Ac
	Float_t BR583 = 0.3054; // 583 keV of 208Tl (from nucleide.org)
	Float_t BR911 = 0.262;  // 911 keV of 228Ac
	Float_t BR969 = 0.159;  // 969 keV of 228Ac
	Float_t BR2615 = 0.3584; // 2615 keV of 208Tl
	Float_t BR295 = 0.184;  // 295 keV of 214Pb
	Float_t BR352 = 0.356;  // 352 keV of 214Pb
	Float_t BR609 = 0.4549;  // 609 keV of 214Bi
	Float_t BR1001 = 0.00846; // 1001 keV of 234mPa
	Float_t BR1120 = 0.1491; // 1120 keV of 214Bi
	Float_t BR1765 = 0.1531; // 1765 keV of 214Bi
	Float_t BR1173 = 0.9985; // 1173 keV of 60Co
	Float_t BR1332 = 0.9998; // 1332 keV of 60Co
	Float_t BR1460 = 0.1055; // 1460 keV of 40K
	Float_t BR835 = 0.999746; // 835 keV of 54Mn
	Float_t BR889 = 0.99984;  // 889 keV of 46Sc
	Float_t BR1120s = 0.99987;  // 1120 keV of 46Sc
	Float_t BR662 = 0.8499;  // 662 keV of 137Cs


Int_t point = 0;
TGraphErrors* g_effic = new TGraphErrors();


//-------- Starting with the 232Th chain --------------//
if(Th232){	
	
	TCanvas* c1 = new TCanvas("c1","Simulated Spectra",870,500);
	c1->SetLogy();
  
	TLegend* leg = new TLegend(0.6,0.7,0.9,0.9);
    
	sprintf(FullFN1,"%s%s_232Th_%s.root",DataPath,file,events);
	sprintf(description1,"%s ^{232}Th Simulation",file);
	cout<<FullFN1<<endl;
    
	TChain* t1 = new TChain("t1");
	t1->Add(FullFN1);
    
	TH1F* h1 = new TH1F("h1",description1,27000,0,2700);
  
      
	h1->SetXTitle("Energy [keV]");
	h1->SetYTitle("counts");
	h1->SetStats(0);
	t1->Draw("GeEtot>>h1");
	
	Int_t NumInEvtTh = 100000000; //Number of simulated 232Th decays


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
 
// ************  338.32 keV from 214Pb (11 % BR)  ************** \\
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

// ************  911.196 keV from 222Ac (27 % BR)  **************/
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

	sprintf(title,"%s%s_232Th.C",workdir.c_str(),file);
	c1->SaveAs(title);

	t1->Delete();//Finished with 232Th chain

} //End of the if(Th232)	
	
	
	
	

//------ Starting with the 238U chain --------------//
if(U238){

	TCanvas *c2 = new TCanvas("c2","Simulated Spectra",870,500);
	c2->SetLogy();

	sprintf(FullFN1,"%s%s_238U_%s.root",DataPath,file,events);
	sprintf(description1,"%s ^{238}U Simulation",file);
	cout<<FullFN1<<endl;

  
	TChain *t1 = new TChain("t1");
	t1->Add(FullFN1);

	TH1F *h2 = new TH1F("h2",description1,27000,0,2700);

	h2->SetXTitle("Energy [keV]");
	h2->SetYTitle("counts");
	h2->SetStats(0);
	t1->Draw("GeEtot>>h2");
	
	Int_t NumInEvtU = 100000000;
	
	

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
	
	if((!Pa1001)&&Pa){
// ************  1001 keV from 234mPa (0.59 % BR)  **************//
// This fainty line is simulated alone if here cannot be determined (visual check of the spectrum)
	binx = h2 -> FindBin(1001.026);
	Float_t BRxEff1001 = (h2->GetBinContent(binx) - (h2->Integral(binx-(compbins+1),binx-2)/compbins + h2->Integral(binx+2,binx+(compbins+1))/compbins)/2)/NumInEvtU;
	
	
	//Float_t BRxEff1001 = (h2->GetBinContent(1002) - (h2->Integral(996,1000)/5 + h2->Integral(1004,1008)/5)/2)/NumInEvtU;

	Float_t RealEff1001 = BRxEff1001 / BR1001;

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
	
	sprintf(title,"%s%s_238U.C",workdir.c_str(),file);
	c2->SaveAs(title);

	t1->Delete();//Finisched with 238U chain

} //End of if(U238)	


	
	
//------ Starting with the 40K --------------//
if(K40){

	TCanvas* c3 = new TCanvas("c3","Simulated Spectra",870,500);
	c3->SetLogy();
	sprintf(FullFN1,"%s%s_40K_%s.root",DataPath,file,events);
	sprintf(description1,"%s ^{40}K Simulation",file);
	cout<<FullFN1<<endl;

	TChain *t1 = new TChain("t1");
	t1->Add(FullFN1);

	TH1F *h3 = new TH1F("h3",description1,27000,0,2700);

	h3->SetXTitle("Energy [keV]");
	h3->SetYTitle("counts");
	h3->SetStats(0);
	t1->Draw("GeEtot>>h3");
	
	Int_t NumInEvtK = 100000000;
	
	
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
	
	sprintf(title,"%s%s_40K.C",workdir.c_str(),file);
	c3->SaveAs(title);
	
	
	t1->Delete(); //Finisched with 40K element
	
} //End of if(K40)	
	
	
//------ Starting with the 60Co --------------//
if(Co60){

	sprintf(FullFN1,"%s%s_60Co_%s.root",DataPath,file,events);
	sprintf(description1,"%s ^{60}Co Simulation",file);
	cout<<FullFN1<<endl;

	Int_t NumInEvtCo = 100000000;

	TChain* t1 = new TChain("t1");
	t1->Add(FullFN1);

	TCanvas* c4 = new TCanvas("c4","Simulated Spectra",870,500);
	c4->SetLogy();
 
	TH1F* h4 = new TH1F("h4",description1,27000,0,2700);
 
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
	
	sprintf(title,"%s%s_60Co.C",workdir.c_str(),file);
	c4->SaveAs(title);
	

	t1->Delete(); //Finisched with 60Co element
	
} //End of if(Co60)	
	
	
//------ Starting with the 46Sc --------------//
	
if(sc){
	
	sprintf(FullFN1,"%s%s_46Sc_%s.root",DataPath,file,events);
	sprintf(description1,"%s ^{46}Sc Simulation",file);
	cout<<FullFN1<<endl;

	Int_t NumInEvtSc = 100000000;

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
	
	sprintf(title,"%s%s_46Sc.C",workdir.c_str(),file);
	c5->SaveAs(title);
  
	t1->Delete(); //Finisched with 46Sc element
	
} //End of if(sc)
	
	
	
//------ Starting with the 137Cs --------------//
if(Cs137){

	sprintf(FullFN1,"%s%s_137Cs_%s.root",DataPath,file,events);
	sprintf(description1,"%s ^{137}Cs Simulation",file);
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
	
	
	Int_t NumInEvtCs = 100000000;
	
	
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
	
	sprintf(title,"%s%s_137Cs.C",workdir.c_str(),file);
	c6->SaveAs(title);
	
	t1->Delete(); //Finished with 137Cs element
	
} //End of if(Cs137)
	
	
	
//------ Starting with the 235U (interested only to the 186 keV line)--------------//
if((!U186)&&U235){
	
	sprintf(FullFN1,"%s%s_235U_%s.root",DataPath,file,events);
	sprintf(description1,"%s ^{235}U Simulation",file);
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
	
	
	Int_t NumInEvtU5 = 100000000;
	
	
//--------------- Calculate the efficiencies -------------------//
	
// ************ 185.712 keV from 235U (57.0 % BR)  **************/
	binx = h8 -> FindBin(185.712); //Sometimes Geant4 knows it as 185.6 keV ==> must be checked each time 
	Float_t BRxEff186 = (h8->GetBinContent(binx) - (h8->Integral(binx-(compbins+1),binx-2)/compbins))/NumInEvtU5;
	
	//Float_t BRxEff186 = (h8->GetBinContent(186) - (h8->Integral(180,184)/5 + h8->Integral(188,192)/5)/2)/NumInEvtU5;
	
	Float_t RealEff186 = BRxEff186 / BR186;
	
	cout<<"Efficiency x BR (186): "<<BRxEff186<<endl;
	cout<<"Real Efficiency (186): "<<RealEff186<<endl;
	
	g_effic -> SetPoint(point,185.712,RealEff186);
	g_effic -> SetPointError(point,0.0,0.1*RealEff186);
	point++;
	
	sprintf(title,"%s%s_235U.C",workdir.c_str(),file);
	c8->SaveAs(title);
	
	t1->Delete(); //Finished with 235U element
}
	
	
if(Pa1001&&Pa){
//--------- Starting with the 1001 KeV 234m fainty line --------------//
//This is simulated only if and when it is necessary other wise from the 238U Chain it be taken
	
	sprintf(FullFN1,"%s%s_1001keV_%s.root",DataPath,file,events);
	sprintf(description1,"%s 1001 KeV ^{234m}Pa Simulation",file);
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
	
	
	Int_t NumInEvt1001 = 100000000;
	
	
//----------------- Calculate the efficiencies -------------------\\
// *************** 1001 KeV from 234mPa (no BR)  **************** \\
	
	Float_t RealEff1001 = h7->GetBinContent(h7->FindBin(1001.026))/NumInEvt1001;
	
	Float_t BRxEff1001 = RealEff1001 * BR1001;
	
	cout<<"Efficiency x BR (1001): "<<BRxEff1001<<endl;
	cout<<"Real Efficiency (1001): "<<RealEff1001<<endl;
	
	g_effic -> SetPoint(point,1001.026,RealEff1001);
	g_effic -> SetPointError(point,0.0,0.1*RealEff1001);
	point++;
	
	sprintf(title,"%s%s_1001keV.C",workdir.c_str(),file);
	c7->SaveAs(title);
	
	t1->Delete(); //Finished with 1001 KeV line from 234mPa
	
} //End of if(Pa1001&&Pa)
	
	
	
if(U186&&U235){
//------------ Starting with the 186 KeV 235U -------------------//
//This is simulated only if and when it is necessary, otherwise it can be used the 235U isotope decay simulation
	
	sprintf(FullFN1,"%s%s_186keV_%s.root",DataPath,file,events);
	sprintf(description1,"%s 186 KeV ^{235}U Simulation",file);
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
	
	
	Int_t NumInEvt186 = 100000000;
	
//------------------ Calculate the efficiencies -------------------//
	
//*************** 185.7 KeV from 235U (no BR)  ****************\\
	
	Float_t RealEff186 = h8->GetBinContent(h8->FindBin(185.720))/NumInEvt186;
	
	Float_t BRxEff186 = RealEff186 * BR186;
	
	cout<<"Efficiency x BR (186): "<<BRxEff186<<endl;
	cout<<"Real Efficiency (186): "<<RealEff186<<endl;
	
	g_effic -> SetPoint(point,185.720,RealEff186);
	g_effic -> SetPointError(point,0.0,0.1*RealEff186);
	point++;
	
	sprintf(title,"%s%s_186keV.C",workdir.c_str(),file);
	c8->SaveAs(title);
	
	t1->Delete(); //Finished with 186 KeV line from 235U
	
} //End of if(U186&&U235)


if(Mn54){
	
	TCanvas* c9 = new TCanvas("c9","Simulated Spectra",870,500);
	c9->SetLogy();
	sprintf(FullFN1,"%s%s_54Mn_%s.root",DataPath,file,events);
	sprintf(description1,"%s ^{54}Mn Simulation",file);
	cout<<FullFN1<<endl;

	TChain *t1 = new TChain("t1");
	t1->Add(FullFN1);

	TH1F *h9 = new TH1F("h9",description1,27000,0,2700);

	h9->SetXTitle("Energy [keV]");
	h9->SetYTitle("counts");
	h9->SetStats(0);
	t1->Draw("GeEtot>>h9");
	
	Int_t NumInEvtMn = 100000000;
	
	
// ------- Calculate the efficiencies (only the line at 1460.9 KeV) ------//
//NOTE: This is the highest energy line.... no Compton affects it.
	binx = h9 -> FindBin(834.838);
	Float_t BRxEff835 = (h9->GetBinContent(binx) - (h9->Integral(binx-(compbins+1),binx-2)/compbins))/NumInEvtMn;
	
	Float_t RealEff835 = BRxEff835 / BR835;

	cout<<"Efficiency x BR (835): "<<BRxEff835<<endl;
	cout<<"Real Efficiency (835): "<<RealEff835<<endl;
	
	g_effic -> SetPoint(point,834.838,RealEff835);
	g_effic -> SetPointError(point,0.0,0.1*RealEff835);
	point++;
	
	sprintf(title,"%s%s_54Mn.C",workdir.c_str(),file);
	c9->SaveAs(title);
	
	
	t1->Delete(); //Finished with 54Mn isotope
	
}	

TCanvas* effCanv = new TCanvas("effCanv","",870,500);
effCanv -> SetLogy();
g_effic -> SetMarkerStyle(20);
g_effic -> Draw("AP");
sprintf(title,"%s%s_efficplot.C",workdir.c_str(),file);
effCanv->SaveAs(title);

//---------- Print out a file with all the efficiences ------------//
if(writetxt){

	cout<<tmpchar<<endl;
	ofstream data_out(outfilename.c_str()); //This file will be the input of the sampleanalysis program
	if(data_out.fail()){
		cout<< "can't open file" <<endl; exit(1);
    } else {
    
		if(U238) data_out << "234" << "\t" << "Th" << "\t" << "92.6" << "\t" << BR92 << "\t" << RealEff92 << "\t" << BRxEff92 << endl;
		if(U235) data_out << "235" << "\t" << "U" << "\t" << "185.720" << "\t" << BR186 << "\t" << RealEff186 << "\t" << BRxEff186 << endl;
		if(Th232) data_out << "212" << "\t" << "Pb" << "\t" << "238.632" << "\t" << BR239 << "\t" << RealEff239 << "\t" << BRxEff239 << endl;
		if(U238) data_out << "214" << "\t" << "Pb" << "\t" << "295.224" << "\t" << BR295 << "\t" << RealEff295 << "\t" << BRxEff295 << endl;
		if(Th232) data_out << "228" << "\t" << "Ac" << "\t" << "338.32" << "\t" << BR339 << "\t" << RealEff339 << "\t" << BRxEff339 << endl;
		if(U238) data_out << "214" << "\t" << "Pb" << "\t" << "351.932" << "\t" << BR352 << "\t" << RealEff352 << "\t" << BRxEff352 << endl;
		if(Th232) data_out << "208" << "\t" << "Tl" << "\t" << "583.187" << "\t" << BR583 << "\t" << RealEff583 << "\t" << BRxEff583 << endl;
		if(U238) data_out << "214" << "\t" << "Bi" << "\t" << "609.312" << "\t" << BR609 << "\t" << RealEff609 << "\t" << BRxEff609 << endl;
		if(Cs137) data_out << "137" << "\t" << "Cs" << "\t" << "661.657" << "\t" << BR662 << "\t" << RealEff662 << "\t" << BRxEff662 << endl;
		if(Mn54) data_out << "54" << "\t" << "Mn" << "\t" << "834.838" << "\t" << BR835 << "\t" << RealEff835 << "\t" << BRxEff835 << endl;
		if(sc)data_out << "46" << "\t" << "Sc" << "\t" << "889.271" << "\t" << BR889 << "\t" << RealEff889 << "\t" << BRxEff889 << endl;
		if(Th232) data_out << "228" << "\t" << "Ac" << "\t" << "911.196" << "\t" << BR911 << "\t" << RealEff911 << "\t" << BRxEff911 << endl;
		if(Th232) data_out << "228" << "\t" << "Ac" << "\t" << "968.96" << "\t" << BR969 << "\t" << RealEff969 << "\t" << BRxEff969 << endl;
		if(Pa) data_out << "234m" << "\t" << "Pa" << "\t" << "1001.026" << "\t" << BR1001 << "\t" << RealEff1001 << "\t" << BRxEff1001 << endl;
		if(U238) data_out << "214" << "\t" << "Bi" << "\t" << "1120.287" << "\t" << BR1120 << "\t" << RealEff1120 << "\t" << BRxEff1120 << endl;
		if(sc) data_out << "46" << "\t" << "Sc" << "\t" << "1120.537" << "\t" << BR1120s << "\t" << RealEff1120s << "\t" << BRxEff1120s << endl;
		if(Co60) data_out << "60" << "\t" << "Co" << "\t" << "1173.228" << "\t" << BR1173 << "\t" << RealEff1173 << "\t" << BRxEff1173 << endl;
		if(Co60) data_out << "60" << "\t" << "Co" << "\t" << "1332.492" << "\t" << BR1332 << "\t" << RealEff1332 << "\t" << BRxEff1332 << endl;
		if(K40) data_out << "40" << "\t" << "K" << "\t" << "1460.882" << "\t" << BR1460 << "\t" << RealEff1460 << "\t" << BRxEff1460 << endl;
		if(U238) data_out << "214" << "\t" << "Bi" << "\t" << "1764.494" << "\t" << BR1765 << "\t" << RealEff1765 << "\t" << BRxEff1765 << endl;
		if(Th232) data_out << "208" << "\t" << "Tl" << "\t" << "2614.511" << "\t" << BR2615 << "\t" << RealEff2615 << "\t" << BRxEff2615 << endl;
		 
		data_out.close();
    }
	
}
   
}
