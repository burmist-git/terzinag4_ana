#!/bin/bash

make -f Makefileterzina clean; make -f Makefileterzina runterzina;

function runana {
    inRootFiles="./data/$1"
    outHistSingleF="./hist/hist_$1"
    ./runterzina 1 $inRootFiles $outHistSingleF
}

#runana lhcBrich_mirror_small_z0m0.root
#runana lhcBrich_mirror_small_z0m1.root
#runana lhcBrich_mirror_small_z0m2.root
#runana lhcBrich_mirror_small_z0m3.root
#runana lhcBrich_mirror_small_z0m4.root
#runana lhcBrich_mirror_small_z0m5.root
#runana lhcBrich_mirror_small_z0m6.root
#runana lhcBrich_mirror_small_z0m7.root
#runana lhcBrich_mirror_small_z0m8.root
#runana lhcBrich_mirror_small_z0m9.root
#runana lhcBrich_mirror_small_z0p1.root
#runana lhcBrich_mirror_small_z0p2.root
#runana lhcBrich_mirror_small_z0p3.root
#runana lhcBrich_mirror_small_z0p4.root
#runana lhcBrich_mirror_small_z0p5.root
#runana lhcBrich_mirror_small_z0p6.root
#runana lhcBrich_mirror_small_z0p7.root
#runana lhcBrich_mirror_small_z0p8.root
#runana lhcBrich_mirror_small_z0p9.root

runana proj_sphere_small_z0m9.root
runana proj_sphere_small_z0m8.root
runana proj_sphere_small_z0m7.root
runana proj_sphere_small_z0m6.root
runana proj_sphere_small_z0m5.root
runana proj_sphere_small_z0m4.root
runana proj_sphere_small_z0m3.root
runana proj_sphere_small_z0m2.root
runana proj_sphere_small_z0m1.root
runana proj_sphere_small_z0m0.root
runana proj_sphere_small_z0p1.root
runana proj_sphere_small_z0p2.root
runana proj_sphere_small_z0p3.root
runana proj_sphere_small_z0p4.root
runana proj_sphere_small_z0p5.root
runana proj_sphere_small_z0p6.root
runana proj_sphere_small_z0p7.root
runana proj_sphere_small_z0p8.root
runana proj_sphere_small_z0p9.root
