#include "dwarfAbbr.h"
#include "utils/byteBuffer.h"

dwarfAbbr::dwarfAbbr() {}

dwarfAbbr::~dwarfAbbr() {}

void dwarfAbbr::deserialize( ByteBuffer &buffer, uint64 abbrevSize, uint64 offset )
{
  buffer.Seek( offset );
  size_t end = buffer.Pos() + abbrevSize;

  while ( buffer.Pos() < end )
  {
    AbbrevEntry newEntry;

    newEntry.abbrevCode = buffer.readLEB128<uint64>();

    // the abbreviation code of 0 marks the end of the CU
    if ( !newEntry.abbrevCode )
    {
      break;
    }

    newEntry.tag = static_cast<DW_TAG>( buffer.readLEB128<uint64>() );
    newEntry.hasChildren = static_cast<DW_CHILDREN>( buffer.readInt<uint8_t>() );

    for ( ;; )
    {
      DW_AT attribute = static_cast<DW_AT>( buffer.readLEB128<uint64>() );
      DW_FORM form = static_cast<DW_FORM>( buffer.readLEB128<uint64>() );

      // 0,0 means no more attribute specs
      if ( !attribute && !form )
      {
        break;
      }
      AT_Base *spec = createAttribute( attribute, form );
      newEntry.attributesSpecs.push_back( spec );
    }

    m_abbrevEntries.push_back( newEntry );
  }
}

AT_Base *createAttribute( DW_AT attribute, DW_FORM form )
{
  switch ( attribute )
  {
    case DW_AT_NAME:
      return new AT_Name( attribute, form );
    case DW_AT_PRODUCER:
      return new AT_Producer( attribute, form );
    case DW_AT_LANGUAGE:
      return new AT_Language( attribute, form );
    case DW_AT_LOW_PC:
      return new AT_LowPC( attribute, form );
    case DW_AT_HIGH_PC:
      return new AT_HighPC( attribute, form );
    case DW_AT_STMT_LIST:
      return new AT_StmtList( attribute, form );
    default:
      return nullptr;
  }
}
