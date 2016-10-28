/**
  Author: Joschka Lingemann
  Date: 26.09.2016
  Description: Aim is to assemble a list of included header files. This can then
               be used to analyse those headers for a report.
*/
#ifndef SAS_INCLUDE_DUMPER
#define SAS_INCLUDE_DUMPER

#include "clang/AST/ASTConsumer.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Frontend/FrontendAction.h"
#include <string>
#include <iostream>

namespace sas {

using clang::SourceLocation;
using clang::Token;
using llvm::StringRef;
using clang::CharSourceRange;
using clang::FileEntry;
using clang::Module;

class IncludeDetailConsumer : public clang::PPCallbacks {
  public:
    IncludeDetailConsumer(const std::string& mask, clang::SourceManager& sourceManager) :
      m_mask(mask), m_manager(sourceManager)
    {
    }

    virtual void  InclusionDirective (SourceLocation HashLoc, const Token &IncludeTok, StringRef FileName, bool IsAngled,
                                      CharSourceRange FilenameRange, const FileEntry *File, StringRef SearchPath,
                                      StringRef RelativePath, const Module *Imported) override;
  private:
    std::string m_mask;
    clang::SourceManager& m_manager;
};

class InclusionDump : public clang::ASTConsumer {
  public:
    InclusionDump(clang::Preprocessor& preprocessor, clang::SourceManager& sourceManager, const std::string& mask) {
      preprocessor.addPPCallbacks(llvm::make_unique<IncludeDetailConsumer>(mask, sourceManager));
    }
};

class InclusionDumpAction : public clang::PluginASTAction {
  public:
    InclusionDumpAction() : m_dirMask("") {}
    virtual bool ParseArgs(const clang::CompilerInstance &CI, const std::vector<std::string>& args) override;

  protected:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &CI,
                                                          llvm::StringRef) override {
      return llvm::make_unique<InclusionDump>(CI.getPreprocessor(), CI.getSourceManager(), m_dirMask);
    }
    std::string m_dirMask;
};
}

#endif /* SAS_INCLUDE_DUMPER */
