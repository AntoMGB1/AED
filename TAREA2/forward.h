#ifndef FORWARD_H
#define FORWARD_H

template <typename T>
struct NodeFL {
    T data;
    NodeFL* next;
    NodeFL() : next(nullptr) {} 
    NodeFL(T value) : data(value), next(nullptr) {} 
};

template <class T>
class ForwardListIterator {
private:
    NodeFL<T>* current;
public:
    ForwardListIterator() : current(nullptr) {};
    ForwardListIterator(NodeFL<T> *current) : current(current) {};

    ForwardListIterator<T>& operator++() {
        if (current != nullptr) {
            current = current->next;
        }
        return *this;
    }

    ForwardListIterator<T>& operator++(int) {
        ForwardListIterator<T> temp = *this;
        ++(*this);
        return temp;
    }

    bool operator!=(const ForwardListIterator<T>& other) {
        return current != other.current;
    }

    T operator*() {
        return current->data;
    }
};

template <typename T>
class ForwardList {
public:
    typedef ForwardListIterator<T> iterator;

private:
    NodeFL<T>* head;

public:
    ForwardList() : head(nullptr) {}

    iterator begin() {
        return iterator(head);  // Devuelve el primer nodo de la lista
    }

    iterator end() {
        return iterator(nullptr);  // Fin de la lista
    }

    void push_front(T data) {
        NodeFL<T>* newNode = new NodeFL<T>(data);
        newNode->next = head;
        head = newNode;
    }

    T pop_front() {
        if (head == nullptr) throw std::out_of_range("List is empty");
        NodeFL<T>* temp = head;
        T data = head->data;
        head = head->next;
        delete temp;
        return data;
    }

    ~ForwardList() {
        while (head != nullptr) {
            pop_front();
        }
    }
};

#endif
