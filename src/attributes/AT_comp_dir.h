#ifndef AT_COMP_DIR_H
#define AT_COMP_DIR_H

#include "AT_base.h"

class AT_CompDir : public AT_Base
{
public:
  AT_CompDir( DW_AT attribute, DW_FORM form )
    : AT_Base( attribute, form ) {};
  bool deserialize( ByteBuffer &buffer ) override;
  std::string m_comp_dir;
};

#endif // AT_COMP_DIR_H
