#include "DancingLinks.hpp"
#include "catch.hpp"

#include <iostream>

SCENARIO("Solving a list", "[Solver]") {
  GIVEN("A puzzle with a single solution") {
    DancingLinks::ListBuilder listBuilder;
    listBuilder.insertNode(0, 0);
    listBuilder.insertNode(0, 2);
    listBuilder.insertNode(1, 1);
    listBuilder.insertNode(1, 2);
    listBuilder.insertNode(2, 1);
    DancingLinks::List list = listBuilder.finalize();
    DancingLinks::Solver listSolver(std::move(list));
    WHEN("Solving the first time") {
      auto result = listSolver.nextModel();
      THEN("Returns the predicted solution") {
        REQUIRE(result);
        REQUIRE(result->size() == 2);
      }
    }
    WHEN("Solving the second time") {
      auto result = listSolver.nextModel();
      result = listSolver.nextModel();
      THEN("Returns empty solution") { REQUIRE_FALSE(result); }
    }
  }
}
