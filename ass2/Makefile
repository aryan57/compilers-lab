####################################
#### Aryan Agarwal              ####   
#### 19CS30005                  ####
#### CS39003 -> Assignment 2    ####
####################################

a.out: main.o libass2_19CS30005.a
	gcc main.o -L. -lass2_19CS30005

main.o: main.c myl.h
	gcc -Wall -c main.c

libass2_19CS30005.a: ass2_19CS30005.o
	ar -rcs libass2_19CS30005.a ass2_19CS30005.o

ass2_19CS30005.o: ass2_19CS30005.c myl.h
	gcc -Wall -c ass2_19CS30005.c

clean:
	rm a.out main.o libass2_19CS30005.a ass2_19CS30005.o
