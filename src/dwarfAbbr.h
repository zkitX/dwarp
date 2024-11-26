#ifndef DWARFABBR_H
#define DWARFABBR_H

#include "dwarpTypes.h"
#include "dwarfEnum.h"

#include "attributes/AT_base.h"
#include "utils/ByteBuffer.h"

class dwarfAbbr
{
public:
  dwarfAbbr();
  ~dwarfAbbr();

  void deserialize( ByteBuffer &buffer, uint64 abbrevSize, uint64 offset );

protected:
  struct AbbrevEntry
  {
    AbbrevEntry()
      : abbrevCode( 0 ),
        tag( DW_TAG_NULL ),
        hasChildren( DW_CHILDREN_no )
    {
    }

    uint64 abbrevCode;
    DW_TAG tag;
    DW_CHILDREN hasChildren;
    std::vector<AT_Base*> attributesSpecs;
  };

public:
  std::vector<AbbrevEntry> m_abbrevEntries;
};

AT_Base* createAttribute( DW_AT attribute, DW_FORM form );

#endif // DWARFABBR_H
