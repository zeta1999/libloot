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

#include "loot/metadata/tag.h"

#include <boost/algorithm/string.hpp>

namespace loot {
Tag::Tag() : addTag_(true) {}

Tag::Tag(const std::string& tag,
         const bool isAddition,
         const std::string& condition) :
    name_(tag),
    addTag_(isAddition),
    ConditionalMetadata(condition) {}

bool Tag::operator<(const Tag& rhs) const {
  if (addTag_ != rhs.addTag_) {
    return addTag_ && !rhs.addTag_;
  }
  
  if (name_ < rhs.name_) {
    return true;
  }

  if (rhs.name_ < name_) {
    return false;
  }
  
  return GetCondition() < rhs.GetCondition();
}

bool Tag::operator==(const Tag& rhs) const {
  return addTag_ == rhs.addTag_ && name_ == rhs.name_ &&
         GetCondition() == rhs.GetCondition();
}

bool Tag::IsAddition() const { return addTag_; }

std::string Tag::GetName() const { return name_; }
}
