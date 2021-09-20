map1: Assignment2.o generalops.o parse.o kdtree.o
	gcc -o map1 Assignment2.o generalops.o parse.o kdtree.o
	
Assignment2.o: Assignment2.c func.h
	gcc -c -Wall Assignment2.c
	
generalops.o: generalops.c func.h
	gcc -c -Wall generalops.c

parse.o: parse.c func.h
	gcc -c -Wall parse.c
	
kdtree.o: kdtree.c func.h
	gcc -c -Wall kdtree.c