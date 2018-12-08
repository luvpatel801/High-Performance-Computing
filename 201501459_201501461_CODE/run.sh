#!/bin/sh

echo "Output"
echo "Output" >> output.txt
gcc sudoku-omp.c -o code -fopenmp -lm

for t in 1 2 4 8 12
do
    echo "Running for $t threads";
	echo "For number of threads = $t" >> output.txt
	for name in "ecase1.txt" "ecase2.txt" "ecase3.txt" "mcase.txt" "hcase.txt" "16x16.txt" "25x25.txt" "64x64.txt" "impcase.txt"
	do
		echo "Filename : $name" >> output.txt
		./code $name $t >> output.txt
	done
done
