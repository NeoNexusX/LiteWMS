cmake_minimum_required(VERSION 3.30)
project(LiteWMS)

set(CMAKE_CXX_STANDARD 20)
set(BUILD ${PROJECT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${BUILD})

find_package(SQLite3 REQUIRED)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)
include_directories(${SQLite3_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(LiteWMS ${SRC})
target_link_libraries(LiteWMS ${SQLite3_LIBRARIES})