#ifndef _BITMAP_H_
#define _BITMAP_H_

// This class allows for manipulation of individual bits inside a 64-bit value.

#include <ostream>

class CBitMap
{
    friend std::ostream& operator<<(std::ostream& os, const CBitMap& bitmap);
    friend CBitMap operator~(const CBitMap& bitmap);

    public:
       // Constructor
       CBitMap(uint64_t val = 0) :
           m_val(val) {}

       // Modifiers
       void Clear(void)
       {
           m_val=0;
       }

       void SetBit(int bit_num)
       {
           m_val |= (1UL << bit_num);
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
           return (m_val & (1UL << bit_num));
       }

       bool operator == (const CBitMap& rhs) const
       {
           return (m_val == rhs.m_val);
       }

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
       uint64_t m_val;
}; /* end of CBitMap */

#endif /* _BITMAP_H_ */

