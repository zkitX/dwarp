#ifndef DWARPTYPES_H
#define DWARPTYPES_H

#include <elfio/elfio.hpp>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>
#include <sstream>
#include <iomanip>
#include <cstring>   // for memcpy
#include <algorithm> // for std::reverse

using namespace ELFIO;

typedef unsigned char ubyte;
typedef char byte;

typedef unsigned char uint8;
typedef char int8;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned int uint32;
typedef int int32;
typedef long long int64;
typedef unsigned long long uint64;

typedef ELFIO::section *dwarfSectionPtr;
typedef byte *dwarfDataPtr;

enum DW_CHILDREN : ubyte
{
  DW_CHILDREN_no,
  DW_CHILDREN_yes
};

#define assert( cond, msg )          \
  if ( !( cond ) )                   \
  {                                  \
    throw std::runtime_error( msg ); \
  }

extern bool isDWARF64;

#include "utils/byteBuffer.h"

#endif // DWARPTYPES_H
