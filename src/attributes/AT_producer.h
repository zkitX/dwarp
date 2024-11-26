#ifndef AT_PRODUCER_H
#define AT_PRODUCER_H

#include "AT_base.h"

/*
A DW_AT_producer attribute whose value is a null-terminated string containing information 
about the compiler that produced the compilation unit. The actual contents of the string will 
be specific to each producer, but should begin with the name of the compiler vendor or some 
other identifying character sequence that should avoid confusion with other producer values. 
*/
class AT_Producer : public AT_Base
{
public:
  AT_Producer( DW_AT attribute, DW_FORM form )
    : AT_Base( attribute, form ) {};
  bool deserialize( ByteBuffer &buffer ) override;
  std::string m_producer;
};

#endif // AT_PRODUCER_H
