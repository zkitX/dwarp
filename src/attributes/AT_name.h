#ifndef AT_NAME_H
#define AT_NAME_H

#include "AT_base.h"

/*
A DW_AT_name attribute whose value is a null-terminated string containing the full or
relative path name of the primary source file from which the compilation unit was derived.
*/
class AT_Name : public AT_Base
{
public:
  AT_Name( DW_AT attribute, DW_FORM form )
    : AT_Base( attribute, form ) {};

  bool deserialize( ByteBuffer &buffer ) override;
  std::string m_name;
};

#endif // AT_NAME_H
