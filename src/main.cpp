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

#include <string>

#include "CLI/Option.hpp"
#include <CLI/CLI.hpp>

#include "include/commands.hpp"

using std::string;

auto
main (int argc, char *argv[]) -> int
{
  CLI::App app{ "Easily manage multiple FLOSS repositories." };
  argv = { app.ensure_utf8 (argv) };

  string filename{ "default" };
  app.add_option ("-f,--file", filename, "A help string");
  app.set_version_flag ("--version", string ("0.0.1"));

  CLI::App *grab_cmd{ app.add_subcommand ("grab", "grab all projects") };
  CLI::App *backup_cmd{ app.add_subcommand (
      "backup", "compress all selected projects") };
  app.require_subcommand ();

  CLI11_PARSE (app, argc, argv);

  Commands commands;

  if (*grab_cmd)
    {
      commands.grab ();
    }

  if (*backup_cmd)
    {
      commands.backup ();
    }

  return 0;
}
