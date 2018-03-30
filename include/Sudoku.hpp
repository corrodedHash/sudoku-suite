#include <pair>

namespace Sudoku {
class Field {
  std::vector<int> Grid;

  const int Blocksize;

  int getIndex(int x, int y);
  std::pair<int, int> getCoord(int index);

public:
  Field(int blocksize);

  const int UnsetValue = 0;
  const int MinNumber = 1;
  int getMaxNumber() const;
  int getBlocksize() const { return Blocksize; };

  int getCellValue(int x, int y) const;
  void setCellValue(int x, int y, int value);

  void print() const;
};

class DLHelper {
private:
  static int getColId(int row, int col, int number, int blocksize);
  static std::tuple<int, int, int> getSudokuPos(int rowIndex, int blocksize);

public:
  static DancingLinks::List toDancingLinksList(const Field& field);
  static Field fromDancingLinksList(const std::vector<int> rowIndices);
};
} // namespace Sudoku
