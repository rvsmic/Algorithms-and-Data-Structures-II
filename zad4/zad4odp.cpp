#include <iostream>
using namespace std;

enum Color {red, black};

//pojedynczy node linked listy
struct List_Node {
  List_Node* next;
  List_Node* prev;
  string data;

  List_Node(){}
  List_Node(string data) {
    this->data = data;
    next = nullptr;
    prev = nullptr;
  }
};

//klasa linked listy
class Linked_List {
  List_Node* head;
  List_Node* tail;

  public:
  Linked_List() {
    head = nullptr;
    tail = nullptr;
  }

  List_Node* get_tail() {
    return tail;
  }

  //dodanie na koniec
  void push_back(string data) {
    List_Node* new_node = new List_Node(data);
    if(head == nullptr) {
      head = new_node;
      tail = new_node;
    } else {
      tail->next = new_node;
      new_node->prev = tail;
      tail = new_node;
    }
  }

  //wydrukowanie calej listy
  void print_list() {
    List_Node* current = head;
    while(current != nullptr) {
      cout<<current->data<<"\n";
      current = current->next;
    }
  }

  //przesuniecie w gore listy o x
  void move_up(List_Node* &moving_node, int x) {
    //jak sie nie da cofnac od razu
    if(moving_node == head) {
      return;
    }
    
    //zawsze o jeden wczesniejszy od oczekiwanej pozycji
    List_Node* predecessor = moving_node->prev;
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

  //przesuniecie w dol listy o x
  void move_down(List_Node* &moving_node, int x) {
    //jak sie nie da pojsc dalej od razu
    if(moving_node == tail) {
      return;
    }

    //zawsze o jeden nastepny od oczekiwanej pozycji
    List_Node* successor = moving_node->next;
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

  //zamiana wartosci dwoch nodeow
  void swap_values(List_Node* &a, List_Node* &b) {
    string tmp = a->data;
    a->data = b->data;
    b->data = tmp;
  }
};

//pojedynczy node drzewa czerwono czarnego
struct Tree_Node {
  Tree_Node* parent;
  Tree_Node* left;
  Tree_Node* right;
  Color color;

  string key;
  List_Node* data;

  Tree_Node(){}
  Tree_Node(string key, List_Node* data) {
    this->key = key;
    this->data = data;
    color = red;
    parent = nullptr;
  }
};

//klasa drzewa czerwono czarnego
class Red_Black_Tree {
  Tree_Node* root;
  //dodatkowy node - ustawiany domyslnie jako lisc, poniewaz puste liscie sa zawsze traktowane jako czarne
  Tree_Node empty_leaf;

  //wewnetrzna operacja dodania elementu do drzewa
  void add_node(Tree_Node* &node) {
    Tree_Node* current = root;
    while(true) {
      if(current->key.compare(node->key) > 0) {
        //jak nowy jest mniejszy od current node'a
        if(current->left == &empty_leaf) {
          current->left = node;
          node->parent = current;
          return;
        } else {
          //schodzimy nizej
          current = current->left;
        }
      } else if(current->key.compare(node->key) < 0) {
        //jak nowy jest wiekszy od current node'a
        if(current->right == &empty_leaf) {
          current->right = node;
          node->parent = current;
          return;
        } else {
          //schodzimy nizej
          current = current->right;
        }
      } else {
        //jak ten sam element - podmiana wartosci
        current->data = node->data;
        delete node;
        return;
      }
    }
  }

  //do operacji rotate przekazywany jest node, ktory jest wyzej - w jego miejsce laduje jeden z synow itd.
  void rotate_left(Tree_Node* top_node) {
    //dziecko z ktorym robimy rotacje
    Tree_Node* rotated_child = top_node->right;
    
    rotated_child->parent = top_node->parent;
    if(top_node == root) {
      root = rotated_child;
    } else {
      if(top_node->parent->left == top_node) {
        top_node->parent->left = rotated_child;
      } else {
        top_node->parent->right = rotated_child;
      }
    }
    top_node->right = rotated_child->left;
    rotated_child->left->parent = top_node;
    rotated_child->left = top_node;
    top_node->parent = rotated_child;
  }
  
  //rotacja ale w druga strone
  void rotate_right(Tree_Node* top_node) {
    Tree_Node* rotated_child = top_node->left;
    
    rotated_child->parent = top_node->parent;
    if(top_node == root) {
      root = rotated_child;
    } else {
      if(top_node->parent->right == top_node) {
        top_node->parent->right = rotated_child;
      } else {
        top_node->parent->left = rotated_child;
      }
    }
    top_node->left = rotated_child->right;
    rotated_child->right->parent = top_node;
    rotated_child->right = top_node;
    top_node->parent = rotated_child;
  }

  //naprawa drzewa - po dodaniu zapewnienie spelniania regul drzewa czerwono czarnego
  void fix_tree(Tree_Node* &snode) {
    Tree_Node* current = snode;
    //jezeli nie doszlismy jeszcze do korzenia i rodzic nie jest czarny
    while(current != root && current->parent->color != black) {
      Tree_Node* parent = current->parent;
      Tree_Node* grandparent = nullptr;
      Tree_Node* uncle = nullptr;
      if(parent != nullptr) {
        grandparent = parent->parent;
        if(grandparent != nullptr) {
          uncle = grandparent->left == parent ? grandparent->right : grandparent->left;
        }
      }

      //upewnienie ze drzewo jest wystarczajaco duze
      if(grandparent != nullptr) {
        //przypadek 1 - wujek jest czerwony
        if(uncle->color == red) {
          grandparent->color = red;
          uncle->color = black;
          parent->color = black;

          //jezeli dziadek jest korzeniem
          if(grandparent == root) {
            grandparent->color = black;
            break;
          } else {
            current = grandparent;
            continue;
          }
        }

        //przypadek 2 - wujek jest czarny, a nowy wezel jest prawym dzieckiem (a rodzic jest lewym dzieckiem dziadka)
        if(uncle->color == black && current == parent->right && parent == grandparent->left) {
          //rotacja w lewo wzgledem rodzica
          rotate_left(parent);
          current = parent;
        //przypadek 2 - wujek jest czarny, a nowy wezel jest lewym dzieckiem (a rodzic jest prawym dzieckiem dziadka)
        } else if (uncle->color == black && current == parent->left && parent == grandparent->right) {
          //rotacja w prawo wzgledem rodzica
          rotate_right(parent);
          current = parent;
        }
        //i przejscie do przypadku 3 z bylym rodzicem jako nowy wezel

        //przypadek 3 - wujek jest czarny, a nowy wezel jest lewym dzieckiem (a rodzic tez jest lewym dzieckiem dziadka)
        if(uncle->color == black && current == parent->left && parent == grandparent->left) {
          //rotacja w prawo wzgledem dziadka
          rotate_right(grandparent);
          //zamiana kolorow rodzica i dziadka na przeciwne
          parent->color = parent->color == black ? red : black;
          grandparent->color = grandparent->color == black ? red : black;
          break;
        } else if (uncle->color == black && current == parent->right && parent == grandparent->right) {
          //rotacja w lewo wzgledem dziadka
          rotate_left(grandparent);
          //zamiana kolorow rodzica i dziadka na przeciwne
          parent->color = parent->color == black ? red : black;
          grandparent->color = grandparent->color == black ? red : black;
          break;
        }
      }
    }
    //korzen jest zawsze czarny
    root->color = black;
  }

  public:
  Red_Black_Tree() {
    root = nullptr;
    empty_leaf.color = black;
  }

  //publiczna operacja dodania elementu do drzewa
  void insert(string key, List_Node* data) {
    Tree_Node* new_node = new Tree_Node(key,data);
    new_node->left = &empty_leaf;
    new_node->right = &empty_leaf;
    if(root == nullptr) {
      root = new_node;
      new_node->color = black;
    } else {
      add_node(new_node);
      fix_tree(new_node);
    }
  }

  //zwrocenie elementu po kluczu (nie bierze pod uwage mozliwosci w ktorej nie ma takiego klucza, ale w zadaniu nie ma takiego wymogu)
  List_Node* get(string key) {
    Tree_Node* current = root;
    while(true) {
      if(current->key.compare(key) > 0) {
        //jak klucz jest mniejszy od current node'a
        //schodzimy nizej
        current = current->left;
        
      } else if(current->key.compare(key) < 0) {
        //jak klucz jest wiekszy od current node'a
        //schodzimy nizej
        current = current->right;
        
      } else {
        //jak znaleziono element spod klucza
        return current->data;
      }
    }
  }

  //aktualizacja wartosci elementu po kluczu (nie bierze pod uwage mozliwosci w ktorej nie ma takiego klucza, ale w zadaniu nie ma takiego wymogu)
  void update(string key, List_Node* new_value) {
    Tree_Node* current = root;
    while(true) {
      if(current->key.compare(key) > 0) {
        //jak klucz jest mniejszy od current node'a
        //schodzimy nizej
        current = current->left;
        
      } else if(current->key.compare(key) < 0) {
        //jak klucz jest wiekszy od current node'a
        //schodzimy nizej
        current = current->right;
        
      } else {
        //jak znaleziono element spod klucza
        current->data = new_value;
        return;
      }
    }
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
  Red_Black_Tree tree;
  
  cin>>n;
  for(int i=0;i<n;++i) {
    cin>>s;
    people.push_back(s);
    tree.insert(s,people.get_tail());
  }

  cin>>m;
  for(int i=0;i<m;++i) {
    cin>>op;
    //dodanie na koniec listy
    if(op == 'a') {
      cin>>s;
      people.push_back(s);
      tree.insert(s,people.get_tail());

      //przesuniecie osoby s o x miejsc
    } else if (op == 'm') {
      int x; //ilosc miejsc do przesuniecia
      cin>>s>>x;
      List_Node* moving_node = tree.get(s);
      if(x > 0) {
        people.move_up(moving_node,x);
      } else if (x < 0) {
        people.move_down(moving_node,x);
      }

      //zamiana miejscami s1 z s2
    } else {
      string s1,s2;
      cin>>s1>>s2;
      List_Node* a = tree.get(s1);
      List_Node* b = tree.get(s2);
      people.swap_values(a,b);
      tree.update(s1,b);
      tree.update(s2,a);
    }
  }

  //wyswietlenie odpowiedzi
  people.print_list();

  return 0;
}