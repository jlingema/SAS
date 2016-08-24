add_sas_test(FILE "Const.cpp"
  CHECKERS "sas.CodingConventions.FCCSW.Const"
  PASSREGEX ":7:1:.*:8:1:.*:9:1:.*3 warnings")
add_sas_test(FILE "DataMember.cpp"
  CHECKERS "sas.CodingConventions.FCCSW.DataMember" 
  PASSREGEX ":9:3:.*:12:3:.*:13:3:.*3 warnings")
add_sas_test(FILE "Enumerator.cpp"
  CHECKERS "sas.CodingConventions.FCCSW.Enumerator"
  PASSREGEX ":8:3:.*:9:3:.*:10:3:.*3 warnings")
add_sas_test(FILE "Function.cpp"
  CHECKERS "sas.CodingConventions.FCCSW.Function"
  PASSREGEX ":7:1:.*:8:1:.*:16:3:.*3 warnings")
add_sas_test(FILE "Namespace.cpp"
  CHECKERS "sas.CodingConventions.FCCSW.Namespace"
  PASSREGEX "10:1:.*:14:1:.*:18:1:.*3 warnings")
add_sas_test(FILE "Type.cpp"
  CHECKERS "sas.CodingConventions.FCCSW.Type" 
  PASSREGEX ":7:3:.*:12:1:.*:16:1:.*:18:10:.*4 warnings")