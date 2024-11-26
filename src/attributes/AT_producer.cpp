#include "AT_producer.h"
#include "AT_utils.h"

bool AT_Producer::deserialize( ByteBuffer &buffer )
{
  m_producer = AT_Utils::readString( buffer, m_spec.form );
  if ( m_producer.empty() )
  {
    return false;
  }
  return true;
}