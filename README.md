# Quicksort
This is my implementation of a quick sort combined with merge sort which we needed to do for our data structures class.

The program works by taking in the number of unordered sublists and the number of numbers in each sublist from the command line in that order. 
Then the array that needs to be sorted is entered. It will then take each of the unordered sublists and perform a quick sort of them by using the pivot as the median number from the first, middle, and last number of the sublist. 
Once that's done, it will do a multiway merge on them to combine them all into one array.

## To run the program
To compile the code, you just need to run the makefile. To run the program you need to run "./a.out < testcases/input1.dat" (this is what I was using WSL).
