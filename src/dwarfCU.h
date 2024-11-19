#ifndef DWARFCU_H
#define DWARFCU_H

#include "dwarpTypes.h"

enum class CU_AddressSize : ubyte
{
  CU_32 = 4,
  CU_64 = 8
};

class dwarfCU
{
public:
  dwarfCU();
  ~dwarfCU();
  void deserialize( dwarfSectionData& data, uint64& offset);

  inline bool is64Bit() const
  {
    return m_is64Bit;
  };

  inline uint64 getAbbrevOffset() const
  {
    return m_is64Bit ? m_header.m_64BitAbbrevOffset : m_header.m_32BitAbbrevOffset;
  }
  
  inline uint64 getAbbrevSize() const
  {
    return m_is64Bit ? m_header.m_64BitSize : m_header.m_32BitSize;
  }

  inline class dwarfAbbr* getAbbr()
  {
    return m_abbr;
  }

protected:
  struct CUHeader
  {
    CUHeader()
      : m_64BitSize( 0 ),
        m_version( 0 ),
        m_64BitAbbrevOffset( 0 ),
        m_addrSize( CU_AddressSize::CU_32 )
    {
    }
    union
    {
      uint32 m_32BitSize;
      uint64 m_64BitSize;
    };

    uint16 m_version;

    union
    {
      uint32 m_32BitAbbrevOffset;
      uint64 m_64BitAbbrevOffset;
    };

    CU_AddressSize m_addrSize;
  } m_header;

  class dwarfAbbr* m_abbr;
  bool m_is64Bit;
};

#endif // DWARFCU_H
