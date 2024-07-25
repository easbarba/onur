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
#include <iostream>
#include <ostream>

#include "../include/commands.hpp"
#include "../include/globals.hpp"
#include "helpers.hpp"

using std::cout;
using std::endl;
using std::filesystem::exists;
using std::filesystem::path;

Commands::Commands () {}

auto
Commands::grab (void) -> void
{
  for (auto single : parse.multi ())
    {
      cout << "\n " << single.topic << ":" << endl;

      for (auto subtopic : single.subtopics)
        {
          cout << "  + " << subtopic.first << endl;
          for (auto project : subtopic.second)
            {
              auto placeholder{ path (globals.projectsDir / single.topic
                                      / subtopic.first / project.name) };
              auto dirpath{ placeholder };

              printProjectInfo (project);

              if (exists (dirpath / ".git" / "config"))
                actions.pull (dirpath);
              else
                actions.klone (project, dirpath);
            }

          cout << endl;
        }
    }
}

auto
Commands::backup (void) -> void
{
  cout << "Backing up" << endl;
}
