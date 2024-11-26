#include "AT_high_pc.h"
#include "dwarfCU.h"

bool AT_HighPC::deserialize( ByteBuffer &buffer )
{
  m_high_pc = DWARFForm::readFORM_addr( buffer, currentCU->getAddressSize() );
  return true;
}

std::string AT_HighPC::toString() const
{
  std::stringstream ss;
  ss << "0x" << std::setfill( '0' ) << std::setw( 16 ) << std::hex << m_high_pc;
  return ss.str();
}