#ifndef TEST_H__
#define TEST_H__

#include <string>
#include <vector>

#include "base.h"

#define ENABLE_TESTS 1

namespace test {

std::string ToS(Word w);
Word ToW(const std::string& s);

class TestCase {
 public:
  virtual void Run() = 0;
};

void RegisterTest(TestCase *test);

template<class TestClass>
TestClass *CreateAndRegisterTest() {
  TestClass *test = TestClass::Create();
  RegisterTest(test);
  return test;
}

void RunTests();

}  // namespace test

#if ENABLE_TESTS

#define EQ(converter, input, expected) \
  do { \
    std::string actual = test::ToS(converter(test::ToW(#input))); \
    if (actual != #expected) { \
      __builtin_trap(); \
    } \
  } while (0)

#define TEST(name__) \
  class name__##Test : public test::TestCase { \
   public: \
    static name__##Test *Create() { \
      return new name__##Test; \
    } \
    virtual void Run(); \
    static name__##Test* instance; \
  }; \
  name__##Test *name__##Test::instance = \
  test::CreateAndRegisterTest<name__##Test>(); \
  void name__##Test::Run()

#else  // ENABLE_TESTS

#define EQ(converter, input, expected)
#define TEST(name__) void WillNotRun##name__()

#endif  // ENABLE_TESTS

#endif  // TEST_H__
