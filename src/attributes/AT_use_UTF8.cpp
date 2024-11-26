#include "AT_use_UTF8.h"

bool AT_Use_UTF8::deserialize( ByteBuffer &buffer )
{
  m_use_utf8 = DWARFForm::readFORM_flag( buffer );
  return true;
}

std::string AT_Use_UTF8::toString() const
{
  return m_use_utf8 ? "true" : "false";
}