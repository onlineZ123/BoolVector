// BoolVector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "BoolVector.h"
#include "BoolMatrix.h"

int _testShift(const int length = 100, const int offset = 1)
{
	using std::cout;
	using std::endl;

	BoolVector vector1(length, 1);
	BoolVector vector2(length, 1);
	for (int i = 0; i <= length; i += offset) {
		vector1 = (vector2 << i);
		cout << vector1 << endl;
	}

	for (int i = 0; i <= length; i += offset) {
		vector1 = (vector2 >> i);
		cout << vector1 << endl;
	}

	return 1;
}

void testShift()
{
	for (int offset = 1; offset < 10; offset += 2) {
		_testShift(100, offset);
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
	}
}

int testSetBit()
{
	BoolVector vector(100, 1);
	for (int i = 0; i < 100; i++)
	{
		vector.setBit(0, 99 - i, 1);
		std::cout << i << "\t";
		std::cout << vector << std::endl;
		vector.set(1);
	}
	return 1;
}

void testConjuction()
{
	BoolVector vector1("100101010101001");
	BoolVector vector2		  ("1101001");

	vector1 &= vector2;
	std::cout << vector1 << " " << vector1.getByte(0);
	return;
}

void testDisjuction()
{
	BoolVector vector1("000101010101001");
	BoolVector vector2("10110");

	vector1 ^= vector2;
	std::cout << vector1 << " " << vector1.getByte(1);
	return;
}

int main()
{
	//testConjuction();
	//return 0;
	BoolMatrix matr(10, 10, 0);
	matr.inverse(0, 0, 9);
	//std::cout << matr;

	const char* arr[] = { "01010010", "00000111111", "001100110011" };
	BoolMatrix m(arr, 3, 8);
	std::cout << m;
	std::cin >> m;
	std::cout << m;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
