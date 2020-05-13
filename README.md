# Gator_2020
This is the new version of the gator directory, which uses the easygator.C script to run simulations and  analysis.

////////////////////////////////////////////////////////////////////

Here you find the following folders and scripts:

i) "simulations": it contains the geant4 geometry files of Gator, the geometry files of samples previously simulated, the python script to submit simulations jobs, etc

ii) The "easygator" script: This script compiles and runs the scripts used for simulations and analysis of samples in gator. It reads the name of the sample, it creates the geometry files (.icc and .ihh - if they do not yet exist), it links them to the GeConstructor.cc file, it makes the geometry, it runs overlap checks, it opens the visualization of the geometry, submits the jobs to run the simulation and creates a new folder with the results. To run the code:

	$ ./easygator
	$ g++ -o easygator easygator.C // to recompile the code:

iii) slurm log: Here you receive the slurm log of the jobs that have been submitted

iv) .bashrc: here the environments and library paths are set. In case a version of root, GEANT4 or freewrl has changed, this file should be accordingly modified !!!!!

v) BAT: if the installation of BAT changes, the paths have to be changed in .bashrc as well

///////////////////////////////////////////////////////////////////
