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
#include <format>
#include <string>

#include "../include/actions.hpp"

using std::format;
using std::string;
using std::system;
using std::filesystem::path;

Actions::Actions () {}

auto
Actions::klone (Project project, path dirpath) -> void
{
  auto finalCommand{ format (
      "git clone --single-branch --depth=1 --quiet {} {}", project.url,
      dirpath.string ()) };
  system (finalCommand.c_str ());
}

auto
Actions::pull (path dirpath) -> void
{
  auto finalCommand{ format ("git -C {}  pull --quiet", dirpath.string ()) };
  system (finalCommand.c_str ());
}
