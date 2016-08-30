// Author: David Ho (2016)

#include "DataMemberChecker.h"

#include <clang/StaticAnalyzer/Core/BugReporter/BugReporter.h>
#include <clang/StaticAnalyzer/Core/BugReporter/PathDiagnostic.h>
#include <clang/StaticAnalyzer/Core/Checker.h>
#include <clang/StaticAnalyzer/Core/PathSensitive/AnalysisManager.h>
#include <regex>

namespace sas {
namespace CodingConventions {
namespace FCCSW {
void DataMemberChecker::checkASTDecl(const clang::FieldDecl* D,
                                clang::ento::AnalysisManager& Mgr,
                                clang::ento::BugReporter& BR) const {
  const char *reportDescription = "[sas.CodingConventions.FCCSW.DataMember] Data member variable names must begin with 'm_' followed by a lowerCamelCase name.";
  std::regex correctRegex("^m_[a-z][a-zA-Z0-9]+");
  auto nameString = D->getNameAsString();
  auto parent = D->getParent();

  if (parent->isStruct()) {
      return;
      // Does not apply to public members of structs
  }

  if (!std::regex_match(nameString, correctRegex)) {
    Report(D, reportDescription, BR);
  }
  
}
}
}
} // end namespace sas