#!/usr/bin/python
import sys
import os
import glob
import string
import time
from sim_input import * # sim_input is the simulation input for a given sample
from subprocess import *


####################################################################################
# directories

macrodir= datadir + "/" + sample + "/" + "macros" 
logdir= datadir + "/" + sample + "/" + "logs" 
effdir = datadir + "/" + sample + "/" + "effic" 


####################################################################################
# number of sim events

eventsxjob_suffix= "_" + str(n_beamOn)
totjobs=totevents/n_beamOn

joboffset = 0 #To submit more series of jobs (number of nodes already submitted)
counter = 0 #when it reaches maxnodes no more jobs are submitted

print ("Total events per isotope: " + str(totevents))
print ("Total events per job: " + str(n_beamOn))
print ("Total num of jobs per isotope: " + str(totjobs))

####################################################################################

for isotope in isotope_list:
	os.system("mkdir %s/%s/%s" %(datadir,sample,isotope))
	job_prename="Gator" + "_" + isotope
	macro = macrodir + "/" + isotope + ".mac"
	print ("macro: " + macro)
	outdir = datadir + "/" + sample + "/" + isotope + "/"     
	outfile_prename = sample + "_" + isotope + eventsxjob_suffix + "_"
	logfile_prename = logdir + "/" + sample + "_" + isotope + eventsxjob_suffix + "_"
	counter = 0


	while (counter+joboffset < totjobs):
		proc1 = Popen(["squeue"],stdout=PIPE)
		proc2 = Popen(["grep","$USER"], stdin=proc1.stdout, stdout=PIPE)
		proc3 = Popen(["wc","-l"], stdin=proc2.stdout, stdout=PIPE)
		allocated = int(proc3.communicate()[0])
		proc3.stdout.close()
		proc2.stdout.close()
		proc1.stdout.close()

		if (maxnodes > allocated):
			
			outfilename = outfile_prename + str(joboffset+counter+1) + ".root"
			logfilename = logfile_prename + str(joboffset+counter+1) + ".log"
			jobname = job_prename + "-" + str(joboffset+counter+1)
			slurmlogname = gatordir+ "/slurmlog/" + job_prename + "-" + str(joboffset+counter+1)
	
			os.system('sbatch --job-name=%s --time=%s --output=%s-%%A.out --error=%s-%%A.err --export=binary=\'%s\',macro=%s,outdir=%s,outfilename=%s,logfilename=%s,gatordir=%s ./GatorSims.slurm' %(jobname,queue,slurmlogname,slurmlogname,binary,macro,outdir,outfilename,logfilename,gatordir))

			print ("\nsubmitting..")
			
			print ("jobname: " + jobname)
			print ("queue: " + queue)
			print ("binary: " + binary)
			print ("macro: " + macro)
			print ("output directory: " + outdir)
			print ("output file name: " + outfilename)
			print ("Log file name: " + logfilename + "\n")
		
			print ("Submitted job: " + str(joboffset+counter+1))
			counter += 1
			time.sleep(3)

		else:
			print ("\n\nAllocated nodes: " + str(allocated))
			print ("You can't submit! Sleeping 2.5 mins")
			time.sleep(150)
