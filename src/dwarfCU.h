#ifndef DWARFCU_H
#define DWARFCU_H

#include "dwarpTypes.h"
#include "utils/byteBuffer.h"

enum CU_AddressSize : ubyte
{
  CU_32 = 4,
  CU_64 = 8
};

class dwarfCU
{
public:
  dwarfCU();
  ~dwarfCU();
  void deserialize( ByteBuffer& buffer, uint64& headerOffset, uint64& nextOffset );
  void parseData( ByteBuffer& buffer );

  inline bool isDWARF64() const
  {
    return m_is64Bit;
  };

  inline uint64 getAbbrevOffset() const
  {
    return m_header.abbrev_offset;
  }
  
  inline uint64 getAbbrevSize() const
  {
    return m_header.unit_length;
  }

  inline class dwarfAbbr* getAbbr()
  {
    return m_abbr;
  }

  inline CU_AddressSize getAddressSize() const
  {
    return m_header.address_size;
  }

protected:
  struct CUHeader
  {
    CUHeader()
      : unit_length( 0 ),
        version( 0 ),
        abbrev_offset( 0 ),
        address_size( CU_AddressSize::CU_32 )
    {
    }
    uint64 unit_length;
    uint16 version;
    uint64 abbrev_offset;
    CU_AddressSize address_size;
  } m_header;

  uint64 m_dieOffset;
  class dwarfAbbr* m_abbr;
  bool m_is64Bit;
};

extern dwarfCU* currentCU;
extern std::vector<dwarfCU*> dwarfCompileUnits;

size_t readCompileUnits();

#endif // DWARFCU_H
