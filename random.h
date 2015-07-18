#ifndef RANDOM_H
#define RANDOM_H

#include <cstdint>
#include <type_traits>

namespace {

// Converts a uint64_t to an integral type,
// or returns the fraction of the uint64_t / UINT64_T_MAX.
template <typename T>
static inline T value(uint64_t bits)
{
  if (std::is_integral<T>::value) {
    return static_cast<T>(bits);
  } else if (std::is_floating_point<T>::value) {
    return static_cast<T>(bits)/~0ULL;
  }
  // T is probably not numerical, and this will error.
  return static_cast<T>(0);
}

// Returns the first bit of bits.
template <>
inline bool value<bool>(uint64_t bits)
{
  return bits & 1;
}

} // namespace

// PRNG based on the xorshift* algorithm.
class Random {
public:
  // Constructs a Random with the given 64 bit seed.
  Random(uint64_t seed);

  // Returns a random T that is uniformly distributed.
  // By default, returns a value between T_MIN and T_MAX
  // for integral types, and returns a value between 0 and 1
  // for floating point types.
  // To add an implementation for your own type, you
  // can implement template<> Random::next<YourType>().
  template <typename T>
  T next() {
    return value<T>(next());
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
