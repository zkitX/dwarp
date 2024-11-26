#ifndef AT_LOW_PC_H
#define AT_LOW_PC_H

#include "AT_base.h"

class AT_LowPC : public AT_Base
{
public:
  AT_LowPC( DW_AT attribute, DW_FORM form )
    : AT_Base( attribute, form ) {};
  bool deserialize( ByteBuffer &buffer ) override;
  std::string toString() const override;
  
  uint64 m_low_pc;
};

#endif // AT_LOW_PC_H
