#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include "list.h"

template <typename T>
class ForwardList : public List<T> {
    private:
        struct Node {
            T data;
            Node* next;

            Node(){
                // Inicializa el siguiente nodo como nullptr
                next = nullptr;
            }

            Node(T value){
                data = value;
                next = nullptr; // Inicializa el siguiente nodo como nullptr
            }

            void killSelf(){
                delete this;
            }
        };

    private:
        Node* head;
        int nodes;

    public:
        ForwardList() : List<T>(), head(nullptr), nodes(0) {}

        ~ForwardList(){
            clear();  // Asegura que la memoria se libere cuando la lista sea destruida
        }

        T front(){
            return head->data;
        }

        T back(){
            if (head == nullptr) {
                return T();
            }  // Retorna un valor por defecto si la lista está vacía
            Node* temp = head;
            while(temp != nullptr){
                if(temp->next == nullptr){
                    return temp->data;
                }
                temp = temp->next;
            }
            return T();  // En caso de que algo salga mal, retorna un valor por defecto
        }

        void push_front(T data){
            Node* temp = new Node(data);
            temp->next = head;
            head = temp;
            nodes++;
        }

        void push_back(T data){
            Node* temp = new Node(data);
            if (head == nullptr) {
                head = temp;
            } else {
                Node* temp2 = head;
                while(temp2->next != nullptr){
                    temp2 = temp2->next;
                }
                temp2->next = temp;
            }
            nodes++;
        }

        T pop_front() {
            if (head == nullptr) {
                return T();
            }  // Si la lista está vacía, retorna un valor por defecto
            Node* temp = head;
            head = head->next;
            T value = temp->data;
            temp->killSelf();
            nodes--;
            return value;
        }

        T pop_back(){
            if (head == nullptr) {
                return T();
            }// Si la lista está vacía, retorna un valor por defecto
            Node* prev = head;
            Node* temp = head;
            while(temp->next != nullptr){
                prev = temp;
                temp = temp->next;
            }
            prev->next = nullptr;
            T value = temp->data;
            temp->killSelf();
            nodes--;
            return value;
        }

        bool insert(T data, int pos) override {
                if (pos < 0 || pos > nodes) return false;  // Posición inválida
                Node* temp = new Node(data);
                if (pos == 0) {
                    temp->next = head;
                    head = temp;
                } else {
                    Node* temp2 = head;
                    for(int i = 0; i < pos - 1; i++){
                        temp2 = temp2->next;
                    }
                    temp->next = temp2->next;
                    temp2->next = temp;
                }
                nodes++;
                return true;  // Retorna true para indicar que la inserción fue exitosa
            }

        bool remove(int pos){
            if (pos < 0 || head == nullptr) {
                return false;
            }

            if (pos == 0) {
                Node* toRemove = head;
                head = head->next;
                toRemove->killSelf();
                nodes--;
                return true;
            }
            Node* current = head;
            for (int i = 0; i < pos - 1; i++) {
                if (current->next == nullptr) {
                    return false;
                }
                current = current->next;
            }
            Node* toRemove = current->next;
            if (toRemove == nullptr) {
                return false;
            }
            current->next = toRemove->next;
            toRemove->killSelf();
            nodes--;
            return true;
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
            }
        }

        void sort() {
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
            if (head == nullptr || head->next == nullptr) {
                return true;
            }

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
            if (head == nullptr || head->next == nullptr) {
                return;  // Si la lista está vacía o tiene un solo elemento, no hay nada que invertir
            }

            Node* prev = nullptr;
            Node* current = head;
            Node* next = nullptr;

            while (current != nullptr) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }

            head = prev;
        }

        std::string name(){
            return "ForwardList";
        }
};

#endif
