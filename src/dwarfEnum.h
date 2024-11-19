#ifndef DWARFTAGENUM_H
#define DWARFTAGENUM_H

#define DWARF_ENUM_BEGIN(name) enum name {
#define DWARF_ENUM_ID(c, v) c = v,
#define DWARF_ENUM_END() };

#include "dwarfEnums.h"

#undef DWARF_ENUM_BEGIN
#undef DWARF_ENUM_ID
#undef DWARF_ENUM_END

#endif // DWARFTAGENUM_H
