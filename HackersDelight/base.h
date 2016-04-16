#ifndef BASE_H__
#define BASE_H__

#include <cinttypes>

typedef uint8_t Word;
static const size_t kWordSize = (sizeof(Word) * 8);

#define UNARY_FUNCN(e) [](Word x) -> Word { return (e); }
#define BINARY_FUNC(e) [](Word x, Word y) -> Word { return (e); }

#define CHECK(e) do { if (!(e)) { __builtin_trap(); } } while (0)

#endif  // BASE_H__
