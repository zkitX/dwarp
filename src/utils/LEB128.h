#ifndef LEB128_H
#define LEB128_H

#include "dwarpTypes.h"

class LEB128
{
public:
  static uint64 decode_uleb128( const byte *data, size_t &bytes_read );
  static int64 decode_sleb128( const byte *data, size_t &bytes_read );
};

#endif // LEB128_H
