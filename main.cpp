//----------------------------------------------//
//												//
//	:: Sparse Matrix Multiplication :: sparse   //
//	Created by: Viktor Dahbura					//
//	Date: 10/01/2016							//
//												//
//----------------------------------------------//

#include <iostream> 
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "array.h"
#include "arraysort.h"
#include "arraysearch.h"
//#include "linkedlist.h"
using namespace std;

int getNumRows(string filename); // FUNCTION DECLATARION FOR getNumRows

int main()
{
	ifstream inStreamA;
	ifstream inStreamB;
	ofstream outStream;
	string line;
	int n1 = 0;
	int n2 = 0;
	int numRowsA;
	int numRowsB;
	int numRowsC;

	//GETTING THE NUMBER OF ROWS OF EACH MATRIX
	numRowsA = getNumRows("A.txt");
	numRowsB = getNumRows("B.txt");

	//NUMBER OF POSSIBLE ENTRIES FOR listC
	numRowsC = numRowsA * numRowsB;

	//CREATING THE MATRICES BASED ON NUMBER OF ROWS
	ArrayList listA(numRowsA);
	ArrayList listB(numRowsB);
	ArrayList listC(numRowsC);

	//FILLING MATRICES listA AND listB
	listA.readFile("A.txt");
	listB.readFile("B.txt");

	//CHECK FOR EMPTY MATRICES										
	listA.checkEmptryMatrix("C.txt");
	listB.checkEmptryMatrix("C.txt");	

	//REMOVES ZEROS FROM MATRICES IF ANY
	listA.removeZeros();
	listB.removeZeros();

	//CHECK MATRIX FOR COMPATIBILITY FOR ADDITION
	listA.compareSizes(listB, "C.txt");

	//DOT PRODUCT MULTIPLICATION
	//CHECKS IF MATRICES ARE SORTED FIRST FOR APPROPIATE FUNCTION CALL
	if (listA.checkIfSorted() == true && listB.checkIfSorted() == true)
		listA.dotProductSorted(listB, listC);
	else
		listA.dotProductNonSorted(listB, listC);

	//SORT listC
	listC.sort();

	//REMOVES ANY ZEROS, IF ANY, FROM MULTIPLICATION IN listC;
	listC.removeZeros();

	//SENDS listC TO THE OUTPUT FILE
	listC.sendToOutput("C.txt");

	//TESTING
	
	system("pause");
	return 0;
}

//getNumRows FUNCTION DEFINITION
int getNumRows(string filename) {
	ifstream inStream;
	string line;
	int numRows = 0;
	int temp;
	inStream.open(filename);
	while (getline(inStream, line)) {
		if (line[0] == '#' || line.length() == 0) continue;
		istringstream fn(line);
		fn >> temp;
		numRows++;
	}
	inStream.close();
	return numRows++;
}