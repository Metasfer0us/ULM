#pragma once

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>
#include <list>
#include <windows.h> // Бібліотеки 

#undef max



// Виставлення кодування 1251 для корректного відображення української мови
void ua() {
	SetConsoleOutputCP(1251);
}


std::string wrong_arg_text = "Невірні дані. Спробуйте ще раз.\n";

// Вивід помилки вводу
void wrong_arg() {
	std::cout << wrong_arg_text;
}

int digitInput()
{
  char digit;
  std::cin >> digit;
  std::cin.clear();
  std::cin.ignore(1);
  return atoi(&digit);
}

void digitInput(int& var)
{
  char digit;
  std::cin >> digit;
  std::cin.clear();
  std::cin.ignore(1);
  var = atoi(&digit);
}

// Очистка буферу
void flush() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

// Вивід запиту для задання змінної у діапазоні від заданного числа з виводом порогу
template <typename inType>
void input(std::string msg, inType from, inType &var) {
	bool check = true;
	while (check) {
		std::cout << msg << " (Від " << from << ") : ";
		std::cin >> var;
		flush();
		if (var < from) {
			wrong_arg();
		}
		else {
			check = 0;
		}
	}
}

// Вивід запиту для задання змінної у діапазоні від/до заданного числа з виводом порогів
template <typename inType>
void input(std::string msg, inType from, inType to, inType &var) {
	bool check = true;
	while (check) {
		std::cout << msg << " (Від " << from << " до " << to << ") : ";
		std::cin >> var;
		flush();
		if (var < from || var > to) {
			wrong_arg();
		}
		else {
			check = 0;
		}
	}
}

// Вивід запиту для задання змінної у діапазоні від/до заданного числа з заданням повідомлень про помилку вводу
template <typename inType>
void input(std::string msg, std::string too_low, std::string too_high, inType from, inType to, inType &var) {
	bool check = true;
	while (check) {
		std::cout << msg << " : ";
		std::cin >> var;
		flush();
		if (var < from || var > to) {
			if (var < from) {
				std::cout << too_low << "\n";
			}
			else {
				std::cout << too_high << "\n";
			}
		}
		else {
			check = 0;
		}
	}
}

// Вивід запиту для задання змінної у діапазоні від/до заданного числа з заданням повідомленя про помилку вводу
template <typename inType>
void input(std::string msg, std::string not_in_range, inType from, inType to, inType &var) {
	bool check = true;
	while (check) {
		std::cout << msg << " : ";
		std::cin >> var;
		flush();
		if (var < from || var > to) {
			std::cout << not_in_range << "\n";
		}
		else {
			check = 0;
		}
	}
}

// Вивід запиту для задання змінної
template <typename inType>
void input(std::string msg, inType &var) {
	std::cout << msg << " : ";
	std::cin >> var;
	flush();
}



// Функція генерації числа від 0 до заданого
template <typename genType>
void generate(int rand_to, genType *var) {
	*var = (genType)(rand() % ++rand_to);
}

// Функція заповнення одновимірного масиву числами від 0 до заданого
template <typename genType>
void generate(int x1_size, int rand_to, genType *arr) {
	for (genType *ptEnd = &arr[x1_size]; arr < ptEnd; arr++) {
		generate(rand_to, arr);
	}
}

// Функція заповнення двовимірного масиву числами від 0 до заданого
template <typename genType>
void generate(int x1_size, int x2_size, int rand_to, genType **arr) {
	for (genType **ptEnd = &arr[x2_size]; arr < ptEnd; arr++) {
		generate(x1_size, rand_to, arr);
	}
}

// Функція заповнення двовимірного масиву числами від 0 до заданого в декілька потоків
template <typename genType>
void generate(int x1_size, int x2_size, int threads, int rand_to, genType **arr) {
	// Директива паралельної обробки циклу OpenMP
#pragma omp parallel for num_threads(threads)
	for (int i = 0; i < x2_size; i++) {
		srand((int)time(NULL) ^ i);
		generate(x1_size, rand_to, *(arr + i));
	}
}



// Функція виводу одновимірного масиву
template <typename outType>
void output(outType *arr, int x1_size) {
	std::cout << std::setprecision(3);
	for (outType *ptEnd = arr + x1_size; arr < ptEnd; arr++) {
		std::cout << std::setw(7) << std::fixed << std::setfill(' ');
		std::cout << " " << *arr;
	}
}

// Функція виводу одновимірного масиву у вигляді двовимірного
template <typename outType>
void output(outType *arr, int x1_size, int x2_size) {
	for (outType *ptEnd = arr + x1_size*x2_size; arr < ptEnd; arr += x2_size) {
		std::cout << "\n\t";
		out(x1_size, arr);
	}
}

