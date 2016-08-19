add_sas_test(FILE "BlackList/match.cpp"
             CHECKERS "sas.CodingConventions.ROOT"
             PASSREGEX ":4:1:.*:5:1:.*2 warnings")
add_sas_test(FILE "BlackList/unmatch.cpp"
             CHECKERS "sas.CodingConventions.ROOT"
             PASSREGEX ":2:1:.*:4:1:.*:5:1:.*3 warnings")
add_sas_test(FILE "WhiteList/match.cpp"
             CHECKERS "sas.CodingConventions.ROOT"
             PASSREGEX ":2:1:.*1 warning")
add_sas_test(FILE "WhiteList/unmatch.cpp"
             CHECKERS "sas.CodingConventions.ROOT"
             PASSREGEX ":2:1:.*:4:1:.*:5:1:.*3 warnings")