#include "IncludeDumper.h"
#include "clang/Frontend/FrontendPluginRegistry.h"

namespace sas {

void IncludeDetailConsumer::InclusionDirective (SourceLocation HashLoc, const Token &IncludeTok, StringRef FileName,
                                                bool IsAngled, CharSourceRange FilenameRange, const FileEntry *File,
                                                StringRef SearchPath, StringRef RelativePath, const Module *Imported) {
  std::string includeFname(File->getName());
  std::string sourceFname(HashLoc.printToString(m_manager));
  sourceFname.resize(sourceFname.find_first_of(":"));
  auto n = includeFname.find(m_mask);
  if (n != std::string::npos) {
    std::cout << includeFname << std::endl;
  }
}


bool InclusionDumpAction::ParseArgs(const clang::CompilerInstance &CI,
                                    const std::vector<std::string>& args) {
  for (unsigned i = 0, e = args.size(); i != e; ++i) {
    if (args[i] == "-dir-mask") {
      ++i;
      m_dirMask = args[i];
    }
  }
  return true;
}

}

