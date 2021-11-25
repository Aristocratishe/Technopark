/*
Дано множество целых чисел из [0..109] размера n.
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
1) 10% перцентиль
2) медиана
3) 90% перцентиль
*/

#include <iostream>
#include <cassert>

template <typename T>
bool lessComparator(const T &first, const T &second) {
	return first < second;
}

template<typename T>
bool lessEqComparator(const T &first, const T &second) {
	return first <= second;
}

template<typename T>
int partition(T *a, T start, T end, bool (*cmpLess)(const T&, const T&), bool (*cmpLessEq)(const T&, const T&)) {
    if (end == start) { return start; }
    unsigned int indexPivot = start + rand() % (end - start + 1);
    const T pivot = a[indexPivot];
    std::swap(a[indexPivot], a[end]);
    int i{}, j{};
    i = start;
    for ( ; (i <= end) && (cmpLessEq(a[i], pivot)); ++i) {}
    if (i >= end) { return end; } else { j = i + 1; }
    while (j < end)
    {
        for ( ; cmpLess(pivot, a[j]); ++j) {}
        if (j < end) { std::swap(a[i++], a[j++]); }
    }
    std::swap(a[i], a[end]);
    return i;
}

unsigned int *kStatistics(unsigned int *a, size_t n) {
    const unsigned int k[3] = {(unsigned int) (n * 0.1), (unsigned int) (n * 0.5), 
                                                    (unsigned int) (n * 0.9)};
    auto *result = new unsigned int[3];
    unsigned int startIndex{};
    unsigned int endIndex{};
    unsigned int indexPivot{};
    for (int i{}; i < 3; ++i) {
        startIndex = 0;
        endIndex = n - 1;
        indexPivot = partition(a, startIndex, endIndex, lessComparator, lessEqComparator);
        while (indexPivot != k[i]) {
            if (k[i] < indexPivot) {
                endIndex = indexPivot - 1; 
            }
            else if (k[i] > indexPivot) { 
                startIndex =  indexPivot + 1; 
            }
            indexPivot = partition(a, startIndex, endIndex, lessComparator, lessEqComparator); 
        }
        result[i] = a[indexPivot];
    }
    return result;
}

int main() {
    srand(time(NULL));
    size_t arrSize{};
    std::cin >> arrSize;
    assert(arrSize > 0);
    auto *arr = new unsigned int[arrSize];
    for (int i{}; i < arrSize; ++i) {
        std::cin >> arr[i];
    }
    auto *result = kStatistics(arr, arrSize);
    for (int i{}; i < 3; ++i) {
        std::cout << result[i] << std::endl;
    }
    delete[] arr; 
    delete[] result; 
    return 0;
}