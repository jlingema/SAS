// Author: David Ho (2016)

#include "ClassNameUppercaseChecker.h"

#include <clang/StaticAnalyzer/Core/BugReporter/BugReporter.h>
#include <clang/StaticAnalyzer/Core/BugReporter/PathDiagnostic.h>
#include <clang/StaticAnalyzer/Core/Checker.h>
#include <clang/StaticAnalyzer/Core/PathSensitive/AnalysisManager.h>
#include <llvm/ADT/StringRef.h>
#include <iostream>

#include <cctype>

namespace sas {
namespace CodingConventions {
namespace FCCSW {
void ClassNameUppercaseChecker::checkASTDecl(const clang::CXXRecordDecl* D,
                                                   clang::ento::AnalysisManager& Mgr,
                                                   clang::ento::BugReporter& BR) const {
  auto declName=D->getName();
  Report(D, "ClassNameUppercaseChecker", BR);
  if (declName.size() == 0) {
    return;
  } // something fishy, we bail out.
  if (declName.size() < 3) {
    Report(D, "Name is too short for a class/struct.", BR);
    return;
  }
  auto firstChar = D->getName()[0];
  if (std::isupper(firstChar)) {
    Report(D, "[sas.CodingConventions.FCCSW.ClassNameUppercase] Class names must begin with an uppercase letter.", BR);
  }
}
}
}
} // end namespace sas
