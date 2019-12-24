#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include <iostream>
#include <sstream>
#include <string>
#include "qsinterface.h"

using namespace std;

template<typename T>
class Quicksort : public QSInterface<T>
{
public:
	T* table;
	int num_elements;
	int array_capacity;
	int swaps;
	int compares;

	Quicksort(int capacity = 0) {
		if (capacity != 0) {
			table = new T[capacity];
			array_capacity = capacity;
		}
		else {
			table = NULL;
			array_capacity = capacity;
		}
		num_elements = 0;
		swaps = 0;
		compares = 0;
	}

	~Quicksort() {
	}

	/** Dynamically allocate an initial array to the QuickSort class. */
	bool createArray(size_t capacity) {
		table = new T[capacity];
		array_capacity = capacity;
		return true;
	}

	/** Add an element to the QuickSort array. Dynamically grow array as needed. */
	bool addElement(T element) {
		if (num_elements < array_capacity) {
			table[num_elements] = element;
			num_elements++;
		}
		else {
			T* temp = new T[array_capacity * 2];
			for (int i = 0; i < num_elements; i++) {
				temp[i] = table[i];
			}
			delete [] table;
			table = temp;
			table[num_elements] = element;
			num_elements++;
			array_capacity *= 2;
		}

		return true;
	}

	/** Sort the elements of a QuickSort subarray using median and partition functions. */
	bool sort(size_t left, size_t right) {
		int pivot = medianOfThree(left, right);
		if (pivot == -1) {
			return false;
		}
		int middle = partition(left, right, pivot);
		if (middle == -1) {
			return false;
		}
		bool lower = sort(left, middle);
		bool upper = sort(middle + 1, right);

		return true;
	}

	/** Sort all elements of the QuickSort array using median and partition functions. */
	bool sortAll() {
		int pivot = medianOfThree(0, num_elements);
		if (pivot == -1) {
			return false;
		}
		int middle = partition(0, num_elements, pivot);
		if (middle == -1) {
			return false;
		}
		
		bool lower = sort(0, middle);
		bool upper = sort(middle + 1, num_elements);

		return true;
		
			
	}

	/** Removes all items from the QuickSort array. */
	bool clear() {
		num_elements = 0;
		delete [] table;
		table = new T[array_capacity];
		return true;
	}

	/** Return size of the QuickSort array. */
	size_t capacity() const {
		return array_capacity;
	}

	/** Return number of elements in the QuickSort array. */
	size_t size() const {
		return num_elements;
	}

	void deleteTable() {
		delete[] table;
	}

	/** The median of three pivot selection has two parts:
	1) Calculates the middle index by averaging the given left and right indices:
	middle = (left + right)/2
	2) Then bubble-sorts the values at the left, middle, and right indices.

	After this method is called, data[left] <= data[middle] <= data[right].

	@param left - the left boundary for the subarray from which to find a pivot
	@param right - the right + 1 boundary for the subarray from which to find a pivot
	@return the index of the pivot (middle index).
	Return -1 if	1) the array is empty,
	2) if either of the given integers is out of bounds,
	3) or if the left index is not less than the right index.
	*/
	int medianOfThree(size_t left, size_t right) {
		//check for illegal input
		if (!(left < right) || right > num_elements || left < 0 || num_elements == 0) {
			return -1;
		}
		size_t middle = (left + right) / 2;

		right--;

		int num_swap;
		int temp;
		while (true) {
			num_swap = 0;
			if (table[left] > table[middle]) {
				temp = table[middle];
				table[middle] = table[left]; 
				table[left] = temp;
				swaps++;
				num_swap++;
			}
			if (table[middle] > table[right]) {
				temp = table[right];
				table[right] = table[middle];
				table[middle] = temp;
				swaps++;
				num_swap++;
			}
			if (num_swap == 0) {
				break;
			}
		}
		compares += 3;
		return middle;
	}

	/** Partitions a subarray around a pivot value selected according
	to median-of-three pivot selection. Because there are multiple ways
	to partition a list, follow the algorithm on page 611.

	The values which are smaller than the pivot should be placed to the left of the pivot;
	the values which are larger than the pivot should be placed to the right of the pivot.

	@param left - left index for the subarray to partition.
	@param right - right index + 1 for the subarray to partition.
	@param pivotIndex - index of the pivot in the subarray.
	@return the pivot's ending index after the partition completes:
	Return -1 if	1) the array is empty,
					2) if any of the given indexes are out of bounds,
					3) if the left index is not less than the right index.
	*/
	int partition(size_t left, size_t right, size_t pivotIndex) {
		if (!(left < right) || right > num_elements || left < 0 || num_elements == 0 || pivotIndex > right || pivotIndex < left) {
			return -1;
		}

		int pivot = table[pivotIndex];
		table[pivotIndex] = table[left];
		table[left] = pivot;
		swaps++;

		int rightIndex = right - 1;
		int leftIndex = left + 1;
		int temp;
		bool crossed = false;

		while (!crossed) {
			compares++;
			if (rightIndex < leftIndex) {
				crossed = true;
			}
			else if (table[rightIndex] <= pivot && table[leftIndex] > pivot) {
				temp = table[rightIndex];
				table[rightIndex] = table[leftIndex];
				table[leftIndex] = temp;
				swaps++;

			}
			else {
				if (table[rightIndex] > pivot) { rightIndex--; }
				if (table[leftIndex] <= pivot) { leftIndex++; }
			}
		}
		temp = table[rightIndex];
		table[rightIndex] = pivot;
		table[left] = temp;
		swaps++;

		return rightIndex;
	}

	string getStats() const {
		ostringstream out;
		out << to_string(compares) << "," << to_string(swaps);
		return out.str();
	}

	void resetStats() {
		compares = 0;
		swaps = 0;
	}

	/** @return: comma delimited string representation of the array. */
	string toString() const {
		ostringstream out;
		if (num_elements > 0) {
			for (int i = 0; i < num_elements - 1; i++) {
				out << to_string(table[i]) << ",";
			}
			out << to_string(table[num_elements - 1]);
		}
		else {
			return "Empty";
		}
		return out.str();
	}

	friend std::ostream& operator<< (ostream& os, const Quicksort& Quicksort)
	{
		os << Quicksort.toString();
		return os;
	}
};

#endif