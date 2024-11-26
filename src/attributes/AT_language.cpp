#include "AT_language.h"

bool AT_Language::deserialize( ByteBuffer &buffer )
{
  switch ( m_spec.form )
  {
    case DW_FORM_data1:
      m_language = static_cast<DW_LANG>( DWARFForm::readFORM_data1( buffer ) );
      break;
    case DW_FORM_data2:
      m_language = static_cast<DW_LANG>( DWARFForm::readFORM_data2( buffer ) );
      break;
    case DW_FORM_udata:
      m_language = static_cast<DW_LANG>( DWARFForm::readFORM_udata( buffer ) );
    default:
      assert( false, "Invalid form for AT_language" );
  }

  return true;
}

std::string AT_Language::toString() const
{
  switch ( m_language )
  {
    case DW_LANG_C89:
      return "DW_LANG_C89";
    case DW_LANG_C:
      return "DW_LANG_C";
    case DW_LANG_Ada83:
      return "DW_LANG_Ada83";
    case DW_LANG_C_plus_plus:
      return "DW_LANG_C_plus_plus";
    case DW_LANG_Cobol74:
      return "DW_LANG_Cobol74";
    case DW_LANG_Cobol85:
      return "DW_LANG_Cobol85";
    case DW_LANG_Fortran77:
      return "DW_LANG_Fortran77";
    case DW_LANG_Fortran90:
      return "DW_LANG_Fortran90";
    case DW_LANG_Pascal83:
      return "DW_LANG_Pascal83";
    case DW_LANG_Modula2:
      return "DW_LANG_Modula2";
    case DW_LANG_Java:
      return "DW_LANG_Java";
    case DW_LANG_C99:
      return "DW_LANG_C99";
    case DW_LANG_Ada95:
      return "DW_LANG_Ada95";
    case DW_LANG_Fortran95:
      return "DW_LANG_Fortran95";
    case DW_LANG_PLI:
      return "DW_LANG_PLI";
    case DW_LANG_ObjC:
      return "DW_LANG_ObjC";
    case DW_LANG_ObjC_plus_plus:
      return "DW_LANG_ObjC_plus_plus";
    case DW_LANG_UPC:
      return "DW_LANG_UPC";
    default:
      return "DW_LANG_Unknown";
  }
}