#include <iostream>
 
struct Box {
    int v;
    int number;
    Box() : v(0), number(0) {}
};
 
void InsertionSort(Box *a, int n) {
    for (int i = 1; i < n; ++i) {
        Box tmp = a[i];
        int j = i - 1;
        for( ; j >= 0 && tmp.v < a[j].v; --j) {
            a[j + 1] = a[j];
        }
        a[j + 1] = tmp;
    }
}
 
int main() {
    int n{};
    std::cin >> n;
    Box *arr = new Box[n];
    for (int i{}; i < n; ++i) {
        int a{}, b{}, c{};
        std::cin >> a >> b >> c;
        Box box;
        box.v = a * b * c;
        box.number = i;
        arr[i] = box;
    }
    InsertionSort(arr, n);
    for(int i{}; i < n; ++i) {
        std::cout << arr[i].number << " ";
    }
    delete[] arr;
    return 0;
}