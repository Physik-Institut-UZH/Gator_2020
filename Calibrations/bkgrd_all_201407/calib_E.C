{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Mon Mar 12 14:11:45 2018) by ROOT version5.34/34
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",2178,773,882,345);
   Canvas_1->Range(-355.3428,-1.349564,3208.494,0.6611784);
   Canvas_1->SetFillColor(0);
   Canvas_1->SetBorderMode(0);
   Canvas_1->SetBorderSize(2);
   Canvas_1->SetFrameBorderMode(0);
   Canvas_1->SetFrameBorderMode(0);
   
   TGraphErrors *gre = new TGraphErrors(9);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetPoint(0,238.632,0.04111459);
   gre->SetPointError(0,0.002,0.07638599);
   gre->SetPoint(1,277.37,0.1302008);
   gre->SetPointError(1,0.02,0.195854);
   gre->SetPoint(2,300.089,-0.04636398);
   gre->SetPointError(2,0.012,0.147507);
   gre->SetPoint(3,583.187,-0.1724153);
   gre->SetPointError(3,0.002,0.07219194);
   gre->SetPoint(4,727.33,-0.06523602);
   gre->SetPointError(4,0.01,0.1803701);
   gre->SetPoint(5,860.53,-0.5052622);
   gre->SetPointError(5,0.02,0.2599765);
   gre->SetPoint(6,1620.738,-0.3767345);
   gre->SetPointError(6,0.01,0.6377054);
   gre->SetPoint(7,2614.511,-0.004625145);
   gre->SetPointError(7,0.01,0.1277652);
   gre->SetPoint(8,834.848,0.06519385);
   gre->SetPointError(8,0.003,0.05648581);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Graph",100,1.0409,2852.11);
   Graph_Graph1->SetMinimum(-1.148489);
   Graph_Graph1->SetMaximum(0.4601042);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1->SetLineColor(ci);
   Graph_Graph1->GetXaxis()->SetTitle("MCA");
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetTitle("Energy [KeV]");
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1);
   
   gre->Draw("alp");
   
   TPaveText *pt = new TPaveText(0.4461567,0.9351869,0.5538433,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("Graph");
   pt->Draw();
   Canvas_1->Modified();
   Canvas_1->cd();
   Canvas_1->SetSelected(Canvas_1);
}
