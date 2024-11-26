#include "AT_low_pc.h"
#include "dwarfCU.h"

bool AT_LowPC::deserialize( ByteBuffer &buffer )
{
  m_low_pc = DWARFForm::readFORM_addr( buffer, currentCU->getAddressSize() );
  return true;
}

std::string AT_LowPC::toString() const
{
  std::stringstream ss;
  ss << "0x" << std::setfill( '0' ) << std::setw( 16 ) << std::hex << m_low_pc;
  return ss.str();
}
