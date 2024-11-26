#include "byteBuffer.h"

std::string ByteBuffer::readString()
{
    assert(m_pos < m_buffer.size(), "Buffer overflow");

    std::string result;
    while (m_pos < m_buffer.size() && m_buffer[m_pos] != '\0')
    {
      result += m_buffer[m_pos++];
    }

    if (m_pos < m_buffer.size())
    {
      m_pos++; // Skip the null terminator
    }

    return result;
}

template<>
uint64 ByteBuffer::readLEB128()
{
  uint64_t result = 0;
  size_t shift = 0;
  size_t index = 0;

  while ( 1 )
  {
    uint8_t byte = m_buffer[m_pos + index++];
    result |= (uint64_t)( byte & 0x7F ) << shift;
    if ( ( byte & 0x80 ) == 0 )
    { // End of LEB128 encoding
      break;
    }
    shift += 7;
  }

  m_pos += index; // Increment our position

  return result;
}

template<>
int64 ByteBuffer::readLEB128()
{
  int64_t result = 0;
  size_t shift = 0;
  size_t index = 0;
  uint8_t byte;

  while ( 1 )
  {
    byte = m_buffer[m_pos + index++];
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

  m_pos += index; // increment our position

  return result;
}