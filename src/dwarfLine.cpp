#include "dwarfLine.h"

#include "dwarfEnum.h"
#include "dwarfForm.h"
#include "dwarfSections.h"

std::vector<dwarfLine*> dwarfLines;

dwarfLine::dwarfLine()
  : m_header(),
    m_state(),
    m_skippedStateMachine( false )
{
  m_state.is_stmt = m_header.default_is_stmt;
}

dwarfLine::~dwarfLine() {}

void dwarfLine::advanceAddr( uint64 operationAdvance )
{
  uint8 maxOpsPerInstruction = std::max( m_header.maximum_operations_per_instruction, uint8{ 1 } );

  uint64 addrOffset = ( ( m_state.op_index + operationAdvance ) / maxOpsPerInstruction ) * m_header.minimum_instruction_length;
  m_state.address += addrOffset;
  m_state.op_index = ( m_state.op_index + operationAdvance ) % maxOpsPerInstruction;
}

void dwarfLine::readDirectoryTable5( ByteBuffer &buffer )
{
  // TODO: Implement
}

void dwarfLine::readDirectoryTable4( ByteBuffer &buffer )
{
  while ( true )
  {
    std::string dir = DWARFForm::readFORM_string( buffer );
    if ( dir.empty() )
      break;
    m_directories.push_back( dir );
  }
}

void dwarfLine::readFileTable5( ByteBuffer &buffer )
{
  // TODO: Implement
}

void dwarfLine::readFileTable4( ByteBuffer &buffer )
{
  while ( true )
  {
    LineFile file;
    file.name = DWARFForm::readFORM_string( buffer );
    if ( file.name.empty() )
      break;

    file.directory = buffer.readLEB128<uint64>();
    file.last_modification = buffer.readLEB128<uint64>();
    file.size = buffer.readLEB128<uint64>();
    m_fileNames.push_back( file );
  }
}

void dwarfLine::readHeader( ByteBuffer &buffer )
{
  ::isDWARF64 = false;
  m_header.unit_length = buffer.readInt<uint32>();
  if ( m_header.unit_length == 0xFFFFFFFF )
  {
    ::isDWARF64 = true;
    m_header.unit_length = buffer.readInt<uint64>();
  }

  m_header.version = buffer.readInt<uint16>();
  assert( m_header.version >= 2 && m_header.version <= 5, "Unsupported DWARF version" );

  if ( ::isDWARF64 )
  {
    m_header.header_length = buffer.readInt<uint64>();
  }
  else
  {
    m_header.header_length = buffer.readInt<uint32>();
  }

  m_header.minimum_instruction_length = buffer.readInt<ubyte>();
  if ( m_header.version >= 4 )
  {
    m_header.maximum_operations_per_instruction = buffer.readInt<ubyte>();
  }
  m_header.default_is_stmt = buffer.readInt<ubyte>();
  m_header.line_base = buffer.readInt<byte>();
  m_header.line_range = buffer.readInt<ubyte>();
  m_header.opcode_base = buffer.readInt<ubyte>();

  for ( int i = 1; i < m_header.opcode_base; i++ )
  {
    m_opcodes.push_back( buffer.readInt<ubyte>() );
  }

  if ( m_header.version >= 5 )
  {
    readDirectoryTable5( buffer );
    readFileTable5( buffer );
  }
  else
  {
    // DWARF 2,3,4 directory/file entries
    readDirectoryTable4( buffer );
    readFileTable4( buffer );
  }
}

