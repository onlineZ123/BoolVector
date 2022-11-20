#include "BoolMatrix.h"

BoolMatrix::BoolMatrix()
{
	m_row		= 8;
	m_column	= 8;
	m_matr = new BoolVector[m_row];

	for (int i = 0; i < m_row; ++i)
	{
		m_matr[i] = BoolVector(m_column, 0);
	}
}

BoolMatrix::BoolMatrix(const int row, const int column, const bool value)
{
	m_row = row;
	m_column = column;
	m_matr = new BoolVector[m_row];
	for (int i = 0; i < m_row; ++i)
	{
		m_matr[i] = BoolVector(m_column, value);
	}
}

BoolMatrix::BoolMatrix(const char** str, const int row, const int column)
{
	m_row = row;
	m_column = column;
	m_matr = new BoolVector[m_row];

	for (int i = 0; i < m_row; ++i)
	{
		m_matr[i].set(0);
	}

	for (int i = 0; i < row; ++i)
	{
		m_matr[i] = BoolVector(str[i], m_column);
	}
}

BoolMatrix::BoolMatrix(const BoolMatrix& other)
{
	m_matr = new BoolVector[other.m_row];
	m_row = other.m_row;
	m_column = other.m_column;

	for (int i = 0; i < m_row; ++i)
	{
		m_matr[i] = other.m_matr[i];
	}
}

BoolMatrix::~BoolMatrix()
{
	delete[] m_matr;
}

int BoolMatrix::weight() const
{
	int weight = 0;
	for (int i = 0; i < m_row; ++i)
	{
		weight += m_matr[i].weight();
	}
	return weight;
}

int BoolMatrix::weight(const int row) const
{
	if (row < 0 || row >= m_row)
	{
		throw std::out_of_range("bla bla bla");
	}

	return m_matr[row].weight();
}

BoolVector BoolMatrix::disjunction() const
{
	BoolVector disjunction(m_matr[0]);
	for (int i = 1; i < m_row; ++i)
	{
		disjunction |= m_matr[i];
	}
	return disjunction;
}

BoolVector BoolMatrix::conjunction() const
{
	BoolVector conjunction(m_matr[0]);
	for (int i = 1; i < m_row; ++i)
	{
		conjunction &= m_matr[i];
	}
	return conjunction;
}

void BoolMatrix::inverse(const int row, const int bitPos)
{
	if (row < 0 || row >= m_row)
	{
		throw std::out_of_range("out of memory block");
	}
	m_matr[row].inverse(bitPos);
}

void BoolMatrix::inverse(const int row, const int bitPos, const int count)
{
	if (row < 0 || row >= m_row || bitPos < 0 || bitPos >= m_column)
	{
		throw std::out_of_range("out of memory block");
	}
	m_matr[row].inverse(bitPos, count);
}

void BoolMatrix::set(const bool value, const int row, const int bitPos)
{
	if (row < 0 || row >= m_row || bitPos < 0 || bitPos >= m_column)
	{
		throw std::out_of_range("out of memory block");
	}
	m_matr[row].setBit(value, bitPos);
}

void BoolMatrix::set(const bool value, const int row, const int bitPos, const int count)
{
	if (row < 0 || row >= m_row || bitPos < 0 || bitPos >= m_column)
	{
		throw std::out_of_range("out of memory block");
	}
	m_matr[row].setBit(value, bitPos, count);
}


BoolMatrix BoolMatrix::operator=(const BoolMatrix& other)
{
	if (this == &other) return *this;

	if (m_row != other.m_row || m_column != other.m_column)
	{
		delete[] m_matr;
		m_matr = new BoolVector[other.m_row];
		m_row = other.m_row;
		m_column = other.m_column;
	}

	for (int i = 0; i < m_column; ++i)
	{
		m_matr[i] = other.m_matr[i];
	}
	return *this;
}

BoolVector& BoolMatrix::operator[](const int row)
{
	if (row < 0 || row >= m_row)
	{
		throw std::out_of_range("bla bla bla");
	}
	return m_matr[row];
}

const BoolVector BoolMatrix::operator[](const int row) const
{
	BoolVector data(m_matr[row]);
	return data;
}

BoolMatrix& BoolMatrix::operator&=(const BoolMatrix& other)
{
	int minRow = m_row > other.m_row ? other.m_row : m_row;
	for (int i = 0; i < minRow; ++i)
	{
		m_matr[i] &= other.m_matr[i];
	}
	return *this;
}

BoolMatrix& BoolMatrix::operator|=(const BoolMatrix& other)
{
	int minRow = m_row > other.m_row ? other.m_row : m_row;
	for (int i = 0; i < minRow; ++i)
	{
		m_matr[i] |= other.m_matr[i];
	}
	return *this;
}

BoolMatrix& BoolMatrix::operator^=(const BoolMatrix& other)
{
	int minRow = m_row > other.m_row ? other.m_row : m_row;
	for (int i = 0; i < minRow; ++i)
	{
		m_matr[i] ^= other.m_matr[i];
	}
	return *this;
}

BoolMatrix BoolMatrix::operator&(const BoolMatrix& other) const
{
	BoolMatrix conjuction(*this);
	conjuction &= other;
	return conjuction;
}

BoolMatrix BoolMatrix::operator|(const BoolMatrix& other) const
{
	BoolMatrix disjuction(*this);
	disjuction &= other;
	return disjuction;
}

BoolMatrix BoolMatrix::operator^(const BoolMatrix& other) const
{
	BoolMatrix XOR(*this);
	XOR &= other;
	return XOR;
}

BoolMatrix BoolMatrix::operator~() const
{
	BoolMatrix NOT(*this);
	for (int i = 0; i < m_row; ++i)
	{
		NOT.m_matr[i].operator~();
	}

	return NOT;
}




