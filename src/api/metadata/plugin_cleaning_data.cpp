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

#include "loot/metadata/plugin_cleaning_data.h"

#include "api/game/game.h"
#include "api/helpers/crc.h"
#include "api/helpers/logging.h"

namespace loot {
PluginCleaningData::PluginCleaningData() : crc_(0), itm_(0), ref_(0), nav_(0) {}

PluginCleaningData::PluginCleaningData(uint32_t crc,
                                       const std::string& utility) :
    crc_(crc),
    utility_(utility),
    itm_(0),
    ref_(0),
    nav_(0) {}

PluginCleaningData::PluginCleaningData(uint32_t crc,
                                       const std::string& utility,
                                       const std::vector<MessageContent>& info,
                                       unsigned int itm,
                                       unsigned int ref,
                                       unsigned int nav) :
    crc_(crc),
    itm_(itm),
    ref_(ref),
    nav_(nav),
    utility_(utility),
    info_(info) {}

bool PluginCleaningData::operator<(const PluginCleaningData& rhs) const {
  return crc_ < rhs.GetCRC();
}

bool PluginCleaningData::operator==(const PluginCleaningData& rhs) const {
  return crc_ == rhs.GetCRC();
}

uint32_t PluginCleaningData::GetCRC() const { return crc_; }

unsigned int PluginCleaningData::GetITMCount() const { return itm_; }

unsigned int PluginCleaningData::GetDeletedReferenceCount() const {
  return ref_;
}

unsigned int PluginCleaningData::GetDeletedNavmeshCount() const { return nav_; }

std::string PluginCleaningData::GetCleaningUtility() const { return utility_; }

std::vector<MessageContent> PluginCleaningData::GetInfo() const {
  return info_;
}

MessageContent PluginCleaningData::ChooseInfo(
    const std::string& language) const {
  return MessageContent::Choose(info_, language);
}
}
