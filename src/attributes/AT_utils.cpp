#include "AT_utils.h"

  std::string AT_Utils::readString( ByteBuffer &buffer, DW_FORM form )
  {
    if ( form == DW_FORM_strp )
    {
      uint64 strOffset;
      if ( isDWARF64 )
      {
        strOffset = buffer.readInt<uint64>();
      }
      else
      {
        strOffset = buffer.readInt<uint32>();
      }
      dwarfData[DEBUG_STR].Seek( strOffset );
      return DWARFForm::readFORM_strp( dwarfData[DEBUG_STR] );
    }
    else if ( form == DW_FORM_string )
    {
      return DWARFForm::readFORM_string( buffer );
    }
    else
    {
      assert( false, "Invalid form for string" );
      return "";
    }
  }