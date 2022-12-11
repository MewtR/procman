cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
project(procman LANGUAGES C) # By default, languages are C and CXX 

SET(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# libproc2
set (LIBPROC_DIR ${CMAKE_CURRENT_BINARY_DIR}/procps)
set (LIBPROC_SRC ${LIBPROC_DIR}/src)
set (LIBPROC_BIN ${LIBPROC_DIR}/bin)
set (LIBPROC_SO ${LIBPROC_DIR}/bin/library/.libs/libproc2.so)
set (LIBPROC_INC ${LIBPROC_SRC}/library/include)

include(ExternalProject)
# fetch and build libproc2
ExternalProject_Add(
    procps-ng
    GIT_REPOSITORY https://gitlab.com/procps-ng/procps.git
    GIT_TAG c444c55ce8187bf38f2891d04f8edc245ed71edd
    GIT_SHALLOW false # --depth 1
    SOURCE_DIR ${LIBPROC_SRC}
    BINARY_DIR ${LIBPROC_BIN} # build files
    CONFIGURE_COMMAND ${LIBPROC_SRC}/autogen.sh && ${LIBPROC_SRC}/configure
    BUILD_COMMAND ${MAKE}
    INSTALL_COMMAND ""
    )

# Import it
add_library(libproc2 SHARED IMPORTED)
# libproc2 depends on the 'procps-ng' external project I made.
add_dependencies(libproc2 procps-ng)
# Specify location of the .so file
set_target_properties(libproc2 PROPERTIES IMPORTED_LOCATION ${LIBPROC_SO})

add_executable(procman main.c)
target_include_directories(procman PRIVATE ${LIBPROC_INC})
target_link_libraries(procman libproc2)

