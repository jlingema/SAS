# HTML Report Index
The report index displays the errors found in each file SAS checks are run on. An example of an HTML report index may be found [here](http://fccsw.web.cern.ch/fccsw/static_checks/FCCSW/index.html).

## Generating the Report Index
Once SAS has been run on a project using CMake, the outputs of the static analysis checks are written to files in the folder specified in the `COMPARISON_REPORT_DIR` argument of the `enable_sas()` CMake macro (see the [Using SAS](usingSAS.md) of SAS documentation for more details). From the project build directory, the command
```
make report_index
```
will generate the report index from these files, printing to the console the total number of errors found and a path to the index file. This calls the Python script `sas_create_index`, found in the `scripts` subfolder of the SAS install directory.

If SAS has been run directly on files using the `sas_check` script, providing that the `--comparison_report_dir` argument has been specified (see [Using SAS](usingSAS.md)), the `sas_create_index` script may be called directly:
```
sas_create_index [path to source directory] [path to comparison report directory] --ignore_dirs [any directories to be ignored]
```
If any comparison report files are found in the report directory matching files in the source directory, they will be included in the report index.

## Report Index Features
The sidebar on the left-hand side of the index page shows all subfolders of the project directory that have been checked using SAS. The number next to each directory or file name indicates the number of errors (both checker warnings and formatting/modernisation transformations, if applicable) in each, cumulatively in the case of a directory.

Clicking on a file on the sidebar will display a table in the centre of the index page. The original file is shown in the left-hand column, whilst, if clang-format or clang-modernize have been run, the formatted file is shown in the right. Currently (August 2016) if neither clang-format nor clang-modernize has been run, the left and right-hand sides of the table will show identical code.

In the left-hand column the table (original file), any warnings raised by the SAS checkers are displayed below the line they are triggered by.

The report index only displays files that contain at least one coding convention violation reported by the SAS checks run. All folders that SAS checks are run on are displayed, even if they contain no errors.
