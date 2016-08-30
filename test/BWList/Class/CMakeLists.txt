add_sas_test(FILE "BlackList/match.cpp"
             CHECKERS "sas.CodingConventions.ROOT"
             SA_CONFIGURATION ".sas.json"
             PASSREGEX ":6:4:.*RN6.*:10:4:.*RN3.*:13:4:.*RN6.*3 warnings")
add_sas_test(FILE "WhiteList/match.cpp"
             CHECKERS "sas.CodingConventions.ROOT"
             SA_CONFIGURATION ".sas.json"
             PASSREGEX ":3:4:.*RN3.*:10:4:.*RN3.*:13:4:.*RN6.*3 warnings")