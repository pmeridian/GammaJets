#! /usr/bin/env python
import os
import sys
import re
import time

#if len(sys.argv) != 1:
#    print "usage sendOnBatch.py files_per_job"
#    print "example : sendOnBatch.py 10"
#    sys.exit(1)


queue = "1nw"
#queue = "1nd"
#applicationlist = "applications.txt"
#ijobmax = int(sys.argv[1])
#application = "/tmp/runTMVA_depthMax100 "
#application = "/tmp/runTMVA_withRho "
#application = "/tmp/runTMVA_withHoverE "
application = "/tmp/runTMVA "

#look for the current directory
#######################################
pwd = os.environ['PWD']
#######################################
#app
######################################
#ijob=0

isEB = ['0', '1']
for ecal_reg in isEB:
######################################

    # prepare the script to run
    if ecal_reg == '0':
        outputname = pwd+"/src/submit_job_EE.src"
    elif ecal_reg == '1':
        outputname = pwd+"/src/submit_job_EB.src"
    outputfile = open(outputname,'w')
    outputfile.write('#!/bin/bash\n')
    outputfile.write('export STAGE_HOST=castorcms\n')
    outputfile.write('export SCRAM_ARCH=slc5_amd64_gcc462\n')
    outputfile.write('cd '+pwd+'; eval `scramv1 runtime -sh` ; cd -\n')
    #outputfile.write('cp '+pwd+'/nvertex* $WORKDIR\n')
    outputfile.write(pwd+application+"  "+ecal_reg+" 400  3 \n")
    outputfile.close


    if ecal_reg == '0':                                                                  
        os.system("echo bsub -q "+queue+" -oo logfile_EE.log source "+outputname) 
        os.system("bsub -q "+queue+" -oo logfile_EE.log source "+outputname)      
    elif ecal_reg== '1':                                                                 
        os.system("echo bsub -q "+queue+" -oo logfile_EB.log source "+outputname) 
        os.system("bsub -q "+queue+" -oo logfile_EB.log source "+outputname)      
    
    #if ecal_reg == '0':                                                                  
    #    os.system("echo bsub -q "+queue+" -oo logfile_withRho_EE.log source "+outputname) 
    #    os.system("bsub -q "+queue+" -oo logfile_withRho_EE.log source "+outputname)      
    #elif ecal_reg== '1':                                                                 
    #    os.system("echo bsub -q "+queue+" -oo logfile_withRho_EB.log source "+outputname) 
    #    os.system("bsub -q "+queue+" -oo logfile_withRho_EB.log source "+outputname)      

    #if ecal_reg == '0':                                                                  
    #    os.system("echo bsub -q "+queue+" -oo logfile_withHoverE_EE.log source "+outputname) 
    #    os.system("bsub -q "+queue+" -oo logfile_withHoverE_EE.log source "+outputname)      
    #elif ecal_reg== '1':                                                                 
    #    os.system("echo bsub -q "+queue+" -oo logfile_withHoverE_EB.log source "+outputname) 
    #    os.system("bsub -q "+queue+" -oo logfile_withHoverE_EB.log source "+outputname)      
