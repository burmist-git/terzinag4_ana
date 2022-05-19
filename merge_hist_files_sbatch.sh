#!/bin/sh

anaHomeDir="/home/users/b/burmistr/terzina_photon_propagation/terzinag4_ana/"
mergRootDir="./merg_hist"

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d       : default - merge all Enegry bins "
    echo " [0] -s       : merge single Enegry bins "
    echo " [0] -compile : compile ./merge_hist_files "
    echo " [0] -info    : print info"
    echo " [0] -kill    : kill all jobs"
    echo " [0] -h       : print help"
}

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then
	for ekin in $(ls ../root/); do
	    ekin_in_PeV=${ekin:0:-3}
	    echo $ekin
	    echo "$ekin_in_PeV"
	    sbatch $anaHomeDir/merge_hist_files_job.sh -d 0 $mergRootDir/merg_hist_$ekin.root $ekin_in_PeV
	done
    elif [ "$1" = "-s" ]; then
	ekin_in_PeV=3000
	ekin=$ekin_in_PeV"PeV"
	sbatch $anaHomeDir/merge_hist_files_job.sh -d 0 $mergRootDir/merg_hist_$ekin.root $ekin_in_PeV
    elif [ "$1" = "-compile" ]; then
	rm -rf merge_hist_files
	make -f Makefileterzina merge_hist_files
    elif [ "$1" = "-info" ]; then
	squeue | head -n 1
	squeue | grep burmistr
    elif [ "$1" = "-kill" ]; then
	scancel --user=burmistr --state=pending
	scancel --user=burmistr --state=CG
	scancel --user=burmistr --state=R
    elif [ "$1" = "-h" ]; then
	printHelp
    else
        printHelp
    fi
fi

#espeak "I have done"
