# SAS Checkers
An SAS checker is an object that identifies a particular language, tests its properties and returns a warning if a project's coding conventions are violated.

SAS checkers inherit from the `clang::ento::Checker` class (see [Clang documentation](http://clang.llvm.org/doxygen/classclang_1_1ento_1_1Checker.html)) and are defined in the "src" folder of the SAS source directory.

## Existing SAS checkers
The following checkers are included in SAS when shipped:
* Coding Convention Checkers (`sas.CodingConventions.[convention style].[checker name]`). There are three convention styles currently available (August 2016):
  * General: warns if `using namespace` or `using std` are found in headers, and if `std` printouts are detected.
  * FCCSW: warns if the [FCCSW naming conventions](https://github.com/jlingema/FCCSW/blob/master/doc/CppCodingStyleGuidelines.md) are broken.
  * ROOT: warns if the [ROOT naming conventions](https://root.cern.ch/TaligentDocs/TaligentOnline/DocumentRoot/1.0/Docs/books/WM/WM_63.html) are broken.
* Performance Checkers (`sas.Performance.[checker name]`). These warn if coding practices that may compromise performance are used.
* Thread Safety Checkers (`sas.ThreadSafety.[checker name]`). These warn if coding practices that may compromise thread safety are used.
* Example checker (`sas.Example.Varname`). This warns if a variable name does not start with a capital letter.

## Custom Checkers
Users may define their own project-specific checkers to customize SAS; these checkers will be run alongside other enabled SAS checks when the project source code is compiled.

### Generating Naming Convention Checkers from yaml
Naming conventions checkers for common declarations may be generated programmatically from a yaml file using the Python script `sas_convention_generator` found in the scripts subfolder of the SAS install directory. The script is called as follows:
```
sas_convention_generator [path to yaml file] [SAS source directory]/src/CodingConventions/[project name]
```
The checkers must be written to an empty subfolder in order for the checkers to be built correctly.
The yaml file must have the following structure:
```
---
project:
  name: "[project name]"
  author: "[project author]"
conventions:
  [object name]:
    name: "[name for checker]"
    regex: "[regular expression that matches a correctly named object]"
    description: "[warning messsage to be raised if the naming convention is broken]"
  [object name 2]:
    name: "[name for checker]"
    regex: "[regular expression that matches a correctly named object]"
    description: "[warning messsage to be raised if the naming convention is broken]"

```
As of August 2016 the allowed values for [object_name] are `Function`, `Type`, `TypeDef`, `ClassStructUnion`, `Enum`, `Enumerator`, `DataMember`, `Const`, `NameSpace`, `GlobalStatic`, `MemberStatic` and `LocalVariable`. An example of a working yaml file used to generate the FCCSW coding conventions may be found in the `config` subfolder of the SAS install directory.

To check other objects for naming convention violations, an additional field `ClangType` can be added to the `[object name]` dictionary, with the value of the name of the Clang `decl` object associated with the declaration (see [Clang documentation](http://clang.llvm.org/doxygen/classclang_1_1Decl.html)) for more details. In addition, if identification of the language construct is more involved than simply calling the `getNameAsString()` method on the `decl` object, an identifier template must be added to the `templates/identifiers` subfolder of the SAS install directory.

Once checkers have been added to the `src/CodingConventions` subfolder of the SAS source directory, adding the line
```
add_subdirectory([project name])
```
to the file `src/CodingConventions/CMakeLists.txt` will build and enable the new checkers when SAS is built.

### Writing custom checkers in C++
Users may also write their own checkers in C++ and add them to the `src` folder of the SAS source directory. The existing checkers may be used as a guide; [Clang documentation](http://clang.llvm.org/doxygen) may also be helpful.

A `CMakeLists.txt` file containing the line
```
add_checker([checker c++ filename])
```
for each checker written must be present in the directory in which the checkers are located, and the line
```
add_subdirectory([checker directory name])
```
must be added to the parent directory's `CMakeLists.txt` in order for the checkers to be compiled correctly when SAS is built.