#include "byteBuffer.h"
#include "dwarfAbbr.h"

#include "dwarfCU.h"

dwarfCU::dwarfCU()
  : m_is64Bit( false )
{
  m_abbr = new dwarfAbbr();
  memset( &m_header, 0, sizeof( m_header ) );
}

dwarfCU::~dwarfCU()
{
  delete m_abbr;
}

void dwarfCU::deserialize( dwarfSectionData &data, uint64 &offset )
{
  data.dataPos = 0;
  const char *buffer = data.sectionPtr->get_data() + offset;
  m_header.m_32BitSize = readInt<uint32>( buffer, data.dataPos );
  if ( m_header.m_32BitSize == 0xFFFFFFFF )
  {
    m_is64Bit = true;
    m_header.m_64BitSize = readInt<uint64>( buffer, data.dataPos );
  }

  offset += data.dataPos + (m_is64Bit ? m_header.m_64BitSize : m_header.m_32BitSize);

  // Read version
  m_header.m_version = readInt<uint16>( buffer, data.dataPos );
  assert( m_header.m_version >= 2 && m_header.m_version <= 5, "Unsupported DWARF version" );

  // Read abbreviation offset
  if ( m_is64Bit )
  {
    m_header.m_64BitAbbrevOffset = readInt<uint64>( buffer, data.dataPos );
  }
  else
  {
    m_header.m_32BitAbbrevOffset = readInt<uint32>( buffer, data.dataPos );
  }

  m_header.m_addrSize = static_cast<CU_AddressSize>( readInt<ubyte>( buffer, data.dataPos ) );
}
