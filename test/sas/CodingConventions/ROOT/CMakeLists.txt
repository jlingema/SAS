add_sas_test(FILE "RN3.cpp" CHECKERS "sas.CodingConventions.ROOT.RN3" PASSREGEX ":2:1:.*RN3.*1 warning")
add_sas_test(FILE "RN4.cpp" CHECKERS "sas.CodingConventions.ROOT.RN4" PASSREGEX ":3:1:.*RN4.*:4:1:.*RN4.*2 warnings")
add_sas_test(FILE "RN6.cpp" CHECKERS "sas.CodingConventions.ROOT.RN6" PASSREGEX ":3:1:.*RN6.*1 warning")
add_sas_test(FILE "RN9.cpp" CHECKERS "sas.CodingConventions.ROOT.RN9" PASSREGEX ":2:1:.*RN9.*1 warning")
add_sas_test(FILE "RN10.cpp" CHECKERS "sas.CodingConventions.ROOT.RN10" PASSREGEX ":2:1:.*RN10.*1 warning")
add_sas_test(FILE "RN11.cpp" CHECKERS "sas.CodingConventions.ROOT.RN11" PASSREGEX ":4:4:.*RN11.*1 warning")
add_sas_test(FILE "RN12.cpp" CHECKERS "sas.CodingConventions.ROOT.RN12" PASSREGEX ":4:4:.*RN12.*1 warning")
add_sas_test(FILE "ptr_cast_win.cpp" CHECKERS "sas.CodingConventions.ROOT.PtrCastWin" PASSREGEX ":5:13:.*PtrCastWin.*1 warning")