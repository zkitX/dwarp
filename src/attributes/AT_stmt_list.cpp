#include "AT_stmt_list.h"

bool AT_StmtList::deserialize( ByteBuffer &buffer )
{
  m_stmt_list = DWARFForm::readFORM_sec_offset( buffer );
  return true;
}

std::string AT_StmtList::toString() const
{
  std::stringstream ss;
  ss << "0x" << std::setfill( '0' ) << std::setw( 16 ) << std::hex << m_stmt_list;
  return ss.str();
}