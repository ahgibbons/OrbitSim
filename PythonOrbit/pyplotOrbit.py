#!/usr/bin/python

import matplotlib
matplotlib.use('Agg')

import sys
import matplotlib.pyplot as plt
import pandas as pd

def plotOrbit(infile,outfile):
        df = pd.read_csv(infile,sep=' ',header=0)
	
        xs0 = df['x0'].get_values()
        ys0 = df['y0'].get_values()	

        xs1 = df['x1'].get_values()
        ys1 = df['y1'].get_values()

        fig = plt.figure()
        ax = fig.add_subplot(111)

        ax.plot(xs0,ys0)
        ax.plot(xs1,ys1)

        plt.savefig(outfile)

        print("Image made!")

        return 1

def main(argv):
	infile = argv[1]
	outfile = argv[2]

	plotOrbit(infile,outfile)

if __name__=="__main__":
	argv = sys.argv
	main(argv)

