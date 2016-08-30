// Author: David Ho (2016)

#include "NamespaceChecker.h"

#include <clang/StaticAnalyzer/Core/BugReporter/BugReporter.h>
#include <clang/StaticAnalyzer/Core/BugReporter/PathDiagnostic.h>
#include <clang/StaticAnalyzer/Core/Checker.h>
#include <clang/StaticAnalyzer/Core/PathSensitive/AnalysisManager.h>
#include <regex>

namespace sas {
namespace CodingConventions {
namespace FCCSW {
void NamespaceChecker::checkASTDecl(const clang::NamespaceDecl* D,
                                clang::ento::AnalysisManager& Mgr,
                                clang::ento::BugReporter& BR) const {
  const char *reportDescription = "[sas.CodingConventions.FCCSW.Namespace] Namespace names may only contain lowercase letters.";
  std::regex correctRegex("[a-z]+");
  auto nameString = D->getNameAsString();

if (!std::regex_match(nameString, correctRegex)) {
    Report(D, reportDescription, BR);
  }
  
}
}
}
} // end namespace sas