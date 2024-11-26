#include "AT_name.h"
#include "AT_utils.h"

bool AT_Name::deserialize( ByteBuffer &buffer )
{
  m_name = AT_Utils::readString( buffer, m_spec.form );
  if ( m_name.empty() )
  {
    return false;
  }
  return true;
}