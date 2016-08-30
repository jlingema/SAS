# SAS
SAS (Static Analysis Suite) is a tool for finding coding convention violations in C++ code. SAS is run in parallel with compilation and as such can run powerful and specific checks: currently included are checkers for code formatting, naming conventions, thread safety, performance and usage of modern language constructs. Users may use and adapt existing checkers, or write new ones specific to their project.

SAS uses the open-source Clang Abstract Syntax Tree to analyse the code in a project, allowing checks on specific language constructs to be carried out. Implemented through the CMake build automisation tool, SAS replaces the C++ compiler and runs a number of [checkers](documentation/sas_checkers.md), which can be general or project-specific, on each file. Any errors found are written to an html file that is displayed in the report index.

Using SAS, continuous integration of static analysis tests can be easily achieved, helping projects to maintain safe, readable and consistent code.

# Documentation
* [Using SAS](documentation/using_sas.md)
* [SAS Checkers](documentation/sas_checkers.md)
* [The HTML Report Index](documentation/report_index.md)

# Prerequisites
The following software is required to run SAS:
## CMake
Version 2.8 or newer.
## Clang/LLVM
Clang version 3.5 or newer.
## Python
Version 2.7 or newer. In order to generate custom checkers from yaml files, the `yaml` module must be installed.

# Quick Start Guide
## Preparing the Environment
Run the following commands to set the required environment variables:
```
source /afs/cern.ch/exp/fcc/sw/0.7/init_fcc_stack.sh
source /afs/cern.ch/sw/lcg/external/llvm/3.6/x86_64-slc6/setup.sh
```
## <a id="buildingAndInstalling"></a> Building and Installing SAS
Clone the SAS repository and run the following:
```
export SASBUILDDIR=[name for build directory]
export SASINSTALLDIR=[name for install directory]
mkdir $SASINSTALLDIR
mkdir $SASBUILDDIR;cd $SASBUILDDIR
cmake -DCMAKE_INSTALL_PREFIX="../$SASINSTALLDIR" ../SAS
make install
```
replacing the square-bracketed terms with approprate names.

This installs SAS with the default checkers (general coding conventions, thread-safety and performance) enabled.

The following CMake options can be used to enable further checkers:
* `-DFCCSW_CHECKERS=ON`: enable FCCSW naming convention checkers (see [FCCSW documentation](https://github.com/jlingema/FCCSW/blob/master/doc/CppCodingStyleGuidelines.md))
* `-DROOT_CHECKERS=ON`: enable ROOT naming convention checkers (see [ROOT/Taligent documentation](https://root.cern.ch/TaligentDocs/TaligentOnline/DocumentRoot/1.0/Docs/books/WM/WM_63.html))
* `-DEXAMPLE_CHECKERS=ON`: enable the example checker (checks that variable names begin with a capital letter)

##<a id="usingSAS"></a>Using SAS
For more detailed SAS options and alternative ways to run SAS, see the [Using SAS](documentation/using_sas.md) section of the documentation.

The simplest way to run SAS is through CMake. Within the project directory, run the command
```
export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:[path to SAS install directory]
```
to set the cmake prefix path, and then add the lines
```
find_package(sas)
enable_sas()
```
to the project's `CMakeLists.txt` after the `project()` command to enable sas. This replaces the C++ compiler with SAS, so executing
```
cmake [path to project source directory]
make
```
will run all enabled SAS checks on the project's source and header files. Once this is complete, the command
```
make report_index
```
will generate an [HTML index](documentation/report_index.md) displaying the files containing coding convention violations and detailing the errors found (note: report index has only been tested in Firefox browser).

# <a id="creditAndHistory"></a> Credit and History
SAS originates from an effort within the CMS collaboration at CERN and quite some checkers were imported from CMSSW (http://cms-sw.github.io/). CMSSSW and its authors cannot be blamed by any mistake or bug present in SAS :-) The credit of single developers is preserved within the single source files. The first version of SAS was created by F. Bartek, D. Piparo and T. Hauth.

Implementation of running SAS through CMake and FCCSW naming convention checkers was carried out by David Ho in a 2016 Summer Student project under supervision of Joschka Lingemann.

The HTML summary page relies on bootstrap and hightlight js (see below for links).

# Useful Links:
* LLVM:                  http://llvm.org
* Clang:                 http://clang.llvm.org
* Clang Static Analyzer: http://clang-analyzer.llvm.org
* scan-build:            http://clang-analyzer.llvm.org/scan-build.html
* CMake:                 http://www.cmake.org
* Bootstrap:             http://getbootstrap.com/
* Highlight-js:          https://highlightjs.org/

# Licence
SAS is licenced under LGPL3.