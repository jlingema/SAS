// Author: David Ho (2016)

#ifndef SAS_CHECKERS_FUNCTION_H
#define SAS_CHECKERS_FUNCTION_H

#include "SasChecker.h"

namespace sas {
namespace CodingConventions {
namespace FCCSW {
class FunctionTraits : public CommonCheckerTraits {
public:
  static constexpr const char* BugName = "Function";
  static constexpr const char* Name="sas.CodingConventions.FCCSW.Function";
  static constexpr const char* Description="Function names must be in lowerCamelCase.";
};

class FunctionChecker : public SasChecker<FunctionTraits,
                                       clang::ento::check::ASTDecl<clang::FunctionDecl>> {
public:
  void checkASTDecl(const clang::FunctionDecl* D, 
                    clang::ento::AnalysisManager& Mgr, 
                    clang::ento::BugReporter& BR) const;
};
}
}
} // end namespace sas

#endif