#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
Date        : Wed Jan 12 11:58:22 CET 2022
Autor       : Leonid Burmistrov
Description : Simple reminder-training example.
'''

import math

R_earth = 6371 #km, Earth radious

#r in km
def calc_g(r):
    r = r*1000;
    G = 6.6743e-11 #m^3*kg^-1*s^-2
    M_earth = 5.97237e+24
    return G*M_earth/r/r

#h in km
def calc_speed(h):
    r = R_earth*1000.0 + h*1000
    return math.sqrt(r*calc_g(r/1000.0))

#h in km
def calc_period(h):
    r = R_earth*1000.0 + h*1000
    return 2*math.pi*r/calc_speed(h)/60
    
if __name__ == "__main__":
    #Terzina BoL
    #h = 550        #km, mean height
    #sma = 6913     #km, Semi-major axis
    #Terzina EoL
    h = 525        #km, mean height
    sma = 6879     #km, Semi-major axis
    #
    l_OT = R_earth + h
    l_OC = R_earth
    l_CT = math.sqrt(l_OT*l_OT - l_OC*l_OC)
    #
    Alpha = math.degrees(math.acos(l_OC/l_OT))
    Beta  = 90 - Alpha
    #
    l_Cp = l_OC*math.sin(math.radians(Alpha))
    print('l_CT           = ',l_CT)
    print('l_Cp           = ',l_Cp)
    print('Alpha          = ',Alpha)
    print('Beta           = ',Beta)
    print('calc_speed(h)  = ',calc_speed(h))
    print('calc_period(h) = ',calc_period(h))
