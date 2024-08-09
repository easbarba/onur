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

#include <optional>
#include <string>

#include "CLI/Option.hpp"
#include <CLI/CLI.hpp>

#include "include/cli.hpp"
#include "include/commands.hpp"

using std::string;

auto
main (int argc, char *argv[]) -> int
{
  CLI::App app{ "Easily manage multiple FLOSS repositories." };
  app.require_subcommand (1);
  argv = { app.ensure_utf8 (argv) };
  app.set_version_flag ("--version", string ("0.2.0"));

  // COMMANDS

  CLI::App *grab_cmd{ app.add_subcommand ("grab", "grab all projects") };
  std::optional<std::string> grab_name;
  grab_cmd->add_option ("config", grab_name, "Config name");

  CLI::App *backup_cmd{ app.add_subcommand (
      "backup", "compress all selected projects") };

  CLI::App *config_cmd{ app.add_subcommand ("config",
                                            "manage configurations") };
  std::string config_entries;
  ConfigEntries config;
  config_cmd
      ->add_option ("config", config_entries, "Configuration name and topic")
      ->required (true);
  config_cmd->add_option ("name", config.name, "Project name");
  config_cmd->add_option ("url", config.url, "Project url");
  config_cmd->add_option ("branch", config.branch, "Project branch");

  // PARSE
  CLI11_PARSE (app, argc, argv);

  // BEGIN
  Commands commands;

  if (*grab_cmd)
    commands.grab (grab_name);

  if (*backup_cmd)
    commands.backup ();

  if (*config_cmd)
    commands.config (config_entries, config);

  return 0;
}
