#include "AT_decl.h"
#include "AT_utils.h"

bool AT_Decl_File::deserialize( ByteBuffer &buffer )
{
  uint64 fileTableIndex = DWARFForm::readFORM_constant(buffer, m_spec.form);

  if ( fileTableIndex == 0 )
  {
    m_decl_file = "<unknown>";
  }
  else
  {
    //m_decl_file = dwarfData[DEBUG_LINE].getFileName( fileTableIndex );
  }

  return true;
}

bool AT_Decl_Line::deserialize( ByteBuffer &buffer )
{
  return false;
}
