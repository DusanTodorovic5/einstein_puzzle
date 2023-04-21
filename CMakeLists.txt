cmake_minimum_required(VERSION 3.0.0)
project(einstein_puzzle C)

include(CTest)
enable_testing()

add_executable(einstein_puzzle main.c defs.h load_file.c conversions.c table_map.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
