#!/usr/bin/python
import sys
import os
import glob
import string
#import re
import time
from sim_input import *
from subprocess import *




# isotopes
#isotope_list=["238U","232Th","186keV","1001keV","40K","137Cs"]
#isotope_list=["40K","56Co","58Co","60Co","54Mn","46Sc"]
#isotope_list=["235U"]
# "57Co" //122 and 136 keV (can add to EffCalc, but at the edge of sensitivity from poor SNR)

#isotope_list=["134Cs"]
#isotope_list=["186keV", "46Sc", "570keV", "137Cs", "207Bi","226Ra", "228Th"]
#isotope_list=["1001keV", "110mAg", "605keV", "658keV"]

#isotope_list=["796keV", "885keV", "937keV", "1064keV"] 
# errors on PMT_9 for isotopes below
#isotope_list=["1001keV", "210Pb", "7Be","207Bi"]

#isotope_list=["228Th"]
#isotope_list=["54Mn", "137Cs"]


#shortlist
#isotope_list=["238U","232Th","40K","60Co", "1001keV", "110mAg", "137Cs", "207Bi", "54Mn", "58Co", "56Co", "57Co", "605keV", "186keV"]
# full list for PMTs
#isotope_list=["238U","232Th","40K","60Co", "1001keV", "110mAg", "137Cs", "207Bi", "54Mn", "58Co", "56Co", "57Co", "605keV", "658keV", "885keV", "1064keV", "134Cs", "186keV", "46Sc", "570keV", "796keV", "937keV"]
#isotope_list=["232Th"]
#isotope_list=["235U"]


####################################################################################
# directories

macrodir= datadir + "/" + sample + "/" + "macros" 
logdir= datadir + "/" + sample + "/" + "logs" 
effdir = datadir + "/" + sample + "/" + "effic" 


####################################################################################
# number of sim events


# for multiple isotopes
#totevents=int(1e8)
#totevents=int(1e7)
#eventsxjob_str = "1e6"
#eventsxjob_suffix = "_1e6"

# for single isotope
#totevents=int(1e4)
#eventsxjob_str = "1e3"
eventsxjob_suffix = "_" + eventsxjob_str

eventsxjob=int(float(eventsxjob_str))
totjobs=totevents/eventsxjob

joboffset = 0 #To submit more series of jobs (number of nodes already submitted)
counter = 0 #when it reaches maxnodes no more jobs are submitted

print ("Total events per isotope: " + str(totevents))
print ("Total events per job: " + str(eventsxjob))
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
