#ifndef TESTCONSTANTNAMES
#define TESTCONSTANTNAMES

/*
Expected Errors:
Constant Variable Name: 3
Enumerator Variable Name: 3
*/

const int kCorrectlyNamedConstant = 0; // Shouldn't raise any errors
const double OmittedPrefix = 0.0; // Prefix "k" omitted
const char klowerCamelCase = 'a'; // Second letter should be uppercase
const float kSnake_case = 0.0; // Incorrect use of snake_case instead of CamelCase
enum TestEnum1 {
  kCorrectEnumerator, // Shouldn't raise any errors
};
enum TestEnum2 {
  OmittedPrefixEnumerator, // Prefix "k" omitted
};
enum TestEnum3 {
  klowerCamelCaseEnumerator, // Second letter should be uppercase
};
enum TestEnum4 {
  kSnake_case_enumerator // Incorrect use of snake_case instead of CamelCase
};

#endif