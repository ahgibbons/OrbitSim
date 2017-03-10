
set terminal png;
set size ratio -1;
set out sprintf(ARG2);
plot ARG1 using 2:3 with lines;
