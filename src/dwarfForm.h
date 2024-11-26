#ifndef DWARFFORM_H
#define DWARFFORM_H

#include "dwarpTypes.h"
#include "dwarfCU.h"
#include "dwarfEnum.h"
#include "utils/byteBuffer.h"

class DWARFForm
{
public:
  static std::string readFORM_strp(ByteBuffer& buffer, bool isUTF8 = true);
  static std::string readFORM_string(ByteBuffer& buffer);
  static byte readFORM_data1(ByteBuffer& buffer);
  static uint16 readFORM_data2(ByteBuffer& buffer);
  static uint32 readFORM_data4(ByteBuffer& buffer);
  static uint64 readFORM_data8(ByteBuffer& buffer);
  static uint64 readFORM_udata(ByteBuffer& buffer);
  static int64 readFORM_sdata(ByteBuffer& buffer);
  static uint64 readFORM_addr(ByteBuffer& buffer, CU_AddressSize addressSize);
  static uint64 readFORM_sec_offset(ByteBuffer& buffer);
  static int8 readFORM_flag(ByteBuffer& buffer);
  static uint64 readFORM_constant(ByteBuffer& buffer, DW_FORM form);
};

#endif // DWARFFORM_H