#pragma once
#include "Sudoku/Field.hpp"
#include "DancingLinks/List.hpp"

#include <vector>

namespace Sudoku {
/// @brief Helper functions to translate sudoku to and from dancing links
/// representation
namespace DLHelper {
DancingLinks::List toDancingLinksList(const Field& field);
Field fromDancingLinksList(const std::vector<DancingLinks::Node*>& rowIndices,
                           int blocksize);
}; // namespace DLHelper
} // namespace Sudoku
