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

test_sources = [ 'test_main.cpp','test_globals.cpp' ]

catch2_with_main = dependency('catch2-with-main')
catch2 = dependency('catch2')

test_executable = executable(
  'onur_tests',
  test_sources,
  include_directories: [ inc_headers ],
  dependencies: [ catch2_with_main, catch2 ]
)

test('onur_tests', test_executable)
