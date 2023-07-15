#include <iostream>

//!!!!!!!
#include <map>

using namespace std;

struct Node {
  Node* next;
  Node* prev;
  string data;

  Node(){}
  Node(string data) {
    this->data = data;
    next = nullptr;
    prev = nullptr;
  }
};

struct Linked_List {
  Node* head;
  Node* tail;
  Linked_List() {
    head = nullptr;
    tail = nullptr;
  }

  void push_back(string data) {
    Node* new_node = new Node(data);
    if(head == nullptr) {
      head = new_node;
      tail = new_node;
    } else {
      tail->next = new_node;
      new_node->prev = tail;
      tail = new_node;
    }
  }

  void print_list() {
    Node* current = head;
    while(current != nullptr) {
      cout<<current->data<<"\n";
      current = current->next;
    }
  }

  void move_up(Node* &moving_node, int x) {
    if(x == 0) {
      return;
    }
    Node* previous = moving_node->prev;
    bool too_high = false;

    if(moving_node == tail) {
      tail = previous;
    } else {
      moving_node->next->prev = previous;
    }

    if(previous == head) {
      head = moving_node;
      too_high = true;
    } else {
      previous->prev->next = moving_node;
    }
    
    moving_node->prev = previous->prev;
    previous->next = moving_node->next;
    previous->prev = moving_node;
    moving_node->next = previous;

    if(too_high) {
      return;
    }
    move_up(moving_node,x - 1);
  }

  void move_down(Node* &moving_node, int x) {
    if(x == 0) {
      return;
    }
    Node* successor = moving_node->next;
    bool too_low = false;

    if(moving_node == head) {
      head = successor;
    } else {
      moving_node->prev->next = successor;
    }

    if(successor == tail) {
      tail = moving_node;
      too_low = true;
    } else {
      successor->next->prev = moving_node;
    }

    moving_node->next = successor->next;
    successor->prev = moving_node->prev;
    successor->next = moving_node;
    moving_node->prev = successor;

    if(too_low) {
      return;
    }
    move_down(moving_node,x + 1);
  }

  void swap(Node* &a, Node* &b) {
    if(a == head) {
      head = b;
      b->prev->next = a;
    } else if (b == head) {
      head = a;
      a->prev->next = b;
    } else {
      a->prev->next = b;
      b->prev->next = a;
    }

    if(a == tail) {
      tail = b;
      b->next->prev = a;
    } else if(b == tail) {
      tail = a;
      a->next->prev = b;
    } else {
      a->next->prev = b;
      b->next->prev = a;
    }
    
    Node* tmp;
    tmp = a->next;
    a->next = b->next;
    b->next = tmp;
    tmp = a->prev;
    a->prev = b->prev;
    b->prev = tmp;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.tie(nullptr);
  
  int n,m; //liczba osob na start, liczba operacji do wykonania
  string s; //pseudonim osoby
  char op; //operacja
  Linked_List people;
  map <string,Node*> name_map;
  
  cin>>n;
  for(int i=0;i<n;++i) {
    cin>>s;
    people.push_back(s);
    name_map[s] = people.tail;
  }

  cin>>m;
  for(int i=0;i<m;++i) {
    cin>>op;
    //dodanie na koniec listy
    if(op == 'a') {
      cin>>s;
      people.push_back(s);
      name_map[s] = people.tail;

      //przesuniecie osoby s o x miejsc
    } else if (op == 'm') {
      int x; //ilosc miejsc do przesuniecia
      cin>>s>>x;
      Node* moving_node = name_map[s];
      if(x > 0) {
        people.move_up(moving_node,x);
      } else {
        people.move_down(moving_node,x);
      }

      //zamiana miejscami s1 z s2
    } else {
      string s1,s2;
      cin>>s1>>s2;
      Node* a = name_map[s1];
      Node* b = name_map[s2];
      people.swap(a,b);
    }
    // people.print_list();
    
    // cout<<"head: "<<people.head->data<<endl;
    // cout<<"tail: "<<people.tail->data<<endl;
    // cout<<"---"<<endl;
  }

  //wyswietlenie odpowiedzi
  people.print_list();

  return 0;
}