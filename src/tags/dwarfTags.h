#ifndef DWARFTAGS_H
#define DWARFTAGS_H

#include "dwarfEnum.h"
#include "attributes/dwarfAttribute.h"

#define DECL                    \
    DW_AT_DECL_COLUMN:          \
    case DW_AT_DECL_FILE:       \
    case DW_AT_DECL_LINE

class Tag_Base
{
public:
  Tag_Base(DW_TAG tag);
  virtual ~Tag_Base();
  DW_TAG getTag() const;
  virtual bool isValidAttr(DW_AT attr) = 0;
protected:
  DW_TAG m_tag;
  std::vector<AT_Base> attributes;

  const char* ToString();
};

#endif // DWARFTAGS_H
