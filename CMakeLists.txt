cmake_minimum_required(VERSION 3.21)
project(WuseMediaServer)

#### Configuration

option(BUILD_TESTS "Build test programs" OFF)
set(BUILD_LOCATION ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_CXX_STANDARD 20)

#### Dependencies
include(FetchContent)

# ---- GTest
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)
# ---- GTest

# ---- taocpp-json
FetchContent_Declare(
        taocpp
        GIT_REPOSITORY https://github.com/taocpp/json
        GIT_TAG 1.0.0-beta.13
)
FetchContent_MakeAvailable(taocpp)
# ---- taocpp-json

# ---- LUA
FetchContent_Declare(
        lua
        GIT_REPOSITORY https://github.com/walterschell/Lua
)
FetchContent_MakeAvailable(lua)
# ---- LUA

# ---- SQLite3
message(CHECK_START "Looking for SQLite3")

if(WIN32)
set(CMAKE_PREFIX_PATH C:\\sdk\\sqlite-3.30.1)
endif()

find_package(SQLite3 REQUIRED)
if(SQLite3_FOUND)
    message(CHECK_PASS "found")
else()
    message(FATAL_ERROR "Looking for SQLite3 - not found")
endif()
# ---- SQLite3

# ---- IMGUI & SDL
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/Pesc0/imgui-cmake
)
FetchContent_MakeAvailable(imgui)
# ---- IMGUI & SDL

#### WuseMediaServer

set(WuseMediaServer_Sources
        "src/Main.cpp"
        "src/Config.cpp"
        "src/Database/Database.cpp"
        "src/Database/DatabaseControl.cpp"
        "src/GUI/Console.cpp")

add_executable(WuseMediaServer ${WuseMediaServer_Sources})

target_link_libraries(WuseMediaServer ${SQLite3_LIBRARIES} taocpp-json lua_static IMGUI)
target_include_directories(WuseMediaServer PRIVATE ${SQLite3_INCLUDE_DIRS} include/)

set_target_properties(WuseMediaServer PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${BUILD_LOCATION}"
        RUNTIME_OUTPUT_DIRECTORY "${BUILD_LOCATION}")


add_custom_command(TARGET WuseMediaServer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory
        ${BUILD_LOCATION}/Queries/)
add_custom_command(TARGET WuseMediaServer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/Database/Queries/ ${BUILD_LOCATION}/Queries/)

#### Tests

if(BUILD_TESTS)
    enable_testing()
    include(GoogleTest)

    add_subdirectory(tests)
endif()