#!/bin/sh

anaHomeDir="/home/users/b/burmistr/terzina_photon_propagation/terzinag4_ana/"
n_jobs=544
#n_jobs=1

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d         : default - simulation with terzinag4"
    echo " [0] -bkg       : run background analysis"
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
	#for i in $(seq 0 $n_jobs); do
        #    jobID=`printf "%05d" $i`
	#    sbatch $anaHomeDir/runterzina_job.sh -d $jobID
	#done
	for i in $(seq 0 $n_jobs); do
            jobID=`printf "%05d" $i`
	    sbatch $anaHomeDir/runterzina_job_10PeV.sh -d $jobID
	done
	for i in $(seq 0 $n_jobs); do
            jobID=`printf "%05d" $i`
	    sbatch $anaHomeDir/runterzina_job_35PeV.sh -d $jobID
	done
	for i in $(seq 0 $n_jobs); do
            jobID=`printf "%05d" $i`
	    sbatch $anaHomeDir/runterzina_job_70PeV.sh -d $jobID
	done
	for i in $(seq 0 $n_jobs); do
            jobID=`printf "%05d" $i`
	    sbatch $anaHomeDir/runterzina_job_100PeV.sh -d $jobID
	done
	for i in $(seq 0 $n_jobs); do
            jobID=`printf "%05d" $i`
	    sbatch $anaHomeDir/runterzina_job_350PeV.sh -d $jobID
	done
	for i in $(seq 0 $n_jobs); do
            jobID=`printf "%05d" $i`
	    sbatch $anaHomeDir/runterzina_job_700PeV.sh -d $jobID
	done
	for i in $(seq 0 $n_jobs); do
            jobID=`printf "%05d" $i`
	    sbatch $anaHomeDir/runterzina_job_1000PeV.sh -d $jobID
	done
	for i in $(seq 0 $n_jobs); do
            jobID=`printf "%05d" $i`
	    sbatch $anaHomeDir/runterzina_job_3000PeV.sh -d $jobID
	done
    elif [ "$1" = "-bkg" ]; then
        inRootFileListG4_dir="../root_fileLists_bkg/"
        outRootHistFileG4_dir="../hist_root_bkg/"
	for bkg_root_file_list in $(ls -lrt $inRootFileListG4_dir/*.dat | awk {'print $9'}) ; do
		bkg_root_file_list_basename=$(basename $bkg_root_file_list)
		bkg_hist_root_file=$outRootHistFileG4_dir"hist_"$bkg_root_file_list_basename".root"
		echo "$bkg_root_file_list"
		echo "$bkg_hist_root_file"		
		sbatch $anaHomeDir/runterzina_job.sh -bkg $bkg_root_file_list $bkg_hist_root_file	 
		#$anaHomeDir/runterzina_job.sh -bkg $bkg_root_file_list $bkg_hist_root_file	 
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
