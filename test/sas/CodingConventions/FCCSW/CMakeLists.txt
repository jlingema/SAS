add_sas_test(FILE "Const.cpp"
  CHECKERS "sas.CodingConventions.FCCSW.Const"
  PASSREGEX ":7:1:.*Const.*:8:1:.*Const.*:9:1:.*Const.*3 warnings")
add_sas_test(FILE "DataMember.cpp"
  CHECKERS "sas.CodingConventions.FCCSW.DataMember" 
  PASSREGEX ":9:3:.*DataMember.*:12:3:.*DataMember.*:13:3:.*DataMember.*3 warnings")
add_sas_test(FILE "Enumerator.cpp"
  CHECKERS "sas.CodingConventions.FCCSW.Enumerator"
  PASSREGEX ":8:3:.*Enumerator.*:9:3:.*Enumerator.*:10:3:.*Enumerator.*3 warnings")
add_sas_test(FILE "Function.cpp"
  CHECKERS "sas.CodingConventions.FCCSW.Function"
  PASSREGEX ":7:1:.*Function.*:8:1:.*Function.*:16:3:.*Function.*3 warnings")
add_sas_test(FILE "Namespace.cpp"
  CHECKERS "sas.CodingConventions.FCCSW.Namespace"
  PASSREGEX "10:1:.*Namespace.*:14:1:.*Namespace.*:18:1:.*Namespace.*3 warnings")
add_sas_test(FILE "Type.cpp"
  CHECKERS "sas.CodingConventions.FCCSW.Type" 
  PASSREGEX ":7:3:.*Type.*:12:1:.*Type.*:16:1:.*Type.*:18:10:.*Type.*4 warnings")