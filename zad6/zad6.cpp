#include <iostream>
#include <list>
#include <stack>
#include <cmath>
using namespace std;
/*
  Algorytm Grahama - otoczka wypukla
  wybieramy skrajnie dolny-lewy punkt - najmniejszy y i wtedy pierwszy z lewej
  sprawdzamy punkt posrodku dwoch punktow:
  - jak po srodku to wywalamy go
  - jak po lewej to wywalam
  - jak po prawej to dodaje

  jak okreslic z ktorej jest punkt?
  iloczyn wektorowy - z tych 3 punktow - zapisujemy w macierzy
  | 1  1  1  |
  | x1 x2 x3 |
  | y1 y2 y3 |
  aby okreslic strone to obliczyc wyznacznik macierzy - (mnozenie na ukosy)
  jezeli jest <0 to po lewej stronie, =0 to na linii - jak wiekszy to po prawej

  liczyc arctan aby liczyc kat - amplituda - funkcja wbudowana chb

  jak amplituda (alfa) jest rowna to wykluczamy punkty blizsze - liczymy odleglosc - sa wspoliniowe wiec nie trzeba pierwiastka

  test moze byc co ma punkty w prawie jednej liniii tylko

  1. posortowac - kat i odleglosc
  2. usunac wspoliniowe - O(n)
  3. posortowac pozostale

  1 albo 3 wybrac - nie dwa na raz

  ALGORYTM:
  (L to lista - std np.)
  1. L = {A,B,C,D,E,...} - szukamy punktu skrajnie dolnego i skrajnie lewego - min(y), min(x)
    znalezlismy punkt O - zlozonosc O(n)
  2. O, L = {A,B,C,D,E,...} - O usuwamy juz z tej listy bo niepotrzebny
    liczymy alfe i odleglosc d
    dla kazdego punktu robimy funkcje liczaca odleglosc od O do tego punktu
    atan2 do liczenia alfy
    (x1 - x2)^2 + (y1 - y2)^2 do liczenia odleglosci - bez pierwiastka
    zlozonosc O(n)
  3. sortujemy punkty - comparator najpierw po alfa potem po d
    zlozonosc O(nlogn) - MOZNA SORTA Z STL
  4. usuwamy elementy o tym samym alfa
    zlozonosc O(n)
  5. inicjalizacja struktur danych - stos - na stos trafia O i pierwsze 2 z listy ~
    S = {O,B,C}, L = {E,F,...}
  6.  def(B,C,O) - dwa ostatnie punkty ze stosu i pierwszy element z listy
    jezeli jej wartosc jest <= 0 to ze stosu sciagam element ostatni (C) [S.pop()] i
    teraz robie dla kolejnych def(O,B,E) > 0 to na stos wrzucam E i usuwam go z listy - [S.push(E), L.pop_front()]
    ^ wywolujemy w petli dla calej listy - for elem in L:...
    zlozonosc O(n)
  7. L = {} - na stosie sa wszystkie elementy tworzace otoczke wypukla S = {O,B,E,...}
  8. Obliczyc obwod figury:
    |OB| + |BE| + |EF| + ... = wynik algorytmu
    zlozonosc O(n)
  CZYLI ZLOZONOSC O(nlogn) ale duzo O(n) wiec trzeba optymalnie wszystko

  PRZYKLAD:
  wejscie jak w przykladzie na tichy - punkty A,B,C,D,E,F,G,H,I
  1. najnizszy po lewej stronie to punkt A(1,1), wiec L = {B,C,D,E,F,G,H,I}
  2. *wyznaczam*
  3. *sortuje liste* -> O(1,1), L = {D,G,H,E,I,F,B,C}
  4. iteruje po kolei i usuwam punkty o tych samych katach - zostawiam drugi ~ usuwam w srodku trojki
  5. O(1,1), L = {G,H,I,F,C}
  stos S = {O,G,H}, lista L = {I,F,C}
  6. iteruje po elementach listy
    sprawdzam wartosc wyznacznika macierzy - dwa ostatnie ze stosu i pierwszy z listy - czy  >= 0 -> usuwam ze stosu ostatni element: S = {O,G}
    iteruje dalej S = {O,G,I}, L = {F,C} >= 0 nie -> dodaje na stos i usuwam z listy
    ??? - iteruje po kolei az sie lista skonczy
    {OGIF}
    {OIFC}
    {OGIC}
  7. stos na koniec S = {O,G,I,C}
  8. iteruje w petli po stosie i licze dlugosci odcinkow |OG| + |GI| + |IC| + |CO| = 2 + 2 + 2 + 2 = 8.00
*/

