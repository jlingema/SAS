 include(CMakeParseArguments)

macro(add_clang_plugin name)
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

   install(TARGETS ${name} DESTINATION lib)

   set_target_properties( ${name} PROPERTIES
      LINKER_LANGUAGE CXX
      PREFIX "")
endmacro(add_clang_plugin)

macro(add_checker checker_name)
   list(APPEND checker_paths "${CMAKE_CURRENT_SOURCE_DIR}/${checker_name}")
   # This is a global cached variable that persists between builds and must be unset in the main CMakeLists.txt file
   set(checker_paths ${checker_paths} CACHE INTERNAL "List of active checkers.")
endmacro(add_checker)

macro(generate_registry_code checker_paths)
   # Generates the code fragments required to format the ClangSasCheckerPluginRegistry template
   # Workaround for lack of dictionary support in cmake: creates list of directory names pointing to lists of checker names
   foreach(checker_path ${checker_paths})
      GET_FILENAME_COMPONENT(checker_dir ${checker_path} DIRECTORY)
      GET_FILENAME_COMPONENT(checker_name ${checker_path} NAME_WE)
      list(APPEND checker_dirs ${checker_dir})
      # Here the content of checker_dir is set as a variable name pointing to the list of checker_names
      list(APPEND ${checker_dir} ${checker_name})
   endforeach()
   list(REMOVE_DUPLICATES checker_dirs)

   # Generate strings to format checker registry template with
   foreach(checker_dir ${checker_dirs})
      string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/src/" "" NAMESPACE_PATH ${checker_dir})
      string(REPLACE "/" "::" NAMESPACE ${NAMESPACE_PATH})
      set(ADD_TO_REGISTRY_BLOCK "  using namespace sas::${NAMESPACE}\;\n")
      # Iterate through 'dictionary'
      foreach(checker_name ${${checker_dir}})
         set(ADD_TO_REGISTRY_BLOCK "${ADD_TO_REGISTRY_BLOCK}  AddToRegistry<${checker_name}>(registry)\;\n")
         set(HEADER_FILES "${HEADER_FILES}#include \"${NAMESPACE_PATH}/${checker_name}.h\"\n")
      endforeach()
      list(APPEND ADD_TO_REGISTRY_BLOCKS "${ADD_TO_REGISTRY_BLOCK}")
   endforeach()
   foreach(code_block ${ADD_TO_REGISTRY_BLOCKS})
      set(ADD_TO_REGISTRY "${ADD_TO_REGISTRY}  {\n${code_block}  }\n")
   endforeach()
endmacro(generate_registry_code)


macro(add_sas_test_new)
   cmake_parse_arguments(ARG  "IS_C"
                              "FILE;CHECKERS;MODERNIZE;PASSREGEX;FAILREGEX;LABELS"
                              "" ${ARGN})
   find_program(env_cmd xenv HINTS ${binary_paths})

   if (NOT ARG_FILE)
      message( SEND_ERROR "Cannot add test, specify file!" )
   endif (NOT ARG_FILE)

   if(NOT ARG_CHECKERS AND NOT ARG_MODERNIZE)
      message( SEND_ERROR "Specify modernize or checkers configuration!" )
   endif(NOT ARG_CHECKERS AND NOT ARG_MODERNIZE)

   set(SAS_CMD "${CMAKE_BINARY_DIR}/scripts/compile")

   set(FULL_FILENAME ${ARG_FILE})
   # set(FULL_FILENAME ${CMAKE_CURRENT_SOURCE_DIR}/${ARG_FILE})
   string(REPLACE "/" "." TEST_NAME ${FULL_FILENAME})

   # prepare environment variable for checkers:
   foreach(CHECKER ${ARG_CHECKERS})
      set(CHECKERS ${CHECKERS} "${CHECKER}:")
   endforeach()

   add_test(NAME "${TEST_NAME}"
     COMMAND ${SAS_CMD} --checkers=${CHECKERS} --modernize=${ARG_MODERNIZE} --cargs="${FULL_FILENAME} -c -std=c++11"
     WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

   if(ARG_PASSREGEX)
    set_property(TEST ${TEST_NAME} PROPERTY PASS_REGULAR_EXPRESSION ${ARG_PASSREGEX})
   endif()
 endmacro(add_sas_test_new)
