// Author: David Ho (2016)

#include "FunctionChecker.h"

#include <clang/StaticAnalyzer/Core/BugReporter/BugReporter.h>
#include <clang/StaticAnalyzer/Core/BugReporter/PathDiagnostic.h>
#include <clang/StaticAnalyzer/Core/Checker.h>
#include <clang/StaticAnalyzer/Core/PathSensitive/AnalysisManager.h>
#include <regex>

namespace sas {
namespace CodingConventions {
namespace FCCSW {
void FunctionChecker::checkASTDecl(const clang::FunctionDecl* D,
                                clang::ento::AnalysisManager& Mgr,
                                clang::ento::BugReporter& BR) const {
  const char *reportDescription = "[sas.CodingConventions.FCCSW.Function] Function names must be in lowerCamelCase.";
  std::regex correctRegex("^[a-z][[:alnum:]]+");
  auto nameString = D->getNameAsString();
  auto declName = D->getDeclName();
  auto nameKind = declName.getNameKind();
  if (nameKind == clang::DeclarationName::NameKind::CXXConstructorName ||
      nameKind == clang::DeclarationName::NameKind::CXXDestructorName) {
    return;
      // Exception to function naming conventions for constructors/destructors
  }

  if (!std::regex_match(nameString, correctRegex)) {
    Report(D, reportDescription, BR);
  }
  
}
}
}
} // end namespace sas