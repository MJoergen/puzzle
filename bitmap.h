#ifndef _BITMAP_H_
#define _BITMAP_H_

// This class allows for manipulation of individual bits inside a fixed-size
// bit set. The size is chosen at compile time with -DBITMAP_BITS=N, and limits
// the number of squares on the board. Smaller is faster.

#ifndef BITMAP_BITS
#define BITMAP_BITS 64
#endif

#include <bitset>
#include <ostream>

class CBitMap
{
    friend std::ostream& operator<<(std::ostream& os, const CBitMap& bitmap);
    friend CBitMap operator~(const CBitMap& bitmap);

    public:
       static const int MaxBits = BITMAP_BITS;

       // Constructor
       CBitMap() :
           m_val(0) {}

       // Modifiers
       void Clear(void)
       {
           m_val=0;
       }

       void SetBit(int bit_num)
       {
           m_val[bit_num] = 1;
       }

       CBitMap& operator &= (const CBitMap& rhs)
       {
           m_val &= rhs.m_val;
           return *this;
       }

       CBitMap& operator |= (const CBitMap& rhs)
       {
           m_val |= rhs.m_val;
           return *this;
       }

       // Inspectors
       bool IsBitSet(int bit_num) const
       {
           return m_val[bit_num];
       }

       bool operator == (const CBitMap& rhs) const
       {
           return (m_val == rhs.m_val);
       }

       // Index of the lowest set bit, or MaxBits if none.
       int FirstSetBit() const { return m_val._Find_first(); }
       // Index of the lowest clear bit, or MaxBits if none.
       int FirstClearBit() const { return (~m_val)._Find_first(); }

       bool AreBitsDistinct(const CBitMap& rhs) const
       {
           return ((m_val & rhs.m_val) == 0);
       }

       CBitMap operator & (const CBitMap& rhs) const
       {
           CBitMap temp(*this);
           temp &= rhs;
           return temp;
       }

    private:
       std::bitset<BITMAP_BITS> m_val;
}; /* end of CBitMap */

#endif /* _BITMAP_H_ */

