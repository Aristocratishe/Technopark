//Алгоритмы

// *******************Бинарный поиск**************************
int BinarySearch(const double *arr, int count, double element) {
	int first = 0;
	int last = count;
	while (first < last) {
		int mid = (first + last) / 2;
		if (arr[mid] < element) { first = mid + 1; }
		else { last = mid; }
	}
	return (first == count || arr[first] != element) ? -1 : first;
}

// Возвращает позицию вставки элемента на отрезке (first, last).
// Равные элементы раполагаются после. (std::lower_bound)
int FindInsertionPoint(const double *arr, int count, double element) {
	int first = 0;
	int last = count;
	while (first < last) {
		int mid = (first + last) / 2;
		if (arr[mid] < element) { first = mid + 1; }
		else { last = mid; }
	}
	return first;
}

// Сложность O(logN), где N - количество элементов в массиве.
// Объем доп памяти M(n) = O(1)

//******************Динамический массив*******************************
// Класс Динамический массив
class Array {
public:
	CArray() : buffer(0), bufferSize(0), realSize(0) {}
	~CArray() : { delete[] buffer; }

	//Размер
	int Size() const { return realSize; }
	// Доступ по индексу
	double GetAt(int index) const;
	double operator[](int index) const {return GetAt(index);}
	double &operator[](int index);

	// Добавление нового элемента
	void Add(double element);
private:
	double *buffer;
	int bufferSize;
	int realSize;

	void grow();
};

double CArray::GetAt(int index) const{
	assert(index >= 0 && index < realSize && buffer != 0);
	return buffer[index];
}
// Увеличение буфера
void CArray::grow() {
	int newBufferSize = std::max(bufferSize * 2, DefaultInitialSize);
	int *newBuffer = new double[newBufferSize];
	std::copy(buffer, buffer + bufferSize, newBuffer);
	delete[] buffer;
	buffer = newBuffer;
	bufferSize = newBufferSize;	
}
// Добавление элемента
void CArray::Add(double element) {
	if (realSize == bufferSize) { grow(); }
	assert(realSize < bufferSize && buffer != 0);
	buffer[realSize++] = element;
}

// ********************Связный список**************************

// 1. Узел односвязного списка
struct Node {
	int data;
	Node *next;

	Node() : data(0), next(nullptr) {}
};
// 2. Узел двусвязного списка
struct Node {
	int data;
	Node *next;
	Node *prev;

	Node() : data(0), next(nullptr) prev(nullptr) {}
};

// Линейный поиск элемента в списке.
// Возвращает 0, если элемент не найден.

Node *Search(Node *head, int a) {
	Node *current = head;
	while (current != nullptr) {
		if (current->data == a) { return current; }
	current = current->next;
	}
	return 0;
}

// Время работы в худшем случае О(n), где n - длина списка.

// Вставка
Node *InsertAfter(Node *node, int a) {
	assert(node != nullptr);
	Node *newNode = new Node();
	newNode->data = a;
	newNode->next = node->next;
	newNode->prev = node;
	if (node->next != nullptr) { node->next->prev = newNode; }
	node->next = newNode;
	return newNode;
}

//Удаление
void DeleteAt(Node *node) {
	assert(node != nullptr);
	if (node->prev != nullptr) { node->prev->next = node->next; }
	if (node->next != nullptr) { node->prev->next = node->prev; }
	delete node;
}

// Объединение односвязных списков. К списку 1 подцепляем список 2.
// Возвращает указатель на начало объединненого списка.
Node *Union(Node *head1, Node *head2) {
	if (head1 == nullptr) { return head2; }
	if (head2 == nullptr) { return head1; }
	Node *tail1 = head1;
	for (; tail1->next !=nullptr; tail1 = tail1->next);
	tail1->next = head2;
	return head1;
}
// Время работы O(n), где n - длина первого списка.

// Сравнение сложности основных операций
/*
-------------------------------------------------------------------------
									|	Массив   |   Односвязный список |
-----------------------------------------------------------------------|
 Вставка							|	 O(n) 	 |	 		O(1)        |
------------------------------------------------------------------------|
 Добавление (вставка в конец)		|    O(1)    |		  O(n)/O(1)     |
------------------------------------------------------------------------|
 Удаление							|    O(n)    |			O(1)		|
------------------------------------------------------------------------|
 Доступ по индексу   				|    O(1)    |			O(n)		|
-------------------------------------------------------------------------
*/

//********************************Стек************************************
//Реализация с помощью массива.
// Интерфейс класса стек
class Stack {
private:
	int buffer_size;
	int top;
	int *buffer;
	void buffer_expansion();
	const short MULTIPLIER = 2;
public:
	Stack();
	~Stack();
	void push(int);
	int pop();
	int which_top();
};

// Конструктор
Stack::Stack() {
	buffer_size = 1;
	top = -1;
	buffer = new int[buffer_size];
}

// Деструктор
Stack::~Stack() {
	delete[] buffer;
}

