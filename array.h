//----------------------------------------------//
//												//
//	:: Sparse Matrix Multiplication :: search   //
//	Created by: Viktor Dahbura					//
//	Date: 10/01/2016							//
//												//
//----------------------------------------------//

#pragma once
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
using namespace std;

struct Entry {
	int row;
	int col;
	float value;
};

class ArrayList {
public:
	ArrayList(int size);
	ArrayList();
	~ArrayList();

	int listSize() const;
	int maxListSize() const;
	void fill(int loc, int row, int col, float value);
	void print();
	int maxRow();
	int maxCol();
	int getRow(int loc);
	int getCol(int loc);
	float getValue(int loc);
	void readFile(string filename);
	void checkEmptryMatrix(string filename);
	void compareSizes(ArrayList& listB, string filename);
	void dotProductNonSorted(ArrayList& listB, ArrayList& listC);
	void dotProductSorted(ArrayList& listB, ArrayList& listC);
	void moveToC(ArrayList& listA, ArrayList& listB, ArrayList& listC);
	void removeAt(int loc);
	void removeZeros();
	bool compareVal(int n, int m);
	int getLineLoc(int n, int m);
	void sendToOutput(string filename);

	bool checkIfSorted();					//FUNCTION DEFINITION ON arraysort.h
	void sort();							//BUBBLE SORT bigO(n^2), FUNCTION DEFINITION ON arraysort.h	
	/*to do*/ void arraySort();				//MERGE SORT  bigO(nlog(n)), FUNCTION DEFINITION ON arraysort.h			
	int seqSearch(int n, int m);			//FUNCTION DEFINITION ON arraysearch.h
	int binSearch(int n, int m);			//FUNCTION DEFINITION ON arraysearch.h

	Entry *list;
	int length;
	int maxSize;
};

ArrayList::ArrayList(int size)
{
	maxSize = size;
	length = 0;
	list = new Entry[maxSize];
	assert(list != NULL);
}

ArrayList::~ArrayList() {
	delete[] list;
}

int ArrayList::listSize() const {
	return length;
}

int ArrayList::maxListSize() const {
	return maxSize;
}

void ArrayList::fill(int loc, int row, int col, float value) {
	list[loc].row = row;
	list[loc].col = col;
	list[loc].value = value;
	length++;
}

void ArrayList::print() {
	for (int i = 0; i < length; i++) {
		cout << list[i].row << " " << list[i].col << " " << setprecision(2) << fixed << list[i].value << endl;
	}
}

//int ArrayList::maxRow() {
//	return list[length - 1].row;
//}

int ArrayList::maxRow() {
	int maxRow = getRow(0);
	for (int i = 0; i < listSize(); i++) {
		if (getRow(i) > maxRow)
			maxRow = getRow(i);
		else
			continue;
	}
	return maxRow;
}

//int ArrayList::maxCol() {
//	return list[length - 1].col;
//}

int ArrayList::maxCol() {
	int maxCol = getCol(0);
	for (int i = 0; i < listSize(); i++) {
		if (getCol(i) > maxCol)
			maxCol = getCol(i);
		else
			continue;
	}
	return maxCol;
}

int ArrayList::getRow(int loc) {
	return list[loc].row;
}

int ArrayList::getCol(int loc) {
	return list[loc].col;
}

float ArrayList::getValue(int loc) {
	return list[loc].value;
}

void ArrayList::readFile(string filename) {
	int row, col;
	int n = 0;
	float value;
	string line;
	ifstream inStream;
	inStream.open(filename);
	while (getline(inStream, line)) {
		if (line[0] == '#' || line.length() == 0) continue;
		istringstream fn(line);
		fn >> row >> col >> value;
		if (row > 0 && col > 0) {
			fill(n, row, col, value);
			n++;
		}
	}
	inStream.close();
}

void ArrayList::checkEmptryMatrix(string filename) {
	ofstream outStream;
	if (maxListSize() == 0) {
		cout << "Empty Matrix " << endl;
		cout << "Terminating Program... " << endl;
		outStream.open(filename);
		outStream.close();

		system("pause");
		exit(1);
	}
}

