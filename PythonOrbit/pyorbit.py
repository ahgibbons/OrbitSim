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
    def __init__(self,x,y,vx,vy,m):
        self.m = m        
        self.r0 = np.array([x,y])
        self.v = np.array([vx,vy])

        self.r = self.r0 
        self.xpath = np.array([])
        self.ypath = np.array([])

        self.otherMasses = []

    def initMotion(self,dt):
        self.r = self.r0 + self.v*dt

    def set_otherMasses(self,masses):
        self.otherMasses = masses
        
    def stepStart(self,dt):

        f = sum([self.grav(m) for m in self.otherMasses])

        a = f/self.m
        
        self.verletStep(a,dt)
                          
    def verletStep(self,a,dt):
        r  = self.r
        r0 = self.r0
        
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

def perpV(G,M,r):
    return np.sqrt(float(G*M)/r)

def period(a,G,M):
    return 2*np.pi*np.sqrt(float(a*a*a)/(G*M))


bigMass = TestMass(0,0,0,0,1)
littleMasses = [TestMass(r,0,0,perpV(1,1,r),1) for r in range(5,10)]
for m in littleMasses:
    m.set_otherMasses([bigMass])

allMasses = [bigMass] + littleMasses

def main(finalTime,totalSteps,masses):
    dt = float(finalTime) / totalSteps
    
    for m in masses:
        m.initMotion(dt)
        m.xpath = np.array([0.0]*totalSteps)
        m.ypath = np.array([0.0]*totalSteps)


    
    for n in np.arange(totalSteps):
        for m in masses:
            m.stepStart(dt)
        for m in masses:
            m.stepEnd()
            m.xpath[n] = m.r[0]
            m.ypath[n] = m.r[1]

        
    ts = np.linspace(0,finalTime,totalSteps)
    res = ts

    for m in masses:
        res = np.vstack([res,m.xpath,m.ypath])

    return res

    
if __name__ == "__main__":
    """
    args: [Final time] [Total steps]
    """
    
    argv = sys.argv

    if len(argv)==1:
        print("args: [Final Time] [Total Steps]")
    

    elif len(argv)!=4:
        raise Exception("Incorrect number of arguments!")
    else:
    
        final_time = float(argv[1])
        total_steps = int(argv[2])
        outfile = argv[3]

        res = main(final_time,total_steps,allMasses).T
        print("Simulation Complete")
        print("Number of masses: {:d}".format(len(allMasses)))

        colnames = ['t']
        for n,m in enumerate(allMasses):
            colnames.append('x{:d}'.format(n))
            colnames.append('y{:d}'.format(n))



        df = pd.DataFrame(res,columns=colnames)
        df.to_csv(outfile,sep=' ')
        print("Data saved to {:s}".format(outfile))
    

