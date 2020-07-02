// ***************************************************************
// This file was created using the CreateProject.sh script
// for project test.
// CreateProject.sh is part of Bayesian Analysis Toolkit (BAT).
// BAT can be downloaded from http://mpp.mpg.de/bat
// ***************************************************************

#include <BAT/BCH1D.h>
#include <BAT/BCH2D.h>
#include <BAT/BCLog.h>
#include <BAT/BCAux.h>
#include <BAT/BCSummaryTool.h>

#include "test.h"

int main()
{

   // set nicer style for drawing than the ROOT default
   BCAux::SetStyle();

   // open log file
   BCLog::OpenLog("log.txt");
   BCLog::SetLogLevel(BCLog::detail);

   // create new test object
   test* m = new test();

   // set precision
   m->MCMCSetPrecision(BCEngineMCMC::kMedium);

   BCLog::OutSummary("Test model created");

   // create a new summary tool object
   BCSummaryTool * summary = new BCSummaryTool(m);

   // perform your analysis here

   // normalize the posterior, i.e. integrate posterior
   // over the full parameter space
//   m->SetIntegrationMethod(BCIntegrate::kDefault);
//   m->SetIntegrationMethod(BCIntegrate::kIntMonteCarlo);
//   m->SetIntegrationMethod(BCIntegrate::kIntCuba);
//   m->SetIntegrationMethod(BCIntegrate::kIntGrid);
//   m->Normalize();

   // run MCMC and marginalize posterior wrt. all parameters
   // and all combinations of two parameters
//   m->SetMarginalizationMethod(BCIntegrate::kMargDefault);
//   m->SetMarginalizationMethod(BCIntegrate::kMargMetropolis);
//   m->SetMarginalizationMethod(BCIntegrate::kMargMonteCarlo);
//   m->SetMarginalizationMethod(BCIntegrate::kMargGrid);
//   m->MarginalizeAll();

   // run mode finding; by default using Minuit
//   m->SetOptimizationMethod(BCIntegrate::kOptDefault);
//   m->SetOptimizationMethod(BCIntegrate::kOptMinuit);
//   m->SetOptimizationMethod(BCIntegrate::kOptSimAnn);
//   m->SetOptimizationMethod(BCIntegrate::kOptMetropolis);
//   m->FindMode();

   // if MCMC was run before (MarginalizeAll()) it is
   // possible to use the mode found by MCMC as
   // starting point of Minuit minimization
//   m->FindMode( m->GetBestFitParameters() );

   // draw all marginalized distributions into a PostScript file
//   m->PrintAllMarginalized("test_plots.pdf");

   // print individual histograms
//   m->GetMarginalized("x")->Print("x.pdf");
//   m->GetMarginalized("y")->Print("y.pdf");
//   m->GetMarginalized("x", "y")->Print("xy.pdf");

   // print all summary plots
//   summary->PrintParameterPlot("test_parameters.pdf");
//   summary->PrintCorrelationPlot("test_correlation.pdf");
//   summary->PrintKnowledgeUpdatePlots("test_update.pdf");

   // calculate p-value
//   m->CalculatePValue( m->GetBestFitParameters() );

   // print results of the analysis into a text file
//   m->PrintResults("test_results.txt");

   delete m;
   delete summary;

   BCLog::OutSummary("Test program ran successfully");
   BCLog::OutSummary("Exiting");

   // close log file
   BCLog::CloseLog();

   return 0;

}

