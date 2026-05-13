#include <cstddef>

using namespace std;

inline void count_sort(unsigned int* in, unsigned int* out, size_t size) {
    if (size == 0) return;

    unsigned int min_value = in[0], max_value = in[0];
    for (size_t i = 1; i < size; ++i) {
        if (in[i] < min_value) min_value = in[i];
        if (in[i] > max_value) max_value = in[i];
    }

    const size_t range = (size_t)max_value - (size_t)min_value + 1;

    size_t* counts = new size_t[range];
    for (size_t i = 0; i < range; ++i) counts[i] = 0;

    for (size_t i = 0; i < size; ++i) {
        size_t idx = (size_t)in[i] - (size_t)min_value;
        ++counts[idx];
    }

    for (size_t i = 1; i < range; ++i) counts[i] += counts[i - 1];

    for (size_t i = size; i > 0; --i) {
        unsigned int v = in[i - 1];
        size_t idx = (size_t)v - (size_t)min_value;
        out[--counts[idx]] = v;
    }

    delete[] counts;
}
