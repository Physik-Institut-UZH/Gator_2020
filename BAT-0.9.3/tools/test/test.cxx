// ***************************************************************
// This file was created using the CreateProject.sh script.
// CreateProject.sh is part of Bayesian Analysis Toolkit (BAT).
// BAT can be downloaded from http://mpp.mpg.de/bat
// ***************************************************************

#include "test.h"

#include <BAT/BCMath.h>

// ---------------------------------------------------------
test::test() : BCModel()
{
   // default constructor
   DefineParameters();
}

// ---------------------------------------------------------
test::test(const char * name) : BCModel(name)
{
   // constructor
   DefineParameters();
}

// ---------------------------------------------------------
test::~test()
   // default destructor
{
}

// ---------------------------------------------------------
void test::DefineParameters()
{
   // Add parameters to your model here.
   // You can then use them in the methods below by calling the
   // parameters.at(i) or parameters[i], where i is the index
   // of the parameter. The indices increase from 0 according to the
   // order of adding the parameters.

//   AddParameter("x",  0.0, 10.0); // index 0
//   AddParameter("y", -5.0,  5.0); // index 1
}

// ---------------------------------------------------------
double test::LogLikelihood(const std::vector<double> &parameters)
{
   // This methods returns the logarithm of the conditional probability
   // p(data|parameters). This is where you have to define your model.

   double logprob = 0.;

//   double x = parameters.at(0);
//   double y = parameters.at(1);

   // Gaussian distribution for x
//   logprob += BCMath::LogGaus(x, 6.0, 2.0);

   // Breit-Wigner distribution for y
//   logprob += BCMath::LogBreitWignerNonRel(y, 0.0, 1.0);

   return logprob;
}

// ---------------------------------------------------------
double test::LogAPrioriProbability(const std::vector<double> &parameters)
{
   // This method returns the logarithm of the prior probability for the
   // parameters p(parameters).

   double logprob = 0.;

//   double x = parameters.at(0);
//   double y = parameters.at(1);

   // exponentially decreasing prior for x
//   logprob += -0.5*x;

   // Gaussian prior for y
//   logprob += BCMath::LogGaus(y, 2., 1.0);

   return logprob;
}
// ---------------------------------------------------------

