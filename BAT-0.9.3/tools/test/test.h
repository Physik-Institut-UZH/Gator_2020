// ***************************************************************
// This file was created using the CreateProject.sh script.
// CreateProject.sh is part of Bayesian Analysis Toolkit (BAT).
// BAT can be downloaded from http://mpp.mpg.de/bat
// ***************************************************************

#ifndef __BAT__TEST__H
#define __BAT__TEST__H

#include <BAT/BCModel.h>

// This is a test header file.
// Model source code is located in file test/test.cxx

// ---------------------------------------------------------
class test : public BCModel
{
   public:

      // Constructors and destructor
      test();
      test(const char * name);
      ~test();

      // Methods to overload, see file test.cxx
      void DefineParameters();
      double LogAPrioriProbability(const std::vector<double> &parameters);
      double LogLikelihood(const std::vector<double> &parameters);
};
// ---------------------------------------------------------

#endif

