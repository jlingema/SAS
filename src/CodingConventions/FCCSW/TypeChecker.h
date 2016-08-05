// Author: David Ho (2016)

#ifndef SAS_CHECKERS_TYPE_H
#define SAS_CHECKERS_TYPE_H

#include "SasChecker.h"

namespace sas {
namespace CodingConventions {
namespace FCCSW {
class TypeTraits : public CommonCheckerTraits {
public:
  static constexpr const char* BugName = "Type";
  static constexpr const char* Name="sas.CodingConventions.FCCSW.Type";
  static constexpr const char* Description="Type names must be in UpperCamelCase.";
};

class TypeChecker : public SasChecker<TypeTraits,
                                       clang::ento::check::ASTDecl<clang::TypeDecl>> {
public:
  void checkASTDecl(const clang::TypeDecl* D, 
                    clang::ento::AnalysisManager& Mgr, 
                    clang::ento::BugReporter& BR) const;
};
}
}
} // end namespace sas

#endif