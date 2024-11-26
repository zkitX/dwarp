#include "dwarfSections.h"

std::unordered_map<std::string, dwarfSectionPtr> dwarfSections;
std::unordered_map<std::string, ByteBuffer> dwarfData;

int findDwarfSections(elfio& reader)
{
  int sectionsFound = 0;
  for ( int i = 0; i < MAX_DWARF_SECTIONS; i++ )
  {
    dwarfSectionPtr data = reader.sections[DWARF_SECTIONS_NAMES[i]];
    if ( data != nullptr )
    {
      dwarfSections[DWARF_SECTIONS_NAMES[i]] = data;
      ++sectionsFound;
    }
  }

  for ( auto &section : dwarfSections )
  {
    std::cout << "Found section: " << section.first << " at offset: " << section.second->get_offset() << std::endl;
  }

  for ( auto &section : dwarfSections )
  {
    const char *name = section.first.c_str();
    const byte *sectionData = reinterpret_cast<const byte *>( section.second->get_data() );
    size_t sectionSize = section.second->get_size();

    std::cout << "Processing section: " << name << std::endl;
    std::cout << "Section size: " << sectionSize << std::endl;

    if ( sectionData == nullptr || sectionSize == 0 )
    {
      std::cerr << "Error: Invalid section data for section " << name << std::endl;
      continue;
    }

    std::vector<byte> buffer( sectionData, sectionData + sectionSize );
    dwarfData.emplace( name, buffer );
  }

  return sectionsFound;
}
