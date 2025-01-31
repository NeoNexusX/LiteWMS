cmake_minimum_required(VERSION 3.27)
project(LiteWMS)
set(STATIC_CRT OFF CACHE BOOL "Use dynamic C runtime library")
set(CMAKE_SYSTEM_VERSION 10.0.18362.0)  # 根据需要调整 SDK 版本
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 90)

# set runtime file directory
set(BUILD ${PROJECT_SOURCE_DIR}/build)
set(INSTALL ${PROJECT_SOURCE_DIR}/install)
set(EXTERNAL ${PROJECT_SOURCE_DIR}/external)
set(SPDLOG_PATH ${EXTERNAL}/include/logger)
set(LIBGIT2_PATH ${EXTERNAL}/libgit2)
set(EXECUTABLE_OUTPUT_PATH  ${BUILD})

#set pbd avoid pbd in a different directory
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/pdb)

#set source directory
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)

# auto find headfiles
include_directories(${PROJECT_SOURCE_DIR}/include
        ${EXTERNAL}/include
        ${LIBGIT2_PATH}/include
)

# auto find dll or lib
link_directories(${EXTERNAL}/sqlite3)

#settings for libgit
set(LINK_WITH_STATIC_LIBRARIES ON)
set(SPDLOG_BUILD_SHARED OFF)

#settings for libgit
set(BUILD_TESTS OFF CACHE BOOL "Disable tests" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "Disable examples" FORCE)
set(BUILD_CLI OFF CACHE BOOL "Disable cli" FORCE)
set(USE_SSH OFF CACHE BOOL "Disable SSH" FORCE)
set(STATIC_CRT OFF CACHE BOOL "Disable CRT lib" FORCE)

# SET CMAKE INSTALL PREFIX:
set(CMAKE_INSTALL_LIBDIR ${INSTALL})
set(CMAKE_INSTALL_PREFIX ${INSTALL})
set(CMAKE_INSTALL_BINDIR ${INSTALL})

#add submodule
add_subdirectory(${SPDLOG_PATH})
add_subdirectory(${LIBGIT2_PATH})

# main target
add_executable(LiteWMS ${SRC})
add_dependencies(LiteWMS
        libgit2package
        spdlog::spdlog_header_only)

target_link_libraries(LiteWMS spdlog::spdlog_header_only)

if(WIN32)
    #set def _WIN32
    target_compile_definitions(${PROJECT_NAME} PUBLIC _WIN32)
    message(STATUS "Configured build on Windows.")
    target_link_libraries(LiteWMS sqlite3)
    target_link_libraries(LiteWMS libgit2package)

    # 设置 DLL 文件的路径
    find_file(SQLITE3_DLL_PATH sqlite3.dll PATHS ${EXTERNAL}/sqlite3)
    message(STATUS "Sqlite pos is ${SQLITE3_DLL_PATH} ")

    # add dll to the target build directory and bind pdb dir
    install(FILES  ${SQLITE3_DLL_PATH} DESTINATION ${BUILD})
    install(TARGETS libgit2package DESTINATION ${BUILD})

elseif(UNIX)
    # set def _UNIX
    target_compile_definitions(${PROJECT_NAME} PUBLIC _UNIX)
    message(STATUS "Configured build on linux.")
    # 查找 SQLite3 包
    find_package(SQLite3 REQUIRED)
    target_link_libraries(LiteWMS ${SQLite3_LIBRARIES})
    target_link_libraries(LiteWMS libgit2package)
endif ()