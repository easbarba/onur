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

#include <filesystem>

#include "../include/files.hpp"
#include "../include/globals.hpp"

using std::list;
using std::filesystem::directory_iterator;
using std::filesystem::path;

Files::Files () {}

auto
Files::allConfigs (void) -> list<path>
{
  Globals globals;

  list<path> allConfigs;
  for (auto config : directory_iterator (globals.onurDir))
    {
      if (config.exists () && config.path ().extension () == ".json")
        {
          allConfigs.push_back (config);
        }
    }

  return allConfigs;
}
