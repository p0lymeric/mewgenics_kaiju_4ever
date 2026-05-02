cmake_minimum_required(VERSION 3.15)

project(amoeboid)

# Read third-party library CMakeLists
add_subdirectory(lib/Detours EXCLUDE_FROM_ALL)
add_subdirectory(lib/mewjector EXCLUDE_FROM_ALL)

# Read our CMakeLists
add_subdirectory(kaiju_4ever)
# add_subdirectory(cosmic_ooze)
