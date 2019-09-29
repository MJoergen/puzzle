
#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <ostream>

using namespace std;

#define LONG_IS_8_BYTES

#ifdef LONG_IS_4_BYTES

class CBitMap /* bitmap_type; */
{
    friend ostream& operator<<(ostream& os, const CBitMap& bitmap);
    friend CBitMap operator~(const CBitMap& bitmap);

    public:
    CBitMap(unsigned long hi = 0, unsigned long lo = 0) :
        hi(hi), lo(lo) {}	// default constructor

    void SetBit(int bit_num)
    {
        if (bit_num<32)
            lo |= (1 << bit_num);
        else
            hi |= (1 << (bit_num-32));
    }

    int IsBitSet(int bit_num) const
    {
        if (bit_num<32)
            return (lo & (1 << bit_num));
        else
            return (hi & (1 << (bit_num-32)));
    }

    bool operator == (const CBitMap& rhs) const
    {
        return (hi == rhs.hi) && (lo == rhs.lo);
    }

    void Clear(void)
    {
        hi=0;
        lo=0;
    }

    bool AreBitsDistinct(const CBitMap& rhs) const
    {
        return ((hi & rhs.hi) == 0) && ((lo & rhs.lo) == 0);
    }

    CBitMap& operator &= (const CBitMap& rhs)
    {
        hi &= rhs.hi;
        lo &= rhs.lo;

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
        hi |= rhs.hi;
        lo |= rhs.lo;

        return *this;
    }

    private:
    unsigned long hi;
    unsigned long lo;
}; /* end of CBitMap */

#endif // LONG_IS_4_BYTES

#ifdef LONG_IS_8_BYTES

class CBitMap /* bitmap_type; */
{
    friend ostream& operator<<(ostream& os, const CBitMap& bitmap);
    friend CBitMap operator~(const CBitMap& bitmap);

    public:
    CBitMap(unsigned long lo = 0) :
        lo(lo) {}	// default constructor

    void SetBit(int bit_num)
    {
        lo |= (1UL << bit_num);
    }

    bool IsBitSet(int bit_num) const
    {
        return (lo & (1UL << bit_num));
    }

    bool operator == (const CBitMap& rhs) const
    {
        return (lo == rhs.lo);
    }

    void Clear(void)
    {
        lo=0;
    }

    bool AreBitsDistinct(const CBitMap& rhs) const
    {
        return ((lo & rhs.lo) == 0);
    }

    CBitMap& operator &= (const CBitMap& rhs)
    {
        lo &= rhs.lo;

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
        lo |= rhs.lo;

        return *this;
    }

    private:
    unsigned long lo;
}; /* end of CBitMap */

#endif // LONG_IS_8_BYTES

#endif /* _BITMAP_H_ */

