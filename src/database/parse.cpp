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

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <list>
#include <nlohmann/json.hpp>
#include <print>
#include <string>

#include "../include/cli.hpp"
#include "../include/konfig.hpp"
#include "../include/parse.hpp"
#include "../include/project.hpp"

using std::ifstream;
using std::istreambuf_iterator;
using std::list;
using std::map;
using std::string;
using std::filesystem::path;

Parse::Parse () {}

auto
Parse::multi (void) -> list<Konfig>
{
  auto _allConfigs{ repository.allConfigs () };
  list<Konfig> result;

  for (auto konfig : _allConfigs)
    {
      result.push_back (single (konfig));
    }

  return result;
}

auto
Parse::single (path filepath) -> Konfig
{
  Konfig result;
  map<string, list<Project>> _topics;

  auto configParsed = parse_file (contents_of (filepath));
  result.name = { filepath.stem () };

  for (auto &[topic, topics] : configParsed.items ())
    {
      list<Project> projects;
      for (auto project : topics)
        {
          string branch{ "master" };
          if (!project["branch"].is_null ())
            branch = project["branch"];

          auto pkt{ Project (project["name"], project["url"], branch) };

          projects.push_back (pkt);
        }

      _topics[topic] = { projects };
    }

  result.topics = { _topics };
  return result;
}

auto
Parse::parse_file (string jsonString) -> nlohmann::basic_json<>
{
  return nlohmann::json::parse (jsonString);
}

auto
Parse::contents_of (string path_to_file) -> string
{
  ifstream file (path_to_file);
  return { istreambuf_iterator<char> (file), istreambuf_iterator<char>{} };
}

auto
Parse::exist (std::string name) -> bool
{
  for (auto config : multi ())
    if (config.name == name)
      return true;

  // std::for_each (multi ().begin (), multi ().end (),
  //                [name, &result] (Konfig config) {
  //                  std::println ("MEH");
  //                  result = { config.name == name };
  //                  std::println ("FOOL");
  //                });

  return false;
}

// Overload the to_json function for automatic conversion
void
to_json (nlohmann::json &j, const Konfig &k)
{
  j = k.to_json ();
}

auto
Parse::save (std::string name, std::string topic,
             ConfigEntries entries) -> void
{
  // if (entries.name || entries.url.has_value () || !entries.branch.empty ())
  //   {
  //     std::println ("Either name or url of project are missing. Exiting!");
  //     return;
  //   }

  Project project{ entries };

  std::map<std::string, std::list<Project>> topics;
  topics[topic] = { entries };

  Konfig konfig{ name, topics };
  nlohmann::json j = konfig;

  std::println ("Saving config with name {} as \n{}", konfig.name, j.dump ());
}
