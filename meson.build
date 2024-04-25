project(
    'onur',
    'cpp',
    license: 'GNU GPL version 3',
    version: '0.0.1',
    default_options: [ 'c_std=c++23', 'warning_level=3' ],
    meson_version: '>=1.2.1',
)

cpp_args = [
    '-Wall',
    '-Werror',
    '-fmodules-ts',
    # '-ansi',
    '-W',
    '-Wextra',
    '-pedantic',
    '-Wno-unused-function',
    '-Wno-unused-but-set-variable',
    '-O0',
    '-g3'
    # '-fsanitize=address,undefined'
]

source_files = [
    'src/main.cc',
    'src/commands.cc'
]
headers = include_directories('include')

# =========================== MAIN

cli11_dep = dependency('cli11')
rapidjson_dep = dependency('rapidjson')

exe = executable(
    meson.project_name(),
    source_files,
    cpp_args: cpp_args,
    gnu_symbol_visibility: 'default',
    dependencies: [cli11_dep,rapidjson_dep],
    include_directories: [headers],
    install: true,
)

test('basic', exe)
