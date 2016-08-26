add_sas_test(FILE "BlackList/match.cpp"
             CHECKERS "sas.CodingConventions.ROOT"
             PASSREGEX ":4:1:.*RN4.*:5:1:.*RN4.*2 warnings")
add_sas_test(FILE "BlackList/unmatch.cpp"
             CHECKERS "sas.CodingConventions.ROOT"
             PASSREGEX ":2:1:.*RN3.*:4:1:.*RN4.*:5:1:.*RN4.*3 warnings")
add_sas_test(FILE "WhiteList/match.cpp"
             CHECKERS "sas.CodingConventions.ROOT"
             PASSREGEX ":2:1:.*RN3.*1 warning")
add_sas_test(FILE "WhiteList/unmatch.cpp"
             CHECKERS "sas.CodingConventions.ROOT"
             PASSREGEX ":2:1:.*RN3.*:4:1:.*RN4.*:5:1:.*RN4.*3 warnings")