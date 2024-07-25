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
#include <iostream>

#include "../include/helpers.hpp"

using std::format;

using namespace std;

auto
printProjectInfo (Project project) -> void
{
  std::string::size_type nameLength = 27;
  auto nameTruncated
      = project.name.length () <= nameLength
            ? project.name
            : project.name.substr (0, nameLength).append ("...");
  std::string::size_type urlLength = 60;
  auto urlTruncated = project.url.length () <= urlLength
                          ? project.url
                          : project.url.substr (0, urlLength).append ("...");
  auto message{ format ("{:5}- {:35} {:75} {}", "", nameTruncated,
                        urlTruncated, project.branch) };
  cout << message << endl;
}
