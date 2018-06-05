#pragma once
#include "DancingLinks/Node.hpp"

namespace DancingLinks {
template <Node* Node::*Next, bool Excluding>
class LineIteratorImpl;

template <Node* Node::*Next>
class LineIteratorImpl<Next, true> {
private:
  Node* StartNode;

public:
  using iterator = LineIteratorImpl<Next, true>;
  using iterator_category = std::forward_iterator_tag;
  using value_type = Node;
  using pointer = Node*;
  using reference = Node&;
  using difference_type = long;

  LineIteratorImpl(Node* node) : StartNode(node->*Next) {}

  iterator& operator++() {
    StartNode = StartNode->*Next;
    return *this;
  }
  iterator operator++(int) {
    iterator buffer = *this;
    StartNode = StartNode->*Next;
    return buffer;
  }

  pointer operator->() const { return StartNode; }
  reference operator*() const { return *StartNode; }

  bool operator==(const iterator& other) const {
    return other.StartNode == StartNode;
  }
  bool operator!=(const iterator& other) const { return !(*this == other); }
};

using RowExcludingRightIterator = LineIteratorImpl<&Node::Right, true>;
using ColumnExcludingDownIterator = LineIteratorImpl<&Node::Down, true>;

} // namespace DancingLinks

template <auto A, auto B>
struct std::iterator_traits<DancingLinks::LineIteratorImpl<A, B>> {
  using iterator_category =
      typename DancingLinks::LineIteratorImpl<A, B>::iterator_category;
  using value_type = typename DancingLinks::LineIteratorImpl<A, B>::value_type;
  using pointer = typename DancingLinks::LineIteratorImpl<A, B>::pointer;
  using reference = typename DancingLinks::LineIteratorImpl<A, B>::reference;
  using difference_type =
      typename DancingLinks::LineIteratorImpl<A, B>::difference_type;
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
