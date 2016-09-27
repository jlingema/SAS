# Using SAS
This section assumes SAS has been installed as detailed in the [Building and Installing](../README.md/#buildingAndInstalling) section of the SAS `README`.
## Running SAS on a single file
The Python script `sas_check` in the `scripts` subfolder of the SAS install directory can be used to check a single source file or for coding convention violations. To run all enabled SAS checks on a file, use the command
```
sas_check [path to source file] --checkers="sas" [compiler flags]
```
The following optional arguments can be passed to `sas_check` (see `sas_check --help`):
*  `--checkers`: the checkers to be run on the source file.
* `--check_format`: If present, `clang-format` is run on source and header files, checking code formatting style. Style must be specified in a yaml file named `.clang-format` in the project base directory; if none can be found LLVM style is used. See [clang-format](http://clang.llvm.org/docs/ClangFormat.html) documentation for more information.
* `--comparison_report_dir`: If specified, the output of the checks is written to files in this directory. Designed to be used to create an html index using the `sas_create_index` function in the `scripts` subfolder of the SAS install directory. If not specified, checker outputs will not be saved and no report index can be created.
* `--disable_checkers`: checkers to be disabled (usage: if a family of checkers, e.g. `sas.CodingConventions` is enabled, individual checkers within that family may be disabled)
* `--do_not_compile`: If present, the Clang compiler is not called on the specified file (only `clang-modernize` and `clang-format`, if enabled, will be run).
* `--ignore_directories`: If the source file is in one of the directories specified, no static analysis checks will be run on it (used when running SAS on a project in CMake)
* `--modernize`: If present, `clang-modernize` is run on source and header files, checking for possible use of modern (post C++11) language constructs. If `--modernize_options` are specified, these will be used; if not `clang-modernize [source file]` will be run, running all clang-modernize checks (see [clang-modernize](http://manpages.ubuntu.com/manpages/trusty/man1/clang-modernize-3.4.1.html) documentation for more information).
* `--modernize_options`: A string containing the command-line options to be passed to `clang-modernize`, e.g. `-risk=safe -loop-convert` (See [Clang](http://manpages.ubuntu.com/manpages/trusty/man1/clang-modernize-3.4.1.html) documentation for more information). The command `clang-modernize [modernize_options] [source file]` is run on the source file.
* `--sa_configuration`: Path to a json file containing information for [blacklisting/whitelisting](#BWList) checkers.
* `--source_dir`: Path to the top-level source directory; this must be present in order to generate a comparison report.
* `--verbose`: If present, the output of clang-modernize and clang-format (if applicable) is printed to the console in a unified diff form.

Any additional arguments passed to the script will be passed directly to the Clang++ compiler; see [Clang](http://clang.llvm.org/docs/CommandGuide/clang.html) documentation pages for more information.

## <a id="usingCmake"></a>Running SAS Using CMake
As mentioned in the [Using SAS](README.md/#usingSAS) section of the README, adding the following lines to a project's main `CMakeLists.txt` will run SAS on all source and header files in the project build at compilation time:
```
find_package(sas)
enable_sas()
```
The CMake macro `enable_sas()` replaces the default C++ compiler with the SAS Clang wrapper and applies user-determined options specifying which checks are to be run, and which directories the checks are to be run on. It is defined in the `sasConfig.cmake` file in the SAS install directory.

Calling `enable_sas()` with no arguments will run all available SAS checkers on all source files and headers that are included in the project build. Code formatting style and use of modern C++ constructs will not be checked.

The following options may be passed to `enable_sas()`:

* `COMPARISON_REPORT_DIR`: Absolute path to a directory where the report files are to be generated. Defaults to the directory `sasreport` in the project build directory if not specified. If the directory specified does not exist, it will be created.
* `DISABLE_CHECKERS`: one or more names of checkers to be disabled
* `FORMAT` If present, `clang-format` is run on source and header files, checking code formatting style. Style must be specified in a yaml file named `.clang-format` in the project base directory; if none can be found LLVM style is used. See [Clang](http://clang.llvm.org/docs/ClangFormat.html) documentation for more information.
* `IGNORE_DIRS`: one or more absolute paths to subdirectories of the project source directory on which SAS checks are not to be run. These directories are still compiled, but no SAS checks are run at compile time, and they are omitted from the report index. The CMake binary directory is automatically ignored.
* `MODERNIZE`: If present, `clang-modernize` is run on source and header files, checking for possible use of modern (post C++11) language constructs. If `MODERNIZE_OPTIONS` are specified, these will be used; if not `clang-modernize [source file]` will be run, running all clang-modernize checks (see [Clang](http://manpages.ubuntu.com/manpages/trusty/man1/clang-modernize-3.4.1.html) documentation for more information). `clang-modernize` is not run on header files.
* `MODERNIZE_OPTIONS`: A string containing the command-line options to be passed to `clang-modernize`. Ignored if `MODERNIZE` flag not present. The command `clang-modernize [MODERNIZE_OPTIONS] [source file]` is run on each source file. See [Clang](http://manpages.ubuntu.com/manpages/trusty/man1/clang-modernize-3.4.1.html) documentation for more information.
* `VERBOSE`: If present, the output of clang-modernize and clang-format (if applicable) is printed to the console in a unified diff form.

### Applying Changes
**WARNING** this is very experimental. This command will override your source files, so only use with caution! In order to apply all clang-modernize and/or clang-format transformations found after SAS has been run, the command
```
make apply
```
can be used. This will overwrite all files with clang-modernize or clang-format transformations available and cannot be undone.

###Examples
Run SAS on all project directories except directories named `ignore1` and `ignore2`:
```
enable_sas(IGNORE_DIRECTORIES ${PROJECT_SOURCE_DIR}/ignore1 ${PROJECT_SOURCE_DIR}/ignore2)
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

## Using Clang with SAS checks
Users may run SAS checks on source files when compiling with Clang by passing the `-analyzer-checker` argument to the Clang compiler. The following command enables the analyzer, and loads and enables SAS checkers.
```
clang++ [compiler options]  -Xclang -analyze -Xclang -analyzer-output=text -Xclang -load -Xclang $SASBUILDDIR/lib/libSas.so -Xclang -analyzer-checker=[Checker1] -Xclang -analyzer-checker=[Checker2] ... -analyzer-checker=[CheckerN]
```
See [Clang](http://clang.llvm.org/docs/CommandGuide/clang.html) documentation pages for more information.

## Using scan-build with SAS checks
Similarly, users may run SAS checks when compiling with scan-build. The following command loads SAS checkers
```
scan-build -load-plugin $SASBUILDDIR/lib/libSas.so -enable-checker [Checker1] enable-checker [Checker2] ... enable-checker [CheckerN]\
           -disable-checker [CheckerA] -disable-checker [CheckerB] ... \
           -o [path to report directory] make
```
For more information see [scan-build](http://clang-analyzer.llvm.org/scan-build.html) documentation.

## Steering Static Analysis Using Environment Variables
**Deprecated** - use CMake, or pass options to the `sas_check` script, instead.

Static analysis may also be invoked by calling `sas_check` using only compiler arguments and setting environmental variables. The command used is as follows:
```
sas_check [path to source file] [compiler arguments]
```
The environment variables used to invoke static analysis are:
* `SA_CHECKERS`: a colon-separated list of checkers to be enabled.
* `SA_FORMATTING`: if this variable is set, formatting style will be checked (identical to the `--check_format` argument of the Python script).
* `SA_MODERNIZE`: if this variable is set, clang-modernize is run with the value of the variable passed as arguments.
* `SA_CONFIGURATION`: the path to a yaml file 
* `SA_PLUGIN`: path to a json file containing information for [blacklisting/whitelisting](#BWList) checkers.

Note that environment variables take priority over arguments passed to the script.

## Disabling Checkers
It may be desirable to disable checkers for a certain part of a project's code to avoid false positives, or, for example, if the project contains third-party code that should not conform to the project's coding conventions. This is possible via a number of methods.
### Using CMake
For a coarse approach, the arguments `DISABLE_CHECKERS` and `IGNORE_DIRECTORIES` of the `enable_sas()` macro can be used to respectively disable certain checkers for all files, or all checkers for certain files (see [above](#usingCmake)).
### <a id="BWList"></a>Blacklisting/Whitelisting
Checkers may be disabled within a file or directory using a json file detailing a blacklist (list of checkers to be disabled) or whitelist (list of checkers to be enabled). The json file may be provided by setting the environment variable `SA_CONFIGURATION` to the path to the file, or by including a file named `.sas.json` in the working directory to which the configuration applies. The environment variable is prioritised over the presence of a file.

A checker may be blacklisted or whitelisted for a given file path, namespace, class or struct. The json file should contain a single object, with a field `"CONFIGURATION"` containing an an array of the blacklists/whitelists, for example:
```
{"CONFIGURATION": [
    {
        "FILE_PATH": ["blacklisted/file/path"],
        "NAMESPACE": ["blacklistednamespace"],
        "CLASS": ["BlacklistedClassName"],
        "STRUCT": ["BlacklistedStructName"],
        "CHECKER": ["sas.Blacklisted.Checker1", "sas.Blacklisted.Checker2"],
        "B/W": "B"
    },
    {
        "FILE_PATH": ["whitelisted/file/path"],
        "NAMESPACE": ["whitelistednamespace"],
        "CLASS": ["WhitelistedClassName"],
        "STRUCT": ["WhitelistedStructName"],
        "CHECKER": ["sas.BlacklistedWhitelisted.Checker1", "sas.Whitelisted.Checker2"],
        "B/W": "W"
    }
]}
```
An asterisk (`*`) may be used as a wildcard to match any number of characters.

### Disabling Checkers from within Source Code
A checker may be disabled for an individual line of code by adding a comment to the line immediately preceding it. The comment must start with two forward slashes (`//`) and must contain the text `sas[disable_checker : "CheckerName"]`, with quotes and spaces either side of the colon, and with `CheckerName` replaced by the name of the checker to be disabled. The checker will only be disabled for the line immediately following the comment, and C-style comments (`/* */`) will not disable checkers.

Example:
```
int main() {
  // sas[disable_checker : "sas.Example.Varname"]
  int noWarning;
  int warningRaised;

  return 0;
}
```
The example checker (checks convention of variable names beginning with capital letters) will not pick up violations for the variable `noWarning`, as it has been disabled on this line by the preceding comment. The line containing the variable declaration `warningRaised` has no checkers disabled, and so will be picked up by the checker.
