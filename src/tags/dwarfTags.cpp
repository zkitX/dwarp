#include "dwarfTags.h"

Tag_Base::Tag_Base( DW_TAG tag )
  : m_tag( tag )
{
}

Tag_Base::~Tag_Base() {}

DW_TAG Tag_Base::getTag() const
{
  return m_tag;
}

const char *Tag_Base::ToString()
{
  switch ( m_tag )
  {
    case DW_TAG_ACCESS_DECLARATION:
      return "DW_TAG_access_declaration";
    case DW_TAG_ARRAY_TYPE:
      return "DW_TAG_array_type";
    case DW_TAG_BASE_TYPE:
      return "DW_TAG_base_type";
    case DW_TAG_CATCH_BLOCK:
      return "DW_TAG_catch_block";
    case DW_TAG_CLASS_TYPE:
      return "DW_TAG_class_type";
    case DW_TAG_COMMON_BLOCK:
      return "DW_TAG_common_block";
    case DW_TAG_COMMON_INCLUSION:
      return "DW_TAG_common_inclusion";
    case DW_TAG_COMPILE_UNIT:
      return "DW_TAG_compile_unit";
    case DW_TAG_CONDITION:
      return "DW_TAG_condition";
    case DW_TAG_CONST_TYPE:
      return "DW_TAG_const_type";
    case DW_TAG_CONSTANT:
      return "DW_TAG_constant";
    case DW_TAG_DWARF_PROCEDURE:
      return "DW_TAG_dwarf_procedure";
    case DW_TAG_ENTRY_POINT:
      return "DW_TAG_entry_point";
    case DW_TAG_ENUMERATION_TYPE:
      return "DW_TAG_enumeration_type";
    case DW_TAG_ENUMERATOR:
      return "DW_TAG_enumerator";
    case DW_TAG_FILE_TYPE:
      return "DW_TAG_file_type";
    case DW_TAG_FORMAL_PARAMETER:
      return "DW_TAG_formal_parameter";
    case DW_TAG_FRIEND:
      return "DW_TAG_friend";
    case DW_TAG_IMPORTED_DECLARATION:
      return "DW_TAG_imported_declaration";
    case DW_TAG_IMPORTED_MODULE:
      return "DW_TAG_imported_module";
    case DW_TAG_IMPORTED_UNIT:
      return "DW_TAG_imported_unit";
    case DW_TAG_INHERITANCE:
      return "DW_TAG_inheritance";
    case DW_TAG_INLINED_SUBROUTINE:
      return "DW_TAG_inlined_subroutine";
    case DW_TAG_INTERFACE_TYPE:
      return "DW_TAG_interface_type";
    case DW_TAG_LABEL:
      return "DW_TAG_label";
    case DW_TAG_LEXICAL_BLOCK:
      return "DW_TAG_lexical_block";
    case DW_TAG_MEMBER:
      return "DW_TAG_member";
    case DW_TAG_MODULE:
      return "DW_TAG_module";
    case DW_TAG_NAMELIST:
      return "DW_TAG_namelist";
    case DW_TAG_NAMELIST_ITEM:
      return "DW_TAG_namelist_item";
    case DW_TAG_NAMESPACE:
      return "DW_TAG_namespace";
    case DW_TAG_PACKED_TYPE:
      return "DW_TAG_packed_type";
    case DW_TAG_PARTIAL_UNIT:
      return "DW_TAG_partial_unit";
    case DW_TAG_POINTER_TYPE:
      return "DW_TAG_pointer_type";
    case DW_TAG_PTR_TO_MEMBER_TYPE:
      return "DW_TAG_ptr_to_member_type";
    case DW_TAG_REFERENCE_TYPE:
      return "DW_TAG_reference_type";
    case DW_TAG_RESTRICT_TYPE:
      return "DW_TAG_restrict_type";
    case DW_TAG_RVALUE_REFERENCE_TYPE:
      return "DW_TAG_rvalue_reference_type";
    case DW_TAG_SET_TYPE:
      return "DW_TAG_set_type";
    case DW_TAG_SHARED_TYPE:
      return "DW_TAG_shared_type";
    case DW_TAG_STRING_TYPE:
      return "DW_TAG_string_type";
    case DW_TAG_STRUCT_TYPE:
      return "DW_TAG_struct_type";
    case DW_TAG_SUBPROGRAM:
      return "DW_TAG_subprogram";
    case DW_TAG_SUBRANGE_TYPE:
      return "DW_TAG_subrange_type";
    case DW_TAG_SUBROUTINE_TYPE:
      return "DW_TAG_subroutine_type";
    case DW_TAG_TEMPLATE_ALIAS:
      return "DW_TAG_template_alias";
    case DW_TAG_TEMPLATE_TYPE_PARAMETRIC:
      return "DW_TAG_template_type_parameter";
    case DW_TAG_TEMPLATE_VALUE_PARAMETRIC:
      return "DW_TAG_template_value_parameter";
    case DW_TAG_THROWN_TYPE:
      return "DW_TAG_thrown_type";
    case DW_TAG_TRY_BLOCK:
      return "DW_TAG_try_block";
    case DW_TAG_TYPEDEF:
      return "DW_TAG_typedef";
    case DW_TAG_TYPE_UNIT:
      return "DW_TAG_type_unit";
    case DW_TAG_UNION_TYPE:
      return "DW_TAG_union_type";
    case DW_TAG_UNSPECIFIED_PARAMETERS:
      return "DW_TAG_unspecified_parameters";
    case DW_TAG_UNSPECIFIED_TYPE:
      return "DW_TAG_unspecified_type";
    case DW_TAG_VARIABLE:
      return "DW_TAG_variable";
    case DW_TAG_VARIANT:
      return "DW_TAG_variant";
    case DW_TAG_VARIANT_PART:
      return "DW_TAG_variant_part";
    case DW_TAG_VOLATILE_TYPE:
      return "DW_TAG_volatile_type";
    case DW_TAG_WITH_STMT:
      return "DW_TAG_with_stmt";
    default:
      return "UNIMPLEMENTED TAG";
  }
}
