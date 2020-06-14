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

#include "loot/metadata/location.h"

namespace loot {
Location::Location() {}

Location::Location(const std::string& url, const std::string& name) :
    url_(url),
    name_(name) {}

bool Location::operator<(const Location& rhs) const {
  if (url_ < rhs.url_) {
    return true;
  }

  if (rhs.url_ < url_) {
    return false;
  }

  return name_ < rhs.name_;
}

bool Location::operator==(const Location& rhs) const {
  return url_ == rhs.url_ && name_ == rhs.name_;
}

std::string Location::GetURL() const { return url_; }

std::string Location::GetName() const { return name_; }
}
