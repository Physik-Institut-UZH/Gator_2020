//========This script should be used as the first part of a wider script for each data taking========//
/*
histogen.c ===> there is the function used to read the ASCII data (raw) files and to generate an histogram.
*/
{
.L histogen.c

TCanvas* myCanv = new TCanvas("MyCanv","Row Background and source Calibration",1);
myCanv -> SetWindowSize(1200,800);
myCanv -> Divide(1,2);


//Creation of an histogram with the ASCII dasta of the background. Draw it in the first pad.
myCanv -> cd(1);
Double_t time1 = 0; //Acquisition time in seconds of the background 
TH1F* h1 = histogen("BG20110625Data.txt",&time1);


//Creation of an histogram with the ASCII data of the Th228 source. Draw it in the second pad.
myCanv -> cd(2);
Double_t time2 = 0; //Acquisition time in seconds of the source
TH1F* h2 = histogen("228Th_supported_20110816Data.txt",&time2);


//Rebinned clones of the original histo are created here. They can be rebinned without lose the original ones

TH1F* h1reb = h1->Rebin(5,"Rebinned background");
TH1F* h2reb = h2->Rebin(5,"Rebinned Th calibration");

TCanvas* fitCanv = new TCanvas("fitCanvas","Fit result for lines",1);
fitCanv->cd(0);


}  //end of the script
