#include "Sudoku.hpp"

namespace Sudoku {
int DLHelper::getColId(int row, int col, int number, int blocksize)
{
  int blocksize2P = blocksize * blocksize;
  assert(row >= 0 && row < blocksize2P);
  assert(col >= 0 && col < blocksize2P);
  assert(number >= 0 && number < blocksize2P);
  return number + col * blocksize2P + row * blocksize2P * blocksize2P;
}

std::tuple<int, int, int> DLHelper::getSudokuPos(int rowIndex, int blocksize)
{
  int blocksize2P = blocksize * blocksize;
  int blocksize4P = blocksize2P * blocksize2P;
  int row = rowIndex / (blocksize4P);
  rowIndex = rowIndex % (blocksize4P);
  int column = rowIndex / (blocksize2P);
  rowIndex = rowIndex % (blocksize2P);
  int number = rowIndex;
  assert(row < blocksize2P);
  assert(column < blocksize2P);
  assert(number < blocksize2P);
  return std::make_tuple(row, column, number);
}

DancingLinks::List toDancingLinksList(const Field& field)
{
  DancingLinks::List result(
      field.getMaxNumber() * field.getMaxNumber() * field.getMaxNumber(),
      field.getMaxNumber() * field.getMaxNumber() * 4);

  int hBase = 0;

  // Each cell can only have one number
  for (int row = 0; row < field.getMaxNumber(); ++row) {
    for (int col = 0; col < field.getMaxNumber(); ++col) {
      for (int number = 0; number < field.getMaxNumber(); ++number) {
        if (field.getCellValue(row, col) == 0 || field.getCellValue(row, col) == number + 1) {
          result.insertNode(getColId(row, col, number, field.getBlocksize()), hBase);
        }
      }
      ++hBase;
    }
  }

  // Each row can only have each number once
  for (int row = 0; row < field.getMaxNumber(); ++row) {
    for (int number = 0; number < field.getMaxNumber(); ++number) {
      for (int col = 0; col < field.getMaxNumber(); ++col) {
        if (field.getCellValue(row, col) == 0 || field.getCellValue(row, col) == number + 1) {
          result.insertNode(getColId(row, col, number, field.getBlocksize()), hBase);
        }
      }
      ++hBase;
    }
  }

  // Each column can only have each number once
  for (int col = 0; col < field.getMaxNumber(); ++col) {
    for (int number = 0; number < field.getMaxNumber(); ++number) {
      for (int row = 0; row < field.getMaxNumber(); ++row) {
        if (field.getCellValue(row, col) == 0 || field.getCellValue(row, col) == number + 1) {
          result.insertNode(getColId(row, col, number, field.getBlocksize()), hBase);
        }
      }
      ++hBase;
    }
  }

  // Each block can only have each number once
  for (int blockStartRow = 0; blockStartRow < field.getMaxNumber(); blockStartRow += T)
    for (int blockStartColumn = 0; blockStartColumn < field.getMaxNumber(); blockStartColumn += T)
      for (int number = 0; number < field.getMaxNumber(); ++number) {
        for (int cellStartRow = 0; cellStartRow < T; ++cellStartRow) {
          for (int cellStartColumn = 0; cellStartColumn < T; ++cellStartColumn) {
            if (field.getCellValue(blockStartRow + cellStartRow, blockStartColumn + cellStartColumn) == 0
                || field.getCellValue(blockStartRow + cellStartRow, blockStartColumn + cellStartColumn) == number + 1) {
              result.insertNode(getColId(blockStartRow + cellStartRow, blockStartColumn + cellStartColumn, number, field.getBlocksize()), hBase);
            }
          }
        }
        ++hBase;
      }
  return result;
}
}
