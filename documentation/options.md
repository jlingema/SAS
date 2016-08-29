#Options
##The `enable_sas()` Macro
The CMake macro `enable_sas()` replaces the default C++ compiler with SAS and applies user-determined options specifying which checks are to be run, and which directories the checks are to be run on. It is defined in the `sasConfig.cmake` file in the SAS install directory.

Calling `enable_sas()` with no arguments will run all available SAS checkers on all source files and headers that are included in the project build. Code formatting style and use of modern C++ constructs will not be checked.

The following options may be passed to `enable_sas()`:

|Option|Number of arguments|Argument description|Notes|
|:---:|:---:|:---:|:---:|:---:|
|`COMPARISON_REPORT_DIR`|1|Absolute path to a directory where the report files are to be generated|Defaults to the directory `sasreport` in the project build directory if not specified. If the directory specified does not exist, it will be created.|
|`DISABLE_CHECKERS`|1 or more|Names of checkers to be disabled|\-|
|`FORMAT`|0|\-|If option is present, `clang-format` is run on source and header files, checking code formatting style. Style must be specified in a yaml file named `.clang-format` in the project base directory; if none can be found LLVM style is used. See [Clang](http://clang.llvm.org/docs/ClangFormat.html) documentation for more information. Alternatively, formatting style checks may be turned on by setting the environment variable `SA_FORMATTING`.|
|`IGNORE_DIRS`|1 or more|Absolute paths to directories on which SAS checks are not to be run|These directories are still compiled, but no SAS checks are run at compile time, and they are omitted from the report index.|
|`MODERNIZE`|0|\-|If option is present `clang-modernize` is run on source and header files, checking for use of modern (post C++11) language constructs. If `MODERNIZE_OPTIONS` are specified, these will be used; if not `clang-modernize [source file]` will be run, running all clang-modernize checks (see [Clang](http://manpages.ubuntu.com/manpages/trusty/man1/clang-modernize-3.4.1.html) documentation for more information). `clang-modernize` is not run on header files.
|`MODERNIZE_OPTIONS`|1|A string containing the command-line options to be passed to `clang-modernize`|Ignored if `MODERNIZE` flag not present. The command `clang-modernize [MODERNIZE_OPTIONS] [source file]` is run on each source file. See [Clang](http://manpages.ubuntu.com/manpages/trusty/man1/clang-modernize-3.4.1.html) documentation for more information. Alternatively, modernize options may be set using the environment variable `SA_MODERNIZE`.|
###Examples
Run SAS on all project directories except the project build directory and a directory called `test`:
```
enable_sas(IGNORE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/test)
```
Run all enabled SAS checkers on all project directories, checking formatting style and all clang-modernize transformations:
```
enable_sas(FORMAT MODERNIZE)
```
Run all enabled checkers except ROOT coding convention checkers on all project directories:
```
enable_sas(DISABLE_CHECKERS "sas.CodingConventions.ROOT")
```
Run all enabled checkers except specific ROOT coding convention checkers `RN3` and `RN4` on all project directories:
```
enable_sas(DISABLE_CHECKERS "sas.CodingConventions.ROOT.RN3" "sas.CodingConventions.ROOT.RN4")
```
Disable all SAS checkers and run clang-modernize on all source files, with the arguments `-risk=safe -loop-convert`:
```
enable_sas(DISABLE_CHECKERS "sas" MODERNIZE MODERNIZE_OPTIONS "-risk=safe -loop-convert")
```
##Blacklisting/Whitelisting Checkers
##Disabling Checkers in Comments