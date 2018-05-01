#include "DancingLinks.hpp"
#include "catch.hpp"

SCENARIO("Building A Correct List", "[List]") {
  GIVEN("A constructed list") {
    DancingLinks::ListBuilder listBuilder;
    listBuilder.insertNode(0, 0);
    listBuilder.insertNode(1, 0);
    listBuilder.insertNode(0, 1);
    listBuilder.insertNode(2, 2);

    DancingLinks::List list = listBuilder.finalize();
    WHEN("Nothing is changed") {
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
      list.coverColumn(
          static_cast<DancingLinks::ColumnNode*>(list.Header->Right));
      THEN("Nodes are correct") {
        REQUIRE(list.Header->Right->Right->Right== list.Header);
        REQUIRE(list.Header->Right->Down->Down ==
                list.Header->Right);
        REQUIRE(list.Header->Right->Right->Down->Down ==
                list.Header->Right->Right);
      }
    }
  }
}
