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

#source /home/gred/root_34_36/bin/thisroot.sh;
#useroot53434
#useroot60806

function runterzina_single_root_file {
    ./runterzina $1 $2 $3
}

#Analyse list of root files 
#rootFilesList="./rootFileList.dat"
#outHistF="./hist/hist_terzina_1.0e7.root"

make -f Makefileterzina clean; make -f Makefileterzina runterzina;

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d      : single root file"
    echo " [0] -l      : list of root files"
    echo " [0] -shower : simulate shower"
    echo " [0] -h      : print help"
}

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then
	#inRootFiles="../terzinag4-build/terzina_PSF_with_corrector_0.0deg.root"
	#outHistSingleF="./hist_GeomID11/hist_terzina_PSF_with_corrector_0.0deg.root"
	#inRootFiles="../terzinag4-build/terzina_PSF_with_corrector_3.5deg.root"
	#outHistSingleF="./hist_GeomID11/hist_terzina_PSF_with_corrector_3.5deg.root"
	inRootFiles="../terzinag4-build/terzina.root"
	outHistSingleF="./hist_GeomID11/hist_Proton_100PeV_525km_30km_0.0deg.root"
	runterzina_single_root_file 1 $inRootFiles $outHistSingleF
    elif [ "$1" = "-shower" ]; then
	#
	#inRootFileShower="../terzinag4-build/Proton_100PeV_525km_30km.root"
	#distanceFromShowerAxis="0.0"
	#inRootFileG4="../terzinag4-build/terzina.root"
	#outHistSingleF="./hist_GeomID11/hist_Proton_100PeV_525km_30km_0.0deg.root"
	#
	#inRootFileShower="../terzinag4-build/Proton_100PeV_525km_30km.root"
	#distanceFromShowerAxis="7.0"
	#inRootFileG4="../terzinag4-build/terzina_Proton_100PeV_525km_30km_dist_7km.root"
	#outHistSingleF="./hist_GeomID11/hist_terzina_Proton_100PeV_525km_30km_dist_7km.root"
	#
	#inRootFileShower="../terzinag4-build/Proton_100PeV_525km_30km.root"
	#distanceFromShowerAxis="7.0"
	#inRootFileG4="../terzinag4-build/terzina_bifocal_theta180deg.root"
	#outHistSingleF="./hist_GeomID11/hist_terzina_bifocal_theta180deg.root"
	#
	#inRootFileShower="../terzinag4-build/Proton_100PeV_525km_30km.root"
	#distanceFromShowerAxis="7.0"
	#inRootFileG4="../terzinag4-build/terzina_bifocal_theta177deg.root"
	#outHistSingleF="./hist_GeomID11/hist_terzina_bifocal_theta177deg.root"
	#
	#inRootFileShower="../terzinag4-build/Proton_100PeV_525km_30km.root"
	#distanceFromShowerAxis="7.0"
	#inRootFileG4="../terzinag4-build/terzina_bifocal_theta176.5deg.root"
	#outHistSingleF="./hist_GeomID11/hist_terzina_bifocal_theta176.5deg.root"
	#
	inRootFileShower="../terzinag4-build/Proton_100PeV_525km_30km.root"
	distanceFromShowerAxis="7.0"
	inRootFileG4="../terzinag4-build/terzina_bifocal_theta177deg_phi45deg.root"
	outHistSingleF="./hist_GeomID11/hist_terzina_bifocal_theta177deg_phi45deg.root"
	#
	#inRootFileShower="../terzinag4-build/Proton_100PeV_525km_30km.root"
	#distanceFromShowerAxis="7.0"
	#inRootFileG4="../terzinag4-build/terzina_PSF_theta180deg.root"
	#outHistSingleF="./hist_GeomID11/hist_terzina_PSF_theta180deg.root"
	#
	./runterzina 2 $inRootFileShower $distanceFromShowerAxis $inRootFileG4 $outHistSingleF
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
