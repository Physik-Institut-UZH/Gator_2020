#!/usr/bin/python
import sys
import os
import glob
import string
#import re
import time
from subprocess import *

homedir="/home/atp/shayne/"
binary= homedir + "geant4/bin/Linux-g++/gator_1.2"
envir="/app/cern/geant_4.9.3.2/env.sh"


#queue = standard
#queue="2:00:00"
queue="12:00:00"

####################################################################################
# sample directory
datadir = "Gator_sims/Screening"
sample="strPMT_R11410"

#datadir = "Gator_sims/Screening/PMT_R12699"
#sample="for_Karl"

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
isotope_list=["235U"]


####################################################################################
# directories

macrodir= datadir + "/" + sample + "/" + "macros" 
logdir= datadir + "/" + sample + "/" + "logs" 
effdir = datadir + "/" + sample + "/" + "effic" 

#os.system("mkdir ~/%s/%s" %(datadir,sample))
#os.system("mkdir ~/%s" %(logdir))
#os.system("mkdir ~/%s" %(effdir))

# PMTs
#macrodir= "Gator_sims/Screening/PMT_R11410/macros" #USE ONLY FOR PMTs!!!
#logdir= datadir + "/" + "logs" #USE ONLY FOR PMTs!!!


####################################################################################
# number of sim events

# test events
#eventsxjob_suffix = "_test"
#eventsxjob_str = "1e2"
#totevents=int(1e2)

# for multiple isotopes
#totevents=int(1e8)
totevents=int(1e8)
eventsxjob_str = "1e6"
eventsxjob_suffix = "_1e6"

# for single isotope
#totevents=int(1e7)
#eventsxjob_str = "1e6"
#eventsxjob_suffix = "_1e6"

eventsxjob=int(float(eventsxjob_str))
totjobs=totevents/eventsxjob

maxnodes = 251 # multiple isotopes
#maxnodes = 10 # test
joboffset = 0 #To submit more series of jobs (number of nodes already submitted)
counter = 0 #when it reaches maxnodes no more jobs are submitted


print ("Total events per isotope: " + str(totevents))
print ("Total events per job: " + str(eventsxjob))
print ("Total num of jobs per isotope: " + str(totjobs))

####################################################################################

for isotope in isotope_list:
	os.system("mkdir ~/%s/%s/%s" %(datadir,sample,isotope))
	job_prename="Gator" + "_" + isotope
#	jobname="Gator" + "_" + sample + "_" + isotope
	macro = macrodir + "/" + isotope + ".mac"
	print ("macro: " + macro)
	outdir = datadir + "/" + sample + "/" + isotope + "/"     
	outfile_prename = sample + "_" + isotope + eventsxjob_suffix + "_"
	logfile_prename = logdir + "/" + sample + "_" + isotope + eventsxjob_suffix + "_"
	counter = 0


	while (counter+joboffset < totjobs):
#	while True:
		proc1 = Popen(["squeue"],stdout=PIPE)
		proc2 = Popen(["grep","shayne"], stdin=proc1.stdout, stdout=PIPE)
		proc3 = Popen(["wc","-l"], stdin=proc2.stdout, stdout=PIPE)
		allocated = int(proc3.communicate()[0])
		proc3.stdout.close()
		proc2.stdout.close()
		proc1.stdout.close()

		if (maxnodes > allocated):
			
			outfilename = outfile_prename + str(joboffset+counter+1) + ".root"
			logfilename = logfile_prename + str(joboffset+counter+1) + ".log"
			jobname = job_prename + "-" + str(joboffset+counter+1)
	
#			os.system("sbatch --job-name=jobname --time=express binary -p macro -o outfilename > logfilename" )

			os.system('sbatch --job-name=%s --time=%s --output=/home/atp/shayne/slurmlog/%s-%%A.out --error=/home/atp/shayne/slurmlog/%s-%%A.err --export=binary=\'%s\',macro=%s,outdir=%s,outfilename=%s,logfilename=%s ./GatorSims.slurm' %(jobname,queue,jobname,jobname,binary,macro,outdir,outfilename,logfilename))

			print ("\nsubmitting..")
			
			print ("jobname: " + jobname)
			print ("queue: " + queue)
			print ("binary: " + binary)
			print ("macro: " + macro)
			print ("output directory: " + outdir)
			print ("output file name: " + outfilename)
			print ("Log file name: " + logfilename + "\n")
		

# from xurich slurm script:
#       os.system('sbatch --job-name=%s --time=%s --export=binary,T1_procset=%s,filename=%s,outfilename=%s,procdir=%s,logfilename=%s ./XuProcSingle.slurm' %(jobname,queue,binary,T1_procset,filename,outfilename,procdir,logfilename))


			print ("Submitted job: " + str(joboffset+counter+1))
			counter += 1
			time.sleep(3)

		else:
			print ("\n\nAllocated nodes: " + str(allocated))
			print ("You can't submit! Sleeping 2.5 mins")
			time.sleep(150)
