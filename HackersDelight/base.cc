#include "base.h"

Word BitwiseEquiv(Word x, Word y) {
  return ~(x ^ y);
}