// Фунція виводу двовимірного массиву
template <typename outType>
void output(outType **arr, int x1_size, int x2_size) {
	std::cout << std::setprecision(3);
	for (int line = 0; line < x2_size; line++) {
		std::cout << "\t";
		for (int column = 0; column < x1_size; column++) {
			std::cout << std::setw(7) << std::fixed << std::setfill(' ');
			std::cout << arr[line][column];
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

// Вивід цілого числа з вставкою символа на кожний третій порядок
// out_with_spaces(1234567, '.') >> 1.234.567
void output(long long number, char symbol) {
	int digits = 0, *tempArray;
	long long int tempVar = (long long int)number;

	// Рахування кількості цифр числа
	for (digits = 0; tempVar; digits++, tempVar /= 10) {}

	// Виділення масиву необхідного розміру
	tempArray = new int[digits];

	// Заповнення масиву
	while (number) {
		tempArray[tempVar++] = number % 10;
		number /= 10;
	}

	// Вивід
	while (tempVar) {
		std::cout << tempArray[--tempVar];
		if (!(tempVar % 3) && tempVar) {
			std::cout << symbol;
		}
	}

	// Видалення масиву
	delete[] tempArray;
}

// Вивід цілого числа з вставкою пробілів на кожний третій порядок
// out_with_spaces(1234567) >> 1 234 567
void output(long long number) {
	void(*ptMyFunc)(long long number, char symbol);
	ptMyFunc = output;
	ptMyFunc(number, ' ');
}



// Фунція обміну двох змінних
template <typename T>
void swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

// Функція обміну
template <typename T>
void swap(T* a, T* b, int size) {
	T* temp = new T[size];
	size *= sizeof(T);
	memcpy(a, b, size);
	memcpy(b, temp, size);
}

// Циклічний зсув елементів масиву
template <typename T>
void shift(T* shiftedArray, int size, int shift) {
	// Чи значення зсуву є додатним
	bool shiftIsPositive = shift < 0 ? 0 : 1;
	// Отримуємо модуль зсуву
	if (shiftIsPositive == false) {
		shift = -shift;
	}
	// Отримуємо фактичне значення зсуву
	if (shift >= size) {
		shift = shift % size;
	}
	// Зсув
	if (shift != 0) {
		// Оптимізація при фактичному зсуві більше ніж на половину розміру масиву
		bool optimize = shift < size >> 1;

		// Розмір тимчасового масиву
		int tempSize = optimize ? shift : size - shift;

		// Різниця розмірів зсовуваного та тимчасового масивів
		int diffSize = size - tempSize;

		// Тимчасовий масив
		T* temp = new T[tempSize];

		// Розмір типу данних у байтах
		int sizeOfT = sizeof(T);

		// Переставляємо частини масиву
		int one = shiftIsPositive ? 1 : 0;
		one += optimize ? 1 : 0;
		int two = (one > 0) && (one < 2);
		if (two)
			// При додатньому зсувові , меншому                ніж половина розміру зсовуваного масиву
			// Або від'ємному зсувові , більшому , по модулю , ніж половина розміру зсовуваного масиву
		{
			// Копіювання меншої частини в тимчасовий масив
			memcpy(temp, shiftedArray, sizeOfT * tempSize);
			// Копіювання більшої частини на нове місце
			memcpy(shiftedArray, shiftedArray + tempSize, sizeOfT * diffSize);
			// Копіювання меншої частини на нове місце
			memcpy(shiftedArray + diffSize, temp, sizeOfT * tempSize);
		}
		else
			// При додатньому зсувові , більшому              ніж половина розміру зсовуваного масиву
			// Або від'ємному зсувові , меншому , по модулю , ніж половина розміру зсовуваного масиву
		{
			// Копіювання меншої частини в тимчасовий масив
			memcpy(temp, shiftedArray + diffSize, sizeOfT * tempSize);
			// Копіювання більшої частини на нове місце
			memcpy(shiftedArray + tempSize, shiftedArray, sizeOfT * diffSize);
			// Копіювання меншої частини на нове місце
			memcpy(shiftedArray, temp, sizeOfT * tempSize);
		}

		// Видалення тимчасового масиву
		delete[] temp;
	}
}

// Видалення елементу масиву
template <typename T>
void delete_element(T* &oldArray, int &size, int index) {
	// Новий масив
	T* newArray = new T[size - 1];
	// Копіювання елементів до видалюваного елемента
	memcpy(newArray, oldArray, sizeof(T) * (index));
	// Копіювання елементів після видалюваного елемента
	memcpy(newArray + index, oldArray + index + 1, sizeof(T) * (size - index));
	// Видалення старого масиву
	delete[] oldArray;
	// Перепризначення вказівника на масив
	oldArray = newArray;
	// Зменшення розміру масиву
	size--;
}

template <typename T>
void combinate(T* combinatedArray, int size, int step, void(*processing)(T* processedArray, int size)) {
	T* combinated = new T[size];
	memcpy(combinated, combinatedArray, sizeof(T) * size);
	if (step == size - 1) {
		processing(combinated, size);
	}
	else {
		for (int i = step; i < size; i++) {
			shift(combinated + step, size - step, 1);
			combinate(combinated, size, step + 1, processing);
		}
	}
}

// Виконання функції над усіма можливими перестановками масиву
template <typename T>
void combinate(T* combinatedArray, int size, void(*processing)(T* processedArray, int size)) {
	combinate(combinatedArray, size, 0, processing);
}