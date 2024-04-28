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

#include "nlohmann/json.hpp"

#include "../include/files.hpp"
#include "../include/konfig.hpp"
#include "../include/project.hpp"
#include "../include/repository.hpp"

std::list<Konfig> multi(void) {
  auto _allConfigs = allConfigs();
  std::list<Konfig> result;

  for (auto konfig : _allConfigs) {
    result.push_back(single(konfig));
  }

  return result;
}

Konfig single(std::filesystem::path filepath) {
  Konfig result;
  std::map<std::string, std::list<Project>> subtopiks;

  auto configParsed = parse_file(contents_of(filepath));
  result.topic = filepath.stem();

  for (auto &[subtopic, subtopics] : configParsed.items()) {
    std::list<Project> projects;
    for (auto projekt : subtopics) {
      std::string branch = "master";
      if (!projekt["branch"].is_null())
        branch = projekt["branch"];

      auto pkt = Project(projekt["name"], projekt["url"], branch);

      projects.push_back(pkt);
    }

    subtopiks[subtopic] = projects;
  }

  result.subtopics = subtopiks;
  return result;
}

nlohmann::basic_json<> parse_file(std::string jsonString) {
  return nlohmann::json::parse(jsonString);
}

std::string contents_of(std::string path_to_file) {
  std::ifstream file(path_to_file);
  return {std::istreambuf_iterator<char>(file),
          std::istreambuf_iterator<char>{}};
}
