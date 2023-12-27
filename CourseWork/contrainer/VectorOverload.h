//
// Created by atema on 28.12.2023.
//

#ifndef COURSEWORK_VECTOROVERLOAD_H
#define COURSEWORK_VECTOROVERLOAD_H
#ifndef MY_VECTOR_H
#define MY_VECTOR_H

template <typename T>
class MyVector {
private:
    T* arr;
    int capacity;
    int current;

public:
    MyVector() {
        arr = new T[1];
        capacity = 1;
        current = 0;
    }

    void push(T data) {
        if (current == capacity) {
            T* temp = new T[2 * capacity];

            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
        arr[current] = data;
        current++;
    }

    void pop() { current--; }

    T at(int index) { return arr[index]; }

    int size() { return current; }

    int getcapacity() { return capacity; }

    ~MyVector() { delete[] arr; }
};

#endif //MY_VECTOR_H

#endif //COURSEWORK_VECTOROVERLOAD_H
