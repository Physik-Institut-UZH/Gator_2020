#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

#include <TH1F.h>
#include <TMath.h>
#include <TDatime.h>

#include "include/GatorStructs.h"
#include "include/GatorCounter.hh"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include <TF1.h>
#include <TH1F.h>
#include <TMath.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include "TH1D.h"

#include "include/GatorDataLoader.hh"
#include "src/loadSPE.cc"

using namespace std;
void plotMCAnew()
{
 TH1F* histoMCA = loadSPE("/disk/gfs_atp/abisma/Gator_2020/Sample_Sim_and_Analysis_Results/PMT_stems_glass_confined/SPE/",1944000);
 histoMCA->Draw();
   histoMCA->SetLineColor(kRed);
    histoMCA->GetXaxis()->SetLabelFont(42);
    histoMCA->GetXaxis()->SetLabelSize(0.035);
    histoMCA->GetXaxis()->SetTitleSize(0.035);
    histoMCA->GetXaxis()->SetTitleFont(42);
    histoMCA->GetYaxis()->SetLabelFont(42);
    histoMCA->GetYaxis()->SetLabelSize(0.035);
    histoMCA->GetYaxis()->SetTitleSize(0.035);
    histoMCA->GetYaxis()->SetTitleFont(42);
    histoMCA->GetZaxis()->SetLabelFont(42);
    histoMCA->GetZaxis()->SetLabelSize(0.035);
    histoMCA->GetZaxis()->SetTitleSize(0.035);
    histoMCA->GetZaxis()->SetTitleFont(42);

   const Int_t n_lines = 22;

   Double_t MCA_lines[n_lines]={5512.28,5539.95, 5049.31,5076.18, 1114.17,1133.1,1780.51,1798.62, 2124.33,2143.12,3684.85,3706.55, 6783.12,6809.92, 10689.3,10721.8,3526.45,3547.86,15843.2,15882.5, 1437.41,1454.81};
   Double_t MCA_lines_compton_l[n_lines]={5498.44,5512.28, 5035.88,5049.31, 1104.7,1114.17, 1771.46,1780.51, 2114.93,2124.33, 3674,3684.85, 6769.72,6783.12,10673,10689.3, 3515.74,3526.45,15450,15843.2, 1428.71,1437.41};
   Double_t MCA_lines_compton_r[n_lines]={5539.95,5553.79, 5076.18,5089.61,1133.1,1142.57,1798.62,1807.67,2143.12,2152.52,3706.55,3717.4, 6809.92,6823.32,10721.8,10738,  3547.86,3558.57,15882.5,15902.1, 1454.81,1463.52};
   string  l_text[n_lines]={"Ac-228", "","Mn-54", "","U-235","","Pb-214","","Pb-214","","Bi-214","","Bi-214","","Bi-214","","Tl-208","", "Tl-208","","Pb-212",""};
 //"Pb-214","Pb-214","Bi-214","Bi-214","Bi-214","Bi-214","Bi-214","Bi-214", "", "Ac-228","Ac-228", "Pb-212", "K-40", "Cs-137"};
 Int_t color_lines[n_lines]={800,800,800, 800,800, 800, 800, 800,800, 800,805,805,805,805,805,805,603, 603,603,603,601, 601};//603,603, 805,805,805,619, 800, 800, 632, 434};
        for (int l=0; l<n_lines; l++)
        {
           //if (MCA_lines[l]==338.32) continue; // skiping Ac-228 line that is barely seen
                string stext= l_text[l];
                TLine *l_en=new TLine(MCA_lines[l], histoMCA->GetMinimum(),MCA_lines[l],0.15* histoMCA->GetMaximum());
                TText *t_en=new TText(MCA_lines[l]-3.,0.00006* histoMCA->GetMaximum(),stext.c_str());
                l_en->SetLineColor(color_lines[l]);//color_lines[l]);
                l_en->SetLineStyle(2); l_en->SetLineWidth(2);
                l_en->Draw();
                t_en->SetTextColor(color_lines[l]);
                t_en->SetTextFont(132);
              t_en->SetTextAngle(90); t_en->SetTextSize(0.045);
                t_en->Draw();
        }
        for (int l=0; l<n_lines; l++)
        {
                //if (MCA_lines[l]==338.32) continue; // skiping Ac-228 line that is barely seen
                string stext= l_text[l];
                TLine *l_en=new TLine(MCA_lines_compton_l[l], histoMCA->GetMinimum(),MCA_lines_compton_l[l],0.15* histoMCA->GetMaximum());
                l_en->SetLineColor(922);//color_lines[l]);
                l_en->SetLineStyle(4);// l_en->SetLineWidth(2);
                l_en->Draw();

        }
        for (int l=0; l<n_lines; l++)
        {
                //if (MCA_lines[l]==338.32) continue; // skiping Ac-228 line that is barely seen
                string stext= l_text[l];
                TLine *l_en=new TLine(MCA_lines_compton_r[l], histoMCA->GetMinimum(),MCA_lines_compton_r[l],0.15* histoMCA->GetMaximum());
                l_en->SetLineColor(922);//color_lines[l]);
                l_en->SetLineStyle(4);// l_en->SetLineWidth(2);
                l_en->Draw();

        }

         histoMCA->Rebin(2);
//      histoMCA->Rebin(2);

}

