#ifndef AT_LANGUAGE_H
#define AT_LANGUAGE_H

#include "AT_base.h"

class AT_Language : public AT_Base
{
public:
  AT_Language( DW_AT attribute, DW_FORM form )
    : AT_Base( attribute, form ) {};
  bool deserialize( ByteBuffer &buffer ) override;
  std::string toString() const override;

  DW_LANG m_language;
};

#endif // AT_LANGUAGE_H
