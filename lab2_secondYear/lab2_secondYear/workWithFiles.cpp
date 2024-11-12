#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include "input.h"
#include "arrayInteracting.h"

using namespace std;

// ������� ��� �������� ������������� ����� �� ��������� �����
bool fileExists(string filename) {
	ifstream file(filename); // ��������� ����
	return file.is_open(); // ���������� true, ���� ���� ������, ����� false
}

// ������� ��� ������������� ���������� ������������� �����
bool confirmOverwrite(string filename) {

	const int YES = 1;

	cout << "���� '" << filename << "' ��� ����������." << endl;
	cout << "������� �� �� ��� ������������?" << endl;
	cout << "[1] - ��" << endl;
	cout << "[2] - ���" << endl;

	int userChoice = 0;

	userChoice = inputInt("������� ����� ����:", 0, 3);

	if (userChoice == YES) { return true; }

	return false;

}

// ������� ��� �������� ������������ ���� � �����
bool isFilepathValid(string filepath) {

	regex filePathRegex("^(?:[a-zA-Z]\\:|\\\\)\\\\([^\\\\]+\\\\)*[^\\/:*?\"<>|]+\\.txt$"); // ���������� ��������� ��� �������� ����

	if (!regex_match(filepath, filePathRegex)) { // ���� ���� �� ������������� �������
		cerr << "������: �������� ���� �����!" << endl;
		return false;
	}

	return true;
}

// ������� ��� �������� ������������ ����� �����
bool isFilenameValid(string filename) {
	regex filenameRegex("^[^\\/:*?\"<>|]+\\.txt$"); // ������ ��� �������� ���������� .txt

	regex filenameReservedNames("^(?:CON|PRN|AUX|NUL|COM[1-9]|LPT[1-9]|con|prn|aux|nul|com[1-9]|lpt[1-9])(?:\\..*)?$");// ����������������� �����

	regex filenameReservedChars("[\\/:*?\"<>|]"); // ����������� �������

	// �������� �� ������������ ����� �����
	if (!regex_match(filename, filenameRegex)) {
		cerr << "������: ������������ ��� �����!" << endl;
		return false;
	}

	if (regex_match(filename, filenameReservedNames)) {
		cerr << "������: ������������ ��� �����!" << endl;
		return false;
	}

	if (regex_search(filename, filenameReservedChars)) {
		cerr << "������: ������������ ��� �����!" << endl;
		return false;
	}

	return true;
}

// ������� ��� ��������� ����������� ���� � ����� �� ������������
string getValidFilepath() {
	bool isPathValid = false;
	bool isNameValid = false;

	string filepath{ "" };

	while (!isPathValid || !isNameValid) {
		cout << "������� ������ ���� ����� � ��� ��������� (�������� ������ ������ .txt): " << endl;
		getline(cin, filepath); // ������ ���� � �����
		size_t pos = filepath.find_last_of("\\"); // ������� ��������� ���� ������� '\'

		// ���� ������� ������ ��� ����� (��� ������������ ����)
		// ���������, �������� �� ��� ����������
		if (pos > sizeof(filepath)) { // �������� ������������ ����� �����

			if (isFilenameValid(filepath)) {

				isPathValid = true;
				isNameValid = true;

			}
		}
		// ���� ������ ������ ���� � ������ �����
		// ���������, �������� �� ��� ����������
		if (pos != string::npos) {
			string filename = filepath.substr(pos + 1); // ��������� ��� ����� ����� ���������� '\'
			string path = filepath.substr(0, pos + 1); // ��������� ���� � ����� �� ���������� '\'

			if (isFilepathValid(path + filename) && isFilenameValid(filename)) {
				isPathValid = true;
				isNameValid = true;
			}

		}
	}

	return filepath;
}

// ������� ��� ������������� ���������� ������������� �����
string getOverwriteConfirmation(string& fullPath) {
	if (fileExists(fullPath)) { // �������� ������������� �����
		if (!confirmOverwrite(fullPath)) { // ���� ������������ �� ���������� ����������
			cout << "����������, �������� ������ ����." << endl;
			fullPath = getValidFilepath(); // ����������� ����� ����
			return getOverwriteConfirmation(fullPath); // ���������� ����������� ������� ��� �������������
		}
	}
	return fullPath; // ���������� ���������� ����
}

// ������� ��� �������� ����� �� ����� � ������
vector<double> loadArrayFromFile(string filename) {

	vector<double> array;

	ifstream file(filename); // ��������� ���� ��� ������
	if (!file.is_open()) { // ��������, ������� �� ������� ����
		cerr << "���������� ������� ���� " << filename << endl;
		return array;
	}

	string line;
	while (getline(file, line)) { // ������ ������ �� �����
		double num;
		istringstream iss(line); // ������� ����� ��� ������ ������
		bool validLine = true;
		bool anyNumber = false;
		while (iss >> num) { // ������ ����� �� ������
			anyNumber = true;
			if (!anyNumber) { // �������� �� ���������� �����
				validLine = false;
			}
			if (validLine) { // ��������� ����� � ������, ���� ������ ���������
				array.push_back(num);
			}
			/*else {
				cerr << "�������� ������ � ������:\"" << line << "\"" << endl;
			}*/
			file.close(); // ��������� ���� ����� ���������� ������
		}
		replaceNegativeZero(array); // ������ ������������� ����� � �������
		return array;
	}
}

// ������� ��� ���������� �������� � ������������ � ����
void saveArraysWithResultsToFile(vector<double>& array, vector<double>& arrayForInsertionSort) {
	string fullPath = getValidFilepath(); // �������� ���������� ���� � �����
	fullPath = getOverwriteConfirmation(fullPath); // ��������� ����������, ���� ���� ����������

	ofstream file(fullPath); // ��������� ���� ��� ������
	if (!file) { // �������� �� �������� �������� �����
		cerr << "������: ���� ��������� � ������:" << "'������ ��� ������' " << "��� ��������� ������ ������!" << endl;
		file.close();

		while (true) { // ��������� ������ ����, ���� �� ������� ������� ����
			cout << "����������, ������� ����� ����." << endl;
			fullPath = getValidFilepath();
			fullPath = getOverwriteConfirmation(fullPath);

			file.open(fullPath);
			if (file) { // ���� ���� ������, ������� �� �����
				break;
			}
			else {
				cerr << "������: ���� ��������� � ������:" << "'������ ��� ������' " << "��� ��������� ������ ������!" << endl;
				file.close();
			}
		}
	}
	// ���������� ������������ ������ � ����
	file << "������������ ������:" << endl;
		for (size_t i = 0; i < array.size(); ++i) {
			file << array[i];
			if (i < array.size() - 1) {
				file << " "; // ���������� ��������� � ������ ��������
			}
		}
	file << endl << endl;

	// ���������� ��������������� ������ � ����
	file << "������ ��������������� ������� �������:" << endl;
	for (size_t i = 0; i < arrayForInsertionSort.size(); ++i) {
		file << arrayForInsertionSort[i];
		if (i < arrayForInsertionSort.size() - 1) {
			file << " "; // ���������� ��������� � ������ ��������
		}
	}
	file << endl << endl;
}