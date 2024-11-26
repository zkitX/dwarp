#include "dwarfTU.h"

std::vector<dwarfTU*> dwarfTypeUnits;

dwarfTU::dwarfTU()
  : m_is64Bit( false )
{
}

dwarfTU::~dwarfTU() {}

void dwarfTU::deserialize( ByteBuffer &buffer, uint64 abbrevSize, uint64 offset )
{
  buffer.Seek( offset );
  m_header.unit_length = buffer.readInt<uint32>();
  if ( m_header.unit_length == 0xFFFFFFFF )
  {
    m_is64Bit = true;
    m_header.unit_length = static_cast<uint32>(buffer.readInt<uint64>());
  }

  m_header.version = buffer.readInt<uint16>();
  assert( m_header.version >= 2 && m_header.version <= 5, "Unsupported DWARF version" );

  m_header.debug_abbrev_offset = m_is64Bit ? buffer.readInt<uint64>() : buffer.readInt<uint32>();
  m_header.address_size = static_cast<ubyte>( buffer.readInt<ubyte>() );
  m_header.type_signature = buffer.readInt<uint64>();
  m_header.type_offset = m_is64Bit ? buffer.readInt<uint64>() : buffer.readInt<uint32>();
}
