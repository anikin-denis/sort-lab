#include <cstddef>

using namespace std;

inline void quick_sort_swap(unsigned int& a, unsigned int& b) {
    unsigned int t = a;
    a = b;
    b = t;
}

inline void quick_sort_impl(unsigned int* a, long left, long right) {
    if (left >= right) return;
    long i = left;
    long j = right;
    unsigned int pivot = a[(left + right) / 2];

    while (i <= j) {
        while (a[i] < pivot) ++i;
        while (a[j] > pivot) --j;
        if (i <= j) {
            quick_sort_swap(a[i], a[j]);
            ++i;
            --j;
        }
    }

    if (left < j) quick_sort_impl(a, left, j);
    if (i < right) quick_sort_impl(a, i, right);
}

inline void quick_sort(unsigned int* in, unsigned int* out, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        out[i] = in[i];
    }
    if (size > 1) quick_sort_impl(out, 0, static_cast<long>(size) - 1);
}
