#include "DancingLinks/ListBuilder.hpp"
#include "DancingLinks/RowIterator.hpp"

#include <catch.hpp>
#include <iostream>

TEST_CASE("Node iterator") {
  DancingLinks::ListBuilder listBuilder;
  listBuilder.insertNode(0, 0);
  listBuilder.insertNode(0, 2);
  listBuilder.insertNode(1, 0);
  listBuilder.insertNode(1, 1);
  listBuilder.insertNode(2, 1);
  listBuilder.print(std::cout);
  DancingLinks::List list = listBuilder.finalize();
  DancingLinks::RowExcludingView rowView(list.Header->Right->Down);
  auto rowIterator(rowView.begin());
  REQUIRE(rowIterator->Column->Id == 2);
  REQUIRE((*rowIterator).Column->Id == 2);
  REQUIRE((rowIterator++)->Column->Id == 2);
  REQUIRE(rowIterator == rowView.end());

  rowView = DancingLinks::RowExcludingView(list.Header->Right->Down);
  REQUIRE(++rowView.begin() == rowView.end());
}
