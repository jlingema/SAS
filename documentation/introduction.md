#Introduction
SAS (Static Analysis Suite) is a tool for finding coding convention violations in C++ code. SAS is run in parallel with compilation and as such can run powerful and specific checks: currently included are checkers for code formatting, naming conventions, thread safety, performance and usage of modern language constructs. Users may use and adapt existing checkers, or write new ones specific to their project.

SAS uses the open-source Clang Abstract Syntax Tree to analyse the code in a project, allowing checks on specific language constructs to be carried out. Implemented through the CMake build automisation tool, SAS replaces the C++ compiler and runs a number of 'checkers', which can be general or project-specific, on each file. Any errors found are written to an html file that is displayed in the report index.

Using SAS, continuous integration of static analysis tests can be easily achieved, helping projects to maintain safe, readable and consistent code.