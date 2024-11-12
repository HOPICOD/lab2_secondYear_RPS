#pragma once
#include <iostream>
#include <vector>
#include "input.h"
#include "workWithFiles.h"

using namespace std;
enum typeOfSortArrayMenu{ increaseSort = 1, decreaseSort = 2};


class InsertionSort {

public:
	InsertionSort() {}

	// ������� ������ ���� ���������� �������
	void typeOfSortArray(vector<double>& arrayForInsertionSort) {
		int userChoice = 0;
		userChoice = inputInt("�������� ������� ����������: \n[1]�� �������� � ��������\n[2]�� �������� � ��������", 0, 3);
		switch (userChoice) {
		case(increaseSort): {
			insertionSortIncrease(arrayForInsertionSort);
			break;
		}
		case(decreaseSort): {
			insertionSortDecrease(arrayForInsertionSort);
			break;
		}
		default: {
			cout << "�������� ����!" << endl;
			break;
		}
		}
	}



private:

	// ������� ���������� ��������� �� �����������
	void insertionSortIncrease(vector<double>& arrayForInsertionSort) {
		for (int i = 1; i < arrayForInsertionSort.size(); i++) { // �������� �� ���� ��������� �������, ������� � 1-��
			for (int j = i; j > 0; j--) { // ��������� ������� ������� �� ������ ����� � ��������������� ����� �������
				if (arrayForInsertionSort[j-1] <= arrayForInsertionSort[j]) { // ���� ������� �� ������ �������, ������� �� �����
					break; 
				}
				swap(arrayForInsertionSort[j-1], arrayForInsertionSort[j]); // ����� ������ �������� ������� �������
			}

		}
	}

	// ������� ���������� ��������� �� ��������
	void insertionSortDecrease(vector<double>& arrayForInsertionSort) { 
		for (int i = 1; i < arrayForInsertionSort.size(); i++) { // �������� �� ���� ��������� �������, ������� � 1-��
			for (int j = i; j > 0; j--) { // ��������� ������� ������� �� ������ ����� � ��������������� ����� �������
				if (arrayForInsertionSort[j - 1] >= arrayForInsertionSort[j]) { // ���� ������� �� ������ �������, ������� �� �����
					break;
				}
				swap(arrayForInsertionSort[j - 1], arrayForInsertionSort[j]); // ����� ������ �������� ������� �������
			}

		}
	}
};