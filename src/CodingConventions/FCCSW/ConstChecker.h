// Author: David Ho (2016)

#ifndef SAS_CHECKERS_CONST_H
#define SAS_CHECKERS_CONST_H

#include "SasChecker.h"

namespace sas {
namespace CodingConventions {
namespace FCCSW {
class ConstTraits : public CommonCheckerTraits {
public:
  static constexpr const char* BugName = "Const";
  static constexpr const char* Name="sas.CodingConventions.FCCSW.Const";
  static constexpr const char* Description="Constant variable names must begin with 'k' followed by an UpperCamelCase name.";
};

class ConstChecker : public SasChecker<ConstTraits,
                                       clang::ento::check::ASTDecl<clang::VarDecl>> {
public:
  void checkASTDecl(const clang::VarDecl* D, 
                    clang::ento::AnalysisManager& Mgr, 
                    clang::ento::BugReporter& BR) const;
};
}
}
} // end namespace sas

#endif