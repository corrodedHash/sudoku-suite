#include "DancingLinks.hpp"
#include "catch.hpp"

SCENARIO("Solving a list", "[Solver]") {
  GIVEN("A puzzle with a single solution") {
    DancingLinks::ListBuilder listBuilder;
    listBuilder.insertNode(0, 0);
    listBuilder.insertNode(0, 2);
    listBuilder.insertNode(1, 1);
    listBuilder.insertNode(1, 2);
    listBuilder.insertNode(2, 1);
    DancingLinks::List list = listBuilder.finalize();
    DancingLinks::Solver listSolver(list);
    WHEN("Solving the first time") {
      auto result = listSolver.nextModel();
      std::vector<int> predictedResult{0, 2};
      THEN("Returns the predicted solution") {
        REQUIRE(result);
        REQUIRE(result->size() == predictedResult.size());
        REQUIRE(std::is_permutation(std::begin(*result), std::end(*result),
                                    std::begin(predictedResult)));
      }
    }
    WHEN("Solving the second time") {
      auto result = listSolver.nextModel();
      THEN("Returns empty solution") { REQUIRE_FALSE(result); }
    }
  }
}
