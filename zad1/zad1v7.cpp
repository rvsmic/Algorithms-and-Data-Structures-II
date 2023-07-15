#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <queue>
#include <cmath>
using namespace std;

//punkt na powierzchni
struct Point {
  int id;
  int x;
  int y;
  Point(){}
  Point(int id, int x, int y) {
    this->id = id;
    this->x = x;
    this->y = y;
  }
};

//id i dystans od jakiegos punktu
struct Distance {
  int id;
  int distance;
  Distance(){}
  Distance(int id, int distance) {
    this->id = id;
    this->distance = distance;
  }
};

struct Compare_Distance {
  //specjalne sortowanie w kolejce
  bool operator()(Distance const& a, Distance const& b) {
    return a.distance > b.distance;
  }
};

//sortowanie po x
bool compare_by_x(Point &a, Point &b) {
  return a.x < b.x;
}

//sortowanie po y
bool compare_by_y(Point &a, Point &b) {
  return a.y < b.y;
}

//obliczenie najmniejszej odleglosci miedzy punktami
int calculate_distance(Point source, Point destination) {
  return min(abs(source.x - destination.x),abs(source.y - destination.y));
}

//przejscie po grafie metoda dijkstry
inline void traverse_graph(vector <Point> points,vector <vector <Distance> > &neighbours, int start_id, int end_id) {
  //tablica odleglosci
  vector <int> distance_arr;
  //tablica odwiedzonych
  vector <bool> checked;
  for(int i=0;i<points.size();++i) {
    distance_arr.push_back(INT_MAX);
    checked.push_back(false);
  }
  //startowy ma dystans 0 i jest sprawdzony
  distance_arr[start_id] = 0;
  checked[start_id] = true;

  priority_queue <Distance,vector <Distance>,Compare_Distance> queue;

  queue.push(Distance(points[start_id].id,0));
  Distance current = Distance(start_id,0);

  //przegladamy az znajdziemy koncowy (bedzie to maksymalnie ostatni element z kolejki wiec moze byc ten warunek)
  while(current.id != end_id) {
    //sciagniecie najblizszego "punktu" z kolejki
    current = queue.top();
    queue.pop();
    //przejscie po sasiadach "punktu"
    for(int i=0;i<neighbours[current.id].size();++i) {
      //odleglosc sasiada od "punktu" z kolejki + laczna odleglosc od startu
      int dist = neighbours[current.id][i].distance + distance_arr[current.id];
      //jak mniejsza od poprzednio okreslonej to zmieniamy
      if(distance_arr[neighbours[current.id][i].id] > dist) {
        distance_arr[neighbours[current.id][i].id] = dist;
      }
      //jak pierwszy raz odwiedzony to oznaczamy i dodajemy do kolejki z wyliczonym dystansem
      if(!checked[neighbours[current.id][i].id]) {
        checked[neighbours[current.id][i].id] = true;
        queue.push(Distance(neighbours[current.id][i].id,dist));
      }
    }
  }
  //wynik
  cout<<distance_arr[end_id];
}

//stworzenie grafu = tablicy sasiedztwa
inline void create_graph(vector <Point> points,vector <vector <Distance> > &neighbours) {
  //sort po x
  sort(points.begin(),points.end(),compare_by_x);

  //dopisanie sasiadow w osi x do tablicy
  if(points.size() > 1) {
    //pierwszy
    neighbours[points[0].id].push_back(Distance(points[1].id,calculate_distance(points[0],points[1])));
    for(int i=1;i<points.size()-1;++i) {
      //poprzedni
      neighbours[points[i].id].push_back(Distance(points[i - 1].id,calculate_distance(points[i],points[i - 1])));
      //nastepny
      neighbours[points[i].id].push_back(Distance(points[i + 1].id,calculate_distance(points[i],points[i + 1])));
    }
    //ostatni
    neighbours[points[points.size() - 1].id].push_back(Distance(points[points.size() - 2].id,calculate_distance(points[points.size() - 1],points[points.size() - 2])));
  }

  //sort po y
  sort(points.begin(),points.end(),compare_by_y);

  //dopisanie sasiadow w osi y do tablicy
  if(points.size() > 1) {
    //pierwszy
    neighbours[points[0].id].push_back(Distance(points[1].id,calculate_distance(points[0],points[1])));
    for(int i=1;i<points.size()-1;++i) {
      //poprzedni
      neighbours[points[i].id].push_back(Distance(points[i - 1].id,calculate_distance(points[i],points[i - 1])));
      //nastepny
      neighbours[points[i].id].push_back(Distance(points[i + 1].id,calculate_distance(points[i],points[i + 1])));
    }
    //ostatni
    neighbours[points[points.size() - 1].id].push_back(Distance(points[points.size() - 2].id,calculate_distance(points[points.size() - 1],points[points.size() - 2])));
  }
}

inline void find_best_path(vector <Point> &points, vector <vector <Distance> > &neighbours, int start_id, int end_id) {
  //ustawienie tablicy sasiedztwa
  create_graph(points,neighbours);

  //przejscie po grafie
  traverse_graph(points,neighbours,start_id,end_id);
}

int main() {
  int n; //ilosc punktow
  int x,y,s,d; //lokacja punktu, numery startowego i koncowego

  cin>>n;
  //tablica punktow
  vector <Point> points;
  //tablica sasiedztwa - indeksy punktow
  vector <vector <Distance> > neighbours;

  for(int i=0;i<n;++i) {
    cin>>x>>y;
    points.push_back(Point(i,x,y));
    //rozszerzenie vectora w osi i
    vector <Distance> dist;
    dist.push_back(Distance(i,2000000001));
    neighbours.push_back(dist);
    dist.clear();
  }

  //usuniecie tymczasowego rozszerzenia vectora
  for(int i=0;i<neighbours.size();++i) {
    neighbours[i].pop_back();
  }
  
  cin>>s>>d;

  find_best_path(points,neighbours,s,d);

  return 0;
}