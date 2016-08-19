/*
Expected Errors:
Constant Variable Name: 3
*/

const int kCorrectlyNamedConstant = 0; // Shouldn't raise any errors
const double OmittedPrefix = 0.0; // Prefix "k" omitted
const char klowerCamelCase = 'a'; // Second letter should be uppercase
const float kSnake_case = 0.0; // Incorrect use of snake_case instead of CamelCase