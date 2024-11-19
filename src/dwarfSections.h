#ifndef DWARFSECTIONS_H
#define DWARFSECTIONS_H

constexpr const char *DEBUG_INFO = ".debug_info";
constexpr const char *DEBUG_ABBREV = ".debug_abbrev";
constexpr const char *DEBUG_LINE = ".debug_line";
constexpr const char *DEBUG_STR = ".debug_str";
constexpr const char *DEBUG_ARANGES = ".debug_aranges";
constexpr const char *DEBUG_PUBNAMES = ".debug_pubnames";
constexpr const char *DEBUG_LOC = ".debug_loc";
constexpr const char *DEBUG_RANGES = ".debug_ranges";
constexpr const char *DEBUG_MACINFO = ".debug_macinfo";
constexpr const char *DEBUG_PUBTYPES = ".debug_pubtypes";
constexpr const char *DEBUG_FRAME = ".debug_frame";

#define MAX_DWARF_SECTIONS 11
constexpr const char *DWARF_SECTIONS_NAMES[MAX_DWARF_SECTIONS] = { DEBUG_INFO,
                                                                   DEBUG_ABBREV,
                                                                   DEBUG_LINE,
                                                                   DEBUG_STR,
                                                                   DEBUG_ARANGES,
                                                                   DEBUG_PUBNAMES,
                                                                   DEBUG_LOC,
                                                                   DEBUG_RANGES,
                                                                   DEBUG_MACINFO,
                                                                   DEBUG_PUBTYPES,
                                                                   DEBUG_FRAME };

#endif // DWARFSECTIONS_H
