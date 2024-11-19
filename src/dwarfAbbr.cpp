#include "dwarfAbbr.h"
#include "byteBuffer.h"

dwarfAbbr::dwarfAbbr() {}

dwarfAbbr::~dwarfAbbr() {}

void dwarfAbbr::deserialize( dwarfSectionData &data, uint64 abbrevSize, uint64 offset )
{
  data.dataPos = 0;
  const byte *ptr = data.sectionPtr->get_data();
  ptr += offset;
  const byte *end = ptr + abbrevSize;

  while ( ptr + data.dataPos < end)
  {
    AbbrevEntry newEntry;

    newEntry.abbrevCode = LEB128::decode_uleb128(ptr, data.dataPos);

    // the abbreviation code of 0 marks the end of the CU
    if (!newEntry.abbrevCode)
    {
      break;
    }

    newEntry.tag = static_cast<DW_TAG>(LEB128::decode_uleb128(ptr, data.dataPos));
    newEntry.hasChildren = static_cast<DW_CHILDREN>( readInt<uint8_t>( ptr, data.dataPos ) );

    for ( ;; )
    {
      attributeSpec spec;
      spec.attribute = static_cast<DW_AT>( LEB128::decode_uleb128( ptr, data.dataPos ) );
      spec.form = static_cast<DW_FORM>( LEB128::decode_uleb128( ptr, data.dataPos ) );

      // 0,0 means no more attribute specs
      if ( !spec.attribute && !spec.form )
      {
        break;
      }
      newEntry.attributesSpecs.push_back( spec );
    }

    m_abbrevEntries.push_back( newEntry );
  }
}