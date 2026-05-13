#include <chrono>
#include <cstddef>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <iomanip>

#include "merge_sort.hpp"
#include "radix_sort.hpp"
//add sort algorithm headers here

using namespace std;

struct Algorithm {
  const char* name;
  void (*sort)(unsigned int*, unsigned int*, size_t);
};

const Algorithm algorithms[] = {
  {"Merge", merge_sort},
  {"Radix", radix_sort},
  //add lablel and function pointers here
};

const size_t sizes[] = {10, 1000, 10000, 1000000, 100000000};
const char* sizeLabels[] = {"10", "1k", "10k", "1M", "100M"};
const size_t sizeCount = sizeof(sizes) / sizeof(sizes[0]);
const size_t maxSize = 100000000;
const double stopSeconds = 0.01;
const size_t algorithmCount = 2;

void fill(unsigned int* out) {
  std::minstd_rand gen(12345);
  for (size_t i = 0; i < maxSize; ++i) out[i] = gen();
}

void trim(const unsigned int* in, unsigned int* out) {
  for (size_t i = 0; i < maxSize; ++i) out[i] = in[i] & 0xFFu;
}	    

void downsample(const unsigned int* in, unsigned int* out, size_t out_size) {
  size_t step = maxSize / out_size;
  for (size_t i = 0; i < out_size; ++i) out[i] = in[i * step];
}

void reverse(unsigned int* a, size_t n) {
  for (size_t i = 0; i < n / 2; ++i) {
    unsigned int t = a[i];
    a[i] = a[n - 1 - i];
    a[n - 1 - i] = t;
  }
}

bool sorted(const unsigned int* a, size_t n) {
  for (size_t i = 1; i < n; ++i) {
    if (a[i - 1] > a[i]) return false;
  }
  return true;
}

string format_seconds(double seconds) {
  ostringstream ss;
  ss.setf(ios::fixed);
  ss.precision(8);
  ss << seconds << " s";
  return ss.str();
}

void print_table(const string& title, const Algorithm* algorithms, const string cells[algorithmCount][sizeCount]) {
  cout << "\n" << title << "\n";
  cout << left << setw(16) << "Algorithm/Size";
  for (size_t s = 0; s < sizeCount; ++s) cout << left << setw(16) << sizeLabels[s];
  cout << "\n";

  for (size_t a = 0; a < algorithmCount; ++a) {
    cout << left << setw(16)  << algorithms[a].name;
    for (size_t s = 0; s < sizeCount; ++s) {
      cout << left << setw(16) << cells[a][s];
    }
    cout << "\n";
  }
}

void run(const unsigned int* longest, const Algorithm* algorithms, string cells[algorithmCount][sizeCount]) {
  bool allow_next[algorithmCount];
  for (size_t a = 0; a < algorithmCount; ++a) {
    allow_next[a] = true;
    for (size_t s = 0; s < sizeCount; ++s) cells[a][s] = "SKIP";
  }

  for (size_t s = 0; s < sizeCount; ++s) {
    const size_t n = sizes[s];
    unsigned int* base = new unsigned int[n];
    downsample(longest, base, n);

    for (size_t a = 0; a < algorithmCount; ++a) {
      if (!allow_next[a]) continue;

      unsigned int* in = new unsigned int[n];
      unsigned int* out = new unsigned int[n];
      for (size_t i = 0; i < n; ++i) in[i] = base[i];

      auto t0 = chrono::high_resolution_clock::now();
      algorithms[a].sort(in, out, n);
      auto t1 = chrono::high_resolution_clock::now();

      const double sec = chrono::duration<double>(t1 - t0).count();
      if (!sorted(out, n)) {
	cells[a][s] = "BAD";
	allow_next[a] = false;
      } else {
	cells[a][s] = format_seconds(sec);
	if (sec >= stopSeconds) allow_next[a] = false;
      }

      delete[] in;
      delete[] out;
    }

    delete[] base;
  }
} 

int main() {
  string t1[algorithmCount][sizeCount];
  string t2[algorithmCount][sizeCount];
  string t3[algorithmCount][sizeCount];
  string t4[algorithmCount][sizeCount];

  unsigned int* large_random = new unsigned int[maxSize];
  fill(large_random);
  run(large_random, algorithms, t1);

  unsigned int* small_random = new unsigned int[maxSize];
  trim(large_random, small_random);
  run(small_random, algorithms, t2);

  unsigned int* large_reverse = new unsigned int[maxSize];
  radix_sort(large_random, large_reverse, maxSize);
  reverse(large_reverse, maxSize);
  run(large_reverse, algorithms, t3);

  unsigned int* small_reverse = new unsigned int[maxSize];
  radix_sort(small_random, small_reverse, maxSize);
  reverse(small_reverse, maxSize);
  run(small_reverse, algorithms, t4);

  print_table("1. Random Large Range", algorithms, t1);
  print_table("2. Random Small Range (0..255)", algorithms, t2);
  print_table("3. Descending Input from Large Range", algorithms, t3);
  print_table("4. Descending Input from Small Range", algorithms, t4);

  delete[] large_reverse;
  delete[] large_random;
  delete[] small_random;
  delete[] small_reverse;

  return 0;
}
