#include "DancingLinks/List.hpp"

#include "DancingLinks/ListBuilder.hpp"
#include "DancingLinks/Node.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <string>

SCENARIO("Using A Correct List", "[List]") {
  GIVEN("A constructed list") {
    DancingLinks::ListBuilder listBuilder(3, 3);
    listBuilder.insertNode(0, 0);
    listBuilder.insertNode(0, 1);
    listBuilder.insertNode(1, 0);
    listBuilder.insertNode(2, 2);

    WHEN("Nothing is changed") {
      DancingLinks::List list = listBuilder.finalize();
      THEN("Nodes are correct") {
        REQUIRE(list.Header->Right->Right->Right->Right == list.Header);
        REQUIRE(list.Header->Right->Down->Down->Down == list.Header->Right);
        REQUIRE(list.Header->Right->Right->Down->Down ==
                list.Header->Right->Right);
        REQUIRE(list.Header->Right->Right->Right->Down->Down ==
                list.Header->Right->Right->Right);
      }
    }
    WHEN("Covering a column") {
      DancingLinks::List list = listBuilder.finalize();
      list.coverColumn(
          static_cast<DancingLinks::ColumnNode*>(list.Header->Right));
      THEN("Nodes are correct") {
        REQUIRE(list.Header->Right->Right->Right == list.Header);
        REQUIRE(list.Header->Right->Down->Down == list.Header->Right);
        REQUIRE(list.Header->Right->Right->Down->Down ==
                list.Header->Right->Right);
      }
    }
    WHEN("Printing the list") {
      std::stringstream list_representation;
      listBuilder.print(list_representation);
      THEN("Presentation is correct") {
        char hitChar = 'X';
        char missChar = ' ';
        std::stringstream expected_representation;
        expected_representation << hitChar;
        expected_representation << hitChar;
        expected_representation << missChar;
        expected_representation << '\n';
        expected_representation << hitChar;
        expected_representation << missChar;
        expected_representation << missChar;
        expected_representation << '\n';
        expected_representation << missChar;
        expected_representation << missChar;
        expected_representation << hitChar;
        expected_representation << '\n';
        REQUIRE(expected_representation.str() == list_representation.str());
      }
    }
  }

  GIVEN("A constructed list with an empty row") {
    DancingLinks::ListBuilder listBuilder(2, 2);
    listBuilder.insertNode(1, 1);
    WHEN("Printing the list") {
      std::stringstream list_representation;
      listBuilder.print(list_representation);
      THEN("Presentation is correct") {
        char hitChar = 'X';
        char missChar = ' ';
        std::stringstream expected_representation;
        expected_representation << missChar;
        expected_representation << missChar;
        expected_representation << '\n';
        expected_representation << missChar;
        expected_representation << hitChar;
        expected_representation << '\n';
        REQUIRE(expected_representation.str() == list_representation.str());
      }
    }
  }
}
