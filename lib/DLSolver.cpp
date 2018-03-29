#include "dancingLinks.hpp"
#include <map>

void DancingLinks::Solver::unlinkNode(DancingLinks::ListNode* toUnlink)
{
  toUnlink->unlink();
  List.unlinkColumn(toUnlink);
  List.unlinkRow(toUnlink);
  for (DancingLinks::ListNode* curColumn = toUnlink->Row->Right; curColumn != nullptr; curColumn = curColumn->Right) {
    List.unlinkColumn(curColumn);
    for (DancingLinks::ListNode* curRow = curColumn->Column->Down; curRow != nullptr; curRow = curRow->Down) {
      List.unlinkRow(curRow);
    }
  }
}

void DancingLinks::Solver::linkNode(DancingLinks::ListNode* toLink)
{
  toLink->link();
  List.linkColumn(toLink);
  List.linkRow(toLink);
  for (DancingLinks::ListNode* curColumn = toLink->Row->Right; curColumn != nullptr; curColumn = curColumn->Right) {
    List.linkColumn(curColumn);
    for (DancingLinks::ListNode* curRow = curColumn->Column->Down; curRow != nullptr; curRow = curRow->Down) {
      List.linkRow(curRow);
    }
  }
}

DancingLinks::ListNode* DancingLinks::Solver::get(int id)
{
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

void DancingLinks::Solver::backtrack()
{
  linkNode(Removed.back());
  TestedId.pop();
  Removed.pop_back();
}
void DancingLinks::Solver::deepen(ListNode* node)
{
  ++TestedId.top();
  TestedId.push(0);
  Removed.push_back(node);
  unlinkNode(node);
}

bool DancingLinks::Solver::checkListEmptyColumn()
{
  for (BaseNode* it = List.RootColumn; it != nullptr; it = static_cast<BaseNode*>(it->Right)) {
    if (it->getCount() == 0) {
      return true;
    }
  }
  return false;
}

bool DancingLinks::Solver::nextModel()
{
  while (true) {
    if (checkListEmptyColumn()) {
      if (Removed.empty()) {
        return false;
      }
      backtrack();
    } else {
      ListNode* next = get(TestedId.top());
      if (next == nullptr) {
        if (Removed.empty()) {
          return false;
        }
        backtrack();
      } else {
        deepen(next);
        if (List.isEmpty()) {
          return true;
        }
      }
    }
  }
}
