/*
Имеется лог-файл, в котором хранятся пары для N пользователей 
(Идентификатор пользователя, посещаемость сайта). Напишите программу, 
которая выбирает K пользователей, которые чаще других заходили на сайт, 
и выводит их в порядке возрастания посещаемости. Количество заходов и 
идентификаторы пользователей не повторяются. 
*/
#include <iostream>
#include <cassert>

// Структура для хранения id и количества посещений пользователей
struct UserData {
	int id;
	int traffic;
	UserData() : id(0), traffic(0) {};
};

// Переопределим оператор ввода для структуры
std::istream& operator>>(std::istream &in, UserData &t) {
	in >> t.id >> t.traffic;
	return in;
}

template <typename T>
bool defaultComparator(const T &first, const T &second) {
	return first < second;
}


// Интерфейс класса куча 
template <class T>
class Heap {
private:
	void bufferExpansion(); 
	void buildHeap();
	void siftUp(int);
	void siftDown(int);
	T ExtractTop();
	void insert(T, int);
	int bufferSize;
	const short MULTIPLIER = 2;
	T *buffer;
	int heapSize;
	bool (*cmp)(const T&, const T&);
	bool (*cmpLE)(const T&, const T&);
public:
	Heap(bool (*)(const T&, const T&), bool (*)(const T&, const T&));
	~Heap();
	void topUsers(const T, const int, const int, const int);
};

template <typename T>
bool trafficComparator(const T &first, const T &second) {
	return first.traffic < second.traffic;
}

template <typename T>
bool trafficComparatorLE(const T &first, const T &second) {
	return first.traffic >= second.traffic;
}

// Конструктор
template <class T>
Heap<T>::Heap(bool (*cmp)(const T&, const T&), bool (*cmpLE)(const T&, const T&)) : cmp(cmp), cmpLE(cmpLE) {
	bufferSize = 1;
	buffer = new T[bufferSize];
	heapSize = 0;
}

// Деструктор
template <class T>
Heap<T>::~Heap() {
	delete[] buffer;
}

// Расширение буфера
template <class T>
void Heap<T>::bufferExpansion() {
	int newBufferSize = bufferSize * MULTIPLIER;
	auto *newBuffer = new T[newBufferSize];
	std::copy(buffer, buffer + bufferSize, newBuffer);
	delete[] buffer;
	buffer = newBuffer;
	bufferSize = newBufferSize;
}

// Построение кучи
template <class T>
void Heap<T>::buildHeap() {
	for (int i = heapSize / 2 - 1; i >= 0; --i) {
		siftDown(i);
	}
}

// Просеивание вниз
template <class T>
void Heap<T>::siftDown(int i) {
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int smallest = i;
	if (left < heapSize && cmp(buffer[left], buffer[i])) {
		smallest = left;
	}
	if (right < heapSize && cmp(buffer[right], buffer[smallest])) {
		smallest = right;
	}
	if (smallest != i) {
		std::swap(buffer[i], buffer[smallest]);
		siftDown(smallest);
	}
}

// Просеивание вверх
template <class T>
void Heap<T>::siftUp(int i) {
	while (i > 0) {
		int parent = (i - 1) / 2;
		if (cmpLE(buffer[i], buffer[parent])) { return; }
		std::swap(buffer[i], buffer[parent]);
		i = parent;
	}
}

template <class T>
T Heap<T>::ExtractTop() {
	assert(buffer);
	T result = buffer[0];
	return result;
}

// Добавление элемента
template <class T>
void Heap<T>::insert(T elem, int i) {
	++heapSize;
	while (bufferSize < heapSize) { bufferExpansion(); }
	assert(buffer && bufferSize >= heapSize);
	buffer[i] = elem;
	siftUp(i);		
}

template <class T>
void Heap<T>::topUsers(const T data, const int i, const int K, const int N) {
	if (i < K) {
			insert(data, i);
		}
	else {
		if (cmp(buffer[0], data)) {
			buffer[0] = data;
			siftDown(0);
		}	
	}
	if (i == N - 1) {
		while (heapSize > 0) {
			std::cout << buffer[0].id << " ";
			std::swap(buffer[0], buffer[--heapSize]);
			siftDown(0);
		}
	}
}

int main() {
	int N{}, K{};
	std::cin >> N >> K;
	assert(N > 0 && K <= N);
	if (K == 0) {
		return 0;
	}
	UserData dataSet{};
	Heap<UserData> users(trafficComparator, trafficComparatorLE);
	for (int i{}; i < N; ++i) {
		std::cin >> dataSet;
		users.topUsers(dataSet, i, K, N);
	}
	return 0;
}

