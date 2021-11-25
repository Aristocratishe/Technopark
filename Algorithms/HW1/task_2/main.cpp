/*
Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. 
Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, 
равного или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. 
Время работы поиска k для каждого элемента B[i]: O(log(k)). n, m ≤ 10000. 
*/

#include <iostream>

unsigned short my_exponential_search(int b_val, int *a_arr, unsigned short b){
	unsigned short count = 1;
	auto n = b;
	while (count < n && a_arr[count] < b_val){
		count *= 2;
	}
	(count > (n - 1)) ? b = n - 1 : b = count;
	return b;
}

unsigned short *my_binary_search(int *a_arr, int *b_arr, unsigned short n, unsigned short m){
	auto *k_arr  = new unsigned short [m];
	for (unsigned short i = 0; i < m; ++i){
		unsigned short a{};
		unsigned short b = n;

		b = my_exponential_search(b_arr[i], a_arr, b);
		a = b/2;

		if (a_arr[b] < b_arr[i]){
			k_arr[i] = n;
		}
		else {
		unsigned short k{};
			while (a < b){
				k = (a + b)/2;
				if (a_arr[k] < b_arr[i]){
					a = k + 1;
				}
				else {
					b = k;
				}
				k = (b + a)/2;
			} 
			k_arr[i] = k; 
		}
	}
	return (unsigned short *) k_arr;
}

int main(int argc, char const *argv[])
{
	unsigned short n{};
	unsigned short m{};

	std::cin >> n;
	std::cin >> m;

	auto *a_arr = new int [n];
	auto *b_arr = new int [m];

	for (unsigned short i = 0; i < n ; ++i){
		std::cin >> a_arr[i];
	}
	
	for (unsigned short i = 0; i < m; ++i){
		std::cin >> b_arr[i];
	}

	unsigned short *k_arr = my_binary_search(a_arr, b_arr, n, m);

	for (unsigned short i = 0; i < m; ++i){
		std::cout << k_arr[i] << " ";
	} 

	delete [] a_arr;
	delete [] b_arr;
	delete [] k_arr;

	return 0;
}