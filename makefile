crg : crg.o
	cc -o crg crg.o

crg.o : crg.c
	cc -c crg.c

clean : 
	rm crg.o