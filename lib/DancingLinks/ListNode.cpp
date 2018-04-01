#include "DancingLinks.hpp"

namespace DancingLinks {
void ListNode::unregisterNeighbors() {
  if (Left != nullptr) {
    Left->Right = Right;
  }
  if (Right != nullptr) {
    Right->Left = Left;
  }
  if (Up != nullptr) {
    Up->Down = Down;
  }
  if (Down != nullptr) {
    Down->Up = Up;
  }
}

void ListNode::unregisterBase() {
  if (!Unlinked) {
    Column->unregisterNode();
  }
  // Row->unregisterNode();
}

void ListNode::registerNeighbors() {
  if (Left != nullptr) {
    Left->Right = this;
  }
  if (Right != nullptr) {
    Right->Left = this;
  }
  if (Up != nullptr) {
    Up->Down = this;
  }
  if (Down != nullptr) {
    Down->Up = this;
  }
}

void ListNode::registerBase() {
  if (Unlinked) {
    Column->registerNode();
  }
  // Row->registerNode();
}

void ListNode::unlink() {
  unregisterNeighbors();
  unregisterBase();
  Unlinked = true;
}
void ListNode::link() {
  registerNeighbors();
  registerBase();
  Unlinked = false;
}
} // namespace DancingLinks
