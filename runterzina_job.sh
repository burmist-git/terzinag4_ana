#!/bin/sh
#SBATCH --job-name crgen%j
#SBATCH --error /home/users/b/burmistr/terzina_photon_propagation/job_error/crgen_%j.error
#SBATCH --output /home/users/b/burmistr/terzina_photon_propagation/job_output/output_%j.output
#SBATCH --ntasks 1
#SBATCH --cpus-per-task 1
#SBATCH --partition public-cpu
#SBATCH --time 0-00:20:00

source /home/users/b/burmistr/terzina_photon_propagation/setupEnv.sh -d

terzina_ana_HomeDir="/home/users/b/burmistr/terzina_photon_propagation/terzinag4_ana/"

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d    : single job"
    echo " [1]       : jobID"
    echo " [0] -h    : print help"
}

if [ $# -eq 0 ] 
then
    printHelp
else
    if [ "$1" = "-d" ]; then
        if [ $# -eq 2 ]; then
	    #
	    jobID=$2
	    energyBin=100
	    eKin=$energyBin
	    #
            inRootFileG4_dir="../root/$energyBin""PeV/$jobID"
	    inRootFileShower_dir="/home/users/b/burmistr/easchersim/root/$jobID"
	    inDatFileShower_dir=$inRootFileShower_dir
	    outHistSingleF_dir="../hist_root/$energyBin""PeV/$jobID"
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
		echo "eventID          = $eventID"
		echo "inRootFileG4     = $inRootFileG4"
		echo "inRootFileShower = $inRootFileShower"
		echo "inDatFileShower  = $inDatFileShower"
		echo "eKin             = $eKin"
		echo "outHistSingleF   = $outHistSingleF"
		#
		srun $terzina_ana_HomeDir/runterzina 2 $inRootFileShower $inDatFileShower $inRootFileG4 $eKin $outHistSingleF
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
