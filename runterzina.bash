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

source /home/users/b/burmistr/terzina_photon_propagation/setupEnv.sh -d

function runterzina_single_root_file {
    ./runterzina $1 $2 $3
}

make -f Makefileterzina clean; make -f Makefileterzina runterzina;

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d          : single root file"
    echo " [0] -l          : list of root files"
    echo " [0] -shower     : simulate shower"
    echo " [0] -showertest : simulate shower new (on yggdrasil)"
    echo " [0] -h          : print help"
}

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then
	inRootFiles="../terzinag4-build/terzina.root"
	outHistSingleF="./hist_GeomID11/hist_Proton_100PeV_525km_30km_0.0deg.root"
	runterzina_single_root_file 1 $inRootFiles $outHistSingleF
    elif [ "$1" = "-shower" ]; then
	#inRootFileShower="../terzinag4-build/Proton_100PeV_525km_30km.root"
	#distanceFromShowerAxis="0.0"
	#theFile="terzina_PSF_CP_Flt_Theta180.0_phi0.0.root"
	#inRootFileG4="../terzinag4-build/$theFile"
	#outHistSingleF="./hist_GeomID11/hist_$theFile"
	#./runterzina 2 $inRootFileShower $distanceFromShowerAxis $inRootFileG4 $outHistSingleF
	echo "Not implemented in yet"
    elif [ "$1" = "-showertest" ]; then
        #               name    dir   theta      phi  distToEarth distToTerzina angleTrzinaTrk
        #trkInfo_0008227.dat  00041   68.04   263.27        31.83           7.1         173.74
        #trkInfo_0085849.dat  00429   68.06   265.22        32.12           6.6         175.54       
        #trkInfo_0032572.dat  00162   68.16   266.45        31.22           5.2         176.65
        #trkInfo_0063772.dat  00318   68.20   268.12        31.48           7.0         178.12
        #trkInfo_0028007.dat  00140   68.20   269.22        31.07           7.6         179.00 
        #trkInfo_0048790.dat  00243   68.09   270.27        31.08           7.4         179.36 
        #trkInfo_0102538.dat  00012   68.00   271.12        30.91           8.0         178.85 
        #trkInfo_0041893.dat  00209   68.28   271.83        31.86           4.9         178.13 
        #trkInfo_0067353.dat  00336   68.17   274.05        32.51           4.8         176.19
        #trkInfo_0017773.dat  00088   68.14   276.11        32.07           7.5         174.30
	inRootFileShower="../../easchersim/root/00243/EASCherSim_0048790.ini.npz.root"
	inDatFileShower="../../easchersim/root/00243/trkInfo_0048790.dat"
	inRootFileG4="../root/100PeV/00243/EASCherSim_0048790_g4.root"
	eKin=100
	outHistSingleF="./hist_EASCherSim_0048790_g4.root"
	./runterzina 2 $inRootFileShower $inDatFileShower $inRootFileG4 $eKin $outHistSingleF
    elif [ "$1" = "-l" ]; then
	./runterzina 0 $rootFilesList $outHistF
        printHelp
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi
fi

#espeak "I have done"
