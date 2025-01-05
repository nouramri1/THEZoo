cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(animal-gpt VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(json)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 871ed52d350214a034f6ef8a3b8f51c5ce1bd400) # The commit hash for 1.9.0. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

# add the executable
add_executable(animal-gpt animal-gpt.cpp)
target_link_libraries(animal-gpt PRIVATE cpr::cpr nlohmann_json::nlohmann_json)
