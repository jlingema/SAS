// Author: David Ho (2016)

#ifndef SAS_CHECKERS_ENUMERATOR_H
#define SAS_CHECKERS_ENUMERATOR_H

#include "SasChecker.h"

namespace sas {
namespace CodingConventions {
namespace FCCSW {
class EnumeratorTraits : public CommonCheckerTraits {
public:
  static constexpr const char* BugName = "Enumerator";
  static constexpr const char* Name="sas.CodingConventions.FCCSW.Enumerator";
  static constexpr const char* Description="Enumerator variable names must begin with 'k' followed by an UpperCamelCase name.";
};

class EnumeratorChecker : public SasChecker<EnumeratorTraits,
                                       clang::ento::check::ASTDecl<clang::EnumConstantDecl>> {
public:
  void checkASTDecl(const clang::EnumConstantDecl* D, 
                    clang::ento::AnalysisManager& Mgr, 
                    clang::ento::BugReporter& BR) const;
};
}
}
} // end namespace sas

#endif