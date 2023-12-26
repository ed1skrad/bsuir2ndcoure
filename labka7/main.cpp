#include <iostream>
#include <algorithm>
#include "Stack.h"
#include <iterator>

template<class T>
void multiply(typename Stack<T>::iterator begin, typename Stack<T>::iterator end, const T& value) {
    std::for_each(begin, end, [value](T& x) {
        x *= value;
    });

    std::cout << "Values after multiplication: ";
    for (auto it = begin; it != end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename Iterator, typename T>
Iterator stack_search(Iterator begin, Iterator end, const T& value) {
    for (auto it = begin; it != end; ++it) {
        if (*it == value) {
            return it;
        }
    }
    return end;
}


int main() {
    Stack<int> stack(10);
    int choice;
    int value;

    while (true) {
        std::cout << "\n1. Push\n2. Pop\n3. Peek\n4. Print\n5. Search\n6. Multiply\n7. Exit\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter value: ";
                std::cin >> value;
                stack.push(value);
                break;
            case 2:
                stack.pop();
                break;
            case 3:
                std::cout << "Top element: " << stack.peek() << std::endl;
                break;
            case 4:
                stack.print();
                break;
            case 5:
                std::cout << "Enter value to search: ";
                std::cin >> value;
                if (stack_search(stack.begin(), stack.end(), value) != stack.end()) {
                    std::cout << "Value found\n";
                } else {
                    std::cout << "Value not found\n";
                }
                break;
            case 6:
                std::cout << "Enter value to multiply: ";
                std::cin >> value;
                multiply(stack.begin(), stack.end(), value);
                break;
            case 7:
                return 0;
            default:
                std::cout << "Invalid choice\n";
        }
    }

    return 0;
}
