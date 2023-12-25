#include "Serializable.h"

template <class T>
class Stack : public Serializable {
    int top;
    T *data;
    int capacity;

public:
    Stack(int capacity = 10) : top(-1), capacity(capacity) {
        data = new T[capacity];
    }

    bool isEmpty() {
        return (top == -1);
    }

    bool isFull() {
        return (top == capacity - 1);
    }

    bool push(const T& x) {
        if (isFull()) {
            std::cout << "Stack overflow" << std::endl;
            return false;
        }
        data[++top] = x;
        return true;
    }

    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack Underflow");
        }
        return data[top--];
    }

    T peek() {
        if (!isEmpty()) {
            return data[top];
        } else {
            throw std::out_of_range("Stack Underflow");
        }
    }


    int size() {
        return top + 1;
    }

    void print() {
        for (int i = 0; i <= top; ++i) {
            std::cout << data[i] << std::endl;
        }
    }

    void serialize(std::ofstream& file) override {
        file.write(reinterpret_cast<const char*>(&top), sizeof(int));
        for (int i = 0; i <= top; ++i) {
            data[i].serialize_bin(file);
        }
    }

    void deserialize(std::ifstream& file) override {
        file.read(reinterpret_cast<char*>(&top), sizeof(int));
        for (int i = 0; i <= top; ++i) {
            data[i].deserialize_bin(file);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, Stack& stack) {
        os << stack.top << "\n";
        for (int i = 0; i <= stack.top; ++i) {
            os << stack.data[i] << "\n";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Stack& stack) {
        is >> stack.top;
        for (int i = 0; i <= stack.top; ++i) {
            is >> stack.data[i];
        }
        return is;
    }

    ~Stack(){
        delete[] data;
    }
};
