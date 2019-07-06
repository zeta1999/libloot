/*  LOOT

    A load order optimisation tool for Oblivion, Skyrim, Fallout 3 and
    Fallout: New Vegas.

    Copyright (C) 2012-2016    WrinklyNinja

    This file is part of LOOT.

    LOOT is free software: you can redistribute
    it and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    LOOT is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with LOOT.  If not, see
    <https://www.gnu.org/licenses/>.
    */
#ifndef LOOT_LOAD_ORDER_GRAPH
#define LOOT_LOAD_ORDER_GRAPH

#include <string>
#include <vector>

#include "loot/enum/edge_type.h"

namespace loot {
/** @brief An edge in a load order constraints graph. */
struct LoadOrderEdge {
    /** @brief The type of load order constraint responsible for this edge. */
    EdgeType edgeType;

    /** @brief The index in the graph vertices vector of the plugin that this
     * edge goes from, i.e. the earlier plugin. */
    size_t sourceIndex;

    /** @brief The index in the graph vertices vector of the plugin that this
     * edge goes to, i.e. the later plugin. */
    size_t targetIndex;
};

/** @brief A directed graph representing plugin load order constraints. */
struct LoadOrderGraph {
  /** @brief The graph vertices, which are plugin filenames. */
  std::vector<std::string> vertices;

  /** @brief The graph edges, representing the constraints between plugin pairs. */
  std::vector<LoadOrderEdge> edges;
};
}

#endif
