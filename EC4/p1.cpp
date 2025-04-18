#include <iostream>
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Stack {
private:
  struct Nodo {
    int val;
    Nodo* next;
    Node(int x) : val(x), next(nullptr) {}
  };
  Nodo* topNode;
public:
  Stack() : topNode(nullptr) {}
  void push(int x) {
    Nodo* node = new Node(x);
    node->next = topNode;
    topNode = node;
  }
  int pop() {
    if (empty()) {
      throw std::out_of_range("Pila vacía");
    }
    int val = topNode->val;
    Nodo* temp = topNode;
    topNode = topNode->next;
    delete temp;
    return val;
  }
  int top() {
    if (empty()) {
      throw std::out_of_range("Pila vacía");
    }
    return topNode->val;
  }
  bool empty() {
    return topNode == nullptr;
  }
  ~Stack() {
    while (!empty()) {
      pop();
    }
  }
};
class Solution {
public:
  bool isPalindrome(ListNode* head) {
    Nodo* fast = head;
    Nodo* slow = head;
    Stack* stack = new Stack;
    while (fast != nullptr && fast->next != nullptr) {
      stack.push(slow->val);
      fast = fast->next->next;
      slow = slow->next;
    }
    while (slow != nullptr) {
      if (stack.top() != slow->val) {
        return false;
      }
      slow = slow->next;
    }
    return true;
  }
};
