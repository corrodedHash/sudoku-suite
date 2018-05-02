#include "Sudoku.hpp"

#include <cassert>

namespace Sudoku {
static int getRowId(int row, int col, int number, int blocksize) {
  int blocksize2P = blocksize * blocksize;
  assert(row >= 0 && row < blocksize2P);
  assert(col >= 0 && col < blocksize2P);
  assert(number >= 0 && number < blocksize2P);
  return number + col * blocksize2P + row * blocksize2P * blocksize2P;
}

static std::tuple<int, int, int> getSudokuPos(DancingLinks::Node* rowIndex,
                                              int blocksize) {
  int blocksize2P = blocksize * blocksize;
  int blocksize4P = blocksize2P * blocksize2P;
  assert(rowIndex->Right->Right->Right->Right == rowIndex);
  DancingLinks::Node* firstEntry = nullptr;
  for (int i = 0; i < 3; ++i) {
    if (rowIndex->Column->Id < blocksize4P) {
      firstEntry = rowIndex;
      break;
    }
    rowIndex = rowIndex->Right;
  }
  assert(firstEntry);
  int columnId = rowIndex->Column->Id;
  int row = columnId / blocksize2P;
  columnId = columnId % blocksize2P;
  int column = blocksize;
  int number = firstEntry->Right->Column->Id % blocksize2P;
  return std::make_tuple(row, column, number);
}

static int
getBlockId(int row, int column, int blocksize) {
  return (row / blocksize) * blocksize + (column / blocksize);
}

std::pair<int, int> static getDancingListSize(int blocksize) {
  return std::make_pair(blocksize * blocksize * blocksize * blocksize *
                            blocksize * blocksize,
                        blocksize * blocksize * blocksize * blocksize * 4);
}

DancingLinks::List
DLHelper::toDancingLinksList(const Field& field) {
  auto [dlHeight, dlWidth] = getDancingListSize(field.getBlocksize());
  DancingLinks::ListBuilder result;
  int hBase = 0;

  int rowId = 0;
  for (int row = 0; row < field.getMaxNumber(); ++row) {
    for (int col = 0; col < field.getMaxNumber(); ++col) {
      for (int number = 0; number < field.getMaxNumber(); ++number) {
        if (field.getCellValue(row, col) == 0 ||
            field.getCellValue(row, col) == number + 1) {
          // Each cell can only have one number
          result.insertNode(rowId, row * field.getMaxNumber() + col);

          // Each row can only have each number once
          result.insertNode(rowId,
                            row * field.getMaxNumber() + number +
                                field.getMaxNumber() * field.getMaxNumber());
          // Each column can only have each number once
          result.insertNode(rowId, col * field.getMaxNumber() + number +
                                       2 * field.getMaxNumber() *
                                           field.getMaxNumber());

          // Each block can only have each number once
          result.insertNode(rowId, getBlockId(row, col, field.getBlocksize()) *
                                           field.getMaxNumber() +
                                       number +
                                       3 * field.getMaxNumber() *
                                           field.getMaxNumber());
          ++rowId;
        }
      }
    }
  }
  result.print();
  return result.finalize();
}

Field
DLHelper::fromDancingLinksList(
    const std::vector<DancingLinks::Node*>& rowIndices, int blocksize) {
  Field field(blocksize);
  for (DancingLinks::Node* entry : rowIndices) {
    auto [cRow, cColumn, cNumber] = getSudokuPos(entry, blocksize);
    field.setCellValue(cColumn, cRow, cNumber);
  }
  return field;
}
} // namespace Sudoku
