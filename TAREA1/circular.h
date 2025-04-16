#ifndef CIRCULAR_H
#define CIRCULAR_H
#include <iostream>
#include "list.h"

// TODO: Implement all methods
template <typename T>
class CircularList : public List<T> {  
    private:
        struct Node {
            T data;
            Node* next;
            Node* prev;

            Node(){
                next = nullptr;
                prev = nullptr;
            }

            Node(T value){
                data = value;
                next = nullptr;
                prev = nullptr;
            }

            void killSelf(){
                delete this;
            }    
        };

    private:
        Node* head; // sentinel node
        int nodes;

    public:
        CircularList() : List<T>(), nodes(0) {
            head = new Node();  // Create a sentinel node to make the list circular
            head->next = head;
            head->prev = head;
        }

        ~CircularList(){
            clear();
            delete head;  // Free sentinel node
        }

        T front(){
            if (head->next == head) return T();  // List is empty
            return head->next->data;
        }

        T back(){
            if (head->prev == head) return T();  // List is empty
            return head->prev->data;
        }

        void push_front(T data){
            Node* temp = new Node;
            temp->data = data;
            if (head->next == head) {
                temp->next = head;
                temp->prev = head;
                head->next = temp;
                head->prev = temp;
            } else {
                temp->next = head->next;
                head->next->prev = temp;
                temp->prev = head;
                head->next = temp;
            }
            nodes++;
        }

        void push_back(T data){
            Node* temp = new Node;
            temp->data = data;
            temp->next = head;
            temp->prev = head->prev;
            head->prev->next = temp;
            head->prev = temp;
            nodes++;
        }

        T pop_front(){
            if (head->next == head) return T();  // List is empty
            Node* temp = head->next;
            head->next = head->next->next;
            head->next->prev = head;
            T data = temp->data;
            temp->killSelf();
            nodes--;
            return data;
        }

        T pop_back(){
            if (head->prev == head) return T();  // List is empty
            Node* temp = head->prev;
            head->prev = head->prev->prev;
            head->prev->next = head;
            T data = temp->data;
            temp->killSelf();
            nodes--;
            return data;
        }

        bool insert(T data, int pos){
            if (pos < 0 || pos > nodes) return false; // Invalid position
            Node* temp = new Node;
            temp->data = data;
            Node* temp2 = head;
            for (int i = 0; i < pos; i++) {
                temp2 = temp2->next;
            }
            temp->next = temp2->next;
            temp->prev = temp2;
            temp2->next = temp;
            temp->next->prev = temp;
            nodes++;
            return true;
        }

        bool remove(int pos){
            if (pos < 0 || pos >= nodes) return false; // Invalid position
            Node* temp = head->next;
            for (int i = 0; i < pos; i++) {
                temp = temp->next;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            temp->killSelf();
            nodes--;
            return true;
        }

        T& operator[](int pos){
            if (pos < 0 || pos >= nodes) throw std::out_of_range("Index out of range");
            Node* temp = head->next;
            for (int i = 0; i < pos; i++) {
                temp = temp->next;
            }
            return temp->data;
        }

        bool is_empty(){
            return head->next == head;
        }

        int size(){
            return nodes;
        }

        void clear(){
            while (head->next != head) {
                Node* temp = head->next;
                head->next = head->next->next;
                head->next->prev = head;
                temp->killSelf();
                nodes--;
            }
        }

        void sort(){
            if (head->next == head || head->next->next == head) return;  // List has 0 or 1 elements
            bool swapped;
            do {
                swapped = false;
                Node* current = head->next;
                while (current->next != head) {
                    if (current->data > current->next->data) {
                        std::swap(current->data, current->next->data);
                        swapped = true;
                    }
                    current = current->next;
                }
            } while (swapped);
        }

        bool is_sorted(){
            Node* current = head->next;
            while (current->next != head) {
                if (current->data > current->next->data) {
                    return false;
                }
                current = current->next;
            }
            return true;
        }

        void reverse(){
            if (head->next == head || head->next->next == head) return;  // List has 0 or 1 elements
            Node* current = head->next;
            Node* prevNode = nullptr;
            Node* nextNode = nullptr;
            while (current != head) {
                nextNode = current->next;
                current->next = prevNode;
                current->prev = nextNode;
                prevNode = current;
                current = nextNode;
            }
            head->next->prev = nullptr;
            head->next = prevNode;
        }

        std::string name(){
            return "CircularList";
        }
};

#endif
