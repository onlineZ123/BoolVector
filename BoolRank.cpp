#include "BoolRank.h"

int BoolRank::value() const
{
	unsigned char mask = 1 << m_bitPos;
	return m_element & mask;
}

BoolRank& BoolRank::operator&=(const int val)
{
	unsigned char mask = 1 << m_bitPos;
	if (!val)
	{
		m_element &= (~mask);
	}
	return *this;
}

BoolRank& BoolRank::operator|=(const int val)
{
	unsigned char mask = 1 << m_bitPos;
	m_element |= mask;
	return *this;
}

BoolRank& BoolRank::operator^=(const int val)
{
	unsigned char mask = 1 << m_bitPos;
	if (*this != val)
	{
		m_element |= mask;
	}
	else
	{
		m_element &= (~mask);
	}

	return *this;
}
/*
TODO: BoolRank -> int
BoolRank BoolRank::operator&(const int val) const 
{
	unsigned char elem	= m_element;
	int bitPos			= m_bitPos;
	BoolRank concatination(elem, bitPos);
	concatination &= val;
	return concatination;
}

BoolRank BoolRank::operator|(const int val) const
{
	unsigned char elem	= m_element;
	int bitPos			= m_bitPos;
	BoolRank disjuction(elem, bitPos);
	disjuction |= val;
	return disjuction;
}

BoolRank BoolRank::operator^(const int val) const
{
	unsigned char elem	= m_element;
	int bitPos			= m_bitPos;
	BoolRank XOR(elem, bitPos);
	XOR ^= val;
	return XOR;
}

BoolRank BoolRank::operator~() const
{
	unsigned char elem	= m_element;
	int bitPos			= m_bitPos;
	BoolRank NOT(elem, bitPos);
	unsigned char mask = 1 << m_bitPos;

	if (NOT.checkBit())
	{
		NOT.m_element &= (~mask);
	}
	else
	{
		NOT.m_element |= mask;
	}

	return NOT;
}
*/
bool BoolRank::operator==(const int value) const
{
	if ((bool)this->value() == (bool)value)
	{
		return true;
	}
	return false;
}
bool BoolRank::operator!=(const int value) const
{
	return !operator==(value);
}

BoolRank& BoolRank::operator=(const int i)
{
	if (i != 0 && i != 1)
	{
		throw std::out_of_range("BoolRank::operator=(int)\n");
	}
	unsigned char mask = 1 << m_bitPos;
	if (*this != i)
	{
		if (!(m_element & mask))
		{
			(m_element) |= mask;
		}
		else
		{
			(m_element) &= (~mask);
		}
	}
	return *this;
}