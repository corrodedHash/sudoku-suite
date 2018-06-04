#pragma once
#include "DancingLinks/Node.hpp"

namespace DancingLinks {
class RowExcludingRightIterator {
private:
  Node* StartNode;

public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = Node;
  using pointer = Node*;
  using reference = Node&;
  using difference_type = long;

  RowExcludingRightIterator(Node* node) : StartNode(node->Right) {}

  RowExcludingRightIterator& operator++() {
    StartNode = StartNode->Right;
    return *this;
  }
  RowExcludingRightIterator operator++(int) {
    RowExcludingRightIterator buffer = *this;
    StartNode = StartNode->Right;
    return buffer;
  }

  pointer operator->() const { return StartNode; }
  reference operator*() const { return *StartNode; }

  bool operator==(const RowExcludingRightIterator& other) const {
    return other.StartNode == StartNode;
  }
  bool operator!=(const RowExcludingRightIterator& other) const {
    return !(*this == other);
  }
};

} // namespace DancingLinks

template <>
struct std::iterator_traits<DancingLinks::RowExcludingRightIterator> {
  using iterator_category =
      DancingLinks::RowExcludingRightIterator::iterator_category;
  using value_type = DancingLinks::RowExcludingRightIterator::value_type;
  using pointer = DancingLinks::RowExcludingRightIterator::pointer;
  using reference = DancingLinks::RowExcludingRightIterator::reference;
  using difference_type =
      DancingLinks::RowExcludingRightIterator::difference_type;
};

namespace DancingLinks {
class RowExcludingRightView {
  Node* StartNode;

public:
  RowExcludingRightView(Node* node) : StartNode(node) {}
  RowExcludingRightIterator begin() {
    return RowExcludingRightIterator(StartNode);
  }
  RowExcludingRightIterator end() {
    return RowExcludingRightIterator(StartNode->Left);
  }
};
} // namespace DancingLinks
