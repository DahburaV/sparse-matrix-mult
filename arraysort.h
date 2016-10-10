#pragma once
#include "array.h"

bool ArrayList::checkIfSorted() {
	bool sorted = true;
	for (int i = 0; i < listSize() - 1; i++) {
		if (list[i].row > list[i + 1].row) {
			sorted = false;
			break;
		}
		else if (list[i].row == list[i + 1].row && list[i].col > list[i + 1].col) {
			sorted = false;
			break;
		}
		else
			sorted = true;
	}
	return sorted;
}

void ArrayList::sort() {			//BUBBLE SORT
	bool swap;
	Entry temp;
	do {
		swap = false;
		for (int i = 0; i < listSize() - 1; i++) {
			if (list[i].row > list[i + 1].row) {
				temp = list[i];
				list[i] = list[i + 1];
				list[i + 1] = temp;
				swap = true;
			}
			else if (list[i].row == list[i + 1].row && list[i].col > list[i + 1].col) {
				temp = list[i];
				list[i] = list[i + 1];
				list[i + 1] = temp;
				swap = true;
			}
		}
	} while (swap);
}		



