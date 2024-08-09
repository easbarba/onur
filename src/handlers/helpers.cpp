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

#include <format>
#include <print>

#include "../include/helpers.hpp"

using namespace std;

auto
printProjectInfo (Project project) -> void
{
  std::string::size_type nameLength = 27;
  auto nameTruncated
      = project.Name ().length () <= nameLength
            ? project.Name ()
            : project.Name ().substr (0, nameLength).append ("...");
  std::string::size_type urlLength = 60;
  auto urlTruncated
      = project.Url ().length () <= urlLength
            ? project.Url ()
            : project.Url ().substr (0, urlLength).append ("...");
  std::println ("{:3}- {:35} {:75} {}", "", nameTruncated, urlTruncated,
                project.Branch ());
}
