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
rootFilesList="./rootFileList.dat"
outHistF="./hist/hist_terzina_1.0e7.root"

#Or analyse single root file 
#inRootFiles="./data/terzina.root"
#outHistSingleF="./hist/hist_terzina.root"
#
#inRootFiles="./data/terzina_1.0e7.root"
#outHistSingleF="./hist/hist_terzina_1.0e7.root"
#
#inRootFiles="./data/terzina_PSF_v01.00.00.root"
#outHistSingleF="./hist/hist_terzina_PSF_v01.00.00.root"

#inRootFiles="./data/terzina_PSF_v01.00.00_0theta_0phi.root";
#outHistSingleF="./hist/hist_terzina_PSF_v01.00.00_0theta_0phi.root";

#inRootFiles="./data/terzina_sipm.root"
#outHistSingleF="./hist/hist_terzina_sipm.root"

#inRootFiles="./data_v02.00.00b/terzina.root"
#outHistSingleF="./hist_v02.00.00b/hist_terzina.root"

#inRootFiles="./data_v02.00.00b/terzina_1e7.0.root"
#outHistSingleF="./hist_v02.00.00b/hist_terzina_1e7.0.root"

#inRootFiles="./data_v02.00.00b/terzina_theta_0deg.root"
#outHistSingleF="./hist_v02.00.00b/hist_terzina_theta_0deg.root"
#inRootFiles="./data_v02.00.00b/terzina_theta_1deg.root"
#outHistSingleF="./hist_v02.00.00b/hist_terzina_theta_1deg.root"
#inRootFiles="./data_v02.00.00b/terzina_theta_2deg.root"
#outHistSingleF="./hist_v02.00.00b/hist_terzina_theta_2deg.root"
#inRootFiles="./data_v02.00.00b/terzina_theta_3deg.root"
#outHistSingleF="./hist_v02.00.00b/hist_terzina_theta_3deg.root"

make -f Makefileterzina clean; make -f Makefileterzina runterzina;

#inRootFiles="./data_fresnel/terzina.root"
#outHistSingleF="./hist_fresnel/hist_terzina.root"

#inRootFiles="./data_fresnel/terzina_1e7.root"
#outHistSingleF="./hist_fresnel/hist_terzina_1e7.root"

#inRootFiles="./data_fresnel/terzina_1e.7_1.0deg.root"
#outHistSingleF="./hist_fresnel/hist_terzina_1e.7_1.0deg.root"

#inRootFiles="./data_fresnel/terzina_1e.7_n25_spectrum_full_0.0deg.root"
#outHistSingleF="./hist_fresnel/hist_terzina_1e.7_n25_spectrum_full_0.0deg.root"

#inRootFiles="./data_fresnel/terzina_1e.7_n25_spectrum_full_1.0deg.root"
#outHistSingleF="./hist_fresnel/hist_terzina_1e.7_n25_spectrum_full_1.0deg.root"

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
	#./runterzina 1 $inRootFiles $outHistSingleF
	#runterzina_single_root_file 1 $inRootFiles $outHistSingleF

	#inRootFiles="./data/terzina_PSF_v01.00.00_0theta_0phi.root";
	#outHistSingleF="./hist/hist_terzina_PSF_v01.00.00_0theta_0phi.root";
	#runterzina_single_root_file 1 $inRootFiles $outHistSingleF
	
	#inRootFiles="./data/terzina_PSF_v01.00.00_1theta_0phi.root";
	#outHistSingleF="./hist/hist_terzina_PSF_v01.00.00_1theta_0phi.root";
	#runterzina_single_root_file 1 $inRootFiles $outHistSingleF
	
	#inRootFiles="./data/terzina_PSF_v01.00.00_2theta_0phi.root";
	#outHistSingleF="./hist/hist_terzina_PSF_v01.00.00_2theta_0phi.root";
	#runterzina_single_root_file 1 $inRootFiles $outHistSingleF
	
	#inRootFiles="./data/terzina_PSF_v01.00.00_3theta_0phi.root";
	#outHistSingleF="./hist/hist_terzina_PSF_v01.00.00_3theta_0phi.root";
	#runterzina_single_root_file 1 $inRootFiles $outHistSingleF
	
	#inRootFiles="./data/terzina_PSF_v01.00.00_3theta_20phi.root";
	#outHistSingleF="./hist/hist_terzina_PSF_v01.00.00_3theta_20phi.root";
	#runterzina_single_root_file 1 $inRootFiles $outHistSingleF
	
	#inRootFiles="./data/terzina_PSF_v01.00.00_3theta_45phi.root";
	#outHistSingleF="./hist/hist_terzina_PSF_v01.00.00_3theta_45phi.root";
	#runterzina_single_root_file 1 $inRootFiles $outHistSingleF
	
	#inRootFiles="./data/terzina_PSF_v01.00.00_3theta_90phi.root";
	#outHistSingleF="./hist/hist_terzina_PSF_v01.00.00_3theta_90phi.root";
	#runterzina_single_root_file 1 $inRootFiles $outHistSingleF
	
	#inRootFiles="./data/terzina_PSF_v01.00.00_3theta_135phi.root";
	#outHistSingleF="./hist/hist_terzina_PSF_v01.00.00_3theta_135phi.root";
	#runterzina_single_root_file 1 $inRootFiles $outHistSingleF
	
	#inRootFiles="./data/terzina_PSF_v01.00.00_3theta_180phi.root";
	#outHistSingleF="./hist/hist_terzina_PSF_v01.00.00_3theta_180phi.root";
	#runterzina_single_root_file 1 $inRootFiles $outHistSingleF

	#inRootFiles="./data_fresnel/terzina_1e.7_n100_spectrum_400_0.0deg.root"
	#outHistSingleF="./hist_fresnel/hist_terzina_1e.7_n100_spectrum_400_0.0deg.root"
	#runterzina_single_root_file 1 $inRootFiles $outHistSingleF
	
	#inRootFiles="./data_fresnel/terzina_1e.7_n100_spectrum_400_1.0deg.root"
	#outHistSingleF="./hist_fresnel/hist_terzina_1e.7_n100_spectrum_400_1.0deg.root"
	#runterzina_single_root_file 1 $inRootFiles $outHistSingleF

	#inRootFiles="./data_fresnel/terzina_1e.7_n100_spectrum_400_2.0deg.root"
	#outHistSingleF="./hist_fresnel/hist_terzina_1e.7_n100_spectrum_400_2.0deg.root"
	#runterzina_single_root_file 1 $inRootFiles $outHistSingleF
	
	#inRootFiles="./data_fresnel/terzina_1e.7_n100_spectrum_400_3.0deg.root"
	#outHistSingleF="./hist_fresnel/hist_terzina_1e.7_n100_spectrum_400_3.0deg.root"
	#runterzina_single_root_file 1 $inRootFiles $outHistSingleF

	#inRootFiles="./data_fresnel/terzina_1e.7_n100_spectrum_400_4.0deg.root"
	#outHistSingleF="./hist_fresnel/hist_terzina_1e.7_n100_spectrum_400_4.0deg.root"
	#runterzina_single_root_file 1 $inRootFiles $outHistSingleF

	inRootFiles="./data_fresnel/terzina_1e.7_n25_spectrum_full_2.0deg.root"
	outHistSingleF="./hist_fresnel/hist_terzina_1e.7_n25_spectrum_full_2.0deg.root"
	runterzina_single_root_file 1 $inRootFiles $outHistSingleF

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
