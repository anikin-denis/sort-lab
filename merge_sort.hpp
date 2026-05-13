#include <cstddef>

using namespace std;

void merge_sort_merge(unsigned int* a, unsigned int* tmp, size_t l, size_t m, size_t r) {
  size_t i = l;
  size_t j = m;
  size_t k = l;
  while (i < m && j < r) {
    if (a[i] <= a[j]) tmp[k++] = a[i++];
    else tmp[k++] = a[j++];
  }
  while (i < m) tmp[k++] = a[i++];
  while (j < r) tmp[k++] = a[j++];
  for (size_t p = l; p < r; ++p) a[p] = tmp[p];
}

void merge_sort_impl(unsigned int* a, unsigned int* tmp, size_t l, size_t r) {
  if (r - l < 2) return;
  size_t m = l + (r - l) / 2;
  merge_sort_impl(a, tmp, l, m);
  merge_sort_impl(a, tmp, m, r);
  merge_sort_merge(a, tmp, l, m, r);
}

void merge_sort(unsigned int* in, unsigned int* out, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    out[i] = in[i];
  }
  if (size < 2) return;
  unsigned int* temp = new unsigned int[size];
  merge_sort_impl(out, temp, 0, size);
  delete[] temp;
}
