#!/usr/bin/python

import matplotlib
matplotlib.use('Agg')

import sys
import matplotlib.pyplot as plt
import pandas as pd

def plotOrbit(infile,outfile):
	df = pd.read_csv(infile,sep=' ',header=0)
	
	df.plot(x=0,y=0)
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

