// GEANT4 GATOR SIMULATIONS
// 26Feb2016
// last update Oct 2019
	
	
	on the farm, the main directory is /disk/bulk_atp/gabriela/Gator
		first load geant4.9.3
		% g4.9.3
		
		// GEOMETRY
		The src folder (simulations/gator_v1.2/src) contains the geometry. Use previous .icc and .ihh files as examples to build a new geometry.
        For new simulations, open the GeConstruction.cc file and include the specific sample geometry.
        In the GeConstruction.hh file, include the relevant header file.

        Added overlap check for main geometry, Feb. 2017. To check overlaps for new geometries, add flag "true" at end of physical volume declaration
            (follows "false, 0"; see latest geometries for example)

For PMTs, only the PMTholders_2018.icc file is needed, as well as the 2 Construct...cc files under /src build the holders and the PMTs. Within the PMTholders_2018 file, one must specify the number of PMTs and also which PTFE holders to build (see notes at the top of the script). Note: currently the other geometries won't compile with when the "Construct..." files are in the source directory (needs debugging). At the moment I move them in and out of the /src/PMTs_only directory

		Rebuild geometry (in gator_v1.2 directory)
		% make clean -f GlobGeom_makefile
		% make -f GlobGeom_makefile	
					
		At this point, one can also create the binary (from /home/atp/galloway/Gator_sims/gator_v1.2 directory)
		% make clean
		% make

        // GEOMETRY CHECKS
        After compiling and finishing the geometry, a quick sanity check can be done by just running the binary:
        % gator_1.2
        this will show overlaps and also generate a .wrl file for visualization.
        If you have freewrl installed, the generated .wrl can be opened with freewrl - in command line just:
        % open *.wrl

        if you have overlaps without obvious fixes, you can try running the geantino macro to see where exactly it gets stuck.
		
		// SOURCES
		in the Screening directory are the results of previous sample simulations and also the macros file. 
		For a new sample, create a directory and the macro files for the specific isotopes/energies to simulate.
		Use previous ones for example. Some notes:
			1. The radius, halfz, and center are 50, 25, and (0 0 13.5) cm, respectively, for the full cavity volume.
				Reduce this to encompass sample size (plus some extra) to speed up the simulations (essentially changes
				the size of the surrounding sphere, or cylinder, in this case, from which the decays/lines are started).
			2. Specify the active physical volumes with confine: Although the lines are initiated at random everywhere within
				the surrounding sphere/cylinder volume, emissions are only generated within the confined volumes



// RUN SIM
        We now run on farm using slurm. script is GatorSim.py
        The .slurm file replaces earlier .pbs files as of ~June 2017
        slurm info: https://www.uzh.ch/cmsssl/physik/de/intern/batch-systems/slurm.html

		In GatorSim.py script:
			1. set batch queue (see slurm info) example runtimes:[all 4 primordial chains, 10^8 events with 10^6 events per job] ~1 hour
			2. set directories
			3. set isotopes
			4. set total number of events and # of events per job (see script for example)	
			5. set max nodes (should not use more than 150)
		Run in screen mode with:
		% sbatch GatorSims.py ->> it seems to be wrong. run
		% python GatorSims.py
			
		Check in the log files of the sample to be sure that all confined volumes have been constructed, physics lists are found, events have started, etc...
			(you may see lots of zero energy events, this is because the surrounding cylinder volume is prob much bigger than the confined volumes
				
		To check the status of the sims on the farm:
		% qstat -u galloway //shows jobs running (R), closed (C), or in Queue (Q)
		kill all jobs:
//		% qselect -u galloway | xargs qdel
             //  see slurm man: kill jobs by user
        % scancel -u galloway

             
        // Check that everything worked as it should
             - check qstat that the jobs are running (when they close immediately, it is usually a sign that a directory path was incorrect, or something wrong in your slurm script.)
             - check the slurm.out to make sure the jobs were submitted with no obvious errors.
             - the slurmlog (typically a directory in your homedir) gives .err and .out files. Generally when something fails, it happens towards the end of the run. Check that the last files were created and spot check a few of the logs. The .err files should be blank (file size zero) as default!
                 some notes on the output (.log files):
                    -the K-40 always throws some error about atomic transitions, this can be ignored
                    -unless the energy is given explicitly in the macro, the primary energy in the output will be zero. otherwise the discrete value shoudl be given.
                    -the outputs also verify that there are no overlaps in the geometry and the correct mass is being simulated (although this shoudl have been checked before in the GlobGeom steps above).
             - Check that all of the root files were created, and that the file sizes look reasonable and consistent with one another.

        // PROCESS SIM FILES
        The MergeFiles.py script creates merged root files from all of the datasets. In this directory, set the following:
             1. sample name (same as in MasterSubmit file)
             2. datadir
             3. isotope list (this can be copy/pasted from the GatorSim.py script)
             4. job suffix (# events per file - important as this can screw up your efficiencies!)
        Run (screen mode preferred, as sometimes it takes a while):
        % ./MergeFiles.py

        Use EffCalcAll.cpp to get line efficiencies from the merged root files. Enter paths in file first, and also specify isotopes to be included. You may need to add your own for special cases.
        Run (screen mode):
        % root -x EffCalcAll.cpp
             
        This generates the lines.list file to be used in analysis. Check that the efficiencies are reasonable (a typo in the number of events in MasterSubmit, for example, can create an order of magnitude difference in results).
             
             
             // analysis
        

