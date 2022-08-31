# Make file for homework 8
# CS1571 Fall 02

data = digit_x.dat digit_x_test.dat digit_y.dat digit_y_test.dat

all: main11.c main11.h $(data)
	g++ -o digits main11.c