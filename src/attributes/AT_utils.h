#ifndef AT_UTILS_H
#define AT_UTILS_H

#include "AT_base.h"

class AT_Utils
{
public:
  static std::string readString( ByteBuffer &buffer, DW_FORM form );
};

#endif // AT_UTILS_H
