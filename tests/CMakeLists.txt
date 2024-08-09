# Onur is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Onur is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Onur. If not, see <https://www.gnu.org/licenses/>.

# Include FetchContent module
include(FetchContent)

# Fetch Catch2
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.6.0
)
FetchContent_MakeAvailable(catch2)

# Add test executable
add_executable(onur_tests test_main.cpp test_globals.cpp)

# Link Catch2
target_link_libraries(onur_tests PRIVATE Catch2::Catch2WithMain)

# Include the src/include directory
target_include_directories(onur_tests PRIVATE ${PROJECT_SOURCE_DIR}/src/include)

# Add CTest support
enable_testing()
add_test(NAME MyTests COMMAND onur_tests)
