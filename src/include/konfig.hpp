/*
 * Onur is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Onur is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Onur. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <list>
#include <map>

#include <nlohmann/json.hpp>

#include "project.hpp"

class Konfig
{
public:
  Konfig (std::string &name, std::map<std::string, std::list<Project>> &topics)
      : name (name), topics (topics) {};

  Konfig ();

  std::string name;
  std::map<std::string, std::list<Project>> topics;

  nlohmann::json
  to_json () const
  {
    nlohmann::json j;
    j["name"] = name;
    j["topics"] = nlohmann::json::object ();
    for (const auto &[topic, projects] : topics)
      {
        j["topics"][topic] = nlohmann::json::array ();
        for (const auto &project : projects)
          {
            j["topics"][topic].push_back (project.to_json ());
          }
      }
    return j;
  }
};
