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
    def __init__(self,x,y,vx,vy):
        self.x = x
        self.y = y
        self.vx = vx
        self.vy = vy
        
class Mass:
    def __init__(self,x,y,vx,vy,m):
        self.x = x
        self.y = y
        self.vx = vx
        self.vy = vy
        self.m = m



def main():
    