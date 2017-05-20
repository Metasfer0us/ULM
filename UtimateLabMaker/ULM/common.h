#pragma once

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>
#include <list>
#include <windows.h> // ��������� 

#undef max



// ����������� ��������� 1251 ��� ����������� ����������� ��������� ����
void ua() {
	SetConsoleOutputCP(1251);
}


std::string wrong_arg_text = "����� ���. ��������� �� ���.\n";

// ���� ������� �����
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

// ������� ������
void flush() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

// ���� ������ ��� ������� ����� � ������� �� ��������� ����� � ������� ������
template <typename inType>
void input(std::string msg, inType from, inType &var) {
	bool check = true;
	while (check) {
		std::cout << msg << " (³� " << from << ") : ";
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

// ���� ������ ��� ������� ����� � ������� ��/�� ��������� ����� � ������� ������
template <typename inType>
void input(std::string msg, inType from, inType to, inType &var) {
	bool check = true;
	while (check) {
		std::cout << msg << " (³� " << from << " �� " << to << ") : ";
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

// ���� ������ ��� ������� ����� � ������� ��/�� ��������� ����� � �������� ���������� ��� ������� �����
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

// ���� ������ ��� ������� ����� � ������� ��/�� ��������� ����� � �������� ���������� ��� ������� �����
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

// ���� ������ ��� ������� �����
template <typename inType>
void input(std::string msg, inType &var) {
	std::cout << msg << " : ";
	std::cin >> var;
	flush();
}



// ������� ��������� ����� �� 0 �� ��������
template <typename genType>
void generate(int rand_to, genType *var) {
	*var = (genType)(rand() % ++rand_to);
}

// ������� ���������� ������������ ������ ������� �� 0 �� ��������
template <typename genType>
void generate(int x1_size, int rand_to, genType *arr) {
	for (genType *ptEnd = &arr[x1_size]; arr < ptEnd; arr++) {
		generate(rand_to, arr);
	}
}

// ������� ���������� ����������� ������ ������� �� 0 �� ��������
template <typename genType>
void generate(int x1_size, int x2_size, int rand_to, genType **arr) {
	for (genType **ptEnd = &arr[x2_size]; arr < ptEnd; arr++) {
		generate(x1_size, rand_to, arr);
	}
}

// ������� ���������� ����������� ������ ������� �� 0 �� �������� � ������� ������
template <typename genType>
void generate(int x1_size, int x2_size, int threads, int rand_to, genType **arr) {
	// ��������� ���������� ������� ����� OpenMP
#pragma omp parallel for num_threads(threads)
	for (int i = 0; i < x2_size; i++) {
		srand((int)time(NULL) ^ i);
		generate(x1_size, rand_to, *(arr + i));
	}
}



// ������� ������ ������������ ������
template <typename outType>
void output(outType *arr, int x1_size) {
	std::cout << std::setprecision(3);
	for (outType *ptEnd = arr + x1_size; arr < ptEnd; arr++) {
		std::cout << std::setw(7) << std::fixed << std::setfill(' ');
		std::cout << " " << *arr;
	}
}

// ������� ������ ������������ ������ � ������ �����������
template <typename outType>
void output(outType *arr, int x1_size, int x2_size) {
	for (outType *ptEnd = arr + x1_size*x2_size; arr < ptEnd; arr += x2_size) {
		std::cout << "\n\t";
		out(x1_size, arr);
	}
}

// ������ ������ ����������� �������
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

// ���� ������ ����� � �������� ������� �� ������ ����� �������
// out_with_spaces(1234567, '.') >> 1.234.567
void output(long long number, char symbol) {
	int digits = 0, *tempArray;
	long long int tempVar = (long long int)number;

	// ��������� ������� ���� �����
	for (digits = 0; tempVar; digits++, tempVar /= 10) {}

	// �������� ������ ����������� ������
	tempArray = new int[digits];

	// ���������� ������
	while (number) {
		tempArray[tempVar++] = number % 10;
		number /= 10;
	}

	// ����
	while (tempVar) {
		std::cout << tempArray[--tempVar];
		if (!(tempVar % 3) && tempVar) {
			std::cout << symbol;
		}
	}

	// ��������� ������
	delete[] tempArray;
}

// ���� ������ ����� � �������� ������ �� ������ ����� �������
// out_with_spaces(1234567) >> 1 234 567
void output(long long number) {
	void(*ptMyFunc)(long long number, char symbol);
	ptMyFunc = output;
	ptMyFunc(number, ' ');
}



// ������ ����� ���� ������
template <typename T>
void swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

// ������� �����
template <typename T>
void swap(T* a, T* b, int size) {
	T* temp = new T[size];
	size *= sizeof(T);
	memcpy(a, b, size);
	memcpy(b, temp, size);
}

// �������� ���� �������� ������
template <typename T>
void shift(T* shiftedArray, int size, int shift) {
	// �� �������� ����� � ��������
	bool shiftIsPositive = shift < 0 ? 0 : 1;
	// �������� ������ �����
	if (shiftIsPositive == false) {
		shift = -shift;
	}
	// �������� �������� �������� �����
	if (shift >= size) {
		shift = shift % size;
	}
	// ����
	if (shift != 0) {
		// ���������� ��� ���������� ���� ����� �� �� �������� ������ ������
		bool optimize = shift < size >> 1;

		// ����� ����������� ������
		int tempSize = optimize ? shift : size - shift;

		// г����� ������ ����������� �� ����������� ������
		int diffSize = size - tempSize;

		// ���������� �����
		T* temp = new T[tempSize];

		// ����� ���� ������ � ������
		int sizeOfT = sizeof(T);

		// ������������� ������� ������
		int one = shiftIsPositive ? 1 : 0;
		one += optimize ? 1 : 0;
		int two = (one > 0) && (one < 2);
		if (two)
			// ��� ���������� ������ , �������                �� �������� ������ ����������� ������
			// ��� ��'������ ������ , ������� , �� ������ , �� �������� ������ ����������� ������
		{
			// ��������� ����� ������� � ���������� �����
			memcpy(temp, shiftedArray, sizeOfT * tempSize);
			// ��������� ����� ������� �� ���� ����
			memcpy(shiftedArray, shiftedArray + tempSize, sizeOfT * diffSize);
			// ��������� ����� ������� �� ���� ����
			memcpy(shiftedArray + diffSize, temp, sizeOfT * tempSize);
		}
		else
			// ��� ���������� ������ , �������              �� �������� ������ ����������� ������
			// ��� ��'������ ������ , ������� , �� ������ , �� �������� ������ ����������� ������
		{
			// ��������� ����� ������� � ���������� �����
			memcpy(temp, shiftedArray + diffSize, sizeOfT * tempSize);
			// ��������� ����� ������� �� ���� ����
			memcpy(shiftedArray + tempSize, shiftedArray, sizeOfT * diffSize);
			// ��������� ����� ������� �� ���� ����
			memcpy(shiftedArray, temp, sizeOfT * tempSize);
		}

		// ��������� ����������� ������
		delete[] temp;
	}
}

// ��������� �������� ������
template <typename T>
void delete_element(T* &oldArray, int &size, int index) {
	// ����� �����
	T* newArray = new T[size - 1];
	// ��������� �������� �� ������������ ��������
	memcpy(newArray, oldArray, sizeof(T) * (index));
	// ��������� �������� ���� ������������ ��������
	memcpy(newArray + index, oldArray + index + 1, sizeof(T) * (size - index));
	// ��������� ������� ������
	delete[] oldArray;
	// ��������������� ��������� �� �����
	oldArray = newArray;
	// ��������� ������ ������
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

// ��������� ������� ��� ���� ��������� �������������� ������
template <typename T>
void combinate(T* combinatedArray, int size, void(*processing)(T* processedArray, int size)) {
	combinate(combinatedArray, size, 0, processing);
}