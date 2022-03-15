rm run_sim_camera
make -f Makefileterzina run_sim_camera
time ./run_sim_camera 0 10000 80.0 7 psf_sigma_flt.dat Proton_100PeV_525km_30km.root 7.0
root -l ./run_sim_camera.root
