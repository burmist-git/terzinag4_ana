#!/bin/sh

anaHomeDir="/home/users/b/burmistr/terzina_photon_propagation/terzinag4_ana/"

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d    : default - merge all Enegry bins "
    echo " [0] -info : print info"
    echo " [0] -kill : kill all jobs"
    echo " [0] -h    : print help"
}

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then
	#for ekin in $(ls ../root/); do
	#ekin_in_PeV=${ekin:0:-3}
	#echo $ekin
	#echo "$ekin_in_PeV"
	ekin_in_PeV=10
	ekin=$ekin_in_PeV"PeV"
	sbatch $anaHomeDir/merge_hist_files_job.sh -d 0 merg_hist_$ekin.root $ekin_in_PeV
	ekin_in_PeV=1000
	ekin=$ekin_in_PeV"PeV"
	sbatch $anaHomeDir/merge_hist_files_job.sh -d 0 merg_hist_$ekin.root $ekin_in_PeV
	#done
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
