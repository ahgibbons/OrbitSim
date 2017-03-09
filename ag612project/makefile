# Makefile

main.out: Mass.o main.o Verlet.o
	g++ -o main.out Mass.o main.o Verlet.o

Mass.o: Mass.cc Mass.h
	g++ -c Mass.cc

Verlet.o: Verlet.cc Mass.h Verlet.h
	g++ -c Verlet.cc

main.o: main.cc Mass.h
	g++ -c main.cc

clean:
	rm *.o