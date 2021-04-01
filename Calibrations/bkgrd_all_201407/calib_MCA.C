{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Mon Mar 12 13:52:20 2018) by ROOT version5.34/34
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",2178,773,994,507);
   Canvas_1->ToggleEventStatus();
   Canvas_1->Range(-2102.247,-0.1118852,18958.23,0.2283859);
   Canvas_1->SetFillColor(0);
   Canvas_1->SetBorderMode(0);
   Canvas_1->SetBorderSize(2);
   Canvas_1->SetFrameBorderMode(0);
   Canvas_1->SetFrameBorderMode(0);
   
   TGraphErrors *gre = new TGraphErrors(9);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetPoint(0,1407.889,-0.006956209);
   gre->SetPointError(0,0.0560727,0.01293783);
   gre->SetPoint(1,1636.745,-0.02203012);
   gre->SetPointError(1,0.1491822,0.03314324);
   gre->SetPoint(2,1771.192,0.007845009);
   gre->SetPointError(2,0.1216964,0.02496336);
   gre->SetPoint(3,3444.422,0.02917333);
   gre->SetPointError(3,0.06502195,0.01221653);
   gre->SetPoint(4,4296.181,0.01103814);
   gre->SetPointError(4,0.1672393,0.03052101);
   gre->SetPoint(5,5083.805,0.08549629);
   gre->SetPointError(5,0.2282406,0.04399226);
   gre->SetPoint(6,9576.166,0.06375654);
   gre->SetPointError(6,0.6317771,0.1079175);
   gre->SetPoint(7,15434,0.001070763);
   gre->SetPointError(7,0.06843896,0.02160924);
   gre->SetPoint(8,4931.46,-0.01103163);
   gre->SetPointError(8,0.03809686,0.009562226);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Graph",100,3.801425,16852.18);
   Graph_Graph1->SetMinimum(-0.07785809);
   Graph_Graph1->SetMaximum(0.1943588);
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
   
   TPaveText *pt = new TPaveText(0.4537097,0.9331443,0.5462903,0.995,"blNDC");
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
