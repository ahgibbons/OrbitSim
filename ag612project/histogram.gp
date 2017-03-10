reset
n=100	#number of intervals
max=9.	#max value
min=0.	#min value
width=(max-min)/n	#interval width
#function used to map a value to the intervals
hist(x,width)=width*floor(x/width)+width/2.0
set term png truecolor enhanced 	#output terminal and file
set output "histogram.png"
set xrange [min:max]
set yrange [0:]
#to put an empty boundary around the
#data inside an autoscaled graph.
set offset graph 0.05,0.05,0.05,0.0
set xtics min,(max-min)/5,max
set boxwidth width*0.9
set style fill transparent solid 0.5	#fillstyle
set tics out nomirror
set xlabel "Distance / distance unit"
set ylabel "Frequency"
set title "Distance From Central Mass: Histogram"
#count and plot
plot "tmass_distance_flipped.csv" u (hist($1,width)):(1.0) smooth freq w boxes lc rgb"green" title "t=0", \
	"tmass_distance_flipped.csv" u (hist($900,width)):(1.0) smooth freq w boxes lc rgb"red" title "t=900"
