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
    if(moving_node == head) {
      return;
    }
    
    //zawsze o jeden wczesniejszy od oczekiwanej pozycji
    Node* predecessor = moving_node->prev;
    while(x > 0 && predecessor != head) {
      predecessor = predecessor->prev;
      --x;
    }

    //jezeli moving_node jest ogonem aspirujacym do bycia glowa
    if(predecessor == head && x > 0 && moving_node == tail) {
      head = moving_node;
      tail = moving_node->prev;

      moving_node->prev->next = nullptr;
      moving_node->prev = nullptr;
      moving_node->next = predecessor;
      predecessor->prev = moving_node;
    //jezeli moving_node chce byc glowa ale nie jest ogonem
    } else if (predecessor == head && x > 0) {
      head = moving_node;
      
      moving_node->prev->next = moving_node->next;
      moving_node->next->prev = moving_node->prev;
      moving_node->prev = nullptr;
      moving_node->next = predecessor;
      predecessor->prev = moving_node;
    //jezeli moving_node jest ogonem ale nie bedzie glowa
    } else if (moving_node == tail) {
      tail = moving_node->prev;
      
      moving_node->prev->next = nullptr;
      moving_node->prev = predecessor;
      moving_node->next = predecessor->next;
      predecessor->next->prev = moving_node;
      predecessor->next = moving_node;
    //standardowy przypadek w srodku listy
    } else {
      moving_node->prev->next = moving_node->next;
      moving_node->next->prev = moving_node->prev;
      moving_node->prev = predecessor;
      moving_node->next = predecessor->next;
      predecessor->next->prev = moving_node;
      predecessor->next = moving_node;
    }
  }

  void move_down(Node* &moving_node, int x) {
    if(moving_node == tail) {
      return;
    }
    //zawsze o jeden nastepny od oczekiwanej pozycji
    Node* successor = moving_node->next;
    while(x < 0 && successor != tail) {
      successor = successor->next;
      ++x;
    }

    //jezeli moving_node jest glowa aspirujaca do bycia ogonem
    if(successor == tail && x < 0 && moving_node == head) {
      head = moving_node->next;
      tail = moving_node;

      moving_node->next->prev = nullptr;
      moving_node->next = nullptr;
      moving_node->prev = successor;
      successor->next = moving_node;
    //jezeli moving_node chce byc ogonem ale nie jest glowa
    } else if (successor == tail && x < 0) {
      tail = moving_node;
      
      moving_node->next->prev = moving_node->prev;
      moving_node->prev->next = moving_node->next;
      moving_node->next = nullptr;
      moving_node->prev = successor;
      successor->next = moving_node;
    //jezeli moving_node jest glowa ale nie bedzie ogonem
    } else if (moving_node == head) {
      head = moving_node->next;
      
      moving_node->next->prev = nullptr;
      moving_node->next = successor;
      moving_node->prev = successor->prev;
      successor->prev->next = moving_node;
      successor->prev = moving_node;
    //standardowy przypadek w srodku listy
    } else {
      moving_node->next->prev = moving_node->prev;
      moving_node->prev->next = moving_node->next;
      moving_node->next = successor;
      moving_node->prev = successor->prev;
      successor->prev->next = moving_node;
      successor->prev = moving_node;
    }
  }

  void swap(Node* &a, Node* &b) {
    string tmp = a->data;
    a->data = b->data;
    b->data = tmp;
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
      Node* tmp = name_map[s1];
      name_map[s1] = name_map[s2];
      name_map[s2] = tmp;
    }
  }

  //wyswietlenie odpowiedzi
  people.print_list();

  return 0;
}