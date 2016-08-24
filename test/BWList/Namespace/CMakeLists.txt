add_sas_test(FILE "BlackList/match.cpp"
             CHECKERS "sas.CodingConventions.ROOT"
             PASSREGEX ":6:7:.*:7:7:.*:13:7:.*:16:7:.*:17:7:.*5 warnings")
add_sas_test(FILE "WhiteList/match.cpp"
             CHECKERS "sas.CodingConventions.ROOT"
             PASSREGEX ":3:7:.*:13:7:.*:16:7:.*:17:7:.*4 warnings")