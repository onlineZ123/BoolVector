#include "BoolVector.h"


BoolVector::BoolVector() : m_data(new unsigned char[1]), m_size(8), m_capacity(1)
{
    m_data[0] = 0;
}

BoolVector::BoolVector(const int size)
{
    m_size      = size;
    m_capacity  = roundToPowerOfTwo(size) / 8;
    m_data      = new unsigned char[m_capacity];

    for (int i = 0; i < m_capacity; ++i)
    {
        m_data[i] = 0;
    }
}

BoolVector::BoolVector(const int size, const bool var)
{
    m_size = size;
    m_capacity = m_size % 8 != 0 ? m_size / 8 + 1 : m_size / 8;
    m_data = new unsigned char[m_capacity];
    m_data[m_capacity - 1] = 0;
    int i;

    unsigned char byteVal = 0;
    if (var)
    {
        byteVal = ~byteVal;
    }

    for (i = 0; i < m_capacity; ++i)
    {
        m_data[i] = byteVal;
    }

    unsigned char mask = ~0;
    mask >>= (8 - m_size % 8);
    m_data[m_capacity - 1] &= mask;
}

BoolVector::BoolVector(const BoolVector& other)
{
    m_data      = new unsigned char[other.m_capacity];
    m_size      = other.m_size;
    m_capacity  = other.m_capacity;

    for (int i = 0; i < m_capacity; ++i)
    {
        m_data[i] = other.m_data[i];
    }
}

BoolVector::BoolVector(const char* boolArr)
{
    m_size      = (int)strlen(boolArr);
    m_capacity  = (m_size % 8 == 0) ? m_size / 8 : m_size / 8 + 1;
    m_data      = new unsigned char[m_capacity];

    m_data[m_capacity - 1] = 0;

    for (int i = 0; i < m_size; ++i)
    {
        try 
        {
            if (convertToBool(boolArr[m_size - i - 1]))
            {
                setBit(1, i);
            }
            else
            {
                setBit(0, i);
            }
        }
        catch (const std::string& str)
        {
            std::cout << str;
        }
    }
}

BoolVector::BoolVector(const char* boolArr, const int size)
{
    m_size = size;
    m_capacity = (m_size % 8 == 0) ? m_size / 8 : m_size / 8 + 1;
    m_data = new unsigned char[m_capacity];

    for (int i = 0; i < m_capacity; ++i)
    {
        m_data[i] = 0;
    }

    int strSize = (int)strlen(boolArr);
    for (int i = 0; i < m_size && i < strSize; ++i)
    {
        try
        {
            if (convertToBool(boolArr[i]))
            {
                setBit(1, i);
            }
            else
            {
                setBit(0, i);
            }
        }
        catch (const std::string& str)
        {
            std::cout << str;
        }
    }
}

void BoolVector::inverse()
{
    for (int i = 0; i < m_capacity; ++i)
    {
        m_data[i] = ~m_data[i];
    }

    unsigned char mask    = (1 << (m_size % 8)) - 1;
    int bytePosition      = m_size / 8;
    m_data[bytePosition]  = m_data[bytePosition] & mask;
}

void BoolVector::inverse(const int bitPosition)
{
    int bytePosition    = bitPosition / 8;
    unsigned char mask  = 1 << (bitPosition % 8);

    if (!(m_data[bytePosition] & mask))
    {
        m_data[bytePosition] |= mask;
    }
    else
    {
        m_data[bytePosition] &= (~mask);
    }
}

void BoolVector::inverse(const int startFrom, const int count)
{
    if (startFrom >= m_size || startFrom < 0 || startFrom + count > m_size)
    {
        throw std::out_of_range("index out of memory");
    }
    else if (count == 0)
    {
        return;
    }

    unsigned char mask = ~0;
    mask <<= startFrom % 8;

    if (startFrom / 8 == ((startFrom + count) / 8))
    {
        unsigned char otherMask = ~0;
        otherMask >>= 8 - (startFrom + count) % 8;

        mask &= otherMask;
        m_data[startFrom / 8] ^= mask;
    }
    else
    {
        m_data[startFrom / 8] ^= mask;

        mask = ~0;
        mask >>= 8 - (startFrom + count) % 8;
        m_data[(startFrom + count) / 8] ^= mask;

        for (int i = startFrom / 8 + 1; i < (startFrom + count) / 8; ++i)
        {
            m_data[i] = ~m_data[i];
        }
    }
}

