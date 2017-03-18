#!/usr/bin/python

import matplotlib
matplotlib.use('Agg')

import sys
import matplotlib.pyplot as plt
import pandas as pd

def plotOrbit(infile,outfile):
        df = pd.read_csv(infile,sep=' ',header=0)

        nplots = len(df.columns)


        fig = plt.figure()
        ax = fig.add_subplot(111,aspect='equal')

        for n in range(1,nplots,2):
                xkey = df.columns[n]
                ykey = df.columns[n+1]
                xs = df[xkey].get_values()
                ys = df[ykey].get_values()
                ax.plot(xs,ys)

        plt.savefig(outfile)

        print("Image made! Plotted trajectory of {:d} mass(es).".format((nplots-1)//2))

        return 1

def main(argv):
        infile = argv[1]
        outfile = argv[2]

        plotOrbit(infile,outfile)

if __name__=="__main__":
        argv = sys.argv
        main(argv)

