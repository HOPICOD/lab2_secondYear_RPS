#include <iostream>
using namespace std;


// Функция для ввода целого числа с проверкой на корректность ввода и диапазон значений
int inputInt(string message, int min, int max) {
	int user_input;
	cout << message << endl;
	cin >> user_input;
	while (cin.fail() || user_input <= min || user_input >= max) { // Проверка на ошибку ввода или выход за пределы диапазона
		cin.clear(); // Сбрасываем флаг ошибки
		cin.ignore(INT_MAX, '\n'); // Очищаем буфер ввода
		cout << "Неверный ввод!" << endl;
		cin >> user_input;
	}
	cin.clear();// Сбрасываем флаг ошибки
	cin.ignore(INT_MAX, '\n'); // Очищаем буфер ввода
	return user_input;
}

// Функция для ввода числа с плавающей точкой с проверкой на корректность ввода и диапазон значений
double inputDouble(string message, double min, double max) {
	double user_input;
	cout << message << endl;
	cin >> user_input;
	while (cin.fail() || user_input < min || user_input > max) { // Проверка на ошибку ввода или выход за пределы диапазона
		cin.clear(); // Сбрасываем флаг ошибки
		cin.ignore(INT_MAX, '\n'); // Очищаем буфер ввода
		cout << "Неверный ввод!" << endl;
		cin >> user_input;
	}
	cin.clear();// Сбрасываем флаг ошибки
	cin.ignore(INT_MAX, '\n'); // Очищаем буфер ввода
	return user_input;
}