void ArrayList::compareSizes(ArrayList& listB, string filename) {
	ofstream outStream;
	if (maxCol() != listB.maxRow()) {
		cout << maxRow() << " " << maxCol() << " <- list A's max Row and max Col" << endl;
		cout << listB.maxRow() << " " << listB.maxCol() << " <- list B's max Row and max Col" << endl;
		cout << "Sparse matrices are not compatible for multiplication." << endl;
		cout << "Generating empty output File..." << endl;
		outStream.open(filename);
		outStream.close();

		system("pause");
		exit(1);
	}
}

void ArrayList::moveToC(ArrayList& listA, ArrayList& listB, ArrayList& listC) {
	int i;
	int j = 0;
	for (i = 0; i < listC.maxListSize() && i < listA.listSize(); i++) {
		listC.fill(i, listA.getRow(i), listA.getCol(i), listA.getValue(i));
	}
}

void ArrayList::removeZeros() {
	for (int i = 0; i < length - 1; i++) {
		if (list[i].value == 0) {
			removeAt(i);
			i--;
		}
		else
			continue;
	}
}

void ArrayList::removeAt(int loc) {
	for (int i = loc; i < length - 1; i++)
		list[i] = list[i + 1];
	length--;
}

bool ArrayList::compareVal(int n, int m) {
	bool found = false;
	for (int i = 0; i < listSize(); i++) {
		if (n == getRow(i) && m == getCol(i)) {
			found = true;
		}
		else
			continue;
	}
	return found;
}

int ArrayList::getLineLoc(int n, int m) {
	for (int i = 0; i < listSize(); i++) {
		if (n == getRow(i) && m == getCol(i)) {
			return i;
		}
		else
			continue;
	}
	return 0;
}

void ArrayList::sendToOutput(string filename) {
	ofstream outStream;
	outStream.open(filename);
	outStream << "#Matrix C=A+B" << endl;
	for (int i = 0; i < listSize(); i++) {
		outStream << getRow(i) << " " << getCol(i) << " " << setprecision(2) << fixed << getValue(i) << endl;
	}
	outStream.close();
}

void ArrayList::dotProductNonSorted(ArrayList& listB, ArrayList& listC) {
	float valA;
	float valB;
	float mult = 0;
	float addMult;
	int searchA;
	int searchB;
	int n = 0;
	int actualMaxRow = maxRow();
	int actualMaxCol = maxCol();

	if (actualMaxRow < listB.maxRow())
		actualMaxRow = listB.maxRow();
	if (actualMaxCol < listB.maxCol())
		actualMaxCol = listB.maxCol();

	for (int i = 1; i <= maxRow(); i++) {
		for (int count = 1; count <= listB.maxCol(); count++) {
			addMult = 0;
			for (int j = 1; j <= maxCol(); j++) {
				searchA = seqSearch(i, j);
				if (searchA != -1)
					valA = getValue(searchA);
				else
					continue;
				searchB = listB.seqSearch(j, count);
				if (searchB != -1) {
					valB = listB.getValue(searchB);
					addMult += (valA * valB);
				}
				else
					continue;
			}
			if (addMult != 0) {
				listC.fill(n, i, count, addMult);
				n++;
			}
			else if (i == actualMaxRow && count == actualMaxCol) {
				listC.fill(n, i, count, addMult);
				n++;
			}
		}
	}
}

void ArrayList::dotProductSorted(ArrayList& listB, ArrayList& listC) {
	float valA;
	float valB;
	float mult = 0;
	float addMult;
	int searchA;
	int searchB;
	int n = 0;
	int actualMaxRow = maxRow();
	int actualMaxCol = maxCol();

	if (actualMaxRow < listB.maxRow())
		actualMaxRow = listB.maxRow();
	if (actualMaxCol < listB.maxCol())
		actualMaxCol = listB.maxCol();

	for (int i = 1; i <= maxRow(); i++) {
		for (int count = 1; count <= listB.maxCol(); count++) {
			addMult = 0;
			for (int j = 1; j <= maxCol(); j++) {
				searchA = binSearch(i, j);
				if (searchA != -1)
					valA = getValue(searchA);
				else
					continue;
				searchB = listB.binSearch(j, count);
				if (searchB != -1) {
					valB = listB.getValue(searchB);
					addMult += (valA * valB);
				}
				else
					continue;
			}
			if (addMult != 0) {
				listC.fill(n, i, count, addMult);
				n++;
			}
			else if (i == actualMaxRow && count == actualMaxCol) {
				listC.fill(n, i, count, addMult);
				n++;
			}
		}
	}
}


