#include "random.h"

#include <cstdint>

Random::Random(uint64_t seed)
{
  for (int i = 0; i < 16; i++) {
    seed ^= seed >> 12;
    seed ^= seed << 25;
    seed ^= seed >> 27;
    s[i] = seed * 2685821657736338717ULL;
  }
}

// Credit to Sebastiano Vigna (vigna@acm.org).
uint64_t Random::next()
{
  uint64_t s0 = s[p];
  uint64_t s1 = s[p = (p+1)&15];
  s1 ^= s1 << 31;
  s1 ^= s1 >> 11;
  s0 ^= s0 >> 30;
  return (s[p] = s0^s1) * 1181783497276652981ULL;
}
