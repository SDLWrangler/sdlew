project(sdlew)

cmake_minimum_required (VERSION 2.6)
if (NOT CMAKE_VERSION VERSION_LESS 2.8.4)
  cmake_policy (SET CMP0017 NEW)
endif()

include(CMakeParseArguments)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
message(STATUS "Project source dir = ${PROJECT_SOURCE_DIR}")
message(STATUS "Project build dir = ${CMAKE_BINARY_DIR}")

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

set(CMAKE_EXE_LINKER_FLAGS "${PLATFORM_LINKFLAGS} -Wl,--version-script=${CMAKE_SOURCE_DIR}/src/sdlew.map")

include_directories(include)

add_library(sdlew src/sdlew.c include/sdlew.h)

add_executable(testsdlew sdlewTest/sdlewTest.c include/sdlew.h)
target_link_libraries(testsdlew sdlew ${CMAKE_DL_LIBS})
