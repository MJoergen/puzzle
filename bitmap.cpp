#include <iomanip>
#include "bitmap.h"

std::ostream& operator<<(std::ostream& os, const CBitMap& bitmap)
{
   return os << bitmap.m_val;
}

CBitMap operator~(const CBitMap& bitmap)
{
   CBitMap temp;
   temp.m_val.set();
   temp.m_val ^= bitmap.m_val;
   return temp;
}

