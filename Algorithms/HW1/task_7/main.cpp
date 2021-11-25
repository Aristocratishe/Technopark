#include <iostream>

int convert(long long a, int i) { return int((a >> (8 * i)) & 255); }

void counting_sort(long long *arr, size_t N) {
    int count[256];
    auto *temp_arr = new long long[N];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 256; ++j) { count[j] = 0; }
        for (int j = 0; j < N; ++j) { ++count[convert(arr[j], i)]; }       
        for (int j = 1; j < 256; ++j) { count[j] += count[j - 1]; }
        for (int j = N - 1; j >= 0; --j) { temp_arr[--count[convert(arr[j], i)]] = arr[j]; }
        std::copy(temp_arr, temp_arr + N, arr);
    }
    delete[] temp_arr;
}

void printing_results(long long *arr, size_t N) {
    for (int i = 0; i < N; ++i) { std::cout << arr[i] << " "; }    
}

int main() {
    size_t N;
    std::cin >> N;
    auto *arr = new long long[N];
    for (int i = 0; i < N; ++i) { std::cin >> arr[i]; }
    counting_sort(arr, N);
    printing_results(arr, N);
    delete[] arr;
    return 0;
}