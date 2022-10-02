#!/bin/sh
#SBATCH --job-name crgen%j
#SBATCH --error /home/users/b/burmistr/terzina_photon_propagation/job_error/crgen_%j.error
#SBATCH --output /home/users/b/burmistr/terzina_photon_propagation/job_output/output_%j.output
#SBATCH --ntasks 1
#SBATCH --cpus-per-task 1
#SBATCH --partition public-cpu
#SBATCH --time 0-10:00:00

source /home/users/b/burmistr/terzina_photon_propagation/setupEnv.sh -d

terzina_ana_HomeDir="/home/users/b/burmistr/terzina_photon_propagation/terzinag4_ana/"

ekin_arr_MeV_e=(
    0.04
    0.10
    0.20
    0.30
    0.40
    0.50
    0.60
    0.70
    0.80
    1.00
    1.25
    1.50
    1.75
    2.00
    2.25
    2.50
    2.75
    3.00
    3.25
    3.50
    3.75
    4.00
    4.25
    4.50
    4.75
    5.00
    5.50
    6.00
    6.50
    7.00
)

ekin_arr_MeV_p=(
    0.100
    0.150
    0.200
    0.300
    0.400
    0.500
    0.600
    0.700
    1.000
    1.500
    2.000
    3.000
    4.000
    5.000
    6.000
    7.000
    10.00
    15.00
    20.00
    30.00
    40.00
    50.00
    60.00
    70.00
    100.0
    150.0
    200.0
    300.0
    400.0
)

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d       : single job for photon simulation"
    echo " [1]          : jobID"
    echo " [0] -bkg     : single job for background simulation"
    echo " [1]          : root file list"
    echo " [2]          : output root file with histograms"
    echo " [0] -bkglist : list creation for background files"
    echo " [0] -compile : compile"
    echo " [0] -h       : print help"
}

if [ $# -eq 0 ] 
then
    printHelp
else
    if [ "$1" = "-d" ]; then
        if [ $# -eq 2 ]; then
	    #
	    jobID=$2
	    energyBin=10   #10PeV     ok
	    #energyBin=35   #35PeV     ok
	    #energyBin=70   #70PeV     ok
	    #energyBin=100  #100PeV    ok
	    #energyBin=350  #350PeV    ok    
	    #energyBin=700  #700PeV    ok
	    #energyBin=1000 #1000PeV   ok 
	    #energyBin=3000 #3000PeV   ok
	    eKin=$energyBin
	    #
            inRootFileG4_dir="../root/$energyBin""PeV/$jobID"
	    inRootFileShower_dir="/home/users/b/burmistr/easchersim/root/$jobID"
	    inDatFileShower_dir=$inRootFileShower_dir
	    outHistSingleF_dir="../hist_root/$energyBin""PeV/$jobID"
	    wfSim_Terzina_conf="wfSim_Terzina_25um_conv_fit_40MHz_filter_signal.conf"
	    #
	    mkdir -p $outHistSingleF_dir
	    for inRootFileG4 in $(ls -l $inRootFileG4_dir/*.root | awk {'print $9'}) ; do
		#for inRootFileG4 in $(ls -l $inRootFileG4_dir/*0000000*.root | awk {'print $9'}) ; do
		echo "$inRootFileG4"
		inRootFileG4BaseName=$(basename $inRootFileG4)
		echo "$inRootFileG4BaseName"
		eventID="${inRootFileG4BaseName:11:7}"
		#
		inRootFileShower=$inRootFileShower_dir/"EASCherSim_"$eventID".ini.npz.root"
		inDatFileShower=$inDatFileShower_dir/"trkInfo_"$eventID".dat"
		outHistSingleF=$outHistSingleF_dir/"hist_"$eventID"_g4.root"
		#
		echo "eventID            = $eventID"
		echo "inRootFileG4       = $inRootFileG4"
		echo "inRootFileShower   = $inRootFileShower"
		echo "inDatFileShower    = $inDatFileShower"
		echo "eKin               = $eKin"
		echo "outHistSingleF     = $outHistSingleF"
		echo "wfSim_Terzina_conf = $wfSim_Terzina_conf"
		#
		srun $terzina_ana_HomeDir/runterzina 2 $inRootFileShower $inDatFileShower $inRootFileG4 $eKin $outHistSingleF $wfSim_Terzina_conf
		#$terzina_ana_HomeDir/runterzina 2 $inRootFileShower $inDatFileShower $inRootFileG4 $eKin $outHistSingleF $wfSim_Terzina_conf
		#echo "$terzina_ana_HomeDir/runterzina 2 $inRootFileShower $inDatFileShower $inRootFileG4 $eKin $outHistSingleF $wfSim_Terzina_conf"
	    done
	else
            printHelp
	fi
    elif [ "$1" = "-compile" ]; then
	make -f Makefileterzina clean; make -f Makefileterzina runterzina;
    elif [ "$1" = "-bkg" ]; then
        if [ $# -eq 3 ]; then
	    #
	    bkg_root_file_list=$2
	    bkg_hist_root_file=$3
	    echo "bkg_root_file_list = $bkg_root_file_list"
	    echo "bkg_hist_root_file = $bkg_hist_root_file"
	    srun $terzina_ana_HomeDir/runterzina 3 $bkg_root_file_list $bkg_hist_root_file
	else
            printHelp
	fi
    elif [ "$1" = "-bkglist" ]; then
        if [ $# -eq 1 ]; then
	    #
            inRootFileG4_data="../root_bkg/"
            listDir="../root_fileLists_bkg/"
	    #../root_bkg/00000/e-_Ekin_0.20MeV_g4.root
            for energy_ekin_Mev in ${ekin_arr_MeV_e[@]} ; do
		echo "energy_ekin_Mev = $energy_ekin_Mev"
		for inRootFileG4dir in $(ls -l $inRootFileG4_data/ | awk {'print $9'}) ; do
		    theFILE=$inRootFileG4_data$inRootFileG4dir"/e-_Ekin_"$energy_ekin_Mev"MeV_g4.root"		
		    if test -f "$theFILE"; then
			echo $theFILE >> $listDir"e-_Ekin_"$energy_ekin_Mev"MeV.dat"
		    fi
		done
	    done
	    #../root_bkg/00000/proton_Ekin_70.00MeV_g4.root
            for energy_ekin_Mev in ${ekin_arr_MeV_p[@]} ; do
		echo "energy_ekin_Mev = $energy_ekin_Mev"
		for inRootFileG4dir in $(ls -l $inRootFileG4_data/ | awk {'print $9'}) ; do
		    theFILE=$inRootFileG4_data$inRootFileG4dir"/proton_Ekin_"$energy_ekin_Mev"MeV_g4.root"
		    if test -f "$theFILE"; then
			echo $theFILE >> $listDir"proton_Ekin_"$energy_ekin_Mev"MeV.dat" 
		    fi
		done
	    done
	else
            printHelp
	fi
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi
fi

#espeak "I have done"
