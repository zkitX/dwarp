#ifndef AT_STMT_LIST_H
#define AT_STMT_LIST_H

#include "AT_base.h"

class AT_StmtList : public AT_Base
{
  public:
    AT_StmtList( DW_AT attribute, DW_FORM form )
      : AT_Base( attribute, form ) {};
    bool deserialize( ByteBuffer &buffer ) override;
    std::string toString() const override;
    
    uint64 m_stmt_list;
};

#endif // AT_STMT_LIST_H
