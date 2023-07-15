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
  vector <Point*> neighbours;
  //dystans od danego sprawdzanego punktu z kolejki
  int priority;
  //odwiedzone
  bool checked;
  Point(){}
  Point(int index, int x, int y) {
    input_index = index;
    this->x = x;
    this->y = y;
    checked = false;
    priority = INT_MAX;
  }

  void add_neighbour(Point* point) {
    //dodatek zeby nie bylo powtorzen - nie wplywa znaczaco na czas w testach
    for(int i=0;i<neighbours.size();++i) {
      if(neighbours[i] == point) {
        return;
      }
    }
    neighbours.push_back(point);
  }
};

struct Compare_Points {
  //funkcja do kolejki priorytetowej
  bool operator()(Point* const& a, Point* const& b) {
    return a->priority > b->priority;
  }
};

bool sort_by_x(Point* a, Point* b) {
  return a->x < b->x;
}

bool sort_by_y(Point* a, Point* b) {
  return a->y < b->y;
}

int calculate_priority(Point* a, Point* b) {
  return min(abs(a->x-b->x),abs(a->y-b->y));
}

inline void traverse_graph(vector <Point*> &points, int point_count, int start_index, int end_index) {
  Point* current_point = points[start_index];
  vector <int> distance_arr;
  for(int i=0;i<point_count;++i) {
    //max int
    distance_arr.push_back(INT_MAX);
  }
  distance_arr[start_index] = 0;

  priority_queue <Point*,vector<Point*>,Compare_Points> queue;

  //startowy punkt
  current_point->priority = 0;
  //oznaczenie ze zostal odwiedzony zeby sie nie zapetlic
  current_point->checked = true;
  queue.push(current_point);
  
  Point* neighbour;
  int priority;
  Point* buffer = new Point(-1,0,0);
  buffer->priority = -1;

  while(current_point != points[end_index]) {
    // std::make_heap(const_cast<Point**>(&queue.top()), const_cast<Point**>(&queue.top()) + queue.size(), Compare_Points());
    // print_queue(queue);
    //sciagniecie elementu z poczatku kolejki
    current_point = queue.top();
    //wyrzucenie elementu z poczatku kolejki
    queue.pop();
    
    //przejscie po sasiadach
    for(int i=0;i<current_point->neighbours.size();++i) {
      neighbour = current_point->neighbours[i];
      //obliczenie odleglosci sasiada od current_pointa (a w zasadzie od startu)
      priority = calculate_priority(current_point,neighbour);
      neighbour->priority = priority;
      priority += distance_arr[current_point->input_index];
      //nadpisanie aktualnie najkrotszej trasy do danego punktu
      if(priority < distance_arr[neighbour->input_index] && priority >= 0) {
        distance_arr[neighbour->input_index] = priority;
      }
      
      //dodanie do kolejki jezeli jeszcze nie sprawdzony
      if(!neighbour->checked) {
        neighbour->checked = true;
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
inline void create_graph(vector <Point*> points, int point_count) {
  //sort po x
  sort(points.begin(),points.end(),sort_by_x);

  //laczenie sasiadow grafu
  if(point_count > 1) {
    points[0]->add_neighbour(points[1]);
    if(point_count > 2) {
      for(int i=1;i<point_count - 1;++i) {
        points[i]->add_neighbour(points[i-1]);
        points[i]->add_neighbour(points[i+1]);
      }
    }
    points[point_count - 1]->add_neighbour(points[point_count - 2]);
  }

  //sort po y
  sort(points.begin(),points.end(),sort_by_y);

  //laczenie sasiadow grafu
  if(point_count > 1) {
    points[0]->add_neighbour(points[1]);
    if(point_count > 2) {
      for(int i=1;i<point_count - 1;++i) {
        points[i]->add_neighbour(points[i-1]);
        points[i]->add_neighbour(points[i+1]);
      }
    }
    points[point_count - 1]->add_neighbour(points[point_count - 2]);
  }
}

inline void find_shortest_path(vector <Point*> &points, int point_count, int start_index, int end_index) {
  //stworzenie powiazan grafu (sortuje tylko kopie)
  create_graph(points,point_count);

  //przejscie po grafie
  traverse_graph(points,point_count,start_index,end_index);
}

int main() {
  int n; //liczba wspolrzednych postojow
  int x, y, s, d; //x, y punktu, indeks startowy i koncowy w tablicy wpisanych danych (numer punktu)
  
  cin>>n;

  vector <Point*> points;
  Point *point;

  for(int i=0;i<n;++i) {
    cin>>x>>y;
    point = new Point(i,x,y);
    points.push_back(point);
  }

  cin>>s>>d;

  find_shortest_path(points, n, s, d);
  points.clear();

  return 0;
}