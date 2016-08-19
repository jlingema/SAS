/*
Expected Errors:
Enumerator Variable Name: 3
*/

enum TestEnum {
  kCorrectEnumerator, // Shouldn't raise any errors
  OmittedPrefixEnumerator, // Prefix "k" omitted
  klowerCamelCaseEnumerator, // Second letter should be uppercase
  kSnake_case_enumerator // Incorrect use of snake_case instead of CamelCase
};