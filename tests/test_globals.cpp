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

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

int
add (int a, int b)
{
  return a + b;
}

TEST_CASE ("Addition is performed correctly", "[math]")
{
  SECTION ("Positive numbers")
  {
    REQUIRE (add (2, 3) == 5);
    REQUIRE (add (10, 20) == 30);
  }

  SECTION ("Negative numbers")
  {
    REQUIRE (add (-2, -3) == -5);
    REQUIRE (add (-10, -20) == -30);
  }

  SECTION ("Mixed positive and negative")
  {
    REQUIRE (add (-5, 10) == 5);
    REQUIRE (add (5, -10) == -5);
  }
}

TEST_CASE ("Floating point comparisons", "[math]")
{
  REQUIRE_THAT (1.0 / 3.0, Catch::Matchers::WithinAbs (0.33333, 0.00001));
}

SCENARIO ("User registration", "[user]")
{
  GIVEN ("A new user")
  {
    std::string username = "newuser";
    std::string password = "password123";

    WHEN ("The user registers")
    {
      bool registration_result = true; // Simulated registration

      THEN ("The registration should be successful")
      {
        REQUIRE (registration_result);
      }
    }
  }
}

// #include "globals.hpp"

// TEST_CASE ("Addition works correctly", "[add]")
// {
// Globals globals;
// REQUIRE (globals.homeDir == "/home/easbarba");
// }
