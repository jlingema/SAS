 include(CMakeParseArguments)

macro(add_clang_plugin name)
   # Updates a cached list of checkers to be added
   set (srcs ${ARGN})

   include_directories(
      "${LLVM_INLCUDE_DIR}/"
      "${CLANG_INCLUDE_DIRS}"
      "${CMAKE_CURRENT_SOURCE_DIR}/src")
   link_directories( "${LLVM_LIB_DIR}/" )

   add_library( ${name} SHARED ${srcs} )

   if (SYMBOL_FILE)
      set_target_properties( ${name} PROPERTIES LINK_FlAGS
         "-exported_symbols_list ${SYMBOL_FILE}")
   endif()
   foreach (user_lib ${USER_LIBS})
      target_link_libraries( ${name} ${user_lib} )
   endforeach()
   if (APPLE) # this was needed on MacOS 10.10?
      target_link_libraries(${name} ${LLVM_LIBS_CORE} ${CLANG_LIBS} ${LLVM_LIBS_SYS})
   endif(APPLE)
   install(TARGETS ${name} DESTINATION lib)

   set_target_properties( ${name} PROPERTIES
      LINKER_LANGUAGE CXX
      PREFIX "")
endmacro(add_clang_plugin)

macro(add_checker checker_name)
   # Updates a cached list of checkers to be added
   set(checker_path "${CMAKE_CURRENT_SOURCE_DIR}/${checker_name}")
   list(APPEND checker_paths "${checker_path}")
   string(REPLACE "${CMAKE_SOURCE_DIR}/src/" "" checker_relative_path ${checker_path})
   list(APPEND checker_relative_paths "${checker_relative_path}")
   # This is a global cached variable that persists between builds and must be unset in the main CMakeLists.txt file
   set(checker_paths ${checker_paths} CACHE INTERNAL "List of absolute paths for active checkers")
   set(checker_relative_paths ${checker_relative_paths} CACHE INTERNAL "List of relative paths for active checkers.")
endmacro(add_checker)

macro(generate_registry_code checker_relative_paths)
   # Generates the code fragments required to format the ClangSasCheckerPluginRegistry template
   # Workaround for lack of dictionary support in cmake: creates list of directory names pointing to lists of checker names
   foreach(checker_path ${checker_relative_paths})
      GET_FILENAME_COMPONENT(checker_dir ${checker_path} DIRECTORY)
      GET_FILENAME_COMPONENT(checker_name ${checker_path} NAME_WE)
      list(APPEND checker_dirs ${checker_dir})
      # Here the content of checker_dir is set as a variable name pointing to the list of checker_names
      list(APPEND ${checker_dir} ${checker_name})
   endforeach()
   list(REMOVE_DUPLICATES checker_dirs)

   # Generate strings to format checker registry template with
   foreach(checker_dir ${checker_dirs})
      string(REPLACE "/" "::" NAMESPACE ${checker_dir})
      set(ADD_TO_REGISTRY_BLOCK "  using namespace sas::${NAMESPACE}\;\n")
      # Iterate through 'dictionary'
      foreach(checker_name ${${checker_dir}})
         set(ADD_TO_REGISTRY_BLOCK "${ADD_TO_REGISTRY_BLOCK}  AddToRegistry<${checker_name}>(registry)\;\n")
         set(HEADER_FILES "${HEADER_FILES}#include \"${checker_dir}/${checker_name}.h\"\n")
      endforeach()
      list(APPEND ADD_TO_REGISTRY_BLOCKS "${ADD_TO_REGISTRY_BLOCK}")
   endforeach()
   foreach(code_block ${ADD_TO_REGISTRY_BLOCKS})
      set(ADD_TO_REGISTRY "${ADD_TO_REGISTRY}  {\n${code_block}  }\n")
   endforeach()
endmacro(generate_registry_code)

#-----------------------------------------------------------------------------------------------------------------------
# Adds a test of sas coding conventions
# Arguments:
# FILE: file test is to be run on
# CHECKERS: colon-separated list of checkers to be used
# MODERNIZE: whether to apply clang-modernize
# MODERNIZE_OPTIONS: clang-modernize options
# SA_CONFIGURATION_FILE: SA configuration file for blacklisting/whitelisting checkers
# WORKING_DIR: working directory in which the test is run; defaults to ${CMAKE_CURRENT_LIST_DIR}
# PASSREGEX: regular expression present in the passing output of the test
# FAILREGEX: regular expression preseng in failing output of the test
#-----------------------------------------------------------------------------------------------------------------------
macro(add_sas_test)
   cmake_parse_arguments(ARG  "MODERNIZE"
                              "FILE;SA_CONFIGURATION_FILE;WORKING_DIR;PASSREGEX;FAILREGEX;LABELS"
                              "MODERNIZE_OPTIONS;CHECKERS" ${ARGN})
   find_program(env_cmd xenv HINTS ${binary_paths})

   if (NOT ARG_FILE)
      message( SEND_ERROR "Cannot add test, specify file!" )
   endif (NOT ARG_FILE)

   if(NOT ARG_CHECKERS AND NOT ARG_MODERNIZE)
      message( SEND_ERROR "Specify modernize or checkers configuration!" )
   endif(NOT ARG_CHECKERS AND NOT ARG_MODERNIZE)

   if(ARG_MODERNIZE)
      set(MODERNIZE_ON "--modernize")
   endif(ARG_MODERNIZE)

   set(SAS_CMD "${CMAKE_BINARY_DIR}/scripts/sas_check++")

   set(FULL_FILENAME "${CMAKE_CURRENT_SOURCE_DIR}/${ARG_FILE}")
   if(ARG_SA_CONFIGURATION_FILE)
      set(CONFIGURATION_FILENAME "${CMAKE_CURRENT_SOURCE_DIR}/${ARG_SA_CONFIGURATION_FILE}")
   endif()
   if(ARG_WORKING_DIR)
      set(WORKING_DIR "${CMAKE_SOURCE_DIR}/${ARG_WORKING_DIR}")
   else()
      set(WORKING_DIR "${CMAKE_CURRENT_LIST_DIR}")
   endif()

   #Prepare test mme from file name
   string(REPLACE "${CMAKE_SOURCE_DIR}/test/" "" TEST_NAME ${FULL_FILENAME})
   string(REPLACE "/" "." TEST_NAME ${TEST_NAME})
   string(REGEX REPLACE "\\.[^.]+$" "" TEST_NAME ${TEST_NAME})


   add_test(NAME "${TEST_NAME}"
      COMMAND ${SAS_CMD} --checkers ${ARG_CHECKERS} ${MODERNIZE_ON} --modernize_options=${ARG_MODERNIZE_OPTIONS}
      --sa_configuration=${CONFIGURATION_FILENAME} "${ARG_FILE}" "-c" "-std=c++11" "-o" "${CMAKE_BINARY_DIR}/{ARG_FILE}.o"
      WORKING_DIRECTORY "${WORKING_DIR}")

   if(ARG_PASSREGEX)
      set_property(TEST ${TEST_NAME} PROPERTY PASS_REGULAR_EXPRESSION ${ARG_PASSREGEX})
   endif()
   if(ARG_FAILREGEX)
      set_property(TEST ${TEST_NAME} PROPERTY FAIL_REGULAR_EXPRESSION ${ARG_FAILREGEX})
   endif()
endmacro(add_sas_test)
