# sparse-matrix-mult
HW3.1 SPARSE MATRIX DOT PRODUCT MULTIPLICATION
by Viktor Dahbura
Created: 10/08/2016

-About:
	This program multiplies two sparse matricies. It then outputs the result values to a text file excluding zeros. 
	The input coordinates can be sorted or unsorted. If the input coordinates are unsorted, it will use a sequential search algorithm.
	If the input coordinates are sorted, it will use a binary seach algorithm to improve program efficiency.
	The output result coordinates will then be sorted using a O(n^2) or O(nlogn) algorithm depeding on user input. 
  
-Input file format:
  #i j v
   1 1 5
   2 3 4
   3 3 0
	
-To compile:
	Command line for compiling in terminal:
	g++ -std=c++11 sparse.cpp -o sparse
-To run:
	Command line to run in terminal given 2 input .txt files and addition implementation:
	sparse "operation=<add|multiply>;storage=<array|linkedlist>;sort=<nosort|nsquared|nlogn>;A=<file>;B=<file>;result=<file>".


	Example:
	./sparse "operation=multiply;storage=array;sort=nlogn;A=a.txt;B=b.txt;result=c.txt".
	
	**Note:
	If method of storage is not given, storage = array by default.
	If method of sorting is not given, sort = nlogn by default.

-To test:
	To test different file cases using provided test.sh:
	sh test.sh






