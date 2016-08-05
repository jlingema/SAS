/*
Expected Errors:
Type name: 4
*/

class CorrectlyNamedClass { // Shouldn't raise any errors
  enum lowercaseNestedEnum { // First letter incorrectly lowercase

  };
};

struct lowerCamelCase { // First letter incorrectly lowercase

};

typedef int Snake_Case; // Incorrect use of snake_case instead of CamelCase

template<typename T> class Foo {}; // Typename too short
