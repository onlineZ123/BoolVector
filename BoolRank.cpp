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

int BoolRank::operator&(const bool val) const 
{	
	unsigned char mask = 1 << m_bitPos;
	if (m_element & mask)
	{
		return val;
	}
	return 0;
}

int BoolRank::operator|(const bool val) const
{
	unsigned char mask = 1 << m_bitPos;
	if (m_element & mask)
	{
		return 1;
	}
	return val;
}

int BoolRank::operator^(const bool val) const
{
	unsigned char mask = 1 << m_bitPos;
	if (m_element & mask)
	{
		return !val;
	}
	return val;
}

int BoolRank::operator~() const
{
	unsigned char mask = 1 << m_bitPos;
	if (m_element & mask)
	{
		return 0;
	}
	return 1;
}


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