#ifndef DOUBLY_H
#define DOUBLY_H
#include <iostream>
#include "list.h"

// TODO: Implement all methods
template <typename T>
class DoubleList : public List<T> {
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
        Node* head;
        Node* tail;
        int nodes;

    public:
        DoubleList() : List<T>(), head(nullptr), tail(nullptr), nodes(0) {}

        ~DoubleList(){
            clear();
        }

        T front(){
            if(head == nullptr) {
                return T();
            };
            return head->data;
        }

        T back(){
            if(tail == nullptr) {
                return T();
            }
            return tail->data;
        }

        void push_front(T data){
            Node* temp = new Node;
            temp->data = data;
            temp->next = head;
            temp->prev = nullptr;
            if(head != nullptr){
                head->prev = temp;
            }
            head = temp;
            if(tail == nullptr){
                tail = head;
            }
            nodes++;
        }

        void push_back(T data){
            Node* temp = new Node;
            temp->data = data;
            temp->next = nullptr;
            temp->prev = tail;
            if(tail != nullptr){
                tail->next = temp;
            }
            tail = temp;
            if(head == nullptr){
                head = tail;
            }
            nodes++;
        }

        T pop_front(){
            if (head == nullptr) return T();  // Add check for empty list
            Node* temp = head;
            head = head->next;
            if (head != nullptr) head->prev = nullptr;
            T data = temp->data;
            temp->killSelf();
            nodes--;
            return data;
        }

        T pop_back(){
            if (tail == nullptr) return T();  // Add check for empty list
            Node* temp = tail;
            tail = tail->prev;
            if (tail != nullptr) tail->next = nullptr;
            T data = temp->data;
            temp->killSelf();
            nodes--;
            return data;
        }

        bool insert(T data, int pos){
            Node* temp = new Node;
            temp->data = data;
            temp->next = nullptr;
            temp->prev = nullptr;
            if (head == nullptr) {
                push_front(data);
                return true;
            }
            else if(pos == 0){
                temp->next = head;
                head->prev = temp;
                head = temp;
                return true;
            }
            else if(pos == nodes-1) {
                temp->prev = tail;
                tail->next = temp;
                tail = temp;
                return true;
            }
            else {
                Node* temp2 = head;
                for(int i = 0; i < pos-1; i++) {
                    temp2 = temp2->next;
                }
                temp->next = temp2->next;
                if (temp2->next != nullptr) temp2->next->prev = temp;
                temp2->next = temp;
                temp->prev = temp2;
            }
            nodes++;
            return true;
        }

        bool remove(int pos){
            Node* temp = head;
            if (pos == 0) {
                head = head->next;
                if (head != nullptr) head->prev = nullptr;
                temp->killSelf();
                nodes--;
                return true;
            }
            else if(pos == nodes-1) {
                tail = tail->prev;
                tail->next = nullptr;
                temp->killSelf();
                nodes--;
                return true;
            }
            else {
                Node* temp2 = head;
                for(int i = 0; i < pos-1; i++) {
                    temp2 = temp2->next;
                }
                temp->next = temp2->next;
                if (temp2->next != nullptr) temp2->next->prev = temp2;
                temp->killSelf();
                nodes--;
                return true;
            }
        }

        T& operator[](int pos){
            Node* temp = head;
            for(int i = 0; i < pos; i++) {
                temp = temp->next;
            }
            return temp->data;
        }

        bool is_empty(){
            return head == nullptr;
        }

        int size(){
            return nodes;
        }

        void clear(){
            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                temp->killSelf();
                nodes--;
            };
        }

        void sort(){
            Node* temp = head;
            while (temp != nullptr) {
                Node* temp2 = temp;
                while (temp2->next != nullptr) {
                    if (temp2->data > temp2->next->data) {
                        T temp3 = temp2->data;
                        temp2->data = temp2->next->data;
                        temp2->next->data = temp3;
                    }
                    temp2 = temp2->next;
                }
                temp = temp->next;
            }
        }

        bool is_sorted(){
            Node* temp = head;
            while (temp->next != nullptr) {
                if (temp->data > temp->next->data) {
                    return false;
                }
                temp = temp->next;
            }
            return true;
        }

        void reverse(){
            Node* prev = nullptr;
            Node* current = head;
            Node* next = nullptr;
            while (current != nullptr) {
                next = current->next;
                current->next = prev;
                if (prev != nullptr) prev->prev = current;
                prev = current;
                current = next;
            }
            head = prev;
            if (head != nullptr) head->prev = nullptr;
            tail = prev;
            if (tail != nullptr) tail->next = nullptr;
        }

        std::string name(){
            return "DoubleList";
        }
};

#endif
