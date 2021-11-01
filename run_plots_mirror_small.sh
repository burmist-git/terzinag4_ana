#!/bin/bash

rm plots_mirror_small_C.d
rm plots_mirror_small_C.so
rm plots_mirror_small_C_ACLiC_dict_rdict.pcm
rm plots_mirror_small.C~

root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0m0.root\" ,\"m0\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0m1.root\" ,\"m1\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0m2.root\" ,\"m2\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0m3.root\" ,\"m3\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0m4.root\" ,\"m4\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0m5.root\" ,\"m5\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0m6.root\" ,\"m6\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0m7.root\" ,\"m7\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0m8.root\" ,\"m8\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0m9.root\" ,\"m9\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0m10.root\",\"m10\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0p1.root\" ,\"p1\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0p2.root\" ,\"p2\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0p3.root\" ,\"p3\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0p4.root\" ,\"p4\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0p5.root\" ,\"p5\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0p6.root\" ,\"p6\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0p7.root\" ,\"p7\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0p8.root\" ,\"p8\")"
root -l -b -q "plots_mirror_small.C+(\"./hist/hist_lhcBrich_mirror_small_z0p9.root\" ,\"p9\")"
