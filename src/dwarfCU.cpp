#include "utils/byteBuffer.h"
#include "dwarfAbbr.h"

#include "dwarfCU.h"

dwarfCU* currentCU;
std::vector<dwarfCU*> dwarfCompileUnits;

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

void dwarfCU::deserialize( ByteBuffer &buffer, uint64 &headerOffset, uint64 &nextOffset )
{
  buffer.Seek( headerOffset );
  m_header.unit_length = buffer.readInt<uint32>();
  if ( m_header.unit_length == 0xFFFFFFFF )
  {
    ::isDWARF64 = true;
    m_is64Bit = true;
    m_header.unit_length = buffer.readInt<uint64>();
  }

  uint64 currentSize = m_is64Bit ? 12 : 4;
  nextOffset = headerOffset + currentSize + m_header.unit_length;

  // Read version
  m_header.version = buffer.readInt<uint16>();
  assert( m_header.version >= 2 && m_header.version <= 5, "Unsupported DWARF version" );

  // Read abbreviation offset
  if ( m_is64Bit )
  {
    m_header.abbrev_offset = buffer.readInt<uint64>();
  }
  else
  {
    m_header.abbrev_offset = buffer.readInt<uint32>();
  }

  m_header.address_size = static_cast<CU_AddressSize>( buffer.readInt<ubyte>() );

  m_dieOffset = headerOffset + buffer.Pos();
}

void dwarfCU::parseData( ByteBuffer &buffer )
{
  buffer.Seek( m_dieOffset );
  for ( auto &entry : m_abbr->m_abbrevEntries )
  {
    uint64 abbrevCode = buffer.readLEB128<uint64>();
    if ( abbrevCode != entry.abbrevCode )
    {
      assert( false, "Abbreviation code mismatch" );
    }

    for ( auto &attr : entry.attributesSpecs )
    {
      if ( attr == nullptr )
      {
        continue;
      }
      attr->deserialize( buffer );
    }
  }
}

size_t readCompileUnits()
{
  ByteBuffer& debugInfoData = dwarfData.at( DEBUG_INFO );
  ByteBuffer& abbrRevData = dwarfData.at( DEBUG_ABBREV );
  uint64 sectionSize = debugInfoData.Size();
  uint64 cuHeaderOffset = 0;
  uint64 nextHeaderOffset = 0;
  while ( debugInfoData.Pos() < sectionSize )
  {
    dwarfCU* unitToAdd = new dwarfCU();
    currentCU = unitToAdd;

    unitToAdd->deserialize( debugInfoData, cuHeaderOffset, nextHeaderOffset);
    cuHeaderOffset = nextHeaderOffset;
    unitToAdd->getAbbr()->deserialize(abbrRevData, unitToAdd->getAbbrevSize(), unitToAdd->getAbbrevOffset());
    unitToAdd->parseData(debugInfoData);

    dwarfCompileUnits.push_back( unitToAdd );
    currentCU = nullptr;
  }

  return dwarfCompileUnits.size();
}
