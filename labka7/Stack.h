#include <iostream>
#include <iterator>

template <class T>
class Stack{
    int top; // индекс верхнего элемента стека
    T *data; // укаазатель на динамический массив, который будет использоваться для хранения элементов стека
    int capacity; // вместимость стека

public:
    // Конструктор класса Stack. По умолчанию вместимость стека равна 10
    Stack(int capacity = 0) : top(-1), capacity(capacity) {
        data = new T[capacity]; // Выделяем память под массив
    }

    bool isEmpty(); // Функция для проверки, пуст ли стек
    bool isFull(); //  для проверки, полон ли стек
    bool push(const T& x); // для добавления элемента в стек
    T pop(); //  для удаления элемента из стека
    T peek(); // Для просмотра верхнего элемента стека
    int size(); // для получения размера стека
    void print(); // для вывода элементов стека

    // Деструктор класса Stack. Освобождает память, выделенную под массив data
    ~Stack(){
        delete[] data;
    }
    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
        T* currentPointer; // Используемое имя переменной, заменяющее p
    public:
        iterator(T* ptr) : currentPointer(ptr) {} // Изменяем имя p на ptr
        iterator(const iterator& other) : currentPointer(other.currentPointer) {} // Изменяем имя mit на other
        iterator& operator++() { ++currentPointer; return *this; }
        iterator operator++(int) { iterator temp(*this); operator++(); return temp; }
        bool operator==(const iterator& rhs) const { return currentPointer == rhs.currentPointer; }
        bool operator!=(const iterator& rhs) const { return currentPointer != rhs.currentPointer; }
        T& operator*() { return *currentPointer; }
        iterator& operator--() { --currentPointer; return *this; }
        iterator operator--(int) { iterator temp(*this); operator--(); return temp; }
    };

    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + size()); }
    iterator rbegin() { return iterator(data + size() - 1); }
    iterator rend() { return iterator(data - 1); }
    iterator cbegin() const { return iterator(data); }
    iterator cend() const { return iterator(data + size()); }
    iterator crbegin() const { return iterator(data + size() - 1); }
    iterator crend() const { return iterator(data - 1); }
};

template<class T>
typename Stack<T>::iterator search(typename Stack<T>::iterator begin, typename Stack<T>::iterator end, const T& value) {
    return std::find(begin, end, value);
}

template<class T>
bool Stack<T>::isEmpty() {
    return (top == -1); // стек пустй, если top равен -1
}

template<class T>
bool Stack<T>::isFull() {
    return (top == capacity - 1);
}

template<class T>
bool Stack<T>::push(const T& x) {
    if (isFull()) {
        std::cout << "Stack overflow" << std::endl;
        return false;
    }

    data[++top] = x; // добавляем элемент в стек и увеличиваем top на 1
    return true;
}

template<class T>
T Stack<T>::pop() {
    if (isEmpty()) {
        std::cout << "Underflow\n";
        return 0;
    }

    return data[top--]; // удаляем верхний элемент из стека и уменьшаем top на 1
}

template<class T>
T Stack<T>::peek() {
    if (!isEmpty()) {
        return data[top];
    } else {
        return 0;
    }
}

template<class T>
int Stack<T>::size() {
    return top + 1;
}

template<class T>
void Stack<T>::print() {
    for (int i = 0; i <= top; ++i) { // выводим все элементы стека от нижнего к верхнему
        std::cout << data[i] << " ";
    }
}
