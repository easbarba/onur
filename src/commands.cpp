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
#include <format>
#include <iostream>
#include <ostream>

#include "../include/commands.hpp"

using std::cout;
using std::endl;
using std::format;
using std::filesystem::exists;
using std::filesystem::path;

Commands::Commands () {}

auto
Commands::grab (void) -> void
{
  for (auto single : repository.multi ())
    {
      cout << "\nConfig: " << single.topic << endl;

      for (auto subtopic : single.subtopics)
        {
          cout << "\n  Subtopic: " << subtopic.first << "\n" << endl;
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
        }
    }
}

auto
Commands::backup (void) -> void
{
  cout << "Backing up" << endl;
}

auto
Commands::printProjectInfo (Project project) -> void
{
  auto message{ format ("\tname: {} - url: {} - branch: {}", project.name,
                        project.url, project.branch) };
  cout << message << endl;
}
