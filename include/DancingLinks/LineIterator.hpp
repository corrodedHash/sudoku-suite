#pragma once
#include "DancingLinks/Node.hpp"

#include <iterator>

namespace DancingLinks {

/// @brief Iterator which is part of LineView
template <Node* Node::*Next>
class LineIterator {
private:
  Node* StartNode;
  bool JustStarted;

public:
  LineIterator(Node* node, bool justStarted) :
      StartNode(node), JustStarted(justStarted) {}

  LineIterator& operator++() {
    StartNode = StartNode->*Next;
    JustStarted = false;
    return *this;
  }
  LineIterator operator++(int) {
    LineIterator buffer = *this;
    ++(*this);
    return buffer;
  }

  Node* operator->() const { return StartNode; }
  Node& operator*() const { return *StartNode; }

  bool operator==(const LineIterator& other) const {
    return other.StartNode == StartNode && other.JustStarted == JustStarted;
  }
  bool operator!=(const LineIterator& other) const { return !(*this == other); }
};

} // namespace DancingLinks

template <auto A>
struct std::iterator_traits<DancingLinks::LineIterator<A>> {
  using iterator_category = std::forward_iterator_tag;
  using value_type = DancingLinks::Node;
  using pointer = DancingLinks::Node*;
  using reference = DancingLinks::Node&;
  using difference_type = long;
};

namespace DancingLinks {

/// @brief View of row or column of a DancingLinks List
template <Node* Node::*Previous, Node* Node::*Next, bool Excluding>
class LineView {
  Node* StartNode;

public:
  LineView(Node* node) : StartNode(node) {}
  using iterator_type = LineIterator<Next>;
  using reverse_iterator_type = LineIterator<Previous>;

  iterator_type begin() {
    if constexpr (Excluding) {
      return iterator_type(StartNode->*Next, false);
    } else {
      return iterator_type(StartNode, true);
    }
  }
  iterator_type end() { return iterator_type(StartNode, false); }

  reverse_iterator_type rbegin() {
    return reverse_iterator_type(StartNode->*Previous, !Excluding);
  }

  reverse_iterator_type rend() {
    if constexpr (Excluding) {
      return reverse_iterator_type(StartNode, false);
    } else {
      return reverse_iterator_type(StartNode->*Previous, false);
    }
  }
};

using RowExcludingView = LineView<&Node::Left, &Node::Right, true>;
using RowIncludingView = LineView<&Node::Left, &Node::Right, false>;
using ColumnExcludingView = LineView<&Node::Up, &Node::Down, true>;
using ColumnIncludingView = LineView<&Node::Up, &Node::Down, false>;

} // namespace DancingLinks
