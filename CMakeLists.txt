cmake_minimum_required(VERSION 3.0)

project(SimpleArgsParser)

set(LIBRARY_NAME "argsparser")
set(EXECUTABLE_OUTPUT_PATH "examples")

option(BUILD_WITHOUT_ASSERTS "Silence all runtime asserts"     OFF)
option(BUILD_EXAMPLES        "Build examples of library usage" ON )

# Build flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror -Wempty-body -Wredundant-move -pedantic -Wimplicit-fallthrough")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror -Wempty-body -pedantic -Wno-nested-anon-types")

if (BUILD_WITHOUT_ASSERTS)
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

if (BUILD_EXAMPLES)
  file(GLOB_RECURSE APPS_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp)

  foreach(FILE ${APPS_LIST})
      string(REPLACE "/" " " FILE_STRINGS ${FILE})
      separate_arguments(FILE_STRINGS)

      list(GET FILE_STRINGS -1 EXECUTABLE_FILE_NAME)

      string(REPLACE "." " " EXECUTABLE_STRINGS ${EXECUTABLE_FILE_NAME})
      separate_arguments(EXECUTABLE_STRINGS)
      list(GET EXECUTABLE_STRINGS 0 EXECUTABLE_NAME)

      add_executable(${EXECUTABLE_NAME} ${FILE})

      target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_NAME})
      target_link_libraries(${EXECUTABLE_NAME} ${TARGET_NAME} "-rdynamic")

      message("-- Compile example: ${EXECUTABLE_NAME}")
  endforeach()
endif()