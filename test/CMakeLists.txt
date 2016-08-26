set (CTEST_PROJECT_NAME "SAS")
set(CTEST_SOURCE_DIRECTORY "$ENV{CMAKE_SOURCE_DIR}")
set(CTEST_BINARY_DIRECTORY "$ENV{CMAKE_BINARY_DIR}")
set(CTEST_COMMAND "ctest")

add_subdirectory(sas)
if(ROOT_CHECKERS)
   add_subdirectory(BWList)
endif()

if(EXAMPLE_CHECKERS)
  set(comment_checker_disabler_passregex ":18:1:.*NoUsingNamespaceInHeaders.*"
                                         ":19:1:.*NoUsingNamespaceInHeaders.*"
                                         ":17:3:.*Varname.*"
                                         ":24:3:.*Varname.*"
                                         ":30:3:.*Varname.*"
                                         ":35:3:.*Varname.*"
                                         ":40:3:.*Varname.*"
                                         ":45:3:.*Varname.*"
                                         ":50:3:.*Varname.*"
                                         ":62:3:.*Varname.*"
                                         ":65:35:.*ConstCast.*"
                                         ":75:35:.*ConstCast.*"
                                         "13 warnings")
  add_sas_test(FILE "comment_checker_disabler.cpp" 
               CHECKERS "sas.Example.Varname:sas.CodingConventions.General.NoUsingNamespaceInHeaders:sas.ThreadSafety.ConstCast"
               PASSREGEX ${comment_checker_disabler_passregex})
endif()
add_sas_test(FILE "loop_convert.cpp" MODERNIZE MODERNIZE_OPTIONS "-risk=safe -loop-convert" PASSREGEX "11,18")