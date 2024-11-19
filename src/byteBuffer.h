#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#include "dwarpTypes.h"

template <typename Int>
inline Int readInt( const byte *src, uint64 &pos, bool littleEndian = true )
{
  static_assert( std::is_integral<Int>::value, "Int must be an integral type" );

  assert(src, "Null source pointer");

  using UnsignedInt = std::make_unsigned_t<Int>;
  UnsignedInt result = 0;
  const ubyte *readPtr = (const ubyte*)&src[pos];
  for ( int i = 0; i < sizeof( Int ); i++ )
  {
    result |= static_cast<UnsignedInt>( readPtr[i] ) << ( littleEndian ? i * 8 : ( sizeof( Int ) - i - 1 ) * 8 );
  }

  pos += sizeof( Int );
  return static_cast<Int>( result );
}

#endif // BYTEBUFFER_H
