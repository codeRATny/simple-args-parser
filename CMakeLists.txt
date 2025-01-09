cmake_minimum_required(VERSION 3.0)

project(SimpleArgsParser)

set(LIBRARY_NAME "argsparser")

option(RELEASE_BUILD "Silence all runtime asserts" OFF)

# Build flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -mavx2 -mno-avx512f -Wall -Werror -Wempty-body -Wredundant-move -pedantic -Wno-gnu -Wno-nested-anon-types -Wno-writable-strings -Wimplicit-fallthrough -Wno-deprecated -O3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -mavx2 -mno-avx512f -Wall -Werror -Wempty-body -pedantic -Wno-gnu -Wno-nested-anon-types -Wno-writable-strings -Wno-deprecated -O3")

if (NO_AUTH_BUILD)
  add_compile_definitions(RELEASE_BUILD)
endif()

# Project sources
file(GLOB_RECURSE LIBRARY_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)

set(SOURCE_DIR_HEADER "")
execute_process(
    COMMAND find ${PROJECT_SOURCE_DIR}/include -type d
    OUTPUT_VARIABLE SOURCE_DIR_HEADER
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
string(REPLACE "\n" ";" SOURCE_DIR_HEADER ${SOURCE_DIR_HEADER})

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SRC})

include_directories(${SOURCE_DIR_HEADER})

add_executable(basic_usage ${PROJECT_SOURCE_DIR}/examples/basic_usage.cpp)
target_link_libraries(basic_usage ${LIBRARY_NAME})

# add_executable(${CMAKE_CURRENT_SOURCE_DIR}/examples/example.cpp shacke_opts)
# target_link_libraries(shacke_opts ${LIBRARY_NAME})
