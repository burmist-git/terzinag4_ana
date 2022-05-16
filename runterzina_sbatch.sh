#!/bin/sh

anaHomeDir="/home/users/b/burmistr/terzina_photon_propagation/terzinag4_ana/"
n_jobs=544
#n_jobs=1

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d         : default - simulation with terzinag4"
    echo " [0] -info      : print info"
    echo " [0] -infoshort : print short info"
    echo " [0] -kill      : kill all jobs"
    echo " [0] -h         : print help"
}

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then
	for i in $(seq 0 $n_jobs); do
            jobID=`printf "%05d" $i`
	    sbatch $anaHomeDir/runterzina_job.sh -d $jobID
	done
    elif [ "$1" = "-info" ]; then
	squeue | head -n 1
	squeue | grep burmistr
    elif [ "$1" = "-infoshort" ]; then
	totnjobs=$(source $anaHomeDir/runterzina_sbatch.sh -info | wc -l)
	cpunjobs=$(source $anaHomeDir/runterzina_sbatch.sh -info | grep cpu |wc -l)
	echo "totnjobs = $totnjobs"
	echo "cpunjobs = $cpunjobs"
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
