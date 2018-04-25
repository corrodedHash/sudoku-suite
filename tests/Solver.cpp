#include "catch.hpp"
#include "DancingLinks.hpp"
#include <algorithm>
#include <iostream>

TEST_CASE("Solver") {
  DancingLinks::ListBuilder lBuilder;
  lBuilder.insertNode(0, 0);
  lBuilder.insertNode(0, 2);
  lBuilder.insertNode(1, 0);
  lBuilder.insertNode(2, 1);
  lBuilder.insertNode(2, 2);

  DancingLinks::Solver s(lBuilder.finalize());

  while (auto model = s.nextModel()) {
    REQUIRE(model->size() == 2);
    REQUIRE(std::find(model->begin(), model->end(), 1) != model->end());
    REQUIRE(std::find(model->begin(), model->end(), 2) != model->end());
  }
}

TEST_CASE("Big Solver") {
  DancingLinks::ListBuilder lBuilder;
  for (int i = 0; i < 99; ++i) {
    lBuilder.insertNode(i, i);
    lBuilder.insertNode(i, i + 1);
  }
  lBuilder.insertNode(99, 99);

  DancingLinks::Solver s(lBuilder.finalize());

  REQUIRE(s.nextModel());
}

TEST_CASE("List") {
  DancingLinks::ListBuilder lBuilder;

  lBuilder.insertNode(0, 0);
  lBuilder.insertNode(1, 0);
  lBuilder.insertNode(2, 0);

  DancingLinks::List l = lBuilder.finalize();

  std::vector<DancingLinks::Node*> nodes;
  nodes.reserve(3);
  nodes.push_back(l.Header->Right->Down);
  nodes.push_back(nodes.back()->Down);
  nodes.push_back(nodes.back()->Down);
  for (DancingLinks::Node* node : nodes) {
    REQUIRE(node->Column == l.Header->Right);
  }
  REQUIRE(nodes[1]->Up == nodes[0]);
  REQUIRE(nodes[2]->Up == nodes[1]);
  REQUIRE(nodes[2]->Down == nullptr);
}
