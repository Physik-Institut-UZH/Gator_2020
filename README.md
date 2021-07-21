Gator_2020

This is the new version of the gator directory, which uses the easygator.C script to run simulations and analysis for the samples screened at the Gator low-background counting facility  [1].


For ATP users: there is a full documentation of how to run the code in the ATP wiki

If you download the code to use in your private machine, make sure to change the .bashrc file accordingly, setting the paths to directories properly there. Then compile the code (as shown below).

////////////////////////////////////////////////////////////////////

Here you find the following folders and scripts:

i) The "easygator" script and its src and include folders: The purpose of this script is summarized in the atp wiki page. The code can be run in the analysis or simulation mode.

a) simulation mode: it compiles and runs the scripts used for simulations (. It can be used to create the geometry files of a sample (.icc and .ihh) using standard geometries which can be then also customized by the user for the specific sample and position. It links the geometry files to the GeConstructor.cc file, it then makes the geometry, runs overlap checks, and opens the visualization of the geometry. If the simulation of the sample does not yet exist, it creates a folder for the simulation/results of the sample, it saves the geometry visualization file there, as well as the macro files and inputs for the simulation. It then submits the jobs to run the simulation (in a screen) and saves the number of simulated events and errors in the log folders creates a new folder with the results.

b) analysis mode: it checks whether the simulation of the sample exists and if it worked as it should by comparing the input file of the simulation to the total of simulated events. It also scans for errors in the log files and shows the amount of errors encountered and if errors were found, it asks the user whether to continue or not. It then merges the root files and runs the analysis scripts to calculate the detection efficiency of each line and the resulting activity.

To run the code: Go to the GATORDIR directory specified in the .bashrc, and type: `$ source .bashrc; ./easygator` or simply `$ ./easygator` 
Depending on whether you set the path for GATORDIR in your personal .bashrc, or in the .bashrc found in the GATORDIR 

To compile the code, type (only necessary if you make changes in the easygator script): `$ g++ -o easygator easygator.C`

ii) "simulations": it contains the geant4 geometry files of Gator, the geometry files of samples previously simulated, the python script to submit slurm simulations jobs, etc

iii) analysis: It contains the scripts to calculate the detection efficiency of each line, the resulting activity and plot spectra from the SPE files. It also contains scripts for producing files for a new calibration.

iv) slurmlog: Here you receive the slurm log of the jobs that have been submitted in the last simulation. (previous log files are kept in slurmlog_archive)

v) .bashrc: here the environments and library paths are set. In case a version of root, GEANT4 or freewrl has changed or does not exist anymore, this file should be accordingly modified! In case you install the software locally, make sure you have all the necessary software.

vi) BAT: if the installation of BAT changes, the paths have to be changed in .bashrc as well. See below how to install BAT

vii) Background data files

viii) Calibration data files (after processing using the code in analysis/calibration)

///////////////////////////////////////////////////////////////////

References: [1] L. Baudis et al. "Gator: a low-background counting facility at the Gran Sasso Underground Laboratory"  https://arxiv.org/pdf/1103.2125v2.pdf

---------------- installing BAT -----------------------
```
$ cd BAT-0.9.3

$ make clean

$ ./configure --prefix=<absolute_path_to_parent_directory_of_BAT-0.9.3>/BAT-0.9.3
$ make
$ make install
```
--------------------------------------------------------

