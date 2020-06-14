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
#ifndef LOOT_YAML_PLUGIN_METADATA
#define LOOT_YAML_PLUGIN_METADATA

#define YAML_CPP_SUPPORT_MERGE_KEYS

#include <cstdint>
#include <list>
#include <regex>
#include <set>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "loot/metadata/plugin_metadata.h"

#include "api/metadata/yaml/file.h"
#include "api/metadata/yaml/location.h"
#include "api/metadata/yaml/message.h"
#include "api/metadata/yaml/message_content.h"
#include "api/metadata/yaml/plugin_cleaning_data.h"
#include "api/metadata/yaml/set.h"
#include "api/metadata/yaml/tag.h"

namespace YAML {
template<>
struct convert<loot::PluginMetadata> {
  static Node encode(const loot::PluginMetadata& rhs) {
    Node node;
    node["name"] = rhs.GetName();

    if (rhs.GetGroup())
      node["group"] = rhs.GetGroup().value();

    if (!rhs.GetLoadAfterFiles().empty())
      node["after"] = rhs.GetLoadAfterFiles();
    if (!rhs.GetRequirements().empty())
      node["req"] = rhs.GetRequirements();
    if (!rhs.GetIncompatibilities().empty())
      node["inc"] = rhs.GetIncompatibilities();
    if (!rhs.GetMessages().empty())
      node["msg"] = rhs.GetMessages();
    if (!rhs.GetTags().empty())
      node["tag"] = rhs.GetTags();
    if (!rhs.GetDirtyInfo().empty())
      node["dirty"] = rhs.GetDirtyInfo();
    if (!rhs.GetCleanInfo().empty())
      node["clean"] = rhs.GetCleanInfo();
    if (!rhs.GetLocations().empty())
      node["url"] = rhs.GetLocations();

    return node;
  }

  static bool decode(const Node& node, loot::PluginMetadata& rhs) {
    if (!node.IsMap())
      throw RepresentationException(
          node.Mark(),
          "bad conversion: 'plugin metadata' object must be a map");
    if (!node["name"])
      throw RepresentationException(
          node.Mark(),
          "bad conversion: 'name' key missing from 'plugin metadata' object");

    rhs = loot::PluginMetadata(node["name"].as<std::string>());

    // Test for valid regex.
    if (rhs.IsRegexPlugin()) {
      try {
        std::regex(rhs.GetName(), std::regex::ECMAScript | std::regex::icase);
      } catch (std::regex_error& e) {
        throw RepresentationException(
            node.Mark(),
            std::string("bad conversion: invalid regex in 'name' key: ") +
                e.what());
      }
    }

    if (node["group"])
      rhs.SetGroup(node["group"].as<std::string>());

    if (node["after"])
      rhs.SetLoadAfterFiles(node["after"].as<std::set<loot::File>>());
    if (node["req"])
      rhs.SetRequirements(node["req"].as<std::set<loot::File>>());
    if (node["inc"])
      rhs.SetIncompatibilities(node["inc"].as<std::set<loot::File>>());
    if (node["msg"])
      rhs.SetMessages(node["msg"].as<std::vector<loot::Message>>());
    if (node["tag"])
      rhs.SetTags(node["tag"].as<std::set<loot::Tag>>());
    if (node["dirty"]) {
      rhs.SetDirtyInfo(
          node["dirty"].as<std::set<loot::PluginCleaningData>>());
    }
    if (node["clean"]) {
       rhs.SetCleanInfo(
          node["clean"].as<std::set<loot::PluginCleaningData>>());
    }
    if (node["url"])
      rhs.SetLocations(node["url"].as<std::set<loot::Location>>());

    return true;
  }
};

inline Emitter& operator<<(Emitter& out, const loot::PluginMetadata& rhs) {
  if (!rhs.HasNameOnly()) {
    out << BeginMap << Key << "name" << Value << YAML::SingleQuoted
        << rhs.GetName();

    if (rhs.GetGroup())
      out << Key << "group" << Value << YAML::SingleQuoted << rhs.GetGroup().value();

    if (!rhs.GetLoadAfterFiles().empty())
      out << Key << "after" << Value << rhs.GetLoadAfterFiles();

    if (!rhs.GetRequirements().empty())
      out << Key << "req" << Value << rhs.GetRequirements();

    if (!rhs.GetIncompatibilities().empty())
      out << Key << "inc" << Value << rhs.GetIncompatibilities();

    if (!rhs.GetMessages().empty())
      out << Key << "msg" << Value << rhs.GetMessages();

    if (!rhs.GetTags().empty())
      out << Key << "tag" << Value << rhs.GetTags();

    if (!rhs.GetDirtyInfo().empty())
      out << Key << "dirty" << Value << rhs.GetDirtyInfo();

    if (!rhs.GetCleanInfo().empty())
      out << Key << "clean" << Value << rhs.GetCleanInfo();

    if (!rhs.GetLocations().empty())
      out << Key << "url" << Value << rhs.GetLocations();

    out << EndMap;
  }

  return out;
}
}

#endif
