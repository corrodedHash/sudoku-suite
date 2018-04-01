#include "DancingLinks.hpp"
#include <map>
#include <iomanip>

namespace DancingLinks {
void Solver::assumeRow(ListNode* row) {
  List->unlinkRow(row);
  for (ListNode* curColumn = row->Row->Right; curColumn != nullptr;
       curColumn = curColumn->Right) {
    List->unlinkColumn(curColumn);
    for (ListNode* curRow = curColumn->Column->Down; curRow != nullptr;
         curRow = curRow->Down) {
      List->unlinkRow(curRow);
    }
  }
}

void Solver::resetRow(ListNode* row) {
  List->linkRow(row);
  for (ListNode* curColumn = row->Row->Right; curColumn != nullptr;
       curColumn = curColumn->Right) {
    List->linkColumn(curColumn);
    for (ListNode* curRow = curColumn->Column->Down; curRow != nullptr;
         curRow = curRow->Down) {
      List->linkRow(curRow);
    }
  }
}

bool Solver::backtrack() {
  resetRow(Removed.back());
  CurrentGuessedRow = Removed.back()->Down;
  Removed.pop_back();
  if (Removed.empty() && CurrentGuessedRow == nullptr) {
    return false;
  } else {
    return true;
  }
}

void Solver::deepen(ListNode* node) {
  Removed.push_back(node);
  assumeRow(node);
  CurrentGuessedRow = List->getFirstRow();
}

bool Solver::checkListEmptyColumn() {
  for (BaseNode* it = List->getFirstColumn(); it != nullptr;
       it = static_cast<BaseNode*>(it->Right)) {
    if (it->getCount() == 0) {
      return true;
    }
  }
  return false;
}

std::optional<std::vector<int>> Solver::nextModel() {
  std::vector<ListNode*> lastVec;
  while (true) {
    if (checkListEmptyColumn()) {
      if (!backtrack()) {
        return std::nullopt;
      }
    } else {
      ListNode* next = CurrentGuessedRow;
      if (next == nullptr) {
        if (!backtrack()) {
          return std::nullopt;
        }
      } else {
        deepen(next);
        if (List->isEmpty()) {
          std::vector<int> result;
          result.reserve(Removed.size());
          for (ListNode* node : Removed) {
            auto [lRow, lColumn] = List->getCoord(node);
            result.push_back(lRow);
          }
          return result;
        }
      }
    }
    /*
    int rowCount = 0;
    for (ListNode* x = List->getFirstRow(); x != nullptr; x = x->Down)
      ++rowCount;
    if (rowCount < 40){
      std::cout << Removed.size() << " " << rowCount << '\n';
      //List->print();
    }
    auto oldit = lastVec.begin();
    auto newit = Removed.begin();
    for (; ; ++oldit, ++newit) {
      if (oldit == lastVec.end()){
        assert(newit != Removed.end());
        break;
      }
      if (newit == Removed.end()){
        assert(CurrentGuessedRow == nullptr || CurrentGuessedRow > *oldit);
        break;
      }
      if (*oldit < *newit){
        break;
      }
      assert(*oldit == *newit);
    }
    lastVec = Removed;
    */

  }
}
} // namespace DancingLinks
