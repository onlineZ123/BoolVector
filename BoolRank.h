#pragma once
#include <iostream>

class BoolRank
{
private:
	//friend std::ostream& operator<<(std::ostream& out, const BoolRank& bRank);
	//friend std::istream& operator>>(std::istream& stream, const BoolRank& bRank);
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

	//int operator&(const int val) const;
	//int operator|(const int val) const;
	//int operator^(const int val) const;
	//int operator~() const;

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

inline std::istream& operator>>(std::istream& stream, BoolRank bRank)
{
	int val;
	stream >> val;
	if (val >= 0 && val <= 1)
	{
		bRank = (bool)val;
	}
	else
	{
		throw std::string("Wrong console input");
	}
	return stream;
}
