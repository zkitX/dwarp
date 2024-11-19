#include "dwarfTagArray.h"

bool TAG_Array::IsValidAttr( DW_AT attr )
{
  switch ( attr )
  {
    case DECL:
    case DW_AT_ABSTRACT_ORIGIN:
    case DW_AT_ACCESSIBILITY:
    case DW_AT_ALLOCATED:
    case DW_AT_ASSOCIATED:
    case DW_AT_BIT_SIZE:
    case DW_AT_BIT_STRIDE:
    case DW_AT_BYTE_SIZE:
    case DW_AT_DATA_LOCATION:
    case DW_AT_DECLARATION:
    case DW_AT_DESCRIPTION:
    case DW_AT_NAME:
    case DW_AT_ORDERING:
    case DW_AT_SIBLING:
    case DW_AT_SPECIFICATION:
    case DW_AT_START_SCOPE:
    case DW_AT_TYPE:
    case DW_AT_VISIBILITY:
      return true;
    default:
      return false;
  }
}