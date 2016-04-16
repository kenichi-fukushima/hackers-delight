#ifndef BASE_H__
#define BASE_H__

#include <cinttypes>
#include <functional>
#include <string>

typedef uint8_t Word;
static const size_t kWordSize = (sizeof(Word) * 8);

typedef std::function<Word(Word)> UnaryFunction;
typedef std::function<Word(Word, Word)> BinaryFunction;

class UnaryFunctionWrapper {
 public:
  explicit UnaryFunctionWrapper(UnaryFunction function,
                                const std::string& description)
    : _function(function), _description(description) {}

  UnaryFunction function() const { return _function; }
  const std::string& description() const { return _description; }

 private:
  const UnaryFunction _function;
  const std::string _description;
};

class BinaryFunctionWrapper {
 public:
  explicit BinaryFunctionWrapper(BinaryFunction function,
                                 const std::string& description)
    : _function(function), _description(description) {}

  BinaryFunction function() const { return _function; }
  const std::string& description() const { return _description; }

private:
  const BinaryFunction _function;
  const std::string _description;
};

#define UNARY_FUNC(e) \
    UnaryFunctionWrapper([](Word x) -> Word { return (e); }, #e)
#define BINARY_FUNC(e) \
    BinaryFunctionWrapper([](Word x, Word y) -> Word { return (e); }, #e)

#define CHECK(e) do { if (!(e)) { __builtin_trap(); } } while (0)

Word BitwiseEquiv(Word x, Word y);

#endif  // BASE_H__
