#ifndef DWARFTU_H
#define DWARFTU_H

#include "dwarpTypes.h"
#include "dwarfCU.h"
#include "utils/byteBuffer.h"

class dwarfTU
{
public:
  dwarfTU();
  ~dwarfTU();

  void deserialize(ByteBuffer& buffer, uint64 abbrevSize, uint64 offset);
protected:
  struct TypeUnitHeader
  {
    TypeUnitHeader()
    {
      memset(this, 0, sizeof(TypeUnitHeader));
    }
    uint32 unit_length;
    uint16 version;
    uint64 debug_abbrev_offset;
    ubyte address_size;
    uint64 type_signature;
    uint64 type_offset;
  } m_header;

  bool m_is64Bit;
};

extern std::vector<dwarfTU*> dwarfTypeUnits;

#endif // DWARFTU_H
