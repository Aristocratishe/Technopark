#include <iostream>
#include <cassert>

// Структура для хранения id и количества посещений пользователей
struct arrayWrapper {
    int *a;
	int size;
	arrayWrapper() : a(nullptr), size(0){};
};

/*/ Переопределим оператор ввода для структуры
std::istream& operator>>(std::istream &in, arrayWrapper &t) {
	in >> t.size >> t.a[i];
	return in;
}
*/

// Интерфейс класса куча 
template <class T>
class Heap {
private:
	void bufferExpansion(); 
	void buildHeap();
	void siftUp(int);
	int bufferSize;
	const short MULTIPLIER = 2;
public:
	Heap();
	~Heap();
	void insert(int *, int, int);
	void siftDown(int);
	int ExtractTop();
	T *buffer;
	int heapSize;
    void meargeHeap(int);
};

// Конструктор
template <class T>
Heap<T>::Heap() {
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

/*/ Построение кучи
template <class T>
void Heap<T>::buildHeap() {
	for (int i = heapSize / 2 - 1; i >= 0; --i) {
		siftDown(i, trafficComparator);
	}
}*/

// Просеивание вниз
template <class T>
void Heap<T>::siftDown(int i) {
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int smallest = i;
	if (left < heapSize && buffer[left].a[0] < buffer[i].a[0]) {
		smallest = left;
	}
	if (right < heapSize && buffer[right].a[0] < buffer[smallest].a[0]) {
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
		if (buffer[i].a[0] > buffer[parent].a[0]) { return; }
		std::swap(buffer[i], buffer[parent]);
		i = parent;
	}
}

template <class T>
int Heap<T>::ExtractTop() {
	assert(buffer);
	int result = buffer[0].a[0];
    --buffer[0].size;
    if (buffer[0].size != 0) { ++buffer[0].a; }
    else { std::swap(buffer[0], buffer[heapSize - 1]); --heapSize; }
	return result;
}

// Добавление элемента
template <class T>
void Heap<T>::insert(int *elem, int K, int i) {
	++heapSize;
	while (bufferSize < heapSize) { bufferExpansion(); }
	assert(buffer && bufferSize >= heapSize);
    buffer[i].a = new int[K];
    std::copy(elem, elem + K, buffer[i].a);
    buffer[i].size = K;
	siftUp(i);
}

template <class T>
void Heap<T>::meargeHeap(int resultSize) {
    auto *result = new int[resultSize];
    int i{};
    while (i < resultSize) {
        result[i] = ExtractTop();
        siftDown(0);
        ++i;
    }
    for (int j{}; j < resultSize; ++j) {
        std::cout << result[j] << " ";
    }
    delete[] result;
}


int main() {
	int N{}, K{};
	std::cin >> N;
	assert(N > 0);
    int resultSize{};
    Heap<arrayWrapper> heap;
    for (int i{}; i < N; ++i) {
        std::cin >> K;
        resultSize += K;
        auto *temp = new int[K];
        for (int j{}; j < K; ++j) {
            std::cin >> temp[j];
        }
        heap.insert(temp, K, i);
        delete[] temp; 
    }
    heap.meargeHeap(resultSize);

    /*
    for (int i{}; i < N; ++i) {
        std::cout << heap.buffer[i].size << std::endl;
    }
    for (int i{}; i < N; ++i) {
        for (int j{}; j < heap.buffer[i].size; ++j) {
            std::cout << heap.buffer[i].a[j] << " ";
        }
        std::cout << std::endl;
    }
    */

	return 0;
}