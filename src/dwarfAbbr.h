#ifndef DWARFABBR_H
#define DWARFABBR_H

#include "dwarpTypes.h"
#include "dwarfEnum.h"

#include "attributes/dwarfAttribute.h"
#include "utils/LEB128.h"

class dwarfAbbr
{
public:
  dwarfAbbr();
  ~dwarfAbbr();

  void deserialize( dwarfSectionData &data, uint64 abbrevSize, uint64 offset );

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
    std::vector<attributeSpec> attributesSpecs;
  };

  std::vector<AbbrevEntry> m_abbrevEntries;
};

#endif // DWARFABBR_H
