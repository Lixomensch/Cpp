#include <iostream>
using namespace std;

void merge(int array[], int left, int mid, int  right){

	int  n1 = mid - left + 1;
	int  n2 = right - mid;

	int* leftArray = new int[n1],* rightArray = new int[n2];

	for (auto i = 0; i < n1; i++)leftArray[i] = array[left + i];
	for (auto j = 0; j < n2; j++)rightArray[j] = array[mid + 1 + j];

	auto arrAux1 = 0, arrAux2 = 0;

	while (arrAux1 < n1 && arrAux2 < n2) {
		if (leftArray[arrAux1] <= rightArray[arrAux2]) {
			array[left] = leftArray[arrAux1];
			arrAux1++;
		}
		else {
			array[left] = rightArray[arrAux2];
			arrAux2++;
		}
		left++;
	}

	while (arrAux1 < n1) {
		array[left] = leftArray[arrAux1];
		arrAux1++;
		left++;
	}

	while (arrAux2 < n2) {
		array[left] = rightArray[arrAux2];
		arrAux2++;
		left++;
	}
	delete[] leftArray;
	delete[] rightArray;
}

void mergeSort(int array[], int  left, int  rigth){
	if (left >= rigth)return;

	int mid = left + (rigth - left) / 2;
	mergeSort(array, left, mid);
	mergeSort(array, mid + 1, rigth);
	merge(array, left, mid, rigth);
}

