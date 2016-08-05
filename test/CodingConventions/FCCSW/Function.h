#ifndef TESTFUNCTIONNAMES
#define TESTFUNCTIONNAMES

/*
Expected Errors:
Function Name: 3
*/

void correctlyNamedTestFunction(); // Shouldn't raise any errors
double UpperCamelCaseFunction(int arg1, float arg2); // First letter incorrectly capitalised
char *snake_case_function(char arg1); // incorrect use of snake_case instead of camelCase

class TestFunctions {
public:
  TestFunctions();
  ~TestFunctions();
  // Constructor and destructor shouldn't be flagged
private:
  int m_functionNotAMemberVariable(); // Function incorrectly named like a member variable
};

#endif