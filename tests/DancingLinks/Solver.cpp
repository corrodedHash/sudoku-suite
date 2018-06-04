#include "DancingLinks/Solver.hpp"

#include "DancingLinks/ListBuilder.hpp"

#include <catch.hpp>

TEST_CASE("Solving a list", "[List][List Solver]") {
  DancingLinks::ListBuilder listBuilder;
  listBuilder.insertNode(0, 0);
  listBuilder.insertNode(0, 2);
  listBuilder.insertNode(1, 0);
  listBuilder.insertNode(1, 1);
  listBuilder.insertNode(2, 1);
  DancingLinks::Solver listSolver(listBuilder.finalize());
  auto result = listSolver.nextModel();
  REQUIRE(result);
  REQUIRE(result->size() == 2);
  result = listSolver.nextModel();
  REQUIRE_FALSE(result);
}