void BoolVector::setBit(const int value, const int bitPosition)
{
    operator[](bitPosition) = (bool)value;
}

void BoolVector::setBit(const bool value, const int startFrom, int count)
{
    if (startFrom >= m_size || startFrom < 0 || startFrom + count > m_size)
    {
        throw std::out_of_range("index out of memory");
    }
    else if (count == 0)
    {
        return;
    }

    unsigned char mask = ~0;
    mask <<= startFrom % 8;

    if (startFrom / 8 == ((startFrom + count) / 8))
    {
        unsigned char otherMask = ~0;
        otherMask >>= (8 - (count + startFrom) % 8);
        mask &= otherMask;
        if (value)
        {
            m_data[startFrom / 8] |= mask;
        }
        else
        {
            mask = ~mask;
            m_data[startFrom / 8] &= mask;
        }
    }
    else
    {
        unsigned char byteVal = 0;
        if (value)
        {
            m_data[startFrom / 8] |= mask;

            mask = ~0;
            mask >>= (8 - (count + startFrom) % 8);
            m_data[(startFrom + count) / 8] |= mask;
            byteVal = ~byteVal;
        }
        else
        {
            mask = ~mask;
            m_data[startFrom / 8] &= mask;

            mask = ~0;
            mask <<= (count + startFrom) % 8;
            m_data[(startFrom + count) / 8] &= mask;
        }

        for (int i = startFrom / 8 + 1; i < (startFrom + count) / 8; ++i)
        {
            m_data[i] = byteVal;
        }
    }

    
}

void BoolVector::set(const bool var)
{
    m_data[m_capacity - 1] = 0;
    int i;

    unsigned char byteVal = 0;
    if (var)
    {
        byteVal = ~byteVal;
    }

    for (i = 0; i < m_capacity; ++i)
    {
        m_data[i] = byteVal;
    }

    unsigned char mask = ~0;
    mask >>= (8 - m_size % 8);
    m_data[m_capacity - 1] &= mask;
}

int BoolVector::weight() const
{
    int weight = 0;

    for (int i = 0; i < m_size; ++i)
    {
        if ((int)operator[](i))
        {
            weight++;
        }
    }
    return weight;
}

int BoolVector::roundToPowerOfTwo(const int n)
{
    int v = n;

    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    
    return ++v;
}

bool BoolVector::convertToBool(const char ch)
{
    if (ch == 49)
    {
        return true;
    }
    else if (ch == 48)
    {
        return false;
    }
    else
    {
        throw std::string("BoolVector::convertToBool(char*) Cannot covert character to bool");
    }
}

BoolRank BoolVector::operator[](const int bitPosition) 
{
    BoolRank data(m_data[bitPosition / 8], (bitPosition % 8));
    return data;
}

const BoolRank BoolVector::operator[](const int bitPosition) const
{
    BoolRank data(m_data[bitPosition / 8], (bitPosition % 8));
    return data;
}

BoolVector& BoolVector::operator&=(const BoolVector& other)
{
    int minCap = m_capacity;
    if (m_capacity > other.m_capacity)
    {
        minCap = other.m_capacity;
        for (int i = minCap; i < m_capacity; i++)
        {
            m_data[i] = 0;
        }
    }

    for (int i = 0; i < minCap - 1; ++i)
    {
        m_data[i] &= other.m_data[i];
    }

    int minSize = m_size > other.m_size ? other.m_size : m_size;
    unsigned char mask = ~0;
    mask >>= 8 - minSize % 8;
    m_data[minCap - 1] &= other.m_data[minCap - 1];
    m_data[minCap - 1] &= mask;
   
    return *this;
}

BoolVector& BoolVector::operator|=(const BoolVector& other)
{
    int minCapacity = m_capacity;
    int minSize = m_size;
    unsigned char mask = ~0;
    mask >>= 8 - minSize % 8;

    if (m_capacity > other.m_capacity)
    {
        minCapacity = other.m_capacity;
        mask = ~0;
    }

    for (int i = 0; i < minCapacity; ++i)
    {
        m_data[i] |= other.m_data[i];
    }
  
    m_data[minCapacity - 1] &= mask;
    return *this;
}

