// Author: David Ho (2016)

#include "LocalVariableLowercaseChecker.h"

#include <clang/StaticAnalyzer/Core/BugReporter/BugReporter.h>
#include <clang/StaticAnalyzer/Core/BugReporter/PathDiagnostic.h>
#include <clang/StaticAnalyzer/Core/Checker.h>
#include <clang/StaticAnalyzer/Core/PathSensitive/AnalysisManager.h>

namespace sas {
namespace CodingConventions {
namespace FCCSW {
void LocalVariableLowercaseChecker::checkASTDecl(const clang::VarDecl* D,
                                                       clang::ento::AnalysisManager& Mgr,
                                                       clang::ento::BugReporter& BR) const {
  if (!D->hasLocalStorage()) {
    return;
  }
  auto varName = D->getName();
  if (varName.size()!=0 && std::islower(varName[0])) {
    return;
  }
  Report(D, "[sas.CodingConventions.FCCSW.LocalVariableLowercase] LocalVariableLowercase: local variable names must"
            "start with a lowercase letter.", BR);
}
}
}
} // end namespace sas