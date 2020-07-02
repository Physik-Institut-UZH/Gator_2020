Gator_2020

This is the new version of the gator directory, which uses the easygator.C script to run simulations and analysis for the samples screneed at the Gator low-background counting facility  [1].

If you download the code to use in your private machine, make sure to change the name of the directories GATORDIR and data_dir in the beginning of the easygator.C script, then compile the code (as shown below).

////////////////////////////////////////////////////////////////////

Here you find the following folders and scripts:

i) The "easygator" script and its src and include folders: The purpose of this script is summarized in the atp wiki page. The code can be run in the analysis or simulation mode. 

  a) simulation mode: it compiles and runs the scripts used for simulations (. It can be used to create the geometry files of a sample (.icc and .ihh) using standard geometries which can be then also customized by the user for the specific sample and position. It links the geometry files to the GeConstructor.cc file, it then makes the geometry, runs overlap checks, and opens the visualization of the geometry. If the simulation of the sample does not yet exist, it creates a folder for the simulation/results of the sample, it saves the geometry visualization file there, as well as the macro files and inputs for the simulation. It then submits the jobs to run the simulation (in a screen) and saves the number of simulated events and erors in the log folderscreates a new folder with the results.

  b) analysis mode: it checks whether the simulation of the sample exists and if it worked as it should by comparing the input file of the simulation to the total of simulated events. It also scans for errors in the log files and shows the amount of errors encountered and if errors were found, it asks the user whether to continue or not. It then merges the root files and runs the analysis scripts to calculate the detection efficiency of each line and the resulting activity.

To run the code:
Go to the GATORDIR directory specified in easygator.C, and type:
$ ./easygator

To compile the code, type (only necessary if you make changes in the easygator script):
$ g++ -o easygator easygator.C 

ii) "simulations": it contains the geant4 geometry files of Gator, the geometry files of samples previously simulated, the python script to submit slurmlimulations jobs, etc

iii) analysis: It contains the scripts to calculate the detection efficiency of each line, the resulting activity and plot spectra from the SPE files.

iv) slurmlog: Here you receive the slurm log of the jobs that have been submitted in the last simulation. (previou log files are kept in slurmlog_archive)

v) .bashrc: here the environments and library paths are set. In case a version of root, GEANT4 or freewrl has changed or does not exist anymore, this file should be accordingly modified! In case you install the software locally, make sure you have all the necessary software.

vi) BAT: if the installation of BAT changes, the paths have to be changed in .bashrc as well

vii) Background data files

viii) Calibration data files

///////////////////////////////////////////////////////////////////

References:
[1] L. Baudis et al. "Gator: a low-background counting facility at the Gran Sasso Underground Laboratory"  https://arxiv.org/pdf/1103.2125v2.pdf
