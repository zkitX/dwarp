#ifndef AT_HIGH_PC_H
#define AT_HIGH_PC_H

#include "AT_base.h"

class AT_HighPC : public AT_Base
{
public:
  AT_HighPC( DW_AT attribute, DW_FORM form )
    : AT_Base( attribute, form ) {};
  bool deserialize( ByteBuffer &buffer ) override;
  std::string toString() const override;
  uint64 m_high_pc;
};

#endif // AT_HIGH_PC_H
