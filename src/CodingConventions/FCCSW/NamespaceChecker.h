// Author: David Ho (2016)

#ifndef SAS_CHECKERS_NAMESPACE_H
#define SAS_CHECKERS_NAMESPACE_H

#include "SasChecker.h"

namespace sas {
namespace CodingConventions {
namespace FCCSW {
class NamespaceTraits : public CommonCheckerTraits {
public:
  static constexpr const char* BugName = "Namespace";
  static constexpr const char* Name="sas.CodingConventions.FCCSW.Namespace";
  static constexpr const char* Description="Namespace names may only contain lowercase letters.";
};

class NamespaceChecker : public SasChecker<NamespaceTraits,
                                       clang::ento::check::ASTDecl<clang::NamespaceDecl>> {
public:
  void checkASTDecl(const clang::NamespaceDecl* D, 
                    clang::ento::AnalysisManager& Mgr, 
                    clang::ento::BugReporter& BR) const;
};
}
}
} // end namespace sas

#endif