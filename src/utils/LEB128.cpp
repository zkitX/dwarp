#include "LEB128.h"

uint64 LEB128::decode_uleb128( const byte *data, size_t &bytes_read )
{
  uint64_t result = 0;
  size_t shift = 0;
  size_t index = 0;
  const uint8_t *readPos = reinterpret_cast<const uint8_t *>( &data[bytes_read] );

  while ( 1 )
  {
    uint8_t byte = readPos[index++];
    result |= (uint64_t)( byte & 0x7F ) << shift;
    if ( ( byte & 0x80 ) == 0 )
    { // End of LEB128 encoding
      break;
    }
    shift += 7;
  }

  bytes_read += index; // Increment our byte position

  return result;
}

int64 LEB128::decode_sleb128( const byte *data, size_t &bytes_read )
{
  int64_t result = 0;
  size_t shift = 0;
  size_t index = 0;
  const uint8_t *readPos = reinterpret_cast<const uint8_t *>( &data[bytes_read] );
  uint8_t byte;

  while ( 1 )
  {
    byte = readPos[index++];
    result |= ( (int64_t)( byte & 0x7F ) << shift );
    shift += 7;

    if ( ( byte & 0x80 ) == 0 )
    { // End of LEB128 encoding
      break;
    }
  }

  // Sign extension
  if ( ( byte & 0x40 ) != 0 )
  { // Check sign bit of the last byte
    result |= -( 1LL << shift );
  }

  bytes_read += index; // increment our bytes position

  return result;
}
