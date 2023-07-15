#include <iostream>
#include <list>
#include <stack>
#include <cmath>
using namespace std;

struct Point {
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

inline void set_alpha_and_distances(list <Point*> &points, Point* source) {
  for (auto point : points) {
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
  Point* erased_point;
  std::advance(third,1);
  while (third != points.end()) {
    if ((*second)->alfa == (*third)->alfa) {
      erased_point = *second;
      second = points.erase(second);
      delete erased_point;
      std::advance(third,1);
    } else {
      std::advance(second,1); std::advance(third,1);
    }
  }
}

inline void prepare_stack_and_list(list <Point*> &points, stack <Point*> &points_stack, Point* &O) {
  points_stack.push(O);
  points_stack.push(points.front());
  points.pop_front();
  points_stack.push(points.front());
  points.pop_front();
}

// wyznacznik macierzy 3x3 (pierwszy wiersz to same 1 wiec pomijam w mnozeniu)
int determinant(Point* &a, Point* &b, Point* &c) {
  return (b->x * c->y) + (c->x * a->y) + (a->x * b->y) - (b->x * a->y) - (a->x * c->y) - (c->x * b->y);
}

inline void convex_hull(list <Point*> &points, stack <Point*> &point_stack, Point* &O) {
  Point* a, *b, *c;
  int det;
  while (!points.empty()) {
    a = point_stack.top(); point_stack.pop();
    b = point_stack.top(); point_stack.pop();
    c = points.front(); points.pop_front();
    det = determinant(a,b,c);
    if (det >= 0) {
      point_stack.push(b);
      points.push_front(c);
      delete a;
    } else {
      point_stack.push(b);
      point_stack.push(a);
      point_stack.push(c);
    }
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

  int n; // liczba punktow
  short x,y,min_x = 10000,min_y = 10000; // wspolrzedne punktu, minimalne wspolrzedne - do szukania O
  cin>>n;
  list <Point*> points;
  Point* new_point, *O;
  for (int i=0;i<n;++i) {
    cin>>x>>y;
    new_point = new Point(x,y);
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
  // posortowanie listy punktow po kacie i odleglosci
  points.sort(polar_compare);
  // usuniecie zbednych punktow lezacych na tej samej prostej
  remove_inline_points(points);
  // przygotowanie stosu i listy
  stack <Point*> points_stack;
  prepare_stack_and_list(points,points_stack,O);
  // algorytm otoczki wypuklej
  convex_hull(points,points_stack,O);
  // obliczenie i wyswietlenie odpowiedzi (obwodu figury)
  double result = 0.0;
  calculate_result(points_stack,O,result);
  printf("%.2f",result);

  return 0;
}