struct Point {
  // //temp
  // char id;
  int x;
  int y;
  // kat od poczatkowego punktu
  float alfa;
  // odleglosc od poczatkowego punktu
  float distance;

  Point(){}
  Point(int x, int y) {
    this->x = x;
    this->y = y;
  }

  void count_alpha_and_distance(Point* &source) {
    this->alfa = atan2(y-source->y,x-source->x);
    this->distance = pow((x - source->x),2) + pow((y - source->y),2);
  }
};

//test
// void test_print(list <Point*> &points) {
//   for(auto point : points) {
//     cout<<point->id<<" ";
//   }
//   cout<<endl;
// }
// void print_stack(stack <Point*> pt) {
//   cout<<"ODWROCONE:"<<endl;
//   while(!pt.empty()) {
//     cout<<pt.top()->id<<" ";
//     pt.pop();
//   }
//   cout<<endl;
// }

inline void set_alpha_and_distances(list <Point*> &points, Point* source) {
  for(auto point : points) {
    point->count_alpha_and_distance(source);
  }
}

bool polar_compare(Point* &a, Point* &b) {
  if (a->alfa < b->alfa) {
    return true;
  } else if (a->alfa == b->alfa && a->distance < b->distance) {
    return true;
  } else {
    return false;
  }
}

inline void remove_inline_points(list <Point*> &points) {
  list <Point*>::iterator second = points.begin(), third = points.begin();
  std::advance(third,1);
  while (third != points.end()) {
    if ((*second)->alfa == (*third)->alfa) {
      second = points.erase(second);
      std::advance(third,1);
    } else {
      std::advance(second,1); std::advance(third,1);
    }
  }
}

// wyznacznik macierzy 3x3 (pierwszy wiersz to same 1 wiec pomijam w mnozeniu)
int determinant(Point* &a, Point* &b, Point* &c) {
  return (b->x * c->y) + (c->x * a->y) + (a->x * b->y) - (b->x * a->y) - (a->x * c->y) - (c->x * b->y);
}

inline void convex_hull(list <Point*> &points, stack <Point*> &point_stack, Point* &O) {
  Point* a, *b, *c;
  int det;
  // int i =0;
  // A G I C czyli u mn C I G A
  while(!points.empty()) {
    a = point_stack.top(); point_stack.pop();
    b = point_stack.top(); point_stack.pop();
    c = points.front(); points.pop_front();
    det = determinant(a,b,c);
    if (det >= 0) {
      point_stack.push(b);
      points.push_front(c);
    } else {
      point_stack.push(b);
      point_stack.push(a);
      point_stack.push(c);
    }
    // cout<<i<<" ";
    // print_stack(point_stack);
    // ++i;
  }
}

inline double calculate_distance(Point* &a, Point* &b) {
  return sqrt(pow((a->x - b->x),2) + pow((a->y - b->y),2));
}

inline void calculate_result(stack <Point*> &points_stack, Point* &O, double &result) {
  Point* a = O;
  Point* b;
  while(!points_stack.empty()) {
    b = points_stack.top();
    points_stack.pop();
    result += calculate_distance(a,b);
    a = b;
  }
  result += calculate_distance(a,O);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.tie(nullptr);

  int n; // liczba punktow, indeks O
  short x,y,min_x = 10000,min_y = 10000; // wspolrzedne punktu, minimalne wspolrzedne - do szukania O
  cin>>n;
  list <Point*> points;
  Point* new_point, *O;
  for (int i=0;i<n;++i) {
    cin>>x>>y;
    new_point = new Point(x,y);
    // new_point->id = 65 + i;
    if (y < min_y || y <= min_y && x < min_x) {
      min_y = y;
      min_x = x;
      O = new_point;
    }
    points.push_back(new_point);
  }
  // usuniecie O z listy punktow
  points.remove(O);
  // ustawienie katow i dystansow od poczatkowego punktu
  set_alpha_and_distances(points,O);

  // test_print(points);

  // posortowanie listy punktow po kacie i odleglosci
  points.sort(polar_compare);

  // test_print(points);

  // usuniecie zbednych punktow lezacych na tej samej prostej
  remove_inline_points(points);

  // test_print(points);

  // przygotowanie stosu i listy
  stack <Point*> points_stack;
  points_stack.push(O);
  points_stack.push(points.front());
  points.pop_front();
  points_stack.push(points.front());
  points.pop_front();

  // print_stack(points_stack);
  // test_print(points);


  // algorytm otoczki wypuklej
  convex_hull(points,points_stack,O);

  // print_stack(points_stack);

  // obliczenie i wyswietlenie odpowiedzi (obwodu figury)
  double result = 0.0;
  calculate_result(points_stack,O,result);
  printf("%.2f",result);

  return 0;
}