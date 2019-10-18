#include <iomanip>
#include "bitmap.h"

std::ostream& operator<<(std::ostream& os, const CBitMap& bitmap)
{
    os << std::hex;
    os << std::setw(16) << std::setfill('0') << bitmap.m_val;
    os << std::dec;
    return os;
}

CBitMap operator~(const CBitMap& bitmap)
{
    return CBitMap(~bitmap.m_val);
}

