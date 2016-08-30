#Setup
##Prerequisites
The following software is required to run SAS:
###CMake
Version 2.8 or newer. CMake must be used to build the project on which SAS checks are to be run.
###Clang/LLVM
Clang version 3.5 or newer.
###Python
Version 2.7 or newer.
##Preparing the Environment
Run the following commands to set the required environment variables:
```
source /afs/cern.ch/exp/fcc/sw/0.7/init_fcc_stack.sh
source /afs/cern.ch/sw/lcg/external/llvm/3.6/x86_64-slc6/setup.sh
```
##Compiling and Installing
From the SAS build directory, running the following commands (including double quotes and replacing square bracketed terms with appropriate paths)
```
cmake -DCMAKE_INSTALL_PREFIX="[path to SAS install directory]" [path to SAS source directory]
make install
```
will compile and install SAS with the default checkers (general coding conventions, thread-safety, performance) enabled. The following CMake options can be used to enable further checkers:
* `-DFCCSW_CHECKERS=ON`: enable FCCSW naming convention checkers (see [FCCSW documentation](https://github.com/jlingema/FCCSW/blob/master/doc/CppCodingStyleGuidelines.md))
* `-DROOT_CHECKERS=ON`: enable ROOT naming convention checkers (see [ROOT/Taligent documentation](https://root.cern.ch/TaligentDocs/TaligentOnline/DocumentRoot/1.0/Docs/books/WM/WM_63.html))
* `-DEXAMPLE_CHECKERS=ON`: enable the example checker (checks that variable names begin with a capital letter)

##Enabling SAS
In order to run SAS on a project, the directory in which SAS is installed must be added to the project's CMake prefix path. This can be achieved by executing the command
```
export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:[path to SAS install directory]
```
The following lines must be added to the project's `CMakeLists.txt` after the `project()` command:
```
find_package(sas)
enable_sas()
```
`find_package()` searches through `CMAKE_PREFIX_PATH` to find the SAS configuration files and loads the package. `enable_sas()` replaces the default C++ compiler with SAS and applies the user's options.

By default, all enabled SAS checkers are run on all source and header files in the project build. The user can pass options to the `enable_sas()` macro to specify behaviour. These are detailed in the [SAS Options](https://github.com/dpiparo/SAS/blob/master/documentation/sas_options.md) section of this documentation.

##Running SAS
SAS runs in place of the C++ compiler, so can be run from the project's build directory by executing the following commands:
```
cmake [path to project source directory]
make
```
The project will be compiled and the enabled SAS checks will be run on each source and header file. Once SAS has been run, the command
```
make report_index
```
will generate an HTML index displaying the files containing coding convention violations and detailing the errors found (note: report index has only been tested in Firefox browser).