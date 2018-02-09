#which compiler used
	cc = gcc
#where the include file is
	INCLUDE = ./include
main:Tool.o main.o math.o
	$(cc) Tool.o main.o -omain 
Tool.o:
	$(cc) -c Tool.cpp
main.o:
	$(cc) -c main.cpp
matn.o:
	$(cc) -c math.cpp
clean:
	rm Tool.o main.o main
