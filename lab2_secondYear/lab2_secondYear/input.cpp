#include <iostream>
using namespace std;


// ������� ��� ����� ������ ����� � ��������� �� ������������ ����� � �������� ��������
int inputInt(string message, int min, int max) {
	int user_input;
	cout << message << endl;
	cin >> user_input;
	while (cin.fail() || user_input <= min || user_input >= max) { // �������� �� ������ ����� ��� ����� �� ������� ���������
		cin.clear(); // ���������� ���� ������
		cin.ignore(INT_MAX, '\n'); // ������� ����� �����
		cout << "�������� ����!" << endl;
		cin >> user_input;
	}
	cin.clear();// ���������� ���� ������
	cin.ignore(INT_MAX, '\n'); // ������� ����� �����
	return user_input;
}

// ������� ��� ����� ����� � ��������� ������ � ��������� �� ������������ ����� � �������� ��������
double inputDouble(string message, double min, double max) {
	double user_input;
	cout << message << endl;
	cin >> user_input;
	while (cin.fail() || user_input < min || user_input > max) { // �������� �� ������ ����� ��� ����� �� ������� ���������
		cin.clear(); // ���������� ���� ������
		cin.ignore(INT_MAX, '\n'); // ������� ����� �����
		cout << "�������� ����!" << endl;
		cin >> user_input;
	}
	cin.clear();// ���������� ���� ������
	cin.ignore(INT_MAX, '\n'); // ������� ����� �����
	return user_input;
}