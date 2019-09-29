
#include "bitmap.h"
#include <iomanip>

#ifdef LONG_IS_4_BYTES
ostream& operator<<(ostream& os, const CBitMap& bitmap)
{
    os << hex;
    os << setw(8) << setfill('0') << bitmap.hi;
    os << setw(8) << setfill('0') << bitmap.lo;
    os << dec;
    return os;
}

CBitMap operator~(const CBitMap& bitmap)
{
    return CBitMap(~bitmap.hi, ~bitmap.lo);
}
#endif // LONG_IS_4_BYTES

#ifdef LONG_IS_8_BYTES
ostream& operator<<(ostream& os, const CBitMap& bitmap)
{
    os << hex;
    os << setw(16) << setfill('0') << bitmap.lo;
    os << dec;
    return os;
}

CBitMap operator~(const CBitMap& bitmap)
{
    return CBitMap(~bitmap.lo);
}
#endif // LONG_IS_8_BYTES

