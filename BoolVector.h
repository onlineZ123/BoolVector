#pragma once
#include <stdarg.h>

#include "BoolRank.h"

class BoolVector
{
private:
	int roundToPowerOfTwo(const int n);
	bool convertToBool(const char ch);
	//void _setBitCollection(const int size, va_list Args);

	friend std::ostream& operator<<(std::ostream& stream, const BoolVector& bvec);
	friend std::istream& operator>>(std::istream& stream, BoolVector& bvec);
public:
	BoolVector();
	explicit BoolVector(const int size);
	explicit BoolVector(const int size, const bool var);
	explicit BoolVector(const char* boolArr);
	BoolVector(const char* boolArr, const int size);
	BoolVector(const BoolVector& other);
	~BoolVector() { delete[] m_data; }

	void inverse();					   // inverses whole boolean vector
	void inverse(const int bitPosition); // inverse certain bit
	void inverse(const int bitPosition, const int count);
	void setBit(const int value, const int bitPosition);  // set a certain bit
	void setBit(const bool value, const int startFrom, int count);	   // setting collection of bit
	void set(const bool var);
	int getSize() const { return m_size; }
	int getCapacity() const { return m_capacity; }
	int getByte(int byte) { return m_data[byte]; }
	int weight() const;
	
	BoolVector operator=(const BoolVector& other); 
	BoolRank operator[](const int bitPosition);
	const BoolRank operator[](const int bitPosition) const;
	BoolVector& operator&=(const BoolVector& other);
	BoolVector& operator|=(const BoolVector& other);
	BoolVector& operator^=(const BoolVector& other);
	BoolVector& operator<<=(const int shiftNumber); 
	BoolVector& operator>>=(const int shiftNumber); 
	BoolVector operator&(const BoolVector& other) const;
	BoolVector operator|(const BoolVector& other) const;
	BoolVector operator^(const BoolVector& other) const;
	BoolVector operator~() const;
	BoolVector operator<<(const int shiftNumber) const;
	BoolVector operator>>(const int shiftNumber) const;
private:
	unsigned char* m_data = nullptr;
	int m_size = 0;
	int m_capacity = 0;
};

inline std::ostream& operator<<(std::ostream& stream, const BoolVector& bvec)
{
	for (int i = bvec.m_size - 1; i >= 0; --i)
	{
		stream << bvec[i];
	}
	return stream;
}

inline std::istream& operator>>(std::istream& stream, BoolVector& bvec)
{
	char* str = new char[(bvec.m_size + 1)];
	bvec.m_data[bvec.m_capacity - 1] = 0;
	stream >> str;
	bvec = BoolVector(str, bvec.m_size);

	return stream;
}
