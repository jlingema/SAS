// Author: David Ho (2016)

#include "EnumeratorChecker.h"

#include <clang/StaticAnalyzer/Core/BugReporter/BugReporter.h>
#include <clang/StaticAnalyzer/Core/BugReporter/PathDiagnostic.h>
#include <clang/StaticAnalyzer/Core/Checker.h>
#include <clang/StaticAnalyzer/Core/PathSensitive/AnalysisManager.h>
#include <regex>

namespace sas {
namespace CodingConventions {
namespace FCCSW {
void EnumeratorChecker::checkASTDecl(const clang::EnumConstantDecl* D,
                                clang::ento::AnalysisManager& Mgr,
                                clang::ento::BugReporter& BR) const {
  const char *reportDescription = "[sas.CodingConventions.FCCSW.Enumerator] Enumerator variable names must begin with 'k' followed by an UpperCamelCase name.";
  std::regex correctRegex("^k[A-Z][a-zA-Z0-9]+");
  auto nameString = D->getNameAsString();

if (!std::regex_match(nameString, correctRegex)) {
    Report(D, reportDescription, BR);
  }
  
}
}
}
} // end namespace sas