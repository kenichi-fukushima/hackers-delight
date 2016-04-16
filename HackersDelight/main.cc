#include "base.h"
#include "test.h"

#pragma mark 2.1 Manipulating rightmost bits

Word TurnOffRightmost1(Word x) {
  return x & (x - 1);
}

TEST(TurnOffRightmost1) {
  EQ(TurnOffRightmost1, 10100101, 10100100);
  EQ(TurnOffRightmost1, 10100100, 10100000);
  EQ(TurnOffRightmost1, 10100000, 10000000);

  EQ(TurnOffRightmost1, 00000000, 00000000);
  EQ(TurnOffRightmost1, 11111111, 11111110);
}

bool IsPowerOf2(Word x) {
  return x != 0 && TurnOffRightmost1(x) == 0;
}

Word TurnOnRightmost0(Word x) {
  return x | (x + 1);
}

TEST(TurnOnRightmost0) {
  EQ(TurnOnRightmost0, 00100100, 00100101);
  EQ(TurnOnRightmost0, 00100101, 00100111);
  EQ(TurnOnRightmost0, 00100111, 00101111);

  EQ(TurnOnRightmost0, 00000000, 00000001);
  EQ(TurnOnRightmost0, 11111111, 11111111);
}

Word TurnOffTrailing1s(Word x) {
  return x & (x + 1);
}

TEST(TurnOffTrailing1s) {
  EQ(TurnOffTrailing1s, 00100101, 00100100);
  EQ(TurnOffTrailing1s, 00100111, 00100000);

  EQ(TurnOffTrailing1s, 00000000, 00000000);
  EQ(TurnOffTrailing1s, 11111111, 00000000);
}

Word TurnOnTrailing0s(Word x) {
  return x | (x - 1);
}

TEST(TurnOnTrailing0s) {
  EQ(TurnOnTrailing0s, 10100100, 10100111);
  EQ(TurnOnTrailing0s, 10100000, 10111111);

  EQ(TurnOnTrailing0s, 00000000, 11111111);
  EQ(TurnOnTrailing0s, 11111111, 11111111);
}

Word Single1AtRightmost0Position(Word x) {
  return ~x & (x + 1);
}

TEST(Single1AtRightmost0Position) {
  EQ(Single1AtRightmost0Position, 10100100, 00000001);
  EQ(Single1AtRightmost0Position, 10100101, 00000010);
  EQ(Single1AtRightmost0Position, 10100111, 00001000);

  EQ(Single1AtRightmost0Position, 00000000, 00000001);
  EQ(Single1AtRightmost0Position, 11111111, 00000000);
}

Word Single0AtRightmost1Position(Word x) {
  return ~x | (x - 1);
}

TEST(Single0AtRightmost1Position) {
  EQ(Single0AtRightmost1Position, 10100101, 11111110);
  EQ(Single0AtRightmost1Position, 10100100, 11111011);
  EQ(Single0AtRightmost1Position, 10100000, 11011111);

  EQ(Single0AtRightmost1Position, 00000000, 11111111);
  EQ(Single0AtRightmost1Position, 11111111, 11111110);
}

Word __Trailing1sAtPositionsOfTrailing0s_A(Word x) {
  return ~x & (x - 1);
}

Word __Trailing1sAtPositionsOfTrailing0s_B(Word x) {
  return ~(x | -x);
}

Word __Trailing1sAtPositionsOfTrailing0s_C(Word x) {
  return (x & -x) - 1;
}

Word Trailing1sAtPositionsOfTrailing0s(Word x) {
  return __Trailing1sAtPositionsOfTrailing0s_A(x);
}

TEST(Trailing1sAtPositionsOfTrailing0s) {
  EQ(Trailing1sAtPositionsOfTrailing0s, 10100101, 00000000);
  EQ(Trailing1sAtPositionsOfTrailing0s, 10100100, 00000011);
  EQ(Trailing1sAtPositionsOfTrailing0s, 10100000, 00011111);

  EQ(Trailing1sAtPositionsOfTrailing0s, 00000000, 11111111);
  EQ(Trailing1sAtPositionsOfTrailing0s, 11111111, 00000000);
}

