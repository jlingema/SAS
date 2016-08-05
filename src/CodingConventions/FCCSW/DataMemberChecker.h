// Author: David Ho (2016)

#ifndef SAS_CHECKERS_DATAMEMBER_H
#define SAS_CHECKERS_DATAMEMBER_H

#include "SasChecker.h"

namespace sas {
namespace CodingConventions {
namespace FCCSW {
class DataMemberTraits : public CommonCheckerTraits {
public:
  static constexpr const char* BugName = "DataMember";
  static constexpr const char* Name="sas.CodingConventions.FCCSW.DataMember";
  static constexpr const char* Description="Data member variable names must begin with 'm_' followed by a lowerCamelCase name.";
};

class DataMemberChecker : public SasChecker<DataMemberTraits,
                                       clang::ento::check::ASTDecl<clang::FieldDecl>> {
public:
  void checkASTDecl(const clang::FieldDecl* D, 
                    clang::ento::AnalysisManager& Mgr, 
                    clang::ento::BugReporter& BR) const;
};
}
}
} // end namespace sas

#endif