// Author: David Ho (2016)

// Checks whether the names of classes start with an uppercase letter

#ifndef SAS_CHECKERS_ClassNameUppercase_H
#define SAS_CHECKERS_ClassNameUppercase_H

#include "SasChecker.h"

namespace sas {
namespace CodingConventions{
namespace FCCSW {
class ClassNameUppercaseTraits : public CommonCheckerTraits{
public:
  static constexpr const char* Name="sas.CodingConventions.FCCSW.ClassNameUppercase";
  static constexpr const char* Description="Classes names must begin with an uppercase letter.";
};

class ClassNameUppercaseChecker : public SasChecker<ClassNameUppercaseTraits,
                                                    clang::ento::check::ASTDecl<clang::CXXRecordDecl>> {
public:
  void checkASTDecl(const clang::CXXRecordDecl* D, 
                    clang::ento::AnalysisManager& Mgr, 
                    clang::ento::BugReporter& BR) const;
};
}
}
} // end namespace sas

#endif
