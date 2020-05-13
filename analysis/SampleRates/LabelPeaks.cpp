{
gROOT->ProcessLine("#include <string>");
gROOT->ProcessLine(".L /Users/francesco/PhD/Gator/data_analysis/convert_histo_ENR.cxx");
//gROOT->ProcessLine("#include <vector>");

string filename1("/Users/francesco/PhD/Gator/data_analysis/samples/PMTs/10xR11410-20/10xR11410-20_out.root");

string filename2("/Users/francesco/PhD/Gator/data_analysis/samples/PMTs/R11410-21/Batch1/Group2/16xPMTs-Batch1-Group2.root");

string calibdir("/Users/francesco/PhD/Gator/data_analysis/calibrations/archive/04-10-2012/");

TFile* f = new TFile(filename1.c_str(),"read");
TH1F* h1 = (TH1F*)f->Get("histoADC");
h1->SetDirectory(0);
f->Close();
delete f;
h1->SetName("h1");

f = new TFile(filename2.c_str(),"read");
TH1F* h2 = (TH1F*)f->Get("histoADC");
h2->SetDirectory(0);
f->Close();
delete f;
h2->SetName("h2");


TH1F* hE1 = convert_histo_ENR(h1,calibdir.c_str());
hE1->SetName("hE1");
hE1->SetLineColor(kBlue);
hE1->Rebin(10);
hE1->Scale(1.,"width");
hE1 -> GetXaxis() -> SetTitle("Energy [keV]");
hE1 -> GetYaxis() -> SetTitle("Rate [counts/(day keV)]");

TH1F* hE2 = convert_histo_ENR(h2,calibdir.c_str());
hE2->SetName("hE2");
hE2->SetLineColor(kRed);
hE2->Rebin(10);
hE2->Scale(1.,"width");
hE2 -> GetXaxis() -> SetTitle("Energy [keV]");
hE2 -> GetYaxis() -> SetTitle("Rate [counts/(day keV)]");


TLegend* leg1 = new TLegend(0.60,0.90,0.90,0.80);
leg1 -> AddEntry(hE1,"R11410-20","L");
leg1 -> AddEntry(hE2,"R11410-21","L");

TCanvas* c1 = new TCanvas("c1");
c1->SetLogy();

hE2->Draw();
hE1->Draw("same");


Double_t energies[] = {1505.0.28,1764.49,2615};
Char_t* mass[] = {"110m","214","208"};
Char_t* element[] = {"Ag","Bi","Tl"};

Int_t nlabels = sizeof(energies)/sizeof(Double_t);

TLatex* text;
TLine* vertline;
//text->SetNDC(true);

Double_t x_line,y_linelow,y_lineup;


for (Int_t i=0; i<nlabels; i++){
	string labtext = string("^{") + string(mass[i]) + string("}") + string(element[i]);
	x_line=energies[i];
	if(hE1->GetBinContent(hE1->FindBin(energies[i])) > hE2->GetBinContent(hE2->FindBin(energies[i]))){
	
		y_linelow = hE1->GetBinContent(hE1->FindBin(energies[i]));
	}else{
	
		y_linelow = hE2->GetBinContent(hE2->FindBin(energies[i]));
	}
		
	y_lineup = y_linelow*TMath::Exp(0.5);
	
	vertline = new TLine(x_line,y_linelow,x_line,y_lineup);	
	vertline->SetLineStyle(3);
	text = new TLatex(x_line-1.,y_lineup,labtext.c_str());
	text->SetTextSize(0.03);
	
	vertline->Draw("same");
	text->Draw("same");
	
	leg1->Draw();
}

}