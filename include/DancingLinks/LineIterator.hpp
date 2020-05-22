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

  auto operator++() -> LineIterator& {
    StartNode = StartNode->*Next;
    JustStarted = false;
    return *this;
  }
  auto operator++(int) -> LineIterator {
    LineIterator buffer = *this;
    ++(*this);
    return buffer;
  }

  auto operator->() const -> Node* { return StartNode; }
  auto operator*() const -> Node& { return *StartNode; }

  auto operator==(const LineIterator& other) const -> bool {
    return other.StartNode == StartNode && other.JustStarted == JustStarted;
  }
  auto operator!=(const LineIterator& other) const -> bool { return !(*this == other); }
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
template <Node* Node::*Previous, Node* Node::*Next>
class LineView {
  Node* StartNode;

public:
  LineView(Node* node) : StartNode(node) {}
  using iterator_type = LineIterator<Next>;
  using reverse_iterator_type = LineIterator<Previous>;

  auto begin() -> iterator_type { return iterator_type(StartNode->*Next, false); }
  auto end() -> iterator_type { return iterator_type(StartNode, false); }

  auto rbegin() -> reverse_iterator_type {
    return reverse_iterator_type(StartNode->*Previous, false);
  }

  auto rend() -> reverse_iterator_type {
    return reverse_iterator_type(StartNode, false);
  }
};

using RowExcludingView = LineView<&Node::Left, &Node::Right>;
using ColumnExcludingView = LineView<&Node::Up, &Node::Down>;

} // namespace DancingLinks
