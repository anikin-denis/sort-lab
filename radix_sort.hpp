#include <cstddef>
#include <cstdint>

using namespace std;

void radix_sort(unsigned int* in, unsigned int* out, size_t size) {
  if (size == 0) return;

  unsigned int* temp = new unsigned int[size];
  unsigned int* src = in;
  unsigned int* dst = out;
  size_t* counts = new size_t[256];

  for (int pass = 0; pass < 4; ++pass) {
    for (size_t i = 0; i < 256; ++i) counts[i] = 0;
    int shift = pass * 8;

    for (size_t i = 0; i < size; ++i) {
      uint32_t key = src[i];
      ++counts[(key >> shift) & 0xFFu];
    }

    size_t offset = 0;
    for (size_t i = 0; i < 256; ++i) {
      size_t c = counts[i];
      counts[i] = offset;
      offset += c;
    }

    for (size_t i = 0; i < size; ++i) {
      uint32_t key = src[i];
      size_t bucket = (key >> shift) & 0xFFu;
      dst[counts[bucket]++] = src[i];
    }

    src = dst;
    dst = (dst == out ? temp : out);
  }

  if (src != out) {
    for (size_t i = 0; i < size; ++i) out[i] = src[i];
  }

  delete[] temp;
  delete[] counts;
}
