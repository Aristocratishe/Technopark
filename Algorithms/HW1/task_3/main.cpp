/* 
Реализвать очередь с помощью двух стеков. 
Испльзовать стек, реализованный с помощью динамического буфера.
*/

#include <iostream>

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

//Интерфейс класса очередь
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


int main() {
    Queue queue;
    unsigned int n{};
    unsigned int command{};
    int value{};
    bool flag = false;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> command;
        if (command == 2) {
        	std::cin >> value;
            if (value == queue.dequeue()) 
            	flag = true;
            else 
            	flag = false;
        }
        else if (command == 3) {
            std::cin >> value;
            queue.enqueue(value);
        }
    }
    if (flag == true) 
    	std::cout << "YES" << std::endl;
    else 
    	std::cout << "NO" << std::endl;
    return 0;
}