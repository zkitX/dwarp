#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#include "dwarpTypes.h"

class ByteBuffer
{
public:
  ByteBuffer()
    : m_buffer( std::vector<byte>() ),
      m_pos( 0 )
  {
  }

  ByteBuffer( const std::vector<byte> &buffer )
    : m_buffer( buffer ),
      m_pos( 0 )
  {
  }

  ByteBuffer( const ByteBuffer &other )
    : m_buffer( other.m_buffer ),
      m_pos( other.m_pos )
  {
  }

  ~ByteBuffer() {}

  void Reset()
  {
    m_pos = 0;
  }

  void Seek( size_t pos )
  {
    m_pos = pos;
  }

  size_t Pos() const
  {
    return m_pos;
  }

  size_t Size() const
  {
    return m_buffer.size();
  }

  template <typename Int>
  inline Int readInt( bool littleEndian = true )
  {
    static_assert( std::is_integral<Int>::value, "Int must be an integral type" );
    assert( m_pos + sizeof( Int ) <= m_buffer.size(), "Buffer overflow" );

    Int result;
    std::memcpy( &result, &m_buffer[m_pos], sizeof( Int ) );

    // Handle endianness if needed
    if ( !littleEndian )
    {
      byte *bytes = reinterpret_cast<byte *>( &result );
      std::reverse( bytes, bytes + sizeof( Int ) );
    }

    m_pos += sizeof( Int );
    return result;
  }

  template <typename Int>
  Int readLEB128();

  std::string readString();

protected:
  const std::vector<byte> m_buffer;
  size_t m_pos;
};

#endif // BYTEBUFFER_H
