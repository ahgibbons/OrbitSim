#!/usr/bin/python

import matplotlib
matplotlib.use('Agg')

import sys
import matplotlib.pyplot as plt
import pandas as pd

def plotOrbit(infile,outfile):
	df = pd.read_csv(infile,sep=' ',header=0)
	
	xs = df['x'].get_values()
	ys = df['y'].get_values()	

	fig = plt.figure()
	ax = fig.add_subplot(111)

	ax.plot(xs,ys)

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

