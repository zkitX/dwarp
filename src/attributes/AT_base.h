#ifndef AT_BASE_H
#define AT_BASE_H

#include "dwarpTypes.h"
#include "dwarfEnum.h"
#include "dwarfForm.h"
#include "utils/byteBuffer.h"
#include "dwarfSections.h"

class AT_Base
{
public:
  AT_Base( DW_AT attribute, DW_FORM form )
    : m_spec( { attribute, form } ) {};
  virtual ~AT_Base() {};
  virtual bool deserialize( ByteBuffer& buffer ) = 0;
  virtual std::string toString() const
  {
    return "";
  }

protected:
  struct attributeSpec
  {
    attributeSpec()
      : attribute( DW_AT_NULL ),
        form( DW_FORM_null )
    {
    }

    attributeSpec( DW_AT attribute, DW_FORM form )
      : attribute( attribute ),
        form( form )
    {
    }

    DW_AT attribute;
    DW_FORM form;
  } m_spec;
};

#include "AT_name.h"
#include "AT_producer.h"
#include "AT_language.h"
#include "AT_low_pc.h"
#include "AT_high_pc.h"
#include "AT_stmt_list.h"

#endif // AT_BASE_H
