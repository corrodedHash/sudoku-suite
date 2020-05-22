#pragma once
#include "DancingLinks/List.hpp"
#include "Sudoku/Field.hpp"

#include <vector>

namespace DancingLinks {
struct Node;
} // namespace DancingLinks

namespace Sudoku {
/// @brief Helper functions to translate sudoku to and from dancing links
/// representation
namespace DLHelper {
auto toDancingLinksList(const Field& field) -> DancingLinks::List;
auto fromDancingLinksList(const std::vector<DancingLinks::Node*>& rowIndices,
                           int blocksize) -> Field;
}; // namespace DLHelper
} // namespace Sudoku
