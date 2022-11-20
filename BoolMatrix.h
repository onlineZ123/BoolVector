#pragma once

#include "BoolVector.h"

class BoolMatrix
{
private:
	friend std::ostream& operator<<(std::ostream& stream, const BoolMatrix& bMatr);
	friend std::istream& operator>>(std::istream& stream, const BoolMatrix& bMatr);
public:
	BoolMatrix();
	BoolMatrix(const int row, const int column, const bool value);
	BoolMatrix(const char** str, const int row, const int column);
	BoolMatrix(const BoolMatrix& other);
	~BoolMatrix();

	int weight() const;
	int weight(const int row) const;

	BoolVector disjunction() const;
	BoolVector conjunction() const;

	void inverse(const int row, const int bitPos);
	void inverse(const int row, const int bitPos, const int count);
	void set(const bool value, const int row, const int bitPos);
	void set(const bool value, const int row, const int bitPos, const int count);

	BoolMatrix operator=(const BoolMatrix& other);

	BoolVector& operator[](const int row);
	const BoolVector operator[](const int row) const;
	BoolMatrix& operator&=(const BoolMatrix& other);
	BoolMatrix& operator|=(const BoolMatrix& other);
	BoolMatrix& operator^=(const BoolMatrix& other);
	BoolMatrix operator&(const BoolMatrix& other) const;
	BoolMatrix operator|(const BoolMatrix& other) const;
	BoolMatrix operator^(const BoolMatrix& other) const;
	BoolMatrix operator~() const;
private:
	BoolVector* m_matr;
	int m_row;
	int m_column;
};

inline std::ostream& operator<<(std::ostream& stream, const BoolMatrix& bMatr)
{
	for (int i = 0; i < bMatr.m_row; ++i)
	{
		stream << bMatr.m_matr[i] << std::endl;
	}
	return stream;
}

inline std::istream& operator>>(std::istream& stream, const BoolMatrix& bMatr)
{
	for (int i = 0; i < bMatr.m_row; ++i)
	{
		try {
			stream >> bMatr.m_matr[i];
		}
		catch (...)
		{
			std::cout << "111";
		}
	}
	return stream;
}
