#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

//drzewo bst

struct Node {
  int value;
  Node* left;
  Node* right;
  
  Node(){}
  Node(int value) {
    this->value = value;
    left = nullptr;
    right = nullptr;
  }

  void add_child(Node* new_node) {
    //this to root drzewa
    Node* current = this;
    while(true) {
      //jak nowy jest mniejszy od current node'a
      if(current->value > new_node->value) {
        if(current->left == nullptr) {
          current->left = new_node;
          return;
        } else {
          //schodzimy nizej
          current = current->left;
        }
      //jak nowy jest wiekszy od current node'a
      } else if(current->value < new_node->value) {
        if(current->right == nullptr) {
          current->right = new_node;
          return;
        } else {
          //schodzimy nizej
          current = current->right;
        }
      //jak ten sam element
      } else {
        delete new_node;
        return;
      }
    }
  }

  void convert_to_value_arr(vector <int> &value_arr) {
    if(left != nullptr) {
      //schodzimy nizej
      left->convert_to_value_arr(value_arr);
      //dodajemy najnizszy z lewej i wracamy do gory
      value_arr.push_back(value);
      //jak sie skonczy lewa odnoga
      if(right != nullptr) {
        right->convert_to_value_arr(value_arr);
      }
    } else if(right != nullptr) {
      //idziemy w prawo
      //dodajemy stary node
      value_arr.push_back(value);
      //schodzimy nizej
      right->convert_to_value_arr(value_arr);
    } else {
      //jak sie skonczy odnoga
      value_arr.push_back(value);
    }
  }
};

//aktualizacja drzewa zaleznie od limitow
Node* adjust_to_limits(Node* &current, int bottom, int top) {
  //zejscie na sam dol
  if(current->left != nullptr) {
    current->left = adjust_to_limits(current->left,bottom,top);
  }
  if(current->right != nullptr) {
    current->right = adjust_to_limits(current->right,bottom,top);
  }
  //usuwanie node'ow 
  if(current->value < bottom) {
    Node* tmp = current->right;
    delete current;
    return tmp;
  } else if (current->value > top) {
    Node* tmp = current->left;
    delete current;
    return tmp;
  } else {
    return current;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.tie(nullptr);
  
  int n, a, b, k; //ilosc wplywow, granica dolna i gorna, oczekiwana suma 
  cin>>n;
  int value; //wartosc

  //ustawienie korzenia
  cin>>value;
  Node* root = new Node(value);
  for(int i=1;i<n;++i) {
    cin>>value;
    root->add_child(new Node(value));
  }

  //ustawienie limitow i zmnieszenie drzewa
  cin>>a>>b>>k;
  root = adjust_to_limits(root,a,b);

  //zamiana na posortowana tablice wartosci do znalezienia par
  vector <int> value_arr;
  root->convert_to_value_arr(value_arr);

  //szukanie par
  unordered_set <int> value_set;
  int x = -1,y;
  for(int i=0;i<value_arr.size();++i) {
    //jezeli juz znaleziono odpowiadajaca pare
    if(value_set.count(k - value_arr[i]) == 1) {
      x = k - value_arr[i];
      y = value_arr[i];
      break;
    }
    value_set.insert(value_arr[i]);
  }

  //odp zaleznie od wyniku
  if(x == -1) {
    cout<<"NIE ZNALEZIONO";
  } else if(x > y) {
    cout<<y<<" "<<x;
  } else {
    cout<<x<<" "<<y;
  }

  return 0;
}