BoolVector& BoolVector::operator^=(const BoolVector& other)
{
    int minCapacity = m_capacity;
    int minSize = m_size;

    if (m_capacity > other.m_capacity)
    {
        minCapacity = other.m_capacity;
        minSize = other.m_size;
    }
    for (int i = 0; i < minCapacity - 1; ++i)
    {
        m_data[i] ^= other.m_data[i];
    }

    unsigned char mask = ~0;
    mask >>= 8 - minSize % 8;
    unsigned char saveByte = other.m_data[minCapacity - 1] & mask;
    m_data[minCapacity - 1] ^= saveByte;
    return *this;
}

BoolVector& BoolVector::operator<<=(const int shiftNumber)
{
    if (shiftNumber < 0)
    {
        return operator>>=(-shiftNumber);
    }

    int shiftByte = shiftNumber / 8;
    if (shiftByte < m_capacity)
    {
        int shiftBit = shiftNumber % 8;

        unsigned char saveByte;

        unsigned char mask = ~0;
        mask <<= (8 - shiftBit);
        for (int i = m_capacity - 1; i >= shiftByte; --i)
        {
            m_data[i] = m_data[i - shiftByte] << shiftBit;
            if (i != shiftByte)
            {
                saveByte = m_data[i - 1 - shiftByte] & mask;
                saveByte >>= (8 - shiftBit);

                m_data[i] |= saveByte;
            }

        }
        mask = ~0;
        mask >>= 8 - (m_size % 8);
        m_data[m_capacity - 1] &= mask;
    }
    else shiftByte = m_capacity;

    for (int i = 0; i < shiftByte; i++)
    {
        m_data[i] = 0;
    }

    return *this;
}

BoolVector& BoolVector::operator>>=(const int shiftNumber)
{
    if (shiftNumber < 0)
    {
        return operator<<=(-shiftNumber);
    }

    int shiftByte = shiftNumber / 8;
    
    if (shiftByte < m_capacity)
    {
        int shiftBit = shiftNumber % 8;

        unsigned char saveByte;

        unsigned int mask = ~0;
        mask >>= (8 - shiftBit);

        for (int i = 0; i < m_capacity - shiftByte; ++i)
        {
            m_data[i] = m_data[i + shiftByte] >> shiftBit;

            if (i != m_capacity - 1 - shiftByte)
            {
                saveByte = m_data[i + 1 + shiftByte] & mask;
                saveByte <<= (8 - shiftBit);

                m_data[i] |= saveByte;
            }
        }
    }
    else
    {
        shiftByte = m_capacity;
    }

    for (int i = m_capacity - shiftByte; i < m_capacity; i++)
    {
        m_data[i] = 0;
    }

    return *this;
}

BoolVector BoolVector::operator&(const BoolVector& other) const
{
    BoolVector conjunction(*this);
    conjunction &= other;
    return conjunction;
}

BoolVector BoolVector::operator|(const BoolVector& other) const
{
    BoolVector disjunction(*this);
    disjunction |= other;
    return disjunction;
}

BoolVector BoolVector::operator^(const BoolVector& other) const
{
    BoolVector XOR(*this);
    XOR ^= other;
    return XOR;
}

BoolVector BoolVector::operator~() const
{
    BoolVector NOT(*this);
    NOT.inverse();
    return NOT;
}

BoolVector BoolVector::operator=(const BoolVector& other)
{
    if (this == &other) return *this;

    if (m_capacity != other.m_capacity)
    {
        delete[] m_data;
        m_data      = new unsigned char[other.m_capacity];
        m_capacity  = other.m_capacity;
    }
    m_size = other.m_size;

    for (int i = 0; i < m_capacity; ++i)
    {
        m_data[i] = other.m_data[i];
    }
    return *this;
}

BoolVector BoolVector::operator<<(const int shiftNumber) const
{
    BoolVector other(*this);
    other <<= shiftNumber;
    return other;
}

BoolVector BoolVector::operator>>(const int shiftNumber) const
{
    BoolVector other(*this);
    other >>= shiftNumber;
    return other;
}

