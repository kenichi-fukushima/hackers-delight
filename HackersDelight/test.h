#ifndef TEST_H__
#define TEST_H__

#include <string>
#include <vector>

#include "base.h"

#define ENABLE_TESTS 1

namespace test {

std::string ToS(Word w);
Word ToW(const std::string& s);
Word SampleWord();

class TestCase {
 public:
  explicit TestCase(const std::string& name)
      : name_(name) {}

  const std::string& name() const { return name_; }

  virtual void Run() = 0;

 private:
  const std::string name_;
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

// Generates a property test to check equivalence of two binary functions.
#define EQ_BINARY_FUNC(a__, b__) \
  do { \
    /* These corner cases are always checked */ \
    std::vector<std::pair<Word, Word>> inputs = { \
        {0, 0}, \
        {0, ~0}, \
        {~0, 0}, \
        {~0, ~0}, \
    }; \
    for (int i = 0; i < 100; ++i) { \
      inputs.push_back(std::make_pair(test::SampleWord(), \
                                      test::SampleWord())); \
    } \
    for (int i = 0; i < inputs.size(); ++i) { \
      std::pair<Word, Word> p = inputs[i]; \
      if (a__(p.first, p.second) != b__(p.first, p.second)) { \
        __builtin_trap(); \
      } \
    } \
  } while (0)

#define TEST(name__) \
  class name__##Test : public test::TestCase { \
   public: \
    explicit name__##Test(const std::string& name) \
        : test::TestCase(name) {} \
    static name__##Test *Create() { \
      return new name__##Test(#name__); \
    } \
    virtual void Run(); \
    static name__##Test* instance; \
  }; \
  name__##Test *name__##Test::instance = \
      test::CreateAndRegisterTest<name__##Test>(); \
  void name__##Test::Run()

#else  // ENABLE_TESTS

#define EQ(converter, input, expected)
#define EQ_BINARY_FUNC(a__, b__)
#define TEST(name__) void WillNotRun##name__()

#endif  // ENABLE_TESTS

#endif  // TEST_H__
