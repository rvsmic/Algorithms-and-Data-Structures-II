#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <queue>
#include <cmath>
using namespace std;

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
    bool operator()(Distance const& a, Distance const& b) {
        return a.distance > b.distance;
    }
};

bool compare_by_x(Point &a, Point &b) {
  return a.x < b.x;
}

bool compare_by_y(Point &a, Point &b) {
  return a.y < b.y;
}

int calculate_distance(Point source, Point destination) {
  return min(abs(source.x - destination.x),abs(source.y - destination.y));
}

void print_neighbours(vector <vector <Distance> > &neighbours) {
  for(int i=0;i<neighbours.size();++i) {
    cout<<i<<": ";
    for(int j=0;j<neighbours[i].size();++j) {
      cout<<neighbours[i][j].id<<" ";
    }
    cout<<endl;
  }
}

void print_points(vector <Point> points) {
  for(int i=0;i<points.size();++i) {
    cout<<points[i].id<<" ";
  }
  cout<<endl;
}

void print_queue(priority_queue <Distance,vector<Distance>,Compare_Distance> queue)
{
  while (!queue.empty())
  {
    Distance a = queue.top();
    std::cout <<a.id<<" - "<< a.distance << " ";
    queue.pop();
  }
  std::cout << std::endl;
}

inline void reset_doubles_check(vector <bool> doubles) {
  for(int i=0;i<doubles.size();++i) {
    doubles[i] = false;
  }
}

inline void traverse_graph(vector <Point> points,vector <vector <Distance> > &neighbours, int start_id, int end_id) {
  vector <int> distance_arr;
  vector <bool> checked;
  vector <bool> doubles;
  for(int i=0;i<points.size();++i) {
    distance_arr.push_back(INT_MAX);
    checked.push_back(false);
    doubles.push_back(false);
  }
  //startowy ma dystans 0 i jest sprawdzony
  distance_arr[start_id] = 0;
  checked[start_id] = true;

  priority_queue <Distance,vector<Distance>,Compare_Distance> queue;
  queue.push(neighbours[start_id][0]);

  Distance current = Distance(-1,-1);

  while(current.id != end_id) {
    current = queue.top();
    queue.pop();
    for(int i=1;i<neighbours[current.id].size();++i) {
      if(!doubles[neighbours[current.id][i].id]) {
        doubles[neighbours[current.id][i].id] = true;
        if(neighbours[current.id][i].distance < distance_arr[neighbours[current.id][i].id]) {
        distance_arr[neighbours[current.id][i].id] = neighbours[current.id][i].distance + distance_arr[current.id];
        neighbours[current.id][i].distance+=distance_arr[current.id];
      }
      if(!checked[neighbours[current.id][i].id]) {
        checked[neighbours[current.id][i].id] = true;
        queue.push(neighbours[current.id][i]);
      }
      }
      
    }
    reset_doubles_check(doubles);
    // cout<<current.id<<": ";
    // print_queue(queue);
  }
  cout<<distance_arr[end_id];
}

inline void create_graph(vector <Point> points,vector <vector <Distance> > &neighbours) {
  //sort po x
  sort(points.begin(),points.end(),compare_by_x);

  //dopisanie sasiadow w osi x do tablicy
  if(points.size() > 1) {
    neighbours[points[0].id].push_back(Distance(points[1].id,calculate_distance(points[0],points[1])));
    for(int i=1;i<points.size()-1;++i) {
      //poprzedni
      neighbours[points[i].id].push_back(Distance(points[i - 1].id,calculate_distance(points[i],points[i - 1])));
      //nastepny
      neighbours[points[i].id].push_back(Distance(points[i + 1].id,calculate_distance(points[i],points[i + 1])));
    }
    neighbours[points[points.size() - 1].id].push_back(Distance(points[points.size() - 2].id,calculate_distance(points[points.size() - 1],points[points.size() - 2])));
  }

  //sort po y
  sort(points.begin(),points.end(),compare_by_y);

  //dopisanie sasiadow w osi y do tablicy
  if(points.size() > 1) {
    neighbours[points[0].id].push_back(Distance(points[1].id,calculate_distance(points[0],points[1])));
    for(int i=1;i<points.size()-1;++i) {
      //poprzedni
      neighbours[points[i].id].push_back(Distance(points[i - 1].id,calculate_distance(points[i],points[i - 1])));
      //nastepny
      neighbours[points[i].id].push_back(Distance(points[i + 1].id,calculate_distance(points[i],points[i + 1])));
    }
    neighbours[points[points.size() - 1].id].push_back(Distance(points[points.size() - 2].id,calculate_distance(points[points.size() - 1],points[points.size() - 2])));
  }
}

inline void find_best_path(vector <Point> points, int start_id, int end_id,vector <vector <Distance> > &neighbours) {
  //ustawienie tablicy sasiedztwa
  create_graph(points,neighbours);

  //przejscie po grafie
  traverse_graph(points,neighbours,start_id,end_id);

  // print_points(points);

  // print_neighbours(neighbours);
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
  // for(int i=0;i<neighbours.size();++i) {
  //   neighbours[i].pop_back();
  // }
  
  cin>>s>>d;

  find_best_path(points,s,d,neighbours);

  return 0;
}