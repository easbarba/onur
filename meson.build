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

project(
    'onur',
    'cpp',
    license: 'GNU GPL version 3',
    version: '0.2.0',
    default_options: [ 'cpp_std=c++23', 'warning_level=3' ],
    meson_version: '>=1.4.0',
)

cpp = meson.get_compiler('cpp')
cpp_args = [
    '-Wall',
    '-Werror',
    '-fmodules-ts',
    '-W',
    '-Wextra',
    '-pedantic',
    '-Wno-unused-function',
    '-Wno-unused-but-set-variable',
    '-O0',
    '-g3'
]
# '-fsanitize=address,undefined'

# SHARED
inc_headers = include_directories('src/include')

# PROJECTS
subdir('src')

if get_option('tests')
  subdir('tests')
endif
