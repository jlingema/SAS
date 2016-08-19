add_sas_test(FILE "BlackList/match.cpp"
             CHECKERS "sas.CodingConventions.ROOT"
             PASSREGEX ":6:4:.*:10:4:.*:13:4:.*3 warnings")
add_sas_test(FILE "WhiteList/match.cpp"
             CHECKERS "sas.CodingConventions.ROOT"
             PASSREGEX ":3:4:.*:10:4:.*:13:4:.*3 warnings")