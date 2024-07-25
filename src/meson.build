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

source_files = [
    'main.cpp',
    'common/globals.cpp',
    'database/parse.cpp',
    'database/repository.cpp',
    'domain/konfig.cpp',
    'handlers/commands.cpp',
    'handlers/actions.cpp',
    'handlers/helpers.cpp'
]

cli11_dep = dependency('cli11')
nlohmann_json_dep  = dependency('nlohmann_json')

exe = executable(
    meson.project_name(),
    source_files,
    cpp_args: cpp_args,
    gnu_symbol_visibility: 'default',
    dependencies: [ cli11_dep, nlohmann_json_dep ],
    include_directories: [ inc_headers ],
    install: true,
)

