#ifndef STACK_H
#define STACK_H
#include <iostream>
#include "Serializable.h"
#include "Exception.h"

template<typename T>
class Stack : public Serializable {
    struct Node {
        T* data;
        Node* next;
    };

    Node* top;
    int size;

public:
    Stack();
    ~Stack();
    Node* begin();
    Node* end();
    void push(T* value);
    void pop();
    T* peek();
    bool isEmpty();
    int getSize();
    void print();
    void serialize(std::ofstream& file) override;
    void deserialize(std::ifstream& file) override;

    friend std::ostream& operator<<(std::ostream& os, Stack& stack) {
        os << stack.size << "\n";
        Node* tempNode = stack.top;
        while (tempNode) {
            os << *(tempNode->data) << "\n";
            tempNode = tempNode->next;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Stack& stack) {
        int size;
        is >> size;
        for (int i = 0; i < size; i++) {
            T* data = new T;
            is >> *data;
            stack.push(data);
        }
        return is;
    }
};

template<typename T>
Stack<T>::Stack() : top(nullptr), size(0) {}

template<typename T>
Stack<T>::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

template<typename T>
typename Stack<T>::Node* Stack<T>::begin() {
    return top;
}

template<typename T>
typename Stack<T>::Node* Stack<T>::end() {
    return nullptr;
}

template<typename T>
void Stack<T>::push(T* value) {
    if (size >= 10) {
        throw StackOverflowException();
    }
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = top;
    top = newNode;
    size++;
}

template<typename T>
void Stack<T>::pop() {
    if (isEmpty()) {
        throw StackUnderflowException();
    }
    Node* tempNode = top;
    top = top->next;
    delete tempNode;
    size--;
}

template<typename T>
T* Stack<T>::peek() {
    if (!isEmpty()) {
        return top->data;
    }
    return nullptr;
}

template<typename T>
bool Stack<T>::isEmpty() {
    return top == nullptr;
}

template<typename T>
int Stack<T>::getSize() {
    return size;
}

template<typename T>
void Stack<T>::print() {
    Node* tempNode = top;
    if (!tempNode) {
        std::cout << "Stack is empty";
    }
    while (tempNode) {
        if (tempNode->data != nullptr) {
            std::cout << "Brand: " << tempNode->data->getBrand()
                      << ", Weight: " << tempNode->data->getWeight()
                      << ", Price: " << tempNode->data->getPrice()
                      << ", Battery Charge: " << tempNode->data->getBatteryCharge()
                      << ", Max Charge: " << tempNode->data->getMaxCharge()
                      << ", Screen Brightness: " << tempNode->data->getScreenBrightness() << "\n";
        }
        else {
            std::cout << "null";
        }
        tempNode = tempNode->next;
    }
    std::cout << std::endl;
}


template<typename T>
void Stack<T>::serialize(std::ofstream& file) {
    file.write(reinterpret_cast<const char*>(&size), sizeof(int));
    Node* tempNode = top;
    while (tempNode) {
        tempNode->data->serialize_bin(file);
        tempNode = tempNode->next;
    }
}

template<typename T>
void Stack<T>::deserialize(std::ifstream& file) {
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(int));
    for (int i = 0; i < size; ++i) {
        T* data = new T;
        data->deserialize_bin(file);
        push(data);
    }
}

#endif // STACK_H

