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

#include "../include/commands.hpp"
#include "../include/repository.hpp"

#include <iostream>
#include <ostream>

void grab(void) {

  for (auto single : multi()) {
    std::cout << "\nConfig: " << single.topic << std::endl;

    for (auto subtopic : single.subtopics) {
      std::cout << "\n  Subtopic: " << subtopic.first << "\n" << std::endl;

      for (auto project : subtopic.second) {
        printProjectInfo(project);
      }
    }
  }
}

void backup(void) { std::cout << "Backing up" << std::endl; }

void printProjectInfo(Project project) {
  std::cout << "    name: " << project.name << " - url: " << project.url
            << " - branch: " << project.branch << std::endl;
}
