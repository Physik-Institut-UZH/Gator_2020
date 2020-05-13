Analysis of radioactive gamma-ray lines as derived from sample measurements using Gator

Analysis is done using sampleanalysis.cpp file in directory:
/Users/shell/Software/Gator_Screening/Gator_analysis

The measured data from Gator need to be transferred from atp (see below) to this directory under the subdirectory for each sample:
(/Users/shell/Data/Gator/Samples/ …)

The lines.list files from the simulations need to be transferred into the sample subdirectories also. 

For the sampleanalysis.cpp program the following paths are hard-coded:
- SPE files from sample measurement (/home/atp/atp/GatorSC/Data/SAMPLE_REPORTS/SPE)
  For PMTs I’ve named the directories and output files according to the number of PMTs and the end date of the measurement.
- SPE files from background (/Users/shell/Software/Gator_Screening/ directory)
   This is either the background from bare samples or the background with the teflon holder, 
   as in the case of the PMTs.
- location of lines.list file(s) found by calculating line efficiencies based on the sample simulations  
- directory of the calibration.root and resolution.root files (/Users/shell/Software/Gator_Screening/calibrations/) 
  The calibration may or may not be the same for the sample vs. the background only measurements.
- Location of output files

After hard-coding directories, just type % make

