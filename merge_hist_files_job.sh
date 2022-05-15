#!/bin/sh
#SBATCH --job-name crgen%j
#SBATCH --error /home/users/b/burmistr/terzina_photon_propagation/job_error/crgen_%j.error
#SBATCH --output /home/users/b/burmistr/terzina_photon_propagation/job_output/output_%j.output
#SBATCH --ntasks 1
#SBATCH --cpus-per-task 1
#SBATCH --partition public-cpu
#SBATCH --time 0-04:00:00

source /home/users/b/burmistr/terzina_photon_propagation/setupEnv.sh -d

terzina_ana_HomeDir="/home/users/b/burmistr/terzina_photon_propagation/terzinag4_ana/"

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d    : single job"
    echo " [1]       : (0) execution ID number"
    echo " [2]       : output root file"
    echo " [3]       : Ekin of the trk in PeV (integer)"
    echo " [0] -h    : print help"
}

if [ $# -eq 0 ] 
then
    printHelp
else
    if [ "$1" = "-d" ]; then
        if [ $# -eq 4 ]; then
	    #echo "$2" #0 (execution ID number)
	    #echo "$3" #output root file
	    #echo "$4" #Ekin of the trk in PeV (integer)
	    $terzina_ana_HomeDir/merge_hist_files $2 $3 $4
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
