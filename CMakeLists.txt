cmake_minimum_required(VERSION 3.2)

# set the project name and version
project(bbeess VERSION 1.0)



# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# search for Storm library
set(storm_DIR "/usr/local/lib/CMake/storm")
find_package(storm REQUIRED)

# Setup testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})


# specify source files
set(SOURCE_FILES examples/storm_pars_api.cc)

# set executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_FILES} ${storm_INCLUDE_DIR} ${storm-parsers_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE storm storm-parsers)

