# sparse-matrix-mult
HW3.1 SPARSE MATRIX DOT PRODUCT MULTIPLICATION
by Viktor Dahbura
Created: 10/08/2016

-About:
	This program multiplies two sparse matricies. It then outputs the result values to a text file excluding zeros. 
	The input coordinates can be sorted or unsorted. If the input coordinates are unsorted, it will use a sequential search algorithm 	  to search for coordinates needed for matrix multiplication.
	If the input coordinates are sorted, it will use a binary seach algorithm to improve program efficiency.
	The output result coordinates will then be sorted using a O(n^2) or O(nlogn) algorithm depeding on user input. 
  
-Input file format:

	Example:
	
 	#i j v
  	1 1 5
   	2 3 4
   	3 3 0
   
**Note:
If method of storage is not given, storage = array by default.
If method of sorting is not given, sort = nlogn by default.







