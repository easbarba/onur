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

#include "konfig.hpp"

std::list<Konfig> multi(void);
Konfig single(std::filesystem::path filepath);
nlohmann::basic_json<> parse_file(std::string jsonString);
std::string contents_of(std::string path_to_file);

#endif // REPOSITORY_H_
