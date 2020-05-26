Gator_2020

This is the new version of the gator directory, which uses the easygator.C script to run simulations and analysis for the samples screneed at the Gator facility.

////////////////////////////////////////////////////////////////////

Here you find the following folders and scripts:

i) The "easygator" script: This script can be used in the analysis or simulation mode. 

	a) simulation mode: it compiles and runs the scripts used for simulations. It can be used to create the geometry files of a sample (.icc and .ihh) using standard geometries which can be then also customized by the user for the specific sample and position. It links the geometry files to the GeConstructor.cc file, it then makes the geometry, runs overlap checks, and opens the visualization of the geometry. 
If the simulation of the sample does not yet exist, it creates a folder for the simulation/results of the sample, it saves the geometry visualization file there, as well as the macro files and inputs for the simulation. 
It then submits the jobs to run the simulation (in a screen) and saves the number of simulated events and erors in the log folderscreates a new folder with the results.

	b) analysis mode: it checks whether the simulation of the sample exists and if it worked as it should by comparing the input file of the simulation to the total of simulated events.
It also scans for errors in the log files and shows the amount of errors encountered and if errors were found, it asks the user whether to continue or not. It then adds the root files and runs the analysis scripts.

To run the code, type:
$ ./easygator

To compile the code, type (only necessary if you make changes in the easygator script):
$ g++ -o easygator easygator.C 

ii) "simulations": it contains the geant4 geometry files of Gator, the geometry files of samples previously simulated, the python script to submit simulations jobs, etc
iii) slurm log: Here you receive the slurm log of the jobs that have been submitted

iv) .bashrc: here the environments and library paths are set. In case a version of root, GEANT4 or freewrl has changed, this file should be accordingly modified !!!!!

v) BAT: if the installation of BAT changes, the paths have to be changed in .bashrc as well

///////////////////////////////////////////////////////////////////
