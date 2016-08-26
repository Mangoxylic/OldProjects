#ifndef MSORT_H
#define MSORT_H

#include <vector>
#include <iostream>


template <class T, class Comparator>

void mergeSort (std::vector<T>& myArray, Comparator comp) {
	msort(myArray, 0, myArray.size() - 1, comp);
}

template <class T, class Comparator>

void msort(std::vector<T>& myArray, int start, int end, Comparator comp) {
	if (start >= end) return;

	int mid = (start + end) / 2;

	/*
	std::cout <<"1st msort call:" << std::endl;
	std::cout << "start:" << start << std::endl;
	std::cout << "mid:" << mid << std::endl;
	std::cout << "end:" << end << std::endl << std::endl;
	*/

	msort(myArray, start, mid, comp);

	/*
	std::cout <<"2nd msort call:" << std::endl;
	std::cout << "start:" << start << std::endl;
	std::cout << "mid:" << mid << std::endl;
	std::cout << "end:" << end << std::endl << std::endl;
	*/

	msort(myArray, mid + 1, end, comp);

	/*
	std::cout <<"Calling merge with these values:" << std::endl;
	std::cout << "start:" << start << std::endl;
	std::cout << "mid:" << mid << std::endl;
	std::cout << "end:" << end << std::endl << std::endl;
	*/

	merge(myArray, start, mid, end, comp);
}

template <class T, class Comparator>

void merge(std::vector<T>& myArray, int start, int mid, int end, Comparator comp) {
	std::vector<T> temp;
	int i = start;
	int j = mid + 1;

	while (i <= mid || j <= end) {
		if (i <= mid && (j > end || comp(myArray[i], myArray[j]))) {
			temp.push_back(myArray[i]);
			// std::cout << "if:Added " << myArray[i] << " to the back of temp" << std::endl;
			i++;
		} else {
			temp.push_back(myArray[j]);
			// std::cout << "else:Added " << myArray[j] << " to the back of temp" << std::endl;
			j++;
		}
	}

	for (unsigned int k = 0; k < temp.size(); k++) {
		myArray[k + start] = temp[k];
	}

	/*
	for (unsigned int n = 0; n < myArray.size(); n++) {
		std::cout << myArray[n] << " ";
	}
	std::cout << std::endl;
	*/

}

#endif