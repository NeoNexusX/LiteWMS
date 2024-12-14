cmake_minimum_required(VERSION 3.27)
project(LiteWMS)

set(CMAKE_SYSTEM_VERSION 10.0.18362.0)  # 根据需要调整 SDK 版本
set(CMAKE_CXX_STANDARD 20)
set(BUILD ${PROJECT_SOURCE_DIR}/build)

# set runtime file directory
set(EXECUTABLE_OUTPUT_PATH  ${BUILD})
set(EXTERNAL ${PROJECT_SOURCE_DIR}/external)
set(SPDLOG_PATH ${EXTERNAL}/include/logger)

#set pbd avoid pbd in a different directory
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/pdb)

#set source directory
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)

# auto find headfiles
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${EXTERNAL}/include)

# auto find dll or lib
link_directories(EXTERNAL)
add_executable(LiteWMS ${SRC})

#add submodule
add_subdirectory(${SPDLOG_PATH})

target_link_libraries(LiteWMS spdlog::spdlog_header_only)
if(WIN32)
    #set def _WIN32
    target_compile_definitions(${PROJECT_NAME} PUBLIC _WIN32)
    message(STATUS "Configured build on Windows.")
    target_link_libraries(LiteWMS sqlite3)
    # 设置 DLL 文件的路径
    find_file(SQLITE3_DLL_PATH sqlite3.dll PATHS ${PROJECT_SOURCE_DIR}/external)
    message(STATUS "HERE IS ${SQLITE3_DLL_PATH} ")
    # add dll to the target build directory and bind pdb dir
    install(FILES  ${SQLITE3_DLL_PATH} DESTINATION ${BUILD})

elseif(UNIX)
    # set def _UNIX
    target_compile_definitions(${PROJECT_NAME} PUBLIC _UNIX)
    message(STATUS "Configured build on linux.")
    # 查找 SQLite3 包
    find_package(SQLite3 REQUIRED)
    target_link_libraries(LiteWMS ${SQLite3_LIBRARIES})
endif ()

