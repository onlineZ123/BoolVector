#pragma once
#include <iostream>

class BoolRank
{
private:
	//friend std::ostream& operator<<(std::ostream& out, const BoolRank& bRank);
public:
	BoolRank(unsigned char& element, const int bitPos) : m_element(element) 
	{
		if (bitPos >= 0 && bitPos < 8)
		{
			m_bitPos = bitPos;
		}
		else
		{
			throw std::out_of_range("BoolRank::BoolRank(char&, int), out of the memory block");
		}
	}

	int value() const;

	BoolRank& operator&=(const int val);
	BoolRank& operator|=(const int val);
	BoolRank& operator^=(const int val);

	int operator&(const bool val) const;
	int operator|(const bool val) const;
	int operator^(const bool val) const;
	int operator~() const;

	bool operator==(const int value) const;
	bool operator!=(const int value) const;

	explicit operator int() const
	{
		return value();
	}

	explicit operator char() const
	{
		return value();
	}

	operator bool() const
	{
		return value();
	}

	BoolRank& operator=(const int i);
private:
	unsigned char& m_element;
	int m_bitPos;
};

inline std::ostream& operator<<(std::ostream& out, const BoolRank& bRank)
{
	out << (bool)bRank;
	return out;
}
