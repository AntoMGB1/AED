#ifndef DOUBLE_H
#define DOUBLE_H

template <typename T>
struct NodeDL {
    T data;
    NodeDL* next;
    NodeDL* prev;
    NodeDL() : next(nullptr), prev(nullptr) {} 
    NodeDL(T value) : data(value), next(nullptr), prev(nullptr) {} 
};

template <typename T>
class DoubleListIterator {     
public:
    NodeDL<T>* current;
    DoubleListIterator() : current(nullptr) {};
    DoubleListIterator(NodeDL<T>* current) : current(current) {};

    DoubleListIterator<T>& operator++() {
        if (current != nullptr) {
            current = current->next;
        }
        return *this;
    }

    DoubleListIterator<T>& operator++(int) {
        DoubleListIterator<T> temp = *this;
        ++(*this);
        return temp;
    }

    DoubleListIterator<T>& operator--() {
        if (current != nullptr) {
            current = current->prev;
        }
        return *this;
    }

    bool operator!=(const DoubleListIterator<T>& other) {
        return current != other.current;
    }

    T operator*() {
        return current->data;
    }
};

template <typename T>
class DoubleList {
public:
    typedef DoubleListIterator<T> iterator;

private:
    NodeDL<T>* head;
    NodeDL<T>* tail;

public:
    DoubleList() : head(nullptr), tail(nullptr) {}

    iterator begin() {
        return iterator(head);  // Primer nodo
    }

    iterator end() {
        return iterator(nullptr);  // Fin de la lista
    }

    void push_back(T data) {
        NodeDL<T>* newNode = new NodeDL<T>(data);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    T pop_back() {
        if (tail == nullptr) throw std::out_of_range("List is empty");

        NodeDL<T>* temp = tail;
        T data = tail->data;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;  // Si la lista queda vacía
        }
        delete temp;
        return data;
    }

    ~DoubleList() {
        while (head != nullptr) {
            pop_back();
        }
    }
};

#endif
