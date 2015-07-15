#ifndef RANDOM_H
#define RANDOM_H

#include <cstdint>

// PRNG based on the xorshift* algorithm.
class Random {
public:
  // Constructs a Random with the given 64 bit seed.
  Random(uint64_t seed);

  // Generates a random T.
  template <typename T>
  T next() {
    return static_cast<T>(next());
  }

private:
  // Current state.
  int p;

  // Stored states.
  uint64_t s[16];

  // Returns a random number in [0, 2**64-1].
  uint64_t next();
};

#endif // RANDOM_H
