# Authors: <CMS>
#         Filip Bartek (2013)
#         David Ho (2016)

# Optional:
# LLVM_DEV_DIR

# Usage:
# cmake [-D LLVM_DEV_DIR=$LLVM_DEV_DIR] $SAS_DIR

cmake_minimum_required (VERSION 2.8)
project (sas CXX)

set( sas_VERSION_MAJOR 0 )
set( sas_VERSION_MINOR 1 )
set( sas_VERSION_PATCH 0 )
set( sas_VERSION "${sas_VERSION_MAJOR}.${sas_VERSION_MINOR}" )

# Check if this is an out-of-source build
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
   message(FATAL_ERROR "In source build is not supported. Please build in a different directory.")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(LLVM)
include(sasMacros)

# /usr/lib/llvm-3.5/
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

# the rest should work automatically

# assumes for clang to be under llvm/tools/, as suggested by the clang website
# http://clang.llvm.org/get_started.html#build

add_definitions (-D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS)
add_definitions (-D_GNU_SOURCE -DHAVE_CLANG_CONFIG_H)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-common -Woverloaded-virtual -Wcast-qual -fno-strict-aliasing -pedantic -Wno-long-long -Wall -W -Wno-unused-parameter -Wwrite-strings -fexceptions -fno-rtti -O3")

set (CMAKE_MODULE_LINKER_FLAGS "-Wl,-flat_namespace -Wl,-undefined -Wl,suppress")

set (USER_LIBS pthread)

option(FCCSW_CHECKERS "Turn on to activate FCCSW coding convention checkers." OFF)
option(ROOT_CHECKERS "Turn on to activate ROOT coding convention checkers." OFF)
option(GENERAL_CHECKERS "Turn on to activate general coding convention checkers." ON)

add_subdirectory(src)

include(CTest)
add_subdirectory(test)

# Generate checker registry from template
generate_registry_code("${checker_relative_paths}")
configure_file(templates/ClangSasCheckerPluginRegister.cpp.in ${CMAKE_CURRENT_SOURCE_DIR}/src/ClangSasCheckerPluginRegister.cpp)

include(cmake/sasCreateConfig.cmake)

# Add checkers and other plugins
add_clang_plugin(libSas
   ${checker_paths}
   src/ClangSasCheckerPluginRegister.cpp
   src/SasException.cpp
#   src/CatchAll.cpp
   src/CommentCheckerDisabler.cpp
   src/jsonxx.cc
   src/BlackWhiteListCheckerDisabler
   )

file(COPY scripts USE_SOURCE_PERMISSIONS DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY config USE_SOURCE_PERMISSIONS DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY templates/report_index.html.in DESTINATION ${CMAKE_BINARY_DIR}/html)

#modify script clang path to the real one
if (LLVM_BIN_DIR)
    set(CLANG_EXES_LOCATION ${LLVM_BIN_DIR}/)
endif()

set(CLANG_PATH "${CLANG_EXES_LOCATION}clang")
set(CLANG_PP_PATH "${CLANG_EXES_LOCATION}clang++")
set(CLANG_FORMAT_PATH "${CLANG_EXES_LOCATION}clang-format")
set(CLANG_MODERNIZE_PATH "${CLANG_EXES_LOCATION}clang-modernize")

configure_file(templates/clang.in ${CMAKE_BINARY_DIR}/scripts/clang)
configure_file(templates/clang++.in ${CMAKE_BINARY_DIR}/scripts/clang++)
configure_file(templates/common/__init__.py.in ${CMAKE_BINARY_DIR}/scripts/common/__init__.py)
configure_file(templates/sas_check.in ${CMAKE_BINARY_DIR}/scripts/sas_check)

install(TARGETS libSas DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(DIRECTORY ${CMAKE_BINARY_DIR}/scripts USE_SOURCE_PERMISSIONS DESTINATION ${CMAKE_INSTALL_PREFIX} PATTERN "*.pyc" EXCLUDE)
install(DIRECTORY ${CMAKE_BINARY_DIR}/config USE_SOURCE_PERMISSIONS DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY ${CMAKE_BINARY_DIR}/html DESTINATION ${CMAKE_INSTALL_PREFIX})

# Remove persistent cached variables
unset(checker_paths CACHE)
unset(checker_relative_paths CACHE)
unset(FCCSW_CHECKERS CACHE)
unset(ROOT_CHECKERS CACHE)
unset(GENERAL_CHECKERS CACHE)
