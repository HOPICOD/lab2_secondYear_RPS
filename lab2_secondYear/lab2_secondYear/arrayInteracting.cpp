#include <iostream>
#include <vector>
#include "input.h"
#include "workWithFiles.h"

using namespace std;
enum SaveMenu { Yes = 1, No = 2 };

// ������� ��� ������ ���� "������������� �����" (�������� -0.0) �� ������� 0.0 � �������
void replaceNegativeZero(vector<double>& array) {
	for (int i = 0; i < array.size(); i++) {
		double val = 0.0;
		if (array[i] == 0.0) {
			array[i] = val;
		}
	}
}

// ������� ��� �������� ������� �� ������ ����������������� �����
vector<double> setArrayByUserInput() {
	int arraySize = inputInt("������� ������ �������:", 0, INT_MAX);
	vector<double> array;

	for (int i = 0; i < arraySize; i++) {
		cout << "������� " << i + 1 << " ������� �������: ";
		array.push_back(inputDouble("", -DBL_MAX, DBL_MAX));
	}
	replaceNegativeZero(array);
	return array;
}

// ������� ��� ������ ������� �� �����
void printArray(vector<double>& array, size_t size, string message) {
	if (array.empty()) { return; }
	cout << message << endl << endl;
	cout << "[ ";
	for (int i = 0; i < size; i++) {
		cout << array[i];
		if (i != size - 1) {
			cout << ", ";
		}
	}
	cout << "]";
	cout << endl;
	cout << endl;
}

// ������� ��� �������� ������ �� ����� � ������
void loadDataFromFile(vector<double>& array) {
	string filepath = getValidFilepath(); // ����������� ���� � ����� � ������������

	vector<double> arrayFromFile = loadArrayFromFile(filepath); // ��������� ������ �� �����

	if (arrayFromFile.empty()) { cerr << "������ ������ �� �����" << endl; } // �������� �� ������ ������
	else {
		array = arrayFromFile; // ����������� ����������� ������ �������
	}
}

// ������� ��� ������� � ������������ � ������������� ���������� �������
void isNeedToSaveArrays(vector<double>& array, vector<double>& arrayForInsertionSort) {
	int userChoice = 0;
	userChoice = inputInt("������ �� ��������� �������? \n[1]��\n[2]���", 0, 3);
	switch (userChoice) {
	case(Yes): {
		saveArraysWithResultsToFile(array, arrayForInsertionSort);
	}
	case(No): {
		break;
	}
	}
}

