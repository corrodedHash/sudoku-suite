#pragma once
#include "DancingLinks/Node.hpp"

namespace DancingLinks {

template <Node* Node::*Next>
class LineIterator{
private:
  Node* StartNode;
  bool JustStarted;

public:
  using iterator = LineIterator;
  using iterator_category = std::forward_iterator_tag;
  using value_type = Node;
  using pointer = Node*;
  using reference = Node&;
  using difference_type = long;

  LineIterator(Node* node, bool justStarted) :
      StartNode(node), JustStarted(justStarted) {}

  iterator& operator++() {
    StartNode = StartNode->*Next;
    JustStarted = false;
    return *this;
  }
  iterator operator++(int) {
    iterator buffer = *this;
    ++(*this);
    return buffer;
  }

  pointer operator->() const { return StartNode; }
  reference operator*() const { return *StartNode; }

  bool operator==(const iterator& other) const {
    return other.StartNode == StartNode && other.JustStarted == JustStarted;
  }
  bool operator!=(const iterator& other) const { return !(*this == other); }
};

using RowIterator = LineIterator<&Node::Right>;
using ColumnIterator = LineIterator<&Node::Down>;

} // namespace DancingLinks

template <auto A>
struct std::iterator_traits<DancingLinks::LineIterator<A>> {
  using iterator_name = typename DancingLinks::LineIterator<A>;
  using iterator_category = typename iterator_name::iterator_category;
  using value_type = typename iterator_name::value_type;
  using pointer = typename iterator_name::pointer;
  using reference = typename iterator_name::reference;
  using difference_type = typename iterator_name::difference_type;
};

namespace DancingLinks {
template <Node* Node::*Previous, Node* Node::*Next, bool Excluding>
class LineView {
  Node* StartNode;

public:
  LineView(Node* node) : StartNode(node) {}
  using iterator_type = LineIterator<Next>;

  iterator_type begin() {
    if constexpr (Excluding) {
      return iterator_type(StartNode->*Next, false);
    } else {
      return iterator_type(StartNode, true);
    }
  }
  iterator_type end() { return iterator_type(StartNode, false); }
};

using RowExcludingView = LineView<&Node::Left, &Node::Right, true>;
using RowIncludingView = LineView<&Node::Left, &Node::Right, false>;
using ColumnExcludingView = LineView<&Node::Up, &Node::Down, true>; 
using ColumnIncludingView = LineView<&Node::Up, &Node::Down, false>; 

} // namespace DancingLinks
