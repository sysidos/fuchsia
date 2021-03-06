/*
  Adapted from:
  https://github.com/akalenuk/wordsandbuttons/blob/master/exp/sort/radix/trie.h

  This is free and unencumbered software released into the public domain.

  Anyone is free to copy, modify, publish, use, compile, sell, or
  distribute this software, either in source code form or as a compiled
  binary, for any purpose, commercial or non-commercial, and by any
  means.

  In jurisdictions that recognize copyright laws, the author or authors
  of this software dedicate any and all copyright interest in the
  software to the public domain. We make this dedication for the benefit
  of the public at large and to the detriment of our heirs and
  successors. We intend this dedication to be an overt act of
  relinquishment in perpetuity of all present and future rights to this
  software under copyright law.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.

  For more information, please refer to <http://unlicense.org>
*/

#ifndef GARNET_EXAMPLES_PROFILER_TRIE_H_
#define GARNET_EXAMPLES_PROFILER_TRIE_H_

#include <array>
#include <string>
#include <vector>

namespace Trie {
template <unsigned int RADIX_BITS>
struct ConstantsFor {
  static_assert(RADIX_BITS == 1 || RADIX_BITS == 2 || RADIX_BITS == 4 || RADIX_BITS == 8,
                "Radix sizes supported: 1, 2, 4, 8.");
  constexpr static unsigned int mask(unsigned int radix_bits) {
    return (radix_bits == 1) ? 1 : (1 + (mask(radix_bits - 1) << 1));
  }
  constexpr static unsigned int pow_of_2(unsigned int exp) {
    return (exp == 1) ? 2 : (2 * pow_of_2(exp - 1));
  }
  constexpr static unsigned int radix_mask = mask(RADIX_BITS);
  constexpr static unsigned int steps_in_byte = 8 / RADIX_BITS;
  constexpr static unsigned int subtries_size = pow_of_2(RADIX_BITS);
};

// Set-like structure illustrating radix sort.
template <unsigned int RADIX_BITS>
struct Set : public ConstantsFor<RADIX_BITS> {
  std::array<Set*, ConstantsFor<RADIX_BITS>::subtries_size> subtries = {{nullptr}};
  unsigned int elements_counter = 0u;

  ~Set() {
    for (auto trie : subtries)
      if (trie != nullptr)
        delete trie;
  }

  void store(const std::string& key) {
    Set* trie = this;
    for (auto i = 0u; i < key.size(); ++i) {
      for (auto j = 0u; j < ConstantsFor<RADIX_BITS>::steps_in_byte; ++j) {
        const int shifted_c = key[i] >> (8 - (j + 1) * RADIX_BITS);
        const int radix0 = shifted_c & ConstantsFor<RADIX_BITS>::radix_mask;
        if (trie->subtries[radix0] == nullptr)
          trie->subtries[radix0] = new Set();
        trie = trie->subtries[radix0];
      }
    }
    ++trie->elements_counter;
  }

  bool contains(const std::string& key) {
    Set* trie = this;
    for (auto i = 0u; i < key.size(); ++i) {
      for (auto j = 0u; j < ConstantsFor<RADIX_BITS>::steps_in_byte; ++j) {
        const int shifted_c = key[i] >> (8 - (j + 1) * RADIX_BITS);
        const int radix0 = shifted_c & ConstantsFor<RADIX_BITS>::radix_mask;
        if (trie->subtries[radix0] == nullptr)
          return false;
        trie = trie->subtries[radix0];
      }
    }
    return true;
  }

  static void fill_vector_sorted(Set* trie, std::vector<std::string>& sorted) {
    std::string key;
    key.resize(256);  // 256 is big enough for testing. Dynamic is better, but
                      // this makes code simpler.
    fill_vector_sorted(trie, sorted, key, 0);
  }

 private:
  static void fill_vector_sorted(Set* trie, std::vector<std::string>& sorted, std::string& key,
                                 int depth) {
    const auto byte_idx = depth / ConstantsFor<RADIX_BITS>::steps_in_byte;
    const auto radix_idx = depth % ConstantsFor<RADIX_BITS>::steps_in_byte;
    for (auto i = 0u; i < trie->elements_counter; ++i)
      sorted.emplace_back(key.begin(), key.begin() + byte_idx);
    for (auto i = 0u; i < ConstantsFor<RADIX_BITS>::subtries_size; ++i) {
      if (trie->subtries[i] != nullptr) {
        auto shift = (ConstantsFor<RADIX_BITS>::steps_in_byte - radix_idx - 1) * RADIX_BITS;
        key[byte_idx] &= ~(ConstantsFor<RADIX_BITS>::radix_mask << shift);
        key[byte_idx] |= i << shift;
        fill_vector_sorted(trie->subtries[i], sorted, key, depth + 1);
      }
    }
  }
};

// Map-like structure to store and retrieve data.
template <class T, unsigned int RADIX_BITS>
struct Map : public ConstantsFor<RADIX_BITS> {
  std::array<Map*, ConstantsFor<RADIX_BITS>::subtries_size> subtries = {{nullptr}};
  T value;

  ~Map() {
    for (auto trie : subtries)
      if (trie != nullptr)
        delete trie;
  }

  void store(const std::string& key, T value) {
    Map* trie = this;
    for (auto i = 0u; i < key.size(); ++i) {
      for (auto j = 0u; j < ConstantsFor<RADIX_BITS>::steps_in_byte; ++j) {
        const int shifted_c = key[i] >> (8 - (j + 1) * RADIX_BITS);
        const int radix0 = shifted_c & ConstantsFor<RADIX_BITS>::radix_mask;
        if (trie->subtries[radix0] == nullptr)
          trie->subtries[radix0] = new Map();
        trie = trie->subtries[radix0];
      }
    }
    trie->value = value;
  }

  std::pair<bool, T> retrieve(const std::string& key) {
    Map* trie = this;
    for (auto i = 0u; i < key.size(); ++i) {
      for (auto j = 0u; j < ConstantsFor<RADIX_BITS>::steps_in_byte; ++j) {
        const int shifted_c = key[i] >> (8 - (j + 1) * RADIX_BITS);
        const int radix0 = shifted_c & ConstantsFor<RADIX_BITS>::radix_mask;
        if (trie->subtries[radix0] == nullptr)
          return {false, T()};
        trie = trie->subtries[radix0];
      }
    }
    return {true, trie->value};
  }

  size_t size_in_bytes() {
    size_t bytes = sizeof(Map<T, RADIX_BITS>);
    for (auto i = 0u; i < ConstantsFor<RADIX_BITS>::subtries_size; ++i)
      if (subtries[i] != nullptr)
        bytes += subtries[i]->size_in_bytes();
    return bytes;
  }
};
}  // namespace Trie
#endif  // GARNET_EXAMPLES_PROFILER_TRIE_H_
