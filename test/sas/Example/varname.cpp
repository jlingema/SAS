// Author: Filip Bartek (2013)

// Test case for checker sas.example.Varname

// Bugs: 1

int main(void) {
  int variable; // bug: doesn't begin with uppercase
  int Variable; // not bug: begins with uppercase
  return 0;
}
