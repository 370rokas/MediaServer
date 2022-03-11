cmake_minimum_required(VERSION 3.21)
project(WuseMediaServer)

#### Configuration

set(BUILD_LOCATION ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_CXX_STANDARD 20)

#### Dependencies

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

#### WuseMediaServer

add_executable(WuseMediaServer src/main.cpp src/Database.cpp)

target_link_libraries(WuseMediaServer ${SQLite3_LIBRARIES})
target_include_directories(WuseMediaServer PRIVATE ${SQLite3_INCLUDE_DIRS})

set_target_properties(WuseMediaServer PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${BUILD_LOCATION}"
        RUNTIME_OUTPUT_DIRECTORY "${BUILD_LOCATION}")