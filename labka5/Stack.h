#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "Exception.h"


template <class T>
class Stack {
    int top;
    T* data;
    int capacity;

public:
    Stack(int capacity = 10) {
        if (capacity <= 0) {
            throw StackIncorrectSizeException();
        }
        top = -1;
        this->capacity = capacity;
        data = new T[capacity];
    }

    bool isEmpty();
    bool isFull();
    bool push(const T& x);
    T pop();
    T peek();
    int size();
    void print();
    ~Stack(){
        delete[] data;
    }

    void serialize(std::ostream &os) const;

    void deserialize(std::istream &is);
};




template<class T>
bool Stack<T>::isEmpty() {
    return (top == -1);
}

template<class T>
bool Stack<T>::isFull() {
    return (top == capacity - 1);
}

template<class T>
bool Stack<T>::push(const T& x) {
    try {
        if (isFull()) {
            throw StackOverflowException();
        }
        data[++top] = x;
    } catch (const StackOverflowException& e) {
        e.show();
        return false;
    }
    return true;
}

template<class T>
T Stack<T>::pop() {
    T poppedValue;
    try {
        if (isEmpty()) {
            throw StackUnderflowException();
        }
        poppedValue = data[top--];
    } catch (const StackUnderflowException& e) {
        e.show();
    }
    return poppedValue;
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
    for (int i = 0; i <= top; ++i) {
        std::cout << data[i] << " ";
    }
}

template<class T>
void Stack<T>::serialize(std::ostream& os) const {
    // Записываем количество элементов в стеке
    os << top + 1 << std::endl;

    // Записываем каждый элемент стека в поток
    for (int i = top; i >= 0; --i) {
        os << data[i] << std::endl;
    }
}

template<class T>
void Stack<T>::deserialize(std::istream& is) {
    // Очищаем стек
    delete[] data;
    top = -1;

    // Читаем количество элементов из потока
    int count;
    is >> count;

    // Пересоздаем стек с новой емкостью
    capacity = count;
    data = new T[capacity];

    // Заполняем стек значениями из потока
    for (int i = 0; i < count; ++i) {
        T value;
        is >> value;
        push(value); // используем метод push для добавления элемента в стек
    }
}

#endif
