/*
Expected Errors:
Data Member Variable Name: 3
*/

class TestMemberVariables {
public:
  int m_correctlyNamedMemberVariable; // Shouldn't raise any error
  float omittingPrefix; // "m_" incorrectly omitted

private:
  char m_UpperCamelCaseMemberVariable; // Incorrect uppercase letter after "m_"
  double m_snake_case_member_variable; // Incorrect snake_case instead of camelCase
};

struct TestMemberVariableStruct {
public:
  int exceptionForStructsMemberVariable; //Shouldn't raise any error; public member varibales of structs are exempt
};
