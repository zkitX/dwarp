#ifndef DWARPTYPES_H
#define DWARPTYPES_H

#include <elfio/elfio.hpp>
#include <vector>
#include <iostream>
#include <unordered_map>

typedef unsigned char ubyte;
typedef char byte;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned int uint32;
typedef int int32;
typedef long long int64;
typedef unsigned long long uint64;

typedef ELFIO::section *dwarfSectionPtr;

enum DW_CHILDREN : ubyte
{
    DW_CHILDREN_no,
    DW_CHILDREN_yes
};

struct dwarfSectionData
{
    const char* name;
    dwarfSectionPtr sectionPtr;
    uint64 dataPos;
};

#define assert(cond, msg)                           \
    if (!(cond))                                    \
    {                                               \
        throw std::runtime_error(msg);              \
    }                                               \

#endif // DWARPTYPES_H
