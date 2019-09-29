
#include "bitmap.h"
#include <iomanip>

#ifdef LONG_IS_4_BYTES
std::ostream& operator<<(std::ostream& os, const CBitMap& bitmap)
{
    os << std::hex;
    os << std::setw(8) << std::setfill('0') << bitmap.m_hi;
    os << std::setw(8) << std::setfill('0') << bitmap.m_lo;
    os << std::dec;
    return os;
}

CBitMap operator~(const CBitMap& bitmap)
{
    return CBitMap(~bitmap.m_hi, ~bitmap.m_lo);
}
#endif // LONG_IS_4_BYTES

#ifdef LONG_IS_8_BYTES
std::ostream& operator<<(std::ostream& os, const CBitMap& bitmap)
{
    os << std::hex;
    os << std::setw(16) << std::setfill('0') << bitmap.m_lo;
    os << std::dec;
    return os;
}

CBitMap operator~(const CBitMap& bitmap)
{
    return CBitMap(~bitmap.m_lo);
}
#endif // LONG_IS_8_BYTES

