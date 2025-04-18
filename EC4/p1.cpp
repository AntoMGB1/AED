class Stack {
private:
  struct Node {
    int val;
    Node* next;
    Node(int x) : val(x), next(nullptr) {}
  };
  Node* topNode;
public:
  Stack() : topNode(nullptr) {}
  
  void push(int x) {
    Node* node = new Node(x);
    node->next = topNode;
    topNode = node;
  }
  
  int pop() {
    if (empty()) {
      throw std::out_of_range("Pila vacía");
    }
    int val = topNode->val;
    Node* temp = topNode;
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
    ListNode* fast = head;
    ListNode* slow = head;
    Stack* stack = new Stack();
    
    while (fast != nullptr && fast->next != nullptr) {
      stack->push(slow->val);
      slow = slow->next;
      fast = fast->next->next;
    }
    
    if (fast != nullptr) {
      slow = slow->next;
    }
    
    while (slow != nullptr) {
      if (stack->top() != slow->val) {
        return false;
      }
      stack->pop();
      slow = slow->next;
    }
    
    return true;
  }
};

