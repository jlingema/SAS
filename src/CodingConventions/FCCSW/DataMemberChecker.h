// Author: David Ho (2016)

// Checks whether data member names start with "m_"

#ifndef SAS_CHECKERS_DataMember_H
#define SAS_CHECKERS_DataMember_H

#include "SasChecker.h"

namespace sas {
namespace CodingConventions {
namespace FCCSW {
class DataMemberTraits : public CommonCheckerTraits {
public:
  static constexpr const char* Name="sas.CodingConventions.FCCSW.DataMember";
  static constexpr const char* Description="Data member variable names must begin with \"m_\"";
};

class DataMemberChecker : public SasChecker<DataMemberTraits,
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