#pragma once

//Copied directly from google benchmark, who in turn copied it from Chandler Carruth's talk. I'm not 100% sure if I'm allowed to do this, but whatever, it's 3 lines of code. It's distributed under Apache's license.

template <class Tp>
inline void DoNotOptimize(Tp const& value) {
  // Clang doesn't like the 'X' constraint on `value` and certain GCC versions
  // don't like the 'g' constraint. Attempt to placate them both.
#if defined(__clang__)
  asm volatile("" : : "g"(value) : "memory");
#else
  asm volatile("" : : "i,r,m"(value) : "memory");
#endif
}
