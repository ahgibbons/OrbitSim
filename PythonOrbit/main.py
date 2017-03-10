# -*- coding: utf-8 -*-
"""
Created on Thu Mar  9 15:16:35 2017

OrbitSim

@author: andrew
"""

import numpy as np
import pandas as pd

G = 1

class TestMass:
    def __init__(self,x,y,vx,vy,dt):
        self.x0 = x
        self.y0 = y
        self.vx = vx
        self.vy = vy
        self.m = 1

        self.x = x + vx*dt
        self.y = y + vy*dt

        self.otherMasses = []

    def set_otherMasses(self,masses):
        self.otherMasses = masses
        
    def stepStart(self):
        x = self.x
        y = self.y
        vx = self.vx
        vy = self.vy
        
        fx = sum([self.grav(m) for m in self.otherMasses])
        fy = sum([self.grav(m) for m in self.otherMasses])

        ax = fx/self.m
        ay = fy/self.m

        self.vxn = vx + ax*dt
        self.vyn = vy + ay*dt

        self.xn = x + 0.5*(self.vxn+self.vx)*dt
        self.yn = y + 0.5*(self.vxn+self.vx)*dt

    def stepEnd(self):
        self.x0 = self.x
        self.y0 = self.x
        self.x = self.xn
        self.y = self.yn
        self.vx = self.vxn
        self.vy = self.vyn
        
class Mass:
    def __init__(self,x,y,vx,vy,dt,m):
        self.x0 = x
        self.y0 = y
        self.vx = vx
        self.vy = vy
        self.m = m

        self.x = x + vx*dt
        self.y = y + vy*dt

        self.otherMasses = []

    

        

def main():
    cmass = Mass(0,0,0,0,1)
    tmass = TestMass(0,5,2,0)

    tmasses = [tmass]
