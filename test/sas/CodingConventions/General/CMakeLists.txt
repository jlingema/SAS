add_sas_test(FILE "using_namespace.cpp" 
  CHECKERS "sas.CodingConventions.General.NoUsingNamespaceInHeaders"
  PASSREGEX ":1:17.*NoUsingNamespaceInHeaders.*1:1:.*NoUsingNamespaceInHeaders.*2 warnings")
add_sas_test(FILE "std_printouts.cpp"
  CHECKERS "sas.CodingConventions.General.StdPrintouts"
  PASSREGEX ":6:4:.*StdPrintouts.*:7:4:.*StdPrintouts.*:8:4:.*StdPrintouts.*3 warnings")