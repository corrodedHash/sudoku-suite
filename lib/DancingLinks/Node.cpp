#include "DancingLinks.hpp"

namespace DancingLinks {
  void Node::linkHorizontally(Node* left, Node* right) {
    Right = right;
    Left = left;
    right->Left = this;
    left->Right = this;
  }

  void Node::linkVertically(Node* up, Node* down) {
    Down = down;
    Up = up;
    down->Up = this;
    up->Down = this;
  }
}
