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

#ifndef REPOSITORY_H_
#define REPOSITORY_H_

#include <list>
#include <string>

#include <nlohmann/json.hpp>

#include "files.hpp"
#include "konfig.hpp"

class Repository
{
public:
  Repository ();

  Files files;

  auto multi (void) -> std::list<Konfig>;
  auto single (std::filesystem::path filepath) -> Konfig;
  auto parse_file (std::string jsonString) -> nlohmann::basic_json<>;
  auto contents_of (std::string path_to_file) -> std::string;
};

#endif // REPOSITORY_H_
