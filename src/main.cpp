#include "dwarpTypes.h"
#include "dwarfSections.h"
#include "dwarfCU.h"
#include "dwarfAbbr.h"
#include "dwarfTU.h"
#include "dwarfLine.h"
#include "utils/byteBuffer.h"

static elfio reader;

bool isDWARF64;

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

  for ( int i = 0; i < reader.sections.size(); i++ )
  {
    std::cout << "Section " << i << ": " << reader.sections[i]->get_name() << std::endl;
  }

  int foundSections = findDwarfSections(reader);
  std::cout << "Found a total of " << foundSections << " DWARF sections." << std::endl;

  size_t totalLineUnits = dwarfLineParse();
  std::cout << "Deserialized a total of " << totalLineUnits << " line units." << std::endl;
  size_t totalCompileUnits = readCompileUnits();
  std::cout << "Deserialized a total of " << totalCompileUnits << " compile units." << std::endl;

  return 1;
}