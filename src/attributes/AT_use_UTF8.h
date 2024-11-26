#ifndef AT_USE_UTF8_H
#define AT_USE_UTF8_H

#include "AT_base.h"

class AT_Use_UTF8 : public AT_Base
{
public:
  AT_Use_UTF8( DW_AT attribute, DW_FORM form )
    : AT_Base( attribute, form ) {};
  bool deserialize( ByteBuffer &buffer ) override;
  std::string toString() const override;

  bool m_use_utf8;
};

#endif // AT_USE_UTF8_H
