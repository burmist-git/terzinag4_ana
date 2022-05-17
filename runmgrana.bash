#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2018 - LBS - (Single person developer.)                 #
# Tue Mar  6 20:15:29 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                 This script run the analysis class.                  #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################


#Analyse list of root files 
rootFilesList="./rootFileList.dat"
outHistF="./hist.root"

#Or analyse single root file 
inRootFiles="./merg_hist/merg_hist_100PeV.root"
outHistSingleF="./merg_hist/hist_merg_hist_100PeV.root"

make -f Makefilemgrana clean; make -f Makefilemgrana runmgrana;

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d  : single root file"
    echo " [0] -l  : list of root files"
    echo " [0] -h  : print help"
}

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then
	Ekin=10PeV
	inRootFiles="./merg_hist/merg_hist_"$Ekin".root"
	outHistSingleF="./merg_hist/hist_merg_hist_"$Ekin".root"
	./runmgrana 1 $inRootFiles $outHistSingleF
	Ekin=35PeV
	inRootFiles="./merg_hist/merg_hist_"$Ekin".root"
	outHistSingleF="./merg_hist/hist_merg_hist_"$Ekin".root"
	./runmgrana 1 $inRootFiles $outHistSingleF
	Ekin=70PeV
	inRootFiles="./merg_hist/merg_hist_"$Ekin".root"
	outHistSingleF="./merg_hist/hist_merg_hist_"$Ekin".root"
	./runmgrana 1 $inRootFiles $outHistSingleF
	Ekin=100PeV
	inRootFiles="./merg_hist/merg_hist_"$Ekin".root"
	outHistSingleF="./merg_hist/hist_merg_hist_"$Ekin".root"
	./runmgrana 1 $inRootFiles $outHistSingleF
	Ekin=350PeV
	inRootFiles="./merg_hist/merg_hist_"$Ekin".root"
	outHistSingleF="./merg_hist/hist_merg_hist_"$Ekin".root"
	./runmgrana 1 $inRootFiles $outHistSingleF
	Ekin=700PeV
	inRootFiles="./merg_hist/merg_hist_"$Ekin".root"
	outHistSingleF="./merg_hist/hist_merg_hist_"$Ekin".root"
	./runmgrana 1 $inRootFiles $outHistSingleF
	Ekin=1000PeV
	inRootFiles="./merg_hist/merg_hist_"$Ekin".root"
	outHistSingleF="./merg_hist/hist_merg_hist_"$Ekin".root"
	./runmgrana 1 $inRootFiles $outHistSingleF
	Ekin=3000PeV
	inRootFiles="./merg_hist/merg_hist_"$Ekin".root"
	outHistSingleF="./merg_hist/hist_merg_hist_"$Ekin".root"
	./runmgrana 1 $inRootFiles $outHistSingleF
    elif [ "$1" = "-l" ]; then
	./runmgrana 0 $rootFilesList $outHistF
        printHelp
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi
fi

#espeak "I have done"
