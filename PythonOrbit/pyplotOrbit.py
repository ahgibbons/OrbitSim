#!/usr/bin/python

import matplotlib
matplotlib.use('Agg')

import sys
import matplotlib.pyplot as plt
import pandas as pd

def plotOrbit(infile,outfile,nplots):
        df = pd.read_csv(infile,sep=' ',header=0)


        fig = plt.figure()
        ax = fig.add_subplot(111)

        for n in range(nplots):
                xkey = 'x'+str(n)
                ykey = 'y'+str(n)
                xs = df[xkey].get_values()
                ys = df[ykey].get_values()
                ax.plot(xs,ys)

        plt.savefig(outfile)

        print("Image made!")

        return 1

def main(argv):
        infile = argv[1]
        outfile = argv[2]
        nplot = int(argv[3])

        plotOrbit(infile,outfile,nplot)

if __name__=="__main__":
        argv = sys.argv
        main(argv)

