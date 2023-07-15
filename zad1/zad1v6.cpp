#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits.h>
using namespace std;

struct Point {
  int input_index;
  int x;
  int y;
  vector <Point> neighbours;
  //dystans od danego sprawdzanego punktu z kolejki
  int priority;
  Point(){}
  Point(int index, int x, int y) {
    input_index = index;
    this->x = x;
    this->y = y;
    priority = INT_MAX;
  }

  void add_neighbour(Point point) {
    neighbours.push_back(point);
  }
};

struct Compare_Points {
  //funkcja do kolejki priorytetowej
  bool operator()(Point const& a, Point const& b) {
    return a.priority > b.priority;
  }
};

bool sort_by_x(Point a, Point b) {
  return a.x < b.x;
}

bool sort_by_y(Point a, Point b) {
  return a.y < b.y;
}

bool sort_by_index(Point a, Point b) {
  return a.input_index < b.input_index;
}

int calculate_priority(Point a, Point b) {
  return min(abs(a.x-b.x),abs(a.y-b.y));
}

inline void traverse_graph(vector <Point> &points, int point_count, int start_index, int end_index) {
  Point current_point;
  vector <int> distance_arr;
  vector <bool> checked;
  for(int i=0;i<point_count;++i) {
    //max int
    distance_arr.push_back(INT_MAX);
    checked.push_back(false);
  }
  distance_arr[start_index] = 0;

  priority_queue <Point,vector<Point>,Compare_Points> queue;

  //startowy punkt
  points[start_index].priority = 0;
  checked[start_index] = true;
  current_point = points[start_index];
  queue.push(current_point);
  
  Point neighbour;
  int priority;

  while(current_point.input_index != end_index) {
    //sciagniecie elementu z poczatku kolejki
    current_point = queue.top();
    //wyrzucenie elementu z poczatku kolejki
    queue.pop();
    
    //przejscie po sasiadach
    for(int i=0;i<current_point.neighbours.size();++i) {
      neighbour = current_point.neighbours[i];
      //obliczenie odleglosci sasiada od current_pointa (a w zasadzie od startu)
      priority = calculate_priority(current_point,neighbour) + distance_arr[current_point.input_index];
      neighbour.priority = priority;
      //nadpisanie aktualnie najkrotszej trasy do danego punktu
      if(priority < distance_arr[neighbour.input_index] && priority >= 0) {
        distance_arr[neighbour.input_index] = neighbour.priority;
      }
      
      //dodanie do kolejki jezeli jeszcze nie sprawdzony
      if(!checked[neighbour.input_index]) {
        checked[neighbour.input_index] = true;
        queue.push(neighbour);
      }
    }

    // queue.push(buffer);
    // queue.pop();
  }
  cout<<distance_arr[end_index];
  distance_arr.clear();
}

//stworzenie polaczen grafu ostatecznego - tu idzie kopia
inline void create_graph(vector <Point> &points, int point_count) {
  //sort po x
  sort(points.begin(),points.end(),sort_by_x);

  //laczenie sasiadow grafu
  if(point_count > 1) {
    points[0].add_neighbour(points[1]);
    if(point_count > 2) {
      for(int i=1;i<point_count - 1;++i) {
        points[i].add_neighbour(points[i-1]);
        points[i].add_neighbour(points[i+1]);
      }
    }
    points[point_count - 1].add_neighbour(points[point_count - 2]);
  }

  //sort po y
  sort(points.begin(),points.end(),sort_by_y);

  //laczenie sasiadow grafu
  if(point_count > 1) {
    points[0].add_neighbour(points[1]);
    if(point_count > 2) {
      for(int i=1;i<point_count - 1;++i) {
        points[i].add_neighbour(points[i-1]);
        points[i].add_neighbour(points[i+1]);
      }
    }
    points[point_count - 1].add_neighbour(points[point_count - 2]);
  }

  //sort po index
  sort(points.begin(),points.end(),sort_by_index);
}

inline void find_shortest_path(vector <Point> &points, int point_count, int start_index, int end_index) {
  //stworzenie powiazan grafu (sortuje tylko kopie)
  create_graph(points,point_count);

  //przejscie po grafie
  traverse_graph(points,point_count,start_index,end_index);
}

int main() {
  int n; //liczba wspolrzednych postojow
  int x, y, s, d; //x, y punktu, indeks startowy i koncowy w tablicy wpisanych danych (numer punktu)
  
  cin>>n;

  vector <Point> points;

  for(int i=0;i<n;++i) {
    cin>>x>>y;
    points.push_back(Point(i,x,y));
  }

  cin>>s>>d;

  find_shortest_path(points, n, s, d);
  points.clear();

  return 0;
}