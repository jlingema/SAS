add_sas_test(FILE "BlackList/match.cpp"
             CHECKERS "sas.CodingConventions.ROOT"
             PASSREGEX ":6:7:.*RN4.*:7:7:.*RN4.*:13:7:.*RN3.*:16:7:.*RN4.*:17:7:.*RN4.*5 warnings")
add_sas_test(FILE "WhiteList/match.cpp"
             CHECKERS "sas.CodingConventions.ROOT"
             PASSREGEX ":3:7:.*RN3.*:13:7:.*RN3.*:16:7:.*RN4.*:17:7:.*RN4.*4 warnings")