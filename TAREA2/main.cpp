#include <iostream>
#include "forward.h"
#include "double.h"

using namespace std;

void testSimpleLinkedList() {
    cout << "Forward Linked List" << endl;

    ForwardList<int> integers;

    for (int i = 0; i < 5; i++) {
        integers.push_front(2 * i);
    }

    integers.pop_front();

    ForwardList<int>::iterator ite;
    for (ite = integers.begin(); ite != integers.end(); ++ite)
        cout << *ite << " ";  // Salida: 6 4 2 0
}

void testDoubleLinkedList() {
    cout << "Doubly Linked List" << endl;

    DoubleList<int> integers;

    for (int i = 0; i < 5; i++) {
        integers.push_back(2 * i);
    }

    integers.pop_back();

    DoubleList<int>::iterator ite = integers.begin();
    ++ite;
    cout << *ite << " ";  // Salida: 2
    ++ite;
    cout << *ite << " ";  // Salida: 4
    --ite;
    cout << *ite << " ";  // Salida: 2
}

int main() {
    testSimpleLinkedList();
    cout << endl;
    testDoubleLinkedList();
    return 0;
}
