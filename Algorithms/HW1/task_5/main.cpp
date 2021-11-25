/*
В супермаркете решили оптимизировать показ рекламы. Известно расписание 
прихода и ухода покупателей (два целых числа). Каждому покупателю необходимо 
показать минимум 2 рекламы.  Рекламу можно транслировать только в целочисленные 
моменты времени. Покупатель может видеть рекламу от момента прихода до момента 
ухода из магазина. В каждый момент времени может показываться только одна реклама. 
Считается, что реклама показывается мгновенно. Если реклама показывается в 
момент ухода или прихода, то считается, что посетитель успел её посмотреть. 
Требуется определить минимальное число показов рекламы.
*/

#include <iostream>
#include <cstring>

struct TimeTable {
	int entry;
	int exit;
	TimeTable() : entry(0), exit(0) {};
};

// Переопределим оператор ввода для структуры
std::istream& operator>>(std::istream &in, TimeTable &t) {
	in >> t.entry >> t.exit;
	return in;
}

template <typename T>
bool defaultComparator(const T &first, const T &second) {
	return first < second;
}
template <typename T>
bool defaultEqualComparator(const T &first, const T &second) {
	return first == second;
}

bool timeExitComparator(const TimeTable &first, const TimeTable &second) {
	return first.exit < second.exit;
}

bool timeEntryComparator(const TimeTable &first, const int second) {
	return first.entry > second;
}

bool timeEntryEqual(const TimeTable &first, const int second) {
	return first.entry == second;
}

template <typename T>
void merge(T *aArr, int aLen, T *bArr, int bLen, T *buffer, 
			bool (*cmp)(const T&, const T&) = defaultComparator) {
	int count{};
	for (int i{}, j{}, k{}; k < aLen + bLen; ++k) {
		if (i == aLen) { buffer[k] = bArr[j++]; continue; }
		if (j == bLen) { buffer[k] = aArr[i++]; continue; }
		buffer[k] = cmp(aArr[i], bArr[j]) ? aArr[i++] : bArr[j++];
	}
}

template <typename T>
void mergeSort(T *aArr, int aLen) {
	if (aLen <= 1) 
		return; 
	int firstLen = aLen / 2;
	int secondLen = aLen - firstLen;
	mergeSort(aArr, firstLen);
	mergeSort(aArr + firstLen, secondLen);
	auto *buffer = new T[aLen];
	merge(aArr, firstLen, aArr + firstLen, secondLen, buffer, timeExitComparator);
	memcpy(aArr, buffer, sizeof(T) * aLen);
	delete[] buffer;
}

template <typename T>
int countAdvertising(T *aArr, int aLen, bool (*cmpLarger)(const T&, const int) = defaultComparator,
					bool (*cmpEqual)(const T&, const int) = defaultEqualComparator) {
	int count{};
	int firstTime = -1;
	int secondTime = -1;
	for (int i{}; i < aLen; ++i) {
        if (cmpLarger(aArr[i], secondTime)) {
            count += 2;
            firstTime = aArr[i].exit - 1;
            secondTime = aArr[i].exit;
        }
        else if (cmpEqual(aArr[i], secondTime)) {
            count++;
            firstTime = secondTime;
            secondTime = aArr[i].exit;
        }
        else if (cmpLarger(aArr[i], firstTime)) {
            count++;
            firstTime = secondTime;
            secondTime = aArr[i].exit;
        }
    }
    return count;
}

int main()
{
	int countVisitors{};
	std::cin >> countVisitors;
	auto *timeTable = new TimeTable[countVisitors];
	for (int i{}; i < countVisitors; ++i) {
		std::cin >> timeTable[i];
	}
	mergeSort(timeTable, countVisitors);
	std::cout << countAdvertising(timeTable, countVisitors, 
								timeEntryComparator, timeEntryEqual) << std::endl;
	delete[] timeTable;
	return 0;
}