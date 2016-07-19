// Author: David Ho (2016)

#include "DataMemberChecker.h"

#include <clang/StaticAnalyzer/Core/BugReporter/BugReporter.h>
#include <clang/StaticAnalyzer/Core/BugReporter/PathDiagnostic.h>
#include <clang/StaticAnalyzer/Core/Checker.h>
#include <clang/StaticAnalyzer/Core/PathSensitive/AnalysisManager.h>

namespace sas {
namespace CodingConventions {
namespace FCCSW {
void DataMemberChecker::checkASTDecl(const clang::VarDecl* D,
                                                       clang::ento::AnalysisManager& Mgr,
                                                       clang::ento::BugReporter& BR) const {
  if (!D->isStaticDataMember()) {
    return;
  }
  auto varName = D->getName();
  if (varName.size() > 2 && varName.startswith("m_")) {
    return;
  }
  Report(D,
         "[sas.CodingConventions.FCCSW.DataMember] DataMember: Data member variable names must begin with \"m_\".",
          BR);
}
}
}
} // end namespace sas