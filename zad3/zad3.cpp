#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

/*
  zwracamy pare liczb z najmniejsza odlegloscia
  trzeba przeszukiwac az sprawdzimy wszystko bo moga byc lepsze

  najpierw robimy drzewo
  przy wpisywaniu tworze drzewo - ustawiam standardowo - po lewej mniejsze po prawej wieksze

  potem dostajemy wartosci do przyciecia (9 i 16 w przykladzie)
  schodze po drzewie rekurencyjnie az do nullptr i potem sie cofam i sprawdzam
  jak jest mniejsza od przedzialu to w jej miejsce przepinam prawy wskaznik
  jak jest w przedziale to nie ruszam
  jak jest wieksza od przedzialu to przepinam w to miejsce lewego syna
  i tak robie az skonczy sie drzewo

  teraz przechodze po drzewie inorder - wartosci beda posortowane (mozna sobie zapisac do tablicy)

  teraz jak mam juz posortowana tablice to szukam pary dajacej sume

  sposob 1: wskaniki na poczatek i koniec (LEPIEJ ZACZAC OD SRODKA I ISC NA ZEWNATRZ) - trzeba sprawdzac czy nie ma lepszych
  suma z tablicy o ineksach i j jest > suma -> j-- jak od srodka to i--
  < suma to i++ jak od srodka j++
  == to okej ale dalej patrzymy

  sposob 2: hashowanie - poprzez unordered_set
  np. wartosci: 10,12,15,16
  zaczynamy od lewego elementu
  sprawdzam czy suma - liczba = wynik ~ czy ten wynik jest w zbiorze
  jak wynik jest w zbiorze to dodajemy liczbe do tego zbioru
  potem jak wynik jest w zbiorze to wyswielam rozwiazanie

  OD MNIEJSZEJ DO WIEKSZEJ WYSWIETLAC WARTOSCI

  WPLYWY POLITYCZNE MOGA SIE DUBLOWAC - ale roznica miedzy liczbami nie bedzie 0 (np suma 24 i liczby 12 i 12)
*/

struct Node {
  int value;
  int count;
  Node* left;
  Node* right;
  
  Node(){}
  Node(int value) {
    this->value = value;
    count = 1;
    left = nullptr;
    right = nullptr;
  }

  void add_child(Node* new_node) {
    //this to root drzewa
    Node* current = this;
    while(true) {
      if(current->value > new_node->value) {
        //jak nowy jest mniejszy od current node'a
        if(current->left == nullptr) {
          current->left = new_node;
          return;
        } else {
          //schodzimy nizej
          current = current->left;
        }
      } else if(current->value < new_node->value) {
        //jak nowy jest wiekszy od current node'a
        if(current->right == nullptr) {
          current->right = new_node;
          return;
        } else {
          //schodzimy nizej
          current = current->right;
        }
      } else {
        //jak ten sam element
        ++current->count;
        delete new_node;
        return;
      }
    }
  }

  void convert_to_value_arr(vector <int> &value_arr) {
    //this to root drzewa za pierwszym razem
    //current bedzie obecnie najwyzszym prawym jeszcze nie dodanym
    Node* current = this;
    if(current->left != nullptr) {
      //schodzimy nizej
      current->left->convert_to_value_arr(value_arr);
      //dodajemy najnizszy z lewej i wracamy do gory
      for(int i=0;i<current->count;++i) {
        value_arr.push_back(current->value);
      }
      //jak sie skonczy lewa odnoga
      if(current->right != nullptr) {
        current->right->convert_to_value_arr(value_arr);
      }
    } else if(current->right != nullptr) {
      //idziemy w prawo
      //dodajemy stary node
      for(int i=0;i<current->count;++i) {
        value_arr.push_back(current->value);
      }
      //schodzimy nizej
      current->right->convert_to_value_arr(value_arr);
    } else {
      //jak sie skonczy odnoga
      for(int i=0;i<current->count;++i) {
        value_arr.push_back(current->value);
      }
    }
  }
};

Node* adjust_to_limits(Node* &current, int bottom, int top) {
  if(current->left != nullptr) {
    current->left = adjust_to_limits(current->left,bottom,top);
    // cout<<"->"<<current->value<<"\n";
  }
  if(current->right != nullptr) {
    current->right = adjust_to_limits(current->right,bottom,top);
    // cout<<"->"<<current->value<<"\n";
  }
  if(current->value < bottom) {
    // cout<<"("<<current->value<<") ";
    return current->right;
  } else if (current->value > top) {
    // cout<<"["<<current->value<<"] ";
    return current->left;
  } else {
    // cout<<"<"<<current->value<<"> ";
    return current;
  }
}

int main() {
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
  cin>>a>>b>>k;

  root = adjust_to_limits(root,a,b);

  vector <int> value_arr;
  root->convert_to_value_arr(value_arr);

  unordered_set <int> value_set;
  int x = -1,y;

  for(int i=0;i<value_arr.size();++i) {
    if(value_set.count(k - value_arr[i]) == 1) {
      x = k - value_arr[i];
      y = value_arr[i];
      break;
    }
    value_set.insert(value_arr[i]);
  }

  if(x == -1) {
    cout<<"NIE ZNALEZIONO";
  } else if(x > y) {
    cout<<y<<" "<<x;
  } else {
    cout<<x<<" "<<y;
  }

  return 0;
}