Word Trailing0sAtPositionsOfTrailing1s(Word x) {
  return ~x | (x + 1);
}

TEST(Trailing0sAtPositionsOfTrailing1s) {
  EQ(Trailing0sAtPositionsOfTrailing1s, 10100100, 11111111);
  EQ(Trailing0sAtPositionsOfTrailing1s, 10100101, 11111110);
  EQ(Trailing0sAtPositionsOfTrailing1s, 10100111, 11111000);

  EQ(Trailing0sAtPositionsOfTrailing1s, 00000000, 11111111);
  EQ(Trailing0sAtPositionsOfTrailing1s, 11111111, 00000000);
}

Word IsolateRightmost1(Word x) {
  return x & -x;
}

TEST(IsolateRightmost1) {
  EQ(IsolateRightmost1, 10100011, 00000001);
  EQ(IsolateRightmost1, 10100100, 00000100);
  EQ(IsolateRightmost1, 10100000, 00100000);

  EQ(IsolateRightmost1, 00000000, 00000000);
  EQ(IsolateRightmost1, 11111111, 00000001);
}

Word Trailing1sAtPositionsOfRightmost1AndTrailing0s(Word x) {
  return x ^ (x - 1);
}

TEST(Trailing1sAtPositionsOfRightmost1AndTrailing0s) {
  EQ(Trailing1sAtPositionsOfRightmost1AndTrailing0s, 10100101, 00000001);
  EQ(Trailing1sAtPositionsOfRightmost1AndTrailing0s, 10100100, 00000111);
  EQ(Trailing1sAtPositionsOfRightmost1AndTrailing0s, 10100000, 00111111);

  EQ(Trailing1sAtPositionsOfRightmost1AndTrailing0s, 00000000, 11111111);
  EQ(Trailing1sAtPositionsOfRightmost1AndTrailing0s, 11111111, 00000001);
}

Word Trailing1sAtPositionsOfRightmost0AndTrailing1s(Word x) {
  return x ^ (x + 1);
}

TEST(Trailing1sAtPositionsOfRightmost0AndTrailing1s) {
  EQ(Trailing1sAtPositionsOfRightmost0AndTrailing1s, 10100100, 00000001);
  EQ(Trailing1sAtPositionsOfRightmost0AndTrailing1s, 10100101, 00000011);
  EQ(Trailing1sAtPositionsOfRightmost0AndTrailing1s, 10100111, 00001111);

  EQ(Trailing1sAtPositionsOfRightmost0AndTrailing1s, 00000000, 00000001);
  EQ(Trailing1sAtPositionsOfRightmost0AndTrailing1s, 11111111, 11111111);
}

Word __TurnOffRightmostContiguous1s_A(Word x) {
  return (TurnOnTrailing0s(x) + 1) & x;
}

Word __TurnOffRightmostContiguous1s_B(Word x) {
  return (IsolateRightmost1(x) + x) & x;
}

Word TurnOffRightmostContiguous1s(Word x) {
  return __TurnOffRightmostContiguous1s_B(x);
}

TEST(TurnOffRightmostContiguous1s) {
  EQ(TurnOffRightmostContiguous1s, 10101101, 10101100);
  EQ(TurnOffRightmostContiguous1s, 10101111, 10100000);
  EQ(TurnOffRightmostContiguous1s, 10101100, 10100000);

  EQ(TurnOffRightmostContiguous1s, 00000000, 00000000);
  EQ(TurnOffRightmostContiguous1s, 11111111, 00000000);
}

#pragma mark De Morgan's Laws Extended

TEST(DeMorganBitwiseAnd) {
  EQ_BINARY_FUNC(BINARY_FUNC( ~(x & y) ),
                 BINARY_FUNC( ~x | ~y) );
}

int main(int argc, const char * argv[]) {
  test::RunTests();
  return 0;
}
