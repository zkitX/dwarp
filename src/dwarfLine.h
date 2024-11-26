#ifndef DWARFLINE_H
#define DWARFLINE_H

#include "dwarpTypes.h"

class dwarfLine
{
public:
  dwarfLine();
  ~dwarfLine();

protected:
  struct LineHeader
  {
    LineHeader()
      : unit_length( 0 ),
        version( 0 ),
        header_length( 0 ),
        minimum_instruction_length( 0 ),
        maximum_operations_per_instruction( 0 ),
        default_is_stmt( 0 ),
        line_base( 0 ),
        line_range( 0 ),
        opcode_base( 0 )
    {
    }

    uint64 unit_length;
    uint16 version;
    uint64 header_length;
    uint8 minimum_instruction_length;
    uint8 maximum_operations_per_instruction;
    uint8 default_is_stmt;
    int8 line_base;
    uint8 line_range;
    uint8 opcode_base;
  } m_header;

  struct LineState
  {
    LineState()
      : address( 0 ),
        op_index( 0 ),
        file( 1 ),
        line( 1 ),
        column( 0 ),
        is_stmt( 0 ),
        basic_block( false ),
        end_sequence( false ),
        prologue_end( false ),
        epilogue_begin( false ),
        isa( 0 ),
        discriminator( 0 )
    {
    }
    void Reset(uint64 default_is_stmt)
    {
      address = 0;
      op_index = 0;
      file = 1;
      line = 1;
      column = 0;
      is_stmt = default_is_stmt;
      basic_block = false;
      end_sequence = false;
      prologue_end = false;
      epilogue_begin = false;
      isa = 0;
      discriminator = 0;
    }

    uint64 address;
    uint64 op_index;
    uint64 file;
    uint64 line;
    uint64 column;
    uint64 is_stmt;
    bool basic_block;
    bool end_sequence;
    bool prologue_end;
    bool epilogue_begin;
    uint64 isa;
    uint64 discriminator;
  } m_state;

  struct LineFile
  {
    LineFile()
      : directory( 0 ),
        last_modification( 0 ),
        size( 0 )
    {
    }
    
    std::string name;
    uint64 directory;
    uint64 last_modification;
    uint64 size;
  };

  bool m_skippedStateMachine;

  std::vector<std::string> m_directories;
  std::vector<LineFile> m_fileNames;
  std::vector<uint8> m_opcodes;

  std::vector<LineState> m_matrix;

protected:
  void advanceAddr( uint64 operationAdvance );

  void readDirectoryTable5( ByteBuffer &buffer );
  void readFileTable5( ByteBuffer &buffer );

  void readDirectoryTable4( ByteBuffer &buffer );
  void readFileTable4( ByteBuffer &buffer );

  void readHeader( ByteBuffer &buffer );

public:
  void deserialize( ByteBuffer &buffer, bool skipStateMachine = false );
};

extern std::vector<dwarfLine*> dwarfLines;

size_t dwarfLineParse();

#endif // DWARFLINE_H
