#!/bin/bash

rm -rf tvector2_2circles_fit.gif
ls -lrt *.gif | awk '{print $9}' | xargs -I {} echo {}
#aa=$?
#aa=(`ls -lrt *.gif | awk '{print $9}' | xargs`)
#echo $aa

#convert -delay 40 -loop 0 tvector2_2circles_fit_0.59999999999999998.gif tvector2_2circles_fit_0.5.gif tvector2_2circles_fit_0.40000000000000002.gif tvector2_2circles_fit_0.29999999999999999.gif tvector2_2circles_fit_0.20000000000000001.gif tvector2_2circles_fit_0.10000000000000001.gif tvector2_2circles_fit_0.gif tvector2_2circles_fit_-0.10000000000000001.gif tvector2_2circles_fit_-0.20000000000000001.gif tvector2_2circles_fit_-0.29999999999999999.gif tvector2_2circles_fit_-0.40000000000000002.gif tvector2_2circles_fit_-0.5.gif tvector2_2circles_fit_-0.59999999999999998.gif tvector2_2circles_fit_-0.69999999999999996.gif tvector2_2circles_fit_-0.80000000000000004.gif tvector2_2circles_fit_-0.90000000000000002.gif tvector2_2circles_fit_-1.gif tvector2_2circles_fit_-1.1000000000000001.gif tvector2_2circles_fit_-1.2.gif tvector2_2circles_fit_-1.3.gif tvector2_2circles_fit_-1.3999999999999999.gif tvector2_2circles_fit_-1.5.gif tvector2_2circles_fit_-1.6000000000000001.gif tvector2_2circles_fit_-1.7.gif tvector2_2circles_fit.gif
