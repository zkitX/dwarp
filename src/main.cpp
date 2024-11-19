#include "dwarpTypes.h"
#include "dwarfSections.h"
#include "dwarfCU.h"
#include "dwarfAbbr.h"

using namespace ELFIO;

static std::unordered_map<std::string, dwarfSectionData> dwarfSections;
static std::vector<dwarfCU*> dwarfCompileUnits;
static elfio reader;

int findDwarfSections()
{
  int sectionsFound = 0;
  for ( int i = 0; i < MAX_DWARF_SECTIONS; i++ )
  {
    dwarfSectionPtr data = reader.sections[DWARF_SECTIONS_NAMES[i]];
    if ( data != nullptr )
    {
      dwarfSections[DWARF_SECTIONS_NAMES[i]] = { DWARF_SECTIONS_NAMES[i], data, 0 };
      ++sectionsFound;
    }
  }

  return sectionsFound;
}

void readCompileUnits()
{
  dwarfSectionData debugInfoData = dwarfSections.at( DEBUG_INFO );
  dwarfSectionData abbrRevData = dwarfSections.at(DEBUG_ABBREV);
  uint64 sectionSize = debugInfoData.sectionPtr->get_size();
  uint64 offset = 0;
  while ( offset < sectionSize )
  {
    dwarfCU* unitToAdd = new dwarfCU();
    unitToAdd->deserialize( debugInfoData, offset );
    unitToAdd->getAbbr()->deserialize(abbrRevData, unitToAdd->getAbbrevSize(), unitToAdd->getAbbrevOffset());

    dwarfCompileUnits.push_back( unitToAdd );
  }
}

int main( int argc, char *argv[] )
{
  if ( argc != 2 )
  {
    std::cout << "Usage: dwarp <elf_file>" << std::endl;
    return 1;
  }

  if ( !reader.load( argv[1] ) )
  {
    std::cout << "Can't find or process ELF file " << argv[1] << std::endl;
    return 0;
  }

  int foundSections = findDwarfSections();
  std::cout << "Found a total of " << foundSections << " DWARF sections." << std::endl;
  readCompileUnits();

  std::cout << "Deserialized a total of " << dwarfCompileUnits.size() << " compile units." << std::endl;
  return 1;
}