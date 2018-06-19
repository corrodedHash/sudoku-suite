#include "DancingLinks/LineIterator.hpp"
#include "DancingLinks/List.hpp"
#include "DancingLinks/ListBuilder.hpp"
#include "DancingLinks/Node.hpp"

#include <catch.hpp>

TEST_CASE("Row excluding iterator") {
  DancingLinks::ListBuilder listBuilder(3, 3);
  listBuilder.insertNode(0, 0);
  listBuilder.insertNode(0, 2);
  listBuilder.insertNode(1, 0);
  listBuilder.insertNode(1, 1);
  listBuilder.insertNode(2, 1);
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

TEST_CASE("Row including Reverse iterator") {
  DancingLinks::ListBuilder listBuilder(3, 3);
  listBuilder.insertNode(0, 0);
  listBuilder.insertNode(0, 2);
  listBuilder.insertNode(1, 0);
  listBuilder.insertNode(1, 1);
  listBuilder.insertNode(2, 1);
  DancingLinks::List list = listBuilder.finalize();
  DancingLinks::RowIncludingView rowView(list.Header->Right->Down);
  auto rowIterator{rowView.rbegin()};
  REQUIRE(rowIterator->Column->Id == 2);
  REQUIRE((*rowIterator).Column->Id == 2);
  REQUIRE((rowIterator++)->Column->Id == 2);
  REQUIRE(++rowIterator == rowView.rend());
}

/*
TEST_CASE("Column excluding iterator") {
  DancingLinks::ListBuilder listBuilder;
  listBuilder.insertNode(0, 0);
  listBuilder.insertNode(0, 2);
  listBuilder.insertNode(1, 0);
  listBuilder.insertNode(1, 1);
  listBuilder.insertNode(2, 1);
  DancingLinks::List list = listBuilder.finalize();
  DancingLinks::ColumnExcludingView colView(list.Header->Right->Down);
  auto colIterator(colView.begin());
  REQUIRE(colIterator->Column->Id == 0);
  REQUIRE((*colIterator).Column->Id == 0);
  REQUIRE((colIterator++)->Column->Id == 0);
  REQUIRE(colIterator == colView.end());

  colView = DancingLinks::ColumnExcludingView(list.Header->Right->Down);
  REQUIRE(++colView.begin() == colView.end());
}

TEST_CASE("Column including Reverse iterator") {
  DancingLinks::ListBuilder listBuilder;
  listBuilder.insertNode(0, 0);
  listBuilder.insertNode(0, 2);
  listBuilder.insertNode(1, 0);
  listBuilder.insertNode(1, 1);
  listBuilder.insertNode(2, 1);
  DancingLinks::List list = listBuilder.finalize();
  DancingLinks::ColumnIncludingView colView(list.Header->Right->Down);
  auto colIterator{colView.rbegin()};
  REQUIRE(colIterator->Column->Id == 0);
  REQUIRE((*colIterator).Column->Id == 0);
  REQUIRE((colIterator++)->Column->Id == 0);
  REQUIRE(++colIterator == colView.rend());
}
*/
