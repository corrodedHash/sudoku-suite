#include "DancingLinks.hpp"
#include <map>

namespace DancingLinks {
void Solver::unlinkNode(ListNode* toUnlink) {
  toUnlink->unlink();
  List.unlinkColumn(toUnlink);
  List.unlinkRow(toUnlink);
  for (ListNode* curColumn = toUnlink->Row->Right; curColumn != nullptr;
       curColumn = curColumn->Right) {
    List.unlinkColumn(curColumn);
    for (ListNode* curRow = curColumn->Column->Down; curRow != nullptr;
         curRow = curRow->Down) {
      List.unlinkRow(curRow);
    }
  }
}

void Solver::linkNode(ListNode* toLink) {
  toLink->link();
  List.linkColumn(toLink);
  List.linkRow(toLink);
  for (ListNode* curColumn = toLink->Row->Right; curColumn != nullptr;
       curColumn = curColumn->Right) {
    List.linkColumn(curColumn);
    for (ListNode* curRow = curColumn->Column->Down; curRow != nullptr;
         curRow = curRow->Down) {
      List.linkRow(curRow);
    }
  }
}

ListNode* Solver::get(int id) {
  BaseNode* currentColumn = List.RootColumn;
  while (currentColumn != nullptr) {
    if (currentColumn->getCount() == 0) {
      return nullptr;
    }
    if (currentColumn->getCount() > id) {
      ListNode* currentCell = currentColumn->Down;
      for (int i = 0; i < id; ++i) {
        currentCell = currentCell->Down;
        assert(currentCell != nullptr);
      }
      return currentCell;
    }
    id -= currentColumn->getCount();
    currentColumn = static_cast<BaseNode*>(currentColumn->Right);
  }
  return nullptr;
}

void Solver::backtrack() {
  linkNode(Removed.back());
  TestedId.pop();
  Removed.pop_back();
}
void Solver::deepen(ListNode* node) {
  ++TestedId.top();
  TestedId.push(0);
  Removed.push_back(node);
  unlinkNode(node);
}

bool Solver::checkListEmptyColumn() {
  for (BaseNode* it = List.RootColumn; it != nullptr;
       it = static_cast<BaseNode*>(it->Right)) {
    if (it->getCount() == 0) {
      return true;
    }
  }
  return false;
}

std::optional<std::vector<int>> Solver::nextModel() {
  while (true) {
    if (checkListEmptyColumn()) {
      if (Removed.empty()) {
        return std::nullopt;
      }
      backtrack();
    } else {
      ListNode* next = get(TestedId.top());
      if (next == nullptr) {
        if (Removed.empty()) {
          return std::nullopt;
        }
        backtrack();
      } else {
        deepen(next);
        if (List.isEmpty()) {
          std::vector<int> result;
          result.reserve(Removed.size());
          for (ListNode* node : Removed){
            auto [lRow, lColumn] = List.getCoord(node); 
            result.push_back(lRow);
          } 
          return result;
        }
      }
    }
  }
}
} // namespace DancingLinks
