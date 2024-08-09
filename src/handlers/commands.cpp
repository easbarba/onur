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
#include <optional>
#include <print>
#include <string>

#include "../include/commands.hpp"
#include "helpers.hpp"

using std::filesystem::exists;
using std::filesystem::path;

Commands::Commands () {}

auto
Commands::grab (std::optional<std::string> name) -> void
{
  // if (name.has_value ())
  //   ConfigTopic config{ configTopicNew (name.value ()) };

  for (auto singleConfig : parse.multi ())
    {
      if (name.has_value () && name.value () != singleConfig.name)
        continue;

      std::println ("{}: ", singleConfig.name);

      for (auto topic : singleConfig.topics)
        {
          std::println ("  + {}", topic.first);
          for (auto project : topic.second)
            {
              auto finalpath{ path (globals.projectsDir / singleConfig.name
                                    / topic.first / project.Name ()) };

              printProjectInfo (project);

              if (exists (finalpath / ".git" / "config"))
                actions.pull (finalpath);
              else
                actions.klone (project, finalpath);
            }

          std::println ();
        }
    }
}

auto
Commands::backup (void) -> void
{
  std::println ("Backing up");
}

ConfigTopic
Commands::configTopicNew (std::string &name)
{
  ConfigTopic config;

  if (name.contains ("."))
    {
      config.dot = { true };

      std::size_t dot_positon{ name.find (".") };
      config.name = { name.substr (0, dot_positon) };
      config.topic = { name.substr (dot_positon + 1) };
    }

  return config;
}

auto
Commands::config (std::string name, ConfigEntries entries) -> void
{
  ConfigTopic config{ configTopicNew (name) };

  if (!parse.exist (config.name.value ()))
    {
      std::println ("No configuration by {} found!", config.name.value ());
      return;
    }

  if (name.ends_with ("."))
    {
      printSingleConfig (config, true);
      return;
    }

  if (!config.topic.has_value ())
    {
      printSingleConfig (config);
      return;
    }
  else
    {
      printSingleConfig (config, true);
      return;
    }

  // std::println (
  //     "Please provide a topic and entries to save a new one. Exiting!",
  //     config.name);

  if (!entries.name.has_value () || !entries.url.has_value ())
    {
      std::println ("Enter name and url entries at least. Exiting!");
      return;
    }

  parse.save (config.name.value (), config.topic.value (), entries);
}

auto
foo () -> void
{
  std::print ("Configurations: [");
  // printf (" %s ", config.path ().stem ().c_str ());
  std::println (" ]\n");
}

void
Commands::printSingleConfig (ConfigTopic config, bool onlytopics)
{
  for (auto singleConfig : parse.multi ())
    {
      if (config.name.value () != singleConfig.name)
        continue;

      std::println ("{}:", singleConfig.name);
      for (auto topic : singleConfig.topics)
        {
          if (onlytopics)
            {
              std::print ("  {} ", topic.first);
              continue;
            }

          if (config.topic.has_value ()
              && config.topic.value () != topic.first)
            continue;

          std::println (" + {}", topic.first);

          for (auto project : topic.second)
            printProjectInfo (project);
        }
    }
}
