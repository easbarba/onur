#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>
#include "globals.hpp"

#define CONFIG_CATCH_MAIN

Globals globals;

TEST_CASE ("Addition works correctly", "[add]")
{
    REQUIRE (globals.homeDir == "/home/easbarba");
}