void dwarfLine::deserialize( ByteBuffer &buffer, bool skipStateMachine )
{
  uint64 startOffset = buffer.Pos();
  readHeader( buffer );

  uint64 currentOffset = buffer.Pos();
  uint64 endOffset = startOffset + m_header.unit_length + ( ::isDWARF64 ? 12 : 4 );

  // skip state machine while keeping the header which contains file and directory tables which are important for parsing the compile units
  if ( skipStateMachine )
  {
    m_skippedStateMachine = true;
    buffer.Seek( endOffset );
    return;
  }
  while ( currentOffset < endOffset )
  {
    uint8 opcode = buffer.readInt<ubyte>();
    if ( opcode == 0 )
    {
      // Extended opcode
      uint64 length = buffer.readLEB128<uint64>();
      uint64 end = buffer.Pos() + length;
      uint8 subOpcode = buffer.readInt<ubyte>();
      switch ( subOpcode )
      {
        case DW_LNE_end_sequence:
        {
          m_state.end_sequence = true;
          m_matrix.push_back( m_state );
          m_state.Reset( m_header.default_is_stmt );
        }
        break;

        case DW_LNE_set_address:
        {
          // infer address size from length
          CU_AddressSize addressSize = static_cast<CU_AddressSize>( length - 1 );
          assert( addressSize == CU_32 || addressSize == CU_64, "Invalid address size" );
          m_state.address = DWARFForm::readFORM_addr( buffer, addressSize );
          m_state.op_index = 0;
        }
        break;

        case DW_LNE_define_file:
        {
          LineFile file;
          file.name = DWARFForm::readFORM_string( buffer );
          file.directory = buffer.readLEB128<uint64>();
          file.last_modification = buffer.readLEB128<uint64>();
          file.size = buffer.readLEB128<uint64>();
          m_fileNames.push_back( file );
        }
        break;

        case DW_LNE_set_discriminator:
        {
          m_state.discriminator = buffer.readLEB128<uint64>();
        }
        break;

        default:
          assert( false, "Invalid extended opcode" );
          break;
      }

      buffer.Seek( end );
    }
    else if ( opcode >= m_header.opcode_base )
    {
      // Special opcode
      opcode -= m_header.opcode_base;
      uint64 addressIncrement = opcode / m_header.line_range;
      uint64 lineIncrement = m_header.line_base + ( opcode % m_header.line_range );
      m_state.address += addressIncrement * m_header.minimum_instruction_length;
      m_state.line += lineIncrement;
      m_state.basic_block = true;
      m_state.prologue_end = false;
      m_state.epilogue_begin = false;
      m_state.end_sequence = false;
      m_state.is_stmt = m_header.default_is_stmt;
    }
    else
    {
      switch ( opcode )
      {
        case DW_LNS_copy:
        {
          m_matrix.push_back( m_state );
          m_state.discriminator = 0;
          m_state.basic_block = false;
          m_state.prologue_end = false;
          m_state.epilogue_begin = false;
        }
        break;

        case DW_LNS_advance_pc:
        {
          uint64 operandAdvance = buffer.readLEB128<uint64>();
          advanceAddr( operandAdvance );
        }
        break;

        case DW_LNS_advance_line:
        {
          int64 lineDelta = buffer.readLEB128<int64>();
          m_state.line += lineDelta;
        }
        break;

        case DW_LNS_set_file:
        {
          int64 fileIndex = buffer.readLEB128<int64>();
          m_state.file = fileIndex;
        }
        break;

        case DW_LNS_set_column:
        {
          m_state.column = buffer.readLEB128<uint64>();
        }
        break;

        case DW_LNS_negate_stmt:
        {
          m_state.is_stmt = !m_state.is_stmt;
        }
        break;

        case DW_LNS_set_basic_block:
        {
          m_state.basic_block = true;
        }
        break;

        case DW_LNS_const_add_pc:
        {
          uint64 operationAdvance = ( 255 - m_header.opcode_base ) / m_header.line_range;
          advanceAddr( operationAdvance );
        }
        break;

        case DW_LNS_fixed_advance_pc:
        {
          uint16 fixedAdvance = buffer.readInt<uint16>();
          m_state.address += fixedAdvance;
          m_state.op_index = 0;
        }
        break;

        case DW_LNS_set_prologue_end:
        {
          m_state.prologue_end = true;
        }
        break;

        case DW_LNS_set_epilogue_begin:
        {
          m_state.epilogue_begin = true;
        }
        break;

        case DW_LNS_set_isa:
        {
          m_state.isa = buffer.readLEB128<uint64>();
        }

        default:
          assert( false, "Invalid opcode" );
          break;
      }
    }
  }
}

size_t dwarfLineParse()
{
  ByteBuffer &debugLineData = dwarfData.at( DEBUG_LINE );
  uint64 sectionSize = debugLineData.Size();

  while ( debugLineData.Pos() < sectionSize )
  {
    dwarfLine *lineToAdd = new dwarfLine();
    // temp skip state machine
    lineToAdd->deserialize( debugLineData, true );

    dwarfLines.push_back( lineToAdd );
  }

  return dwarfLines.size();
}
