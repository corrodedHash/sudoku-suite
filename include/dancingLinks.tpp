
template <int T>
int getColId(int row, int col, int number)
{
  assert(row >= 0 && row < T * T);
  assert(col >= 0 && col < T * T);
  assert(number >= 0 && number < T * T);
  return number + col * T * T + row * T * T * T * T;
}

template <int T>
std::tuple<int, int, int> getSudokuPos(int rowIndex)
{
  int row = rowIndex / (T * T * T * T);
  rowIndex = rowIndex % (T * T * T * T);
  int column = rowIndex / (T * T);
  rowIndex = rowIndex % (T * T);
  int number = rowIndex;
  assert(row < T * T);
  assert(column < T * T);
  assert(number < T * T);
  return std::make_tuple(row, column, number);
}

template <int T>
std::array<std::array<bool, T * T * T * T * 4>, T * T * T * T * T * T> createExactCover()
{
  std::array<std::array<bool, T * T * T * T * 4>, T * T * T * T * T * T> result;
  for (int row = 0; row < result.size(); ++row) {
    for (int column = 0; column < result[0].size(); ++column) {
      result.at(row).at(column) = false;
    }
  }
  int hBase = 0;
  constexpr int maxNum = T * T;

  // Each cell can only have one number
  for (int row = 0; row < maxNum; ++row) {
    for (int col = 0; col < maxNum; ++col) {
      for (int number = 0; number < maxNum; ++number) {
        result[getColId<T>(row, col, number)][hBase] = true;
      }
      ++hBase;
    }
  }

  // Each row can only have each number once
  for (int row = 0; row < maxNum; ++row) {
    for (int number = 0; number < maxNum; ++number) {
      for (int col = 0; col < maxNum; ++col) {
        result[getColId<T>(row, col, number)][hBase] = true;
      }
      ++hBase;
    }
  }

  // Each column can only have each number once
  for (int col = 0; col < maxNum; ++col) {
    for (int number = 0; number < maxNum; ++number) {
      for (int row = 0; row < maxNum; ++row) {
        result[getColId<T>(row, col, number)][hBase] = true;
      }
      ++hBase;
    }
  }

  // Each block can only have each number once
  for (int blockStartRow = 0; blockStartRow < maxNum; blockStartRow += T)
    for (int blockStartColumn = 0; blockStartColumn < maxNum; blockStartColumn += T)
      for (int number = 0; number < maxNum; ++number) {
        for (int cellStartRow = 0; cellStartRow < T; ++cellStartRow) {
          for (int cellStartColumn = 0; cellStartColumn < T; ++cellStartColumn) {
            result[getColId<T>(blockStartRow + cellStartRow, blockStartColumn + cellStartColumn, number)][hBase] = true;
          }
        }
        ++hBase;
      }
  return result;
}

template <int T>
DancingLinks::List toDancingLinksList(std::array<std::array<bool, T * T * T * T * 4>, T * T * T * T * T * T> matrix)
{
  DancingLinks::List result(matrix.size(), matrix[0].size());
  for (int row = 0; row < matrix.size(); ++row) {
    for (int column = 0; column < matrix[0].size(); ++column) {
      if (matrix.at(row).at(column) == true) {
        result.insertNode(row, column);
      }
    }
  }
  return result;
}

template <int T> void drawSudoku(const DancingLinks::Solver& s)
{
  std::map<std::pair<int, int>, int> sudokuField;
  for (auto cell : s.Removed) {
    auto [lRow, lColumn] = s.List.getCoord(cell);
    auto [sRow, sColumn, sNumber] = getSudokuPos<T>(lRow);
    auto [nope, inserted] = sudokuField.insert(std::make_pair(std::make_pair(sRow, sColumn), sNumber));
    std::cout << sudokuField.size() << '\n';
    if (!inserted) {
      std::cout << sRow << " " << sColumn << " " << sNumber << " " << nope->second << '\n';
    }
  }
  for (int column = 0; column < T * T; ++column) {
    for (int row = 0; row < T * T; ++row) {
      assert(sudokuField.count(std::make_pair(row, column)) == 1);
      std::cout << sudokuField[std::make_pair(row, column)] << " ";
    }
    std::cout << '\n';
  }
}