// Метод расширения буфера
void Stack::buffer_expansion() {
	int new_buffer_size = buffer_size * MULTIPLIER;
	int *new_buffer = new int[new_buffer_size];
	std::copy(buffer, buffer + buffer_size, new_buffer);
	delete[] buffer;
	buffer = new_buffer;
	buffer_size = new_buffer_size;
}

// Метод вставки в стек
void Stack::push(int t) {
	if (top + 1 == buffer_size)
		buffer_expansion();
	buffer[++top] = t;
}

// Метод извлечения из стека верхнего элемента
int Stack::pop() {
	if (top == -1 )
		return -1;
	else
		return buffer[top--];
}

// Метод для просмотра верхнего элемента в стеке
int Stack::which_top() {
	if (top == -1)
		return -1;
	return buffer[top];
}

//********************************Очередь************************************
//Интерфейс класса очередь, реализованной через два стек
class Queue {
private:
	Stack *head;
	Stack *tail;
public:
	Queue();
	~Queue();
	void enqueue(int);
	int dequeue();
};

// Конструктор
Queue::Queue(){
	head = new Stack();
	tail = new Stack();
}

// Деструктор
Queue::~Queue(){
	delete head;
	delete tail;
}

// Добавления элемента в хвост очереди
void Queue::enqueue(int t) {
	tail->push(t);
}

// Извелечение элемента из головы очереди
int Queue::dequeue() {
	if (head->which_top() == -1)
		while (tail->which_top() != -1) {
			head->push(tail->pop());
		}
	return head->pop();
}

//Интерфейс класса очередь, реализованной через массив
class Queue {
private:
	int *buffer;
	int bufferSize;
	int head;
	int tail;
public:
	Queue(int size);
	~Queue();
	void enqueue(int);
	int dequeue();
	bool isEmpty() const {return head == tail; }
};
// Конструктор
Queue::Queue(int size):
	bufferSize(size),
	head(0),
	tail(0)
	{ buffer = new int[bufferSize]; }

// Деструктор
Queue::~Queue(){ delete[] buffer; }

// Добавления элемента в хвост очереди
void Queue::enqueue(int a) {
	assert((tail + 1) % bufferSize != head);
	buffer[tail] = a;
	tail = (tail + 1) % bufferSize;
}

// Извелечение элемента из головы очереди
int Queue::dequeue() {
	assert(head != tail);
	int result = buffer[head];
	head = (head + 1) % bufferSize;
	return result;
}

//********************************Двоичная куча************************************
// Интерфейс класса куча 
template <class T>
class Heap {
private:
	void bufferExpansion(); 
	void buildHeap();
	void siftUp(int, bool (*)(const T&, const T&));
	int bufferSize;
	const short MULTIPLIER = 2;
public:
	Heap();
	~Heap();
	void heapSort(T *, unsigned, unsigned, bool (*)(const T&, const T&));
	void insert(T, int);
	void siftDown(int, bool (*)(const T&, const T&));
	T ExtractTop();
	T *buffer;
	int heapSize;
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

// Построение кучи
template <class T>
void Heap<T>::buildHeap() {
	for (int i = heapSize / 2 - 1; i >= 0; --i) {
		siftDown(i, trafficComparator);
	}
}

// Просеивание вниз
template <class T>
void Heap<T>::siftDown(int i, bool (*cmp)(const T&, const T&)) {
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
		siftDown(smallest, trafficComparator);
	}
}

// Просеивание вверх
template <class T>
void Heap<T>::siftUp(int i, bool (*cmp)(const T&, const T&)) {
	while (i > 0) {
		int parent = (i - 1) / 2;
		if (cmp(buffer[i], buffer[parent])) { return; }
		std::swap(buffer[i], buffer[parent]);
		i = parent;
	}
}

//Извлечение верхнего элемента
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
	siftUp(i, trafficComparatorLE);		
}

//*************************Пирамидальная сортировка*******************
void HeapSort(int *a, int n) {
	int heapSize = n;
	buildHeap(a, heapSize);
	while(heapSize > 1) {
		swap(a[0], a[heapSize - 1]);
		--heapSize;
		siftDown(a, heapSize, 0);
	}
}
// T(n) = O(nlogn). Локальная

//***********************Сортировка слиянием*******************************
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
// T(n) = O(nlogn). Нелокальная, стабильная

//*************************Быстрая сортировка***********************************
//Выбор Pivot методом прохода двумя индексами от начала к концу
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
//Выбор Pivot методом прохода двумя индексами на встречу друг другу
int partition(int *a, int n) {
	if (n <= 1) { return 0; }
	const int &pivot = a[n - 1];
	int i = 0;
	j = n - 2;
	while (i <= j) {
		for ( ; a[i] < pivot; ++i) {}
		for ( ; j >= 0 && !(a[j] < pivot); --j) {}
		if (i < j) { swap(a[i++], a[j--]); }
	}
	swap(a[i], a[n - 1]);
	return i;
}

void quickSort(Number *a, int n) {
    int i{};
    int part = partition(int *a, int n);
    if (i > 0) { quickSort(a, part); }
    if (part + 1 < n) { quickSort(a + part + 1, n - (part + 1)); }
}