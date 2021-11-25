/* 
Вернуть значение бита в числе N по его номеру K.
 */

#include <iostream>

bool searching_bit(unsigned int n, unsigned int k){
	return ((n >> k) & 1);
}

int main(int argc, char const *argv[])
{
	unsigned int n = {};
	unsigned int k = {};

	std::cin >> n;
	std::cin >> k;
	std::cout << searching_bit(n, k) << std::endl;

	return 0;
}