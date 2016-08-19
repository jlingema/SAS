set (CTEST_PROJECT_NAME "SAS")
set(CTEST_SOURCE_DIRECTORY "$ENV{CMAKE_SOURCE_DIR}")
set(CTEST_BINARY_DIRECTORY "$ENV{CMAKE_BINARY_DIR}")
set(CTEST_COMMAND "ctest")

add_subdirectory(sas)
if(ROOT_CHECKERS)
   add_subdirectory(BWList)
endif()

add_sas_test(FILE "comment_checker_disabler.cpp" 
             CHECKERS "sas.Example.Varname:sas.CodingConventions.General.NoUsingNamespaceInHeaders:sas.ThreadSafety.ConstCast"
             PASSREGEX ":18:1.*:19:1:.*:17:3:.*:24:3:.*:30:3:.*:35:3:.*:40:3:.*:45:3:.*:50:3:.*:53:3:.*:62:3:.*:65:35:.*:75:35:.*13 warnings")
add_sas_test(FILE "loop_convert.cpp" MODERNIZE "-risk=safe -loop-convert" PASSREGEX "11,18")