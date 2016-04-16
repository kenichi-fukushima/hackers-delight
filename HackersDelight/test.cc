#include "test.h"

#include <iostream>
#include <sstream>

namespace test {

std::vector<TestCase*>* gTests;

std::string ToS(Word w) {
  std::ostringstream os;
  size_t len = 0;
  while (w) {
    os << (w & 1);
    w >>= 1;
    len += 1;
  }
  for (int i = 0; i < kWordSize - len; ++i) {
    os << '0';
  }
  std::string s = os.str();
  std::reverse(s.begin(), s.end());
  return s;
}

Word ToW(const std::string& s) {
  CHECK(s.length() <= kWordSize);
  Word w;
  for (int i = 0; i < s.length(); ++i) {
    if (i > 0) {
      w <<= 1;
    }
    w += (s[i] == '1' ? 1 : 0);
  }
  return w;
}

void RegisterTest(TestCase *test) {
  if (!gTests) {
    gTests = new std::vector<TestCase*>;
  }
  gTests->push_back(test);
}

void RunTests() {
  if (!gTests) {
    return;
  }
  for (int i = 0; i < gTests->size(); ++i) {
    const TestCase& test_case= *(*gTests)[i];
    std::cout << "Start " << test_case.name() << "\n";
    (*gTests)[i]->Run();
    std::cout << "Finish " << test_case.name() << "\n";
  }
}

}  // namespace test
