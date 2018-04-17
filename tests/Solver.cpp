#include "catch.hpp"
#include "DancingLinks.hpp"
#include <algorithm>

TEST_CASE("Solver") {
  auto l = std::make_unique<DancingLinks::List>(3, 3);
  l->insertNode(0, 0);
  l->insertNode(0, 2);
  l->insertNode(1, 0);
  l->insertNode(2, 1);
  l->insertNode(2, 2);

  DancingLinks::Solver s(std::move(l));

  while (auto model = s.nextModel()) {
    REQUIRE(model->size() == 2);
    std::cout << "Model ";
    for (int x : *model) {
      std::cout << x << " ";
    }
    std::cout << '\n';
    REQUIRE(std::find(model->begin(), model->end(), 1) != model->end());
    REQUIRE(std::find(model->begin(), model->end(), 2) != model->end());
  }
}

TEST_CASE("Big Solver") {
  auto l = std::make_unique<DancingLinks::List>(100, 100);
  for (int i = 0; i < 99; ++i) {
    l->insertNode(i, i);
    l->insertNode(i, i + 1);
  }
  l->insertNode(99, 99);

  DancingLinks::Solver s(std::move(l));

  while (auto model = s.nextModel()) {
    std::cout << "Model ";
    for (int x : *model) {
      std::cout << x << " ";
    }
    std::cout << '\n';
  }
}

TEST_CASE("List") {
  DancingLinks::List l(3, 1);

  l.insertNode(0, 0);
  l.insertNode(1, 0);
  l.insertNode(2, 0);

  std::vector<DancingLinks::ListNode*> nodes;
  nodes.reserve(3);
  nodes.push_back(l.getFirstColumn()->Down);
  nodes.push_back(nodes.back()->Down);
  nodes.push_back(nodes.back()->Down);
  for (DancingLinks::ListNode* node : nodes) {
    REQUIRE(node->Column == l.getFirstColumn());
  }
  REQUIRE(nodes[1]->Up == nodes[0]);
  REQUIRE(nodes[2]->Up == nodes[1]);
  REQUIRE(nodes[2]->Down == nullptr);

  nodes[1]->unlink();

  REQUIRE(nodes[0]->Down == nodes[2]);
  REQUIRE(nodes[2]->Up == nodes[0]);
}
