#include "dwarfForm.h"

std::string DWARFForm::readFORM_strp(ByteBuffer& buffer, bool isUTF8)
{
  return buffer.readString();
}

std::string DWARFForm::readFORM_string(ByteBuffer& buffer)
{
  return buffer.readString();
}

byte DWARFForm::readFORM_data1(ByteBuffer& buffer)
{
  return buffer.readInt<byte>();
}

uint16 DWARFForm::readFORM_data2(ByteBuffer& buffer)
{
  return buffer.readInt<uint16>();
}

uint32 DWARFForm::readFORM_data4(ByteBuffer& buffer)
{
  return buffer.readInt<uint32>();
}

uint64 DWARFForm::readFORM_data8(ByteBuffer& buffer)
{
  return buffer.readInt<uint64>();
}

uint64 DWARFForm::readFORM_udata(ByteBuffer& buffer)
{
  return buffer.readLEB128<uint64>();
}

int64 DWARFForm::readFORM_sdata(ByteBuffer& buffer)
{
  return buffer.readLEB128<int64>();
}

uint64 DWARFForm::readFORM_addr(ByteBuffer& buffer, CU_AddressSize addressSize)
{
  switch (addressSize)
  {
    case CU_32:
      return buffer.readInt<uint32>();
    case CU_64:
      return buffer.readInt<uint64>();
    default:
      assert(false, "Invalid address size");
      return 0;
  }
}

uint64 DWARFForm::readFORM_sec_offset(ByteBuffer& buffer)
{
  if (currentCU->isDWARF64())
    return buffer.readInt<uint64>();
  else
    return static_cast<uint64>(buffer.readInt<uint32>());
}

int8 DWARFForm::readFORM_flag(ByteBuffer& buffer)
{
  return buffer.readInt<int8>();
}

uint64 DWARFForm::readFORM_constant(ByteBuffer& buffer, DW_FORM form)
{
  uint64 retn;
  switch (form)
  {
    case DW_FORM_data1:
      retn = DWARFForm::readFORM_data1(buffer);
      break;
    case DW_FORM_data2:
      retn = DWARFForm::readFORM_data2(buffer);
      break;
    case DW_FORM_data4:
      retn = DWARFForm::readFORM_data4(buffer);
      break;
    case DW_FORM_data8:
      retn = DWARFForm::readFORM_data8(buffer);
      break;
    case DW_FORM_udata:
      retn = DWARFForm::readFORM_udata(buffer);
      break;
    default:
      retn = 0;
      assert(false, "Invalid form for constant");
      break;
  }
  return retn;
}