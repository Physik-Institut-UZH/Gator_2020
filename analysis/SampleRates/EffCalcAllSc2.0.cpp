{
	
  gROOT->Reset();
  gStyle->SetPalette(1);
  gStyle->SetFuncColor(2);

  gROOT->ProcessLine(".x FileName.C");
  
  Char_t FullFN1[100], description1[100];
  
  Char_t tmpchar[1000], title[1000];
	
	Bool_t sc = true;

//////    Define the branching ratio (BR) for the main lines  
  Float_t BR46 = 0.0425; // 46 keV of 210Pb
  Float_t BR186 = 0.570; // 286 keV of 235U
  Float_t BR239 = 0.436;  // 239 keV of 212Pb
  Float_t BR339 = 0.114;  // 339 keV of 228Ac
  Float_t BR583 = 0.3054; // 583 keV of 208Tl (from nucleide.org)
  Float_t BR911 = 0.262;  // 911 keV of 228Ac
  Float_t BR969 = 0.159;  // 969 keV of 228Ac
  Float_t BR2615 = 0.3584;// 2615 keV of 208Tl
  Float_t BR295 = 0.184;  // 295 keV of 214Pb
  Float_t BR352 = 0.356;  // 352 keV of 214Pb
  Float_t BR609 = 0.4549;  // 609 keV of 214Bi
  Float_t BR1001 = 0.00846; // 1001 keV of 234mPa
  Float_t BR1120 = 0.1491; // 1120 keV of 214Bi
  Float_t BR1765 = 0.1531; // 1765 keV of 214Bi
  Float_t BR1173 = 0.9985; // 1173 keV of 60Co
  Float_t BR1332 = 0.9998; // 1332 keV of 60Co
  Float_t BR1460 = 0.1055; // 1460 keV of 40K
  Float_t BR889 = 0.99984;  // 889 keV of 46Sc
  Float_t BR1120s = 0.99987;  // 1120 keV of 46Sc
  Float_t BR662 = 0.8499;  // 662 keV of 137Cs


//-------- Starting with the 232Th chain --------------//
	
  TCanvas *c1 = new TCanvas("c1","Simulated Spectra",870,500);
  c1->SetLogy();
  
  TLegend *leg = new TLegend(0.6,0.7,0.9,0.9);
    
  sprintf(FullFN1,"%s%s_Th232_2e6.root",DataPath,file);
  sprintf(description1,"%s ^{232}Th Simulation",file);
  cout<<FullFN1<<endl;
    
  TChain *t1 = new TChain("t1");
  t1->Add(FullFN1);
    
  TH1F *h1 = new TH1F("h1",description1,2700,0,2700);
      
  h1->SetXTitle("Energy [keV]");
  h1->SetYTitle("counts");
  h1->SetStats(0);
  t1->Draw("GeEtot>>h1");
	
	Int_t NumInEvtTh = 2000000; //Number of simulated 232Th decays

// --------------- Calculate the efficiencies -------------------/

// ************  239 keV from 212Pb (44 % BR)  **************/
 Float_t EffBR239 = (h1->GetBinContent(239)-(h1->Integral(228,237)/10+h1->Integral(241,255)/10)/2)/NumInEvtTh;

 Float_t RealEff239 = EffBR239 / BR239;
  
 cout<<"Efficiency x BR (239): "<<EffBR239<<endl;
 cout<<"Real Efficiency (239): "<<RealEff239<<endl;

// ************  339 keV from 214Pb (11 % BR)  **************/
 Float_t EffBR339 = (h1->GetBinContent(339)-(h1->Integral(328,337)/10+h1->Integral(341,350)/10)/2)/NumInEvtTh;
 
 Float_t RealEff339 = EffBR339 / BR339;

 cout<<"Efficiency x BR (339): "<<EffBR339<<endl;
 cout<<"Real Efficiency (339): "<<RealEff339<<endl;

// ************  583 keV from 208Tl (30.4 % BR)  **************/
 Float_t EffBR583 = (h1->GetBinContent(584)-(h1->Integral(573,582)/10+h1->Integral(586,595)/10)/2)/NumInEvtTh;
 
 Float_t RealEff583 = EffBR583 / BR583;

 cout<<"Efficiency x BR (583): "<<EffBR583<<endl;
 cout<<"Real Efficiency (583): "<<RealEff583<<endl;

// ************  911 keV from 222Ac (27 % BR)  **************/
 Float_t EffBR911 = (h1->GetBinContent(912)-(h1->Integral(901,910)/10+h1->Integral(914,923)/10)/2)/NumInEvtTh;

 Float_t RealEff911 = EffBR911 / BR911;

 cout<<"Efficiency x BR (911): "<<EffBR911<<endl;
 cout<<"Real Efficiency (911): "<<RealEff911<<endl;

// ************  969 keV from 228Ac (16 % BR)  **************/
 Float_t EffBR969 = (h1->GetBinContent(969)-(h1->Integral(958,967)/10+h1->Integral(971,980)/10)/2)/NumInEvtTh;

 Float_t RealEff969 = EffBR969 / BR969;
 
 cout<<"Efficiency x BR (969): "<<EffBR969<<endl;
 cout<<"Real Efficiency (969): "<<RealEff969<<endl;

// ************  2615 keV from 208Tl (35.6 % BR)  **************/
 Float_t EffBR2615 = (h1->GetBinContent(2615)-(h1->Integral(2610,2614)/5))/NumInEvtTh;

 Float_t RealEff2615 = EffBR2615 / BR2615;
 
 cout<<"Efficiency x BR (2615): "<<EffBR2615<<endl;
 cout<<"Real Efficiency (2615): "<<RealEff2615<<endl;


   sprintf(title,"./%s/%s_Th232.png",file,file);
   c1->SaveAs(title);

	t1->Delete();//Finisched with 232Th chain
	
	
//------ Starting with the 238U chain --------------//
  TCanvas *c2 = new TCanvas("c2","Simulated Spectra",870,500);
  c2->SetLogy();

  sprintf(FullFN1,"%s%s_U238_2e6.root",DataPath,file);
  sprintf(description1,"%s ^{238}U Simulation",file);
  cout<<FullFN1<<endl;

  
  TChain *t1 = new TChain("t1");
  t1->Add(FullFN1);

  TH1F *h2 = new TH1F("h2",description1,2700,0,2700);

  h2->SetXTitle("Energy [keV]");
  h2->SetYTitle("counts");
  h2->SetStats(0);
  t1->Draw("GeEtot>>h2");
	
	Int_t NumInEvtU = 2000000;
	

// --------------- Calculate the efficiencies -------------------//

// ************  295 keV from 214Pb (19 % BR)  **************/
 Float_t EffBR295 = (h2->GetBinContent(296)-(h2->Integral(285,294)/10+h2->Integral(298,307)/10)/2)/NumInEvtU;

 Float_t RealEff295 = EffBR295 / BR295;

 cout<<"Efficiency x BR (295): "<<EffBR295<<endl;
 cout<<"Real Efficiency (295): "<<RealEff295<<endl;
// ************  352 keV from 214Pb (37 % BR)  **************/
 Float_t EffBR352 = (h2->GetBinContent(352)-(h2->Integral(340,349)/10+h2->Integral(354,363)/10)/2)/NumInEvtU;

 Float_t RealEff352 = EffBR352 / BR352;

 cout<<"Efficiency x BR (352): "<<EffBR352<<endl;
 cout<<"Real Efficiency (352): "<<RealEff352<<endl;

// ************  609 keV from 214Bi (46 % BR)  **************/
 Float_t EffBR609 = (h2->GetBinContent(610)-(h2->Integral(598,607)/10+h2->Integral(612,621)/10)/2)/NumInEvtU;

 Float_t RealEff609 = EffBR609 / BR609;

 cout<<"Efficiency x BR (609): "<<EffBR609<<endl;
 cout<<"Real Efficiency (609): "<<RealEff609<<endl;


// ************  1001 keV from 234mPa (0.59 % BR)  **************//
/* This fainty line is simulated alone
	
 Float_t EffBR1001 = (h2->GetBinContent(1002)-(h2->Integral(991,1000)/10+h2->Integral(1004,1013)/10)/2)/NumInEvtU;

 Float_t RealEff1001 = EffBR1001 / BR1001;

 cout<<"Efficiency x BR (1001): "<<EffBR1001<<endl;
 cout<<"Real Efficiency (1001): "<<RealEff1001<<endl;
*/
	
	
// ************  1120 keV from 214Bi (15 % BR)  **************/
 Float_t EffBR1120 = (h2->GetBinContent(1121)-(h2->Integral(1110,1119)/10+h2->Integral(1123,1132)/10)/2)/NumInEvtU;

 Float_t RealEff1120 = EffBR1120 / BR1120;

 cout<<"Efficiency x BR (1120): "<<EffBR1120<<endl;
 cout<<"Real Efficiency (1120): "<<RealEff1120<<endl;

// ************  1765 keV from 214Bi (16 % BR)  **************/
 Float_t EffBR1765 = (h2->GetBinContent(1765)-(h2->Integral(1755,1764)/10+h2->Integral(1768,1777)/10)/2)/NumInEvtU;

 Float_t RealEff1765 = EffBR1765 / BR1765;

 cout<<"Efficiency x BR (1765): "<<EffBR1765<<endl;
 cout<<"Real Efficiency (1765): "<<RealEff1765<<endl;
	
	sprintf(title,"./%s/%s_238U.png",file,file);
   c2->SaveAs(title);

	t1->Delete();//Finisched with 238U chain



//------ Starting with the 210Pb --------------//	
	
 TCanvas *c210 = new TCanvas("c210","Simulated Spectra",870,500);
 c210->SetLogy();
 sprintf(FullFN1,"%s%s_Pb210_1e6.root",DataPath,file);
 sprintf(description1,"%s ^{210}Pb Simulation",file);
 cout<<FullFN1<<endl;

 

  TChain *t1 = new TChain("t1");
  t1->Add(FullFN1);

  TH1F *h210 = new TH1F("h210",description1,2700,0,2700);

  h210->SetXTitle("Energy [keV]");
  h210->SetYTitle("counts");
  h210->SetStats(0);
  t1->Draw("GeEtot>>h210");
	
	Int_t NumInEvtPb210 = 1000000;
	
	
// ------- Calculate the efficiencies (46.539 keV line) ------//

 //Float_t EffBR47 = h210->GetBinContent(47)/NumInEvtPb210;
 Float_t EffBR47 = (h210->GetBinContent(47)-(h210->Integral(36,45)/10+h210->Integral(48,57)/10)/2)/NumInEvtPb210;

 Float_t RealEff47 = EffBR47 / BR47;

 cout<<"Efficiency x BR (47): "<<EffBR47<<endl;
 cout<<"Real Efficiency (47): "<<RealEff47<<endl;
	
	sprintf(title,"./%s/%s_210Pb.png",file,file);
   c210->SaveAs(title);
	
	
	t1->Delete(); //Finisched with 210Pb element
	
	
	
//------ Starting with the 40K --------------//	
	
 TCanvas *c3 = new TCanvas("c3","Simulated Spectra",870,500);
 c3->SetLogy();
 sprintf(FullFN1,"%s%s_K40_1e6.root",DataPath,file);
 sprintf(description1,"%s ^{40}K Simulation",file);
 cout<<FullFN1<<endl;

 

  TChain *t1 = new TChain("t1");
  t1->Add(FullFN1);

  TH1F *h3 = new TH1F("h3",description1,2700,0,2700);

  h3->SetXTitle("Energy [keV]");
  h3->SetYTitle("counts");
  h3->SetStats(0);
  t1->Draw("GeEtot>>h3");
	
	Int_t NumInEvtK = 1000000;
	
	
// ------- Calculate the efficiencies (only the line at 1460 KeV) ------//

 Float_t EffBR1460 = h3->GetBinContent(1461)/NumInEvtK;

 Float_t RealEff1460 = EffBR1460 / BR1460;

 cout<<"Efficiency x BR (1460): "<<EffBR1460<<endl;
 cout<<"Real Efficiency (1460): "<<RealEff1460<<endl;
	
	sprintf(title,"./%s/%s_40K.png",file,file);
   c3->SaveAs(title);
	
	
	t1->Delete(); //Finisched with 40K element
	
	
	
	
//------ Starting with the 60Co --------------//

 sprintf(FullFN1,"%s%s_Co60_1e6.root",DataPath,file);
 sprintf(description1,"%s ^{60}Co Simulation",file);
 cout<<FullFN1<<endl;

	Int_t NumInEvtCo = 1000000;

 TChain *t1 = new TChain("t1");
 t1->Add(FullFN1);

 TCanvas *c4 = new TCanvas("c4","Simulated Spectra",870,500);
 c4->SetLogy();
 
 TH1F *h4 = new TH1F("h4",description1,2700,0,2700);
 
  h4->SetXTitle("Energy [keV]");
  h4->SetYTitle("counts");
  h4->SetStats(0);
  t1->Draw("GeEtot>>h4");

// --------------- Calculate the efficiencies -------------------/

// ************ 1173 keV from 60Co (99 % BR)  **************/
 Float_t EffBR1173 = (h4->GetBinContent(1174)-(h4->Integral(1163,1172)/10+h4->Integral(1175,1184)/10)/2)/NumInEvtCo;

 Float_t RealEff1173 = EffBR1173 / BR1173;
 
 cout<<"Efficiency x BR (1173): "<<EffBR1173<<endl;
 cout<<"Real Efficiency (1173): "<<RealEff1173<<endl;

// ************ 1332 keV from 60Co (99 % BR)  **************/
 Float_t EffBR1332 = (h4->GetBinContent(1333)-(h4->Integral(1323,1332)/10+h4->Integral(1334,1343)/10)/2)/NumInEvtCo;

 Float_t RealEff1332 = EffBR1332 / BR1332;

 cout<<"Efficiency x BR (1332): "<<EffBR1332<<endl;
 cout<<"Real Efficiency (1332): "<<RealEff1332<<endl;
	
	sprintf(title,"./%s/%s_60Co.png",file,file);
   c4->SaveAs(title);
	

	t1->Delete(); //Finisched with 60Co element
	
	
	
	
//------ Starting with the 46Sc --------------//
	
 sprintf(FullFN1,"%s%s_Sc46_1e6.root",DataPath,file);
 sprintf(description1,"%s ^{46}Sc Simulation",file);
 cout<<FullFN1<<endl;

	Int_t NumInEvtSc = 1000000;

 TChain *t1 = new TChain("t1");
 t1->Add(FullFN1);

 TCanvas *c5 = new TCanvas("c5","Simulated Spectra",870,500);
 c5->SetLogy();
 
 TH1F *h5 = new TH1F("h5",description1,2100,0,2100);
 
  h5->SetXTitle("Energy [keV]");
  h5->SetYTitle("counts");
  h5->SetStats(0);
  t1->Draw("GeEtot>>h5");

// --------------- Calculate the efficiencies -------------------/

  if(sc){
// ************ 889 keV from 46Sc (85 % BR)  **************/
 Float_t EffBR889 = (h5->GetBinContent(h5->FindBin(890))-(h5->Integral(879,888)/10+h5->Integral(892,901)/10)/2)/NumInEvtSc;

 Float_t RealEff889 = EffBR889 / BR889;
 
 cout<<"Efficiency x BR (889): "<<EffBR889<<endl;
 cout<<"Real Efficiency (889): "<<RealEff889<<endl;

// ************ 1120 keV from 46Sc (85 % BR)  **************/
 Float_t EffBR1120s = (h5->GetBinContent(h5->FindBin(1121))-h5->GetBinContent(h5->FindBin(1120)))/NumInEvtSc;

 Float_t RealEff1120s = EffBR1120s / BR1120s;
 
 cout<<"Efficiency x BR (1120): "<<EffBR1120s<<endl;
 cout<<"Real Efficiency (1120): "<<RealEff1120s<<endl;
	  
	  sprintf(title,"./%s/%s_46Sc.png",file,file);
	  c5->SaveAs(title);
  }
	
	t1->Delete(); //Finisched with 46Sc element
	
	
	
	
//------ Starting with the 137Cs --------------//
	
	sprintf(FullFN1,"%s%s_Cs137_1e6.root",DataPath,file);
	sprintf(description1,"%s ^{137}Cs Simulation",file);
	cout<<FullFN1<<endl;
	
	
	
	TChain *t1 = new TChain("t1");
	t1->Add(FullFN1);
	
	TCanvas *c6 = new TCanvas("c6","Simulated Spectra",870,500);
	c6->SetLogy();
	
	TH1F *h6 = new TH1F("h6",description1,2100,0,2100);
	
	h6->SetXTitle("Energy [keV]");
	h6->SetYTitle("counts");
	h6->SetStats(0);
	t1->Draw("GeEtot>>h6");
	
	
	Int_t NumInEvtCs = 1000000;
	
	
//--------------- Calculate the efficiencies -------------------//
	
// ************ 662 keV from 137Cs (84.99 % BR)  **************/
	
	Float_t EffBR662 = (h6->GetBinContent(h6->FindBin(662))-(h6->Integral(651,660)/10+h6->Integral(664,673)/10)/2)/NumInEvtCs;
	
	Float_t RealEff662 = EffBR662 / BR662;
	
	cout<<"Efficiency x BR (662): "<<EffBR1120s<<endl;
	cout<<"Real Efficiency (662): "<<RealEff1120s<<endl;
	
	sprintf(title,"./%s/%s_137Cs.png",file,file);
	c6->SaveAs(title);
	
	t1->Delete(); //Finished with 137Cs element
	
	
	
//--------- Starting with the 1001 KeV 234m fainty line --------------//
	
	sprintf(FullFN1,"%s%s_1001_1e6.root",DataPath,file);
	sprintf(description1,"%s 1001 KeV ^{234m}Pa Simulation",file);
	cout<<FullFN1<<endl;
	
	
	TChain *t1 = new TChain("t1");
	t1->Add(FullFN1);
	
	TCanvas *c7 = new TCanvas("c7","Simulated Spectra",870,500);
	c7->SetLogy();
	
	TH1F *h7 = new TH1F("h7",description1,2100,0,2100);
	
	h7->SetXTitle("Energy [keV]");
	h7->SetYTitle("counts");
	h7->SetStats(0);
	t1->Draw("GeEtot>>h7");
	
	
	Int_t NumInEvt1001 = 100000;
	
//--------------- Calculate the efficiencies -------------------//
	
//*************** 1001 KeV from 234mPa (no BR)  ****************//
	
	Float_t RealEff1001 = h7->GetBinContent(h7->FindBin(1001))/NumInEvt1001;
	
	Float_t EffBR1001 = RealEff1001 * BR1001;
	
	cout<<"Efficiency x BR (1001): "<<EffBR1001<<endl;
	cout<<"Real Efficiency (1001): "<<RealEff1001<<endl;
	
	sprintf(title,"./%s/%s_1001.png",file,file);
	c7->SaveAs(title);
	
	t1->Delete(); //Finished with 1001 KeV line from 234mPa
	
	
	
//------------ Starting with the 186 KeV 235U -------------------//
	
	sprintf(FullFN1,"%s%s_186KeV_1e6.root",DataPath,file);
	sprintf(description1,"%s 186 KeV ^{235}U Simulation",file);
	cout<<FullFN1<<endl;
	
	
	TChain *t1 = new TChain("t1");
	t1->Add(FullFN1);
	
	TCanvas *c8 = new TCanvas("c8","Simulated Spectra",870,500);
	c8->SetLogy();
	
	TH1F *h8 = new TH1F("h8",description1,2100,0,2100);
	
	h8->SetXTitle("Energy [keV]");
	h8->SetYTitle("counts");
	h8->SetStats(0);
	t1->Draw("GeEtot>>h8");
	
	
	Int_t NumInEvt186 = 1000000;
	
//------------------ Calculate the efficiencies -------------------//
	
//*************** 186 KeV from 235U (no BR)  ****************//
	
	Float_t RealEff186 = h8->GetBinContent(h8->FindBin(185.720))/NumInEvt186;
	
	Float_t EffBR186 = RealEff186 * BR186;
	
	cout<<"Efficiency x BR (186): "<<EffBR186<<endl;
	cout<<"Real Efficiency (186): "<<RealEff186<<endl;
	
	sprintf(title,"./%s/%s_186.png",file,file);
	c8->SaveAs(title);
	
	t1->Delete(); //Finished with 186 KeV line from 235U
	
	
	
	
//---------- Print out a file with all the efficiences ------------//

 sprintf(tmpchar,"%s_Overall_eff.txt",file);
 cout<<tmpchar<<endl;
 ofstream data_out(tmpchar);
 if(data_out.fail())
    {
      cout<< "can't open file" <<endl; exit(1);
    }
  else
    {
		data_out << "^{210}Pb" << "\t" << "46" << "\t" << BR46 << "\t" << RealEff46 << "\t" << EffBR46 << "\n";
		data_out << "^{235}U" << "\t" << "186" << "\t" << BR186 << "\t" << RealEff186 << "\t" << EffBR186 << "\n";
      data_out << "^{212}Pb" << "\t" << "239" << "\t" << BR239 << "\t" << RealEff239 << "\t" << EffBR239 << "\n";
      data_out << "^{214}Pb" << "\t" << "295" << "\t" << BR295 << "\t" << RealEff295 << "\t" << EffBR295 << "\n";
      data_out << "^{228}Ac" << "\t" << "339" << "\t" << BR339 << "\t" << RealEff339 << "\t" << EffBR339 << "\n";
      data_out << "^{214}Pb" << "\t" << "352" << "\t" << BR352 << "\t" << RealEff352 << "\t" << EffBR352 << "\n";
		data_out << "^{208}Tl" << "\t" << "583" << "\t" << BR583 << "\t" << RealEff583 << "\t" << EffBR583 << "\n";
      data_out << "^{214}Bi" << "\t" << "609" << "\t" << BR609 << "\t" << RealEff609 << "\t" << EffBR609 << "\n";
		data_out << "^{137}Cs" << "\t" << "662" << "\t" << BR662 << "\t" << RealEff662 << "\t" << EffBR662 << "\n"; 
		 if(sc){
      data_out << "^{46}Sc" << "\t" << "889" << "\t" << BR889 << "\t" << RealEff889 << "\t" << EffBR889 << "\n";
		 }
      data_out << "^{228}Ac" << "\t" << "911" << "\t" << BR911 << "\t" << RealEff911 << "\t" << EffBR911 << "\n";
      data_out << "^{228}Ac" << "\t" << "969" << "\t" << BR969 << "\t" << RealEff969 << "\t" << EffBR969 << "\n";
		data_out << "^{234m}Pa" << "\t" << "1001" << "\t" << BR1001 << "\t" << RealEff1001 << "\t" << EffBR1001 << "\n";
		 if(sc){
      data_out << "^{46}Sc" << "\t" << "1120" << "\t" << BR1120s << "\t" << RealEff1120s << "\t" << EffBR1120s << "\n";
		 }
		data_out << "^{214}Bi" << "\t" << "1120" << "\t" << BR1120 << "\t" << RealEff1120 << "\t" << EffBR1120 << "\n";
      data_out << "^{60}Co" << "\t" << "1173" << "\t" << BR1173 << "\t" << RealEff1173 << "\t" << EffBR1173 << "\n";
		data_out << "^{60}Co" << "\t" << "1332" << "\t" << BR1332 << "\t" << RealEff1332 << "\t" << EffBR1332 << "\n";
      data_out << "^{40}K" << "\t" << "1460" << "\t" << BR1460 << "\t" << RealEff1460 << "\t" << EffBR1460 << "\n";
      data_out << "^{214}Bi" << "\t" << "1765" << "\t" << BR1765 << "\t" << RealEff1765 << "\t" << EffBR1765 << "\n";
      data_out << "^{208}Tl" << "\t" << "2615" << "\t" << BR2615 << "\t" << RealEff2615 << "\t" << EffBR2615 << "\n";
		 
		 data_out.close();
    }
	
   
   
   
   
   

}
