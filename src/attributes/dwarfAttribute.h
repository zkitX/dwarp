#ifndef DWARFATTRIBUTE_H
#define DWARFATTRIBUTE_H

#include "dwarpTypes.h"
#include "dwarfEnum.h"

struct attributeSpec
{
  attributeSpec()
    : attribute( DW_AT_NULL ),
      form( DW_FORM_null )
  {
  }

  DW_AT attribute;
  DW_FORM form;
};

class AT_Base
{
public:
  virtual ~AT_Base();

  virtual bool deserialize();

protected:
  DW_AT m_type;
};

#endif // DWARFATTRIBUTE_H
