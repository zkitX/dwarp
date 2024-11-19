#ifndef DWARFTAGARRAY_H
#define DWARFTAGARRAY_H

#include "tags/dwarfTags.h"

class TAG_Array : Tag_Base
{
public:
    TAG_Array();
    virtual ~TAG_Array();
    
    virtual bool IsValidAttr(DW_AT attr);
protected:
};

#endif // DWARFTAGARRAY_H
