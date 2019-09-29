#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <ostream>

#define LONG_IS_8_BYTES

#ifdef LONG_IS_4_BYTES

class CBitMap /* bitmap_type; */
{
    friend std::ostream& operator<<(std::ostream& os, const CBitMap& bitmap);
    friend CBitMap operator~(const CBitMap& bitmap);

    public:
    CBitMap(unsigned long hi = 0, unsigned long lo = 0) :
        m_hi(hi), m_lo(lo) {}	// default constructor

    void SetBit(int bit_num)
    {
        if (bit_num<32)
            m_lo |= (1 << bit_num);
        else
            m_hi |= (1 << (bit_num-32));
    }

    int IsBitSet(int bit_num) const
    {
        if (bit_num<32)
            return (m_lo & (1 << bit_num));
        else
            return (m_hi & (1 << (bit_num-32)));
    }

    bool operator == (const CBitMap& rhs) const
    {
        return (m_hi == rhs.m_hi) && (m_lo == rhs.m_lo);
    }

    void Clear(void)
    {
        m_hi=0;
        m_lo=0;
    }

    bool AreBitsDistinct(const CBitMap& rhs) const
    {
        return ((m_hi & rhs.m_hi) == 0) && ((m_lo & rhs.m_lo) == 0);
    }

    CBitMap& operator &= (const CBitMap& rhs)
    {
        m_hi &= rhs.m_hi;
        m_lo &= rhs.m_lo;

        return *this;
    }

    CBitMap operator & (const CBitMap& rhs) const
    {
        CBitMap temp(*this);
        temp &= rhs;
        return temp;
    }

    CBitMap& operator |= (const CBitMap& rhs)
    {
        m_hi |= rhs.m_hi;
        m_lo |= rhs.m_lo;

        return *this;
    }

    private:
    unsigned long m_hi;
    unsigned long m_lo;
}; /* end of CBitMap */

#endif // LONG_IS_4_BYTES

#ifdef LONG_IS_8_BYTES

class CBitMap /* bitmap_type; */
{
    friend std::ostream& operator<<(std::ostream& os, const CBitMap& bitmap);
    friend CBitMap operator~(const CBitMap& bitmap);

    public:
    CBitMap(unsigned long lo = 0) :
        m_lo(lo) {}	// default constructor

    void SetBit(int bit_num)
    {
        m_lo |= (1UL << bit_num);
    }

    bool IsBitSet(int bit_num) const
    {
        return (m_lo & (1UL << bit_num));
    }

    bool operator == (const CBitMap& rhs) const
    {
        return (m_lo == rhs.m_lo);
    }

    void Clear(void)
    {
        m_lo=0;
    }

    bool AreBitsDistinct(const CBitMap& rhs) const
    {
        return ((m_lo & rhs.m_lo) == 0);
    }

    CBitMap& operator &= (const CBitMap& rhs)
    {
        m_lo &= rhs.m_lo;

        return *this;
    }

    CBitMap operator & (const CBitMap& rhs) const
    {
        CBitMap temp(*this);
        temp &= rhs;
        return temp;
    }

    CBitMap& operator |= (const CBitMap& rhs)
    {
        m_lo |= rhs.m_lo;

        return *this;
    }

    private:
    unsigned long m_lo;
}; /* end of CBitMap */

#endif // LONG_IS_8_BYTES

#endif /* _BITMAP_H_ */

