add_sas_test(FILE "using_namespace.cpp" 
  CHECKERS "sas.CodingConventions.General.NoUsingNamespaceInHeaders"
  PASSREGEX ":1:17.*1:1:.*2 warnings")
add_sas_test(FILE "std_printouts.cpp"
  CHECKERS "sas.CodingConventions.General.StdPrintouts"
  PASSREGEX ":6:4:.*:7:4:.*:8:4:.*3 warnings")