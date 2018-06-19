#include "Sudoku/DLHelper.hpp"

#include "DancingLinks/ListBuilder.hpp"

#include <cassert>
#include <iostream>
#include <tuple>

namespace Sudoku {

static std::tuple<int, int, int>
getSudokuPos(DancingLinks::Node* rowIndex, int blocksize) {
  int blocksize2P = blocksize * blocksize;
  assert(rowIndex->Right->Right->Right->Right == rowIndex);
  assert(rowIndex->Column->Id < blocksize2P * blocksize2P);

  int row = rowIndex->Column->Id / blocksize2P;
  int column = rowIndex->Column->Id % blocksize2P;
  int number = (rowIndex->Right->Column->Id % blocksize2P) + 1;

  return std::make_tuple(row, column, number);
}

static int
getBlockId(int row, int column, int blocksize) {
  return (row / blocksize) * blocksize + (column / blocksize);
}

static std::pair<int, int>
getDancingListSize(int blocksize) {
  return std::make_pair(blocksize * blocksize * blocksize * blocksize *
                            blocksize * blocksize,
                        blocksize * blocksize * blocksize * blocksize * 4);
}

DancingLinks::List
DLHelper::toDancingLinksList(const Field& field) {
  auto [dlHeight, dlWidth] = getDancingListSize(field.getBlocksize());
  DancingLinks::ListBuilder result(dlHeight, dlWidth);

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
                            col * field.getMaxNumber() + number +
                                field.getMaxNumber() * field.getMaxNumber());

          // Each column can only have each number once
          result.insertNode(rowId, row * field.getMaxNumber() + number +
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
  // result.print(std::cout);
  return result.finalize();
}

Field
DLHelper::fromDancingLinksList(
    const std::vector<DancingLinks::Node*>& rowIndices, int blocksize) {
  Field field(blocksize);
  assert(rowIndices.size() == blocksize * blocksize * blocksize * blocksize);
  for (DancingLinks::Node* entry : rowIndices) {
    auto [cRow, cColumn, cNumber] = getSudokuPos(entry, blocksize);
    field.setCellValue(cColumn, cRow, cNumber);
  }
  assert(field.isSolved());
  assert(field.isCorrect());
  return field;
}
} // namespace Sudoku
