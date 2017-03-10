# -*- coding: utf-8 -*-
"""
Created on Thu Mar  9 15:16:35 2017

OrbitSim

@author: andrew
"""

import numpy as np
import pandas as pd
import sys

G = 1

class TestMass:
    def __init__(self,x,y,vx,vy,dt,m):
        self.m = m        
        self.r0 = np.array([x,y])
        self.v = np.array([vx,vy])
        self.dt = dt

        self.r = self.r0 + self.v*dt 


        self.otherMasses = []

    def set_otherMasses(self,masses):
        self.otherMasses = masses
        
    def stepStart(self):

        f = sum([self.grav(m) for m in self.otherMasses])

        a = f/self.m
        
        self.verletStep(a)
                          
    def verletStep(self,a):
        r  = self.r
        r0 = self.r0
        dt = self.dt
        
        rn = 2*r - r0 + (dt*dt*a)
        vn = (rn - r0) / (2*dt)  

        self.rn = rn            
        self.vn = vn
    

    def stepEnd(self):
        self.r0 = self.r
        self.r  = self.rn
        self.v  = self.vn
        
        
    def grav(self,omass):
        m1 = self.m
        r1 = self.r
        
        m2 = omass.m
        r2 = omass.r
        
        A = G*m1*m2
        dr = r2-r1
        r_32 = np.power(np.dot(dr,dr),3/2)
               
        f = A*dr/r_32
               
        return f
                

def main(finalTime,totalSteps):
    dt = float(finalTime) / totalSteps
    
    m1 = TestMass(3,0,0,0.5,dt,1)
    m0 = TestMass(0,0,0,0,dt,1)
    
    m1.set_otherMasses([m0])
    
    allMasses = [m0,m1]
    
    xs = np.array([0.0]*totalSteps)
    ys = np.array([0.0]*totalSteps)
    
    
    for n in np.arange(totalSteps):
        for m in allMasses:
            m.stepStart()
        for m in allMasses:
            m.stepEnd()
        xs[n] = m1.r[0]
        ys[n] = m1.r[1]
        
    ts = np.linspace(0,finalTime,totalSteps)
    
    return np.array([xs,ys,ts]).T
    
if __name__ == "__main__":
    """
    args: [Final time] [Total steps]
    """
    
    argv = sys.argv

    if len(argv)!=3:
        raise Exception("Incorrect number of arguments!")

    
    final_time = float(argv[1])
    total_steps = int(argv[2])

    res = main(final_time,total_steps)
    print("Simulation Complete")

    df = pd.DataFrame(res,columns=['x','y','t'])
    df.to_csv("orbit_out.csv",sep=' ')
    print("Data saved to orbit_out.csv")
    

