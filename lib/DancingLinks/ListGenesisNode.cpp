#include "DancingLinks.hpp"

namespace DancingLinks {
void BaseNode::unlink() { unregisterNeighbors(); }

void BaseNode::link() { registerNeighbors(); }

int BaseNode::getCount() const {
  /*
  int sum = 0;
  for (ListNode* node = Down; node != nullptr; node = node->Down) {
    ++sum;
  }
  assert(sum == Count);
  */
  return Count;
}

void BaseNode::unregisterNode() { --Count; }

void BaseNode::registerNode() { ++Count; }
} // namespace DancingLinks
