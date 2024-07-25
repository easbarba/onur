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
#include <string>

#include <nlohmann/json.hpp>

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
  map<string, list<Project> > subtopiks;

  auto configParsed = parse_file (contents_of (filepath));
  result.topic = { filepath.stem () };

  for (auto &[subtopic, subtopics] : configParsed.items ())
    {
      list<Project> projects;
      for (auto projekt : subtopics)
        {
          string branch{ "master" };
          if (!projekt["branch"].is_null ())
            branch = projekt["branch"];

          auto pkt{ Project (projekt["name"], projekt["url"], branch) };

          projects.push_back (pkt);
        }

      subtopiks[subtopic] = { projects };
    }

  result.subtopics = { subtopiks };
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
