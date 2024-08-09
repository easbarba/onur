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

#include <cstdio>
#include <filesystem>
#include <fstream>

#include "../include/globals.hpp"
#include "../include/repository.hpp"

using std::list;
using std::filesystem::directory_iterator;
using std::filesystem::path;

Repository::Repository () {}

auto
Repository::allConfigs (void) -> list<path>
{
  list<path> result;
  Globals globals;

  for (auto config : directory_iterator (globals.onurDir))
    {
      if (config.path ().extension () != ".json")
        continue;

      if (config.is_symlink () && !config.exists ())
        continue;

      std::ifstream file (config.path ());
      if (file.peek () == std::ifstream::traits_type::eof ())
        continue;

      result.push_back (config);
    }

  return result;
}
