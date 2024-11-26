#ifndef DW_AT_DECL_H
#define DW_AT_DECL_H

#include "AT_base.h"

class AT_Decl_File : public AT_Base
{
public:
  AT_Decl_File( DW_AT attribute, DW_FORM form )
    : AT_Base( attribute, form ) {};
  bool deserialize( ByteBuffer &buffer ) override;

  std::string m_decl_file;
};

class AT_Decl_Line : public AT_Base
{
public:
  AT_Decl_Line( DW_AT attribute, DW_FORM form )
    : AT_Base( attribute, form ) {};
  bool deserialize( ByteBuffer &buffer ) override;

  uint64 m_decl_line;
};

#endif // DW_AT_DECL_H
