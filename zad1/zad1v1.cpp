#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef unsigned short ushort;
typedef unsigned int uint;

struct Point {
  ushort input_index;
  uint x;
  uint y;
  vector <Point*> neighbours;
  //dystans od danego sprawdzanego punktu z kolejki
  uint priority;
  //odwiedzone
  bool checked;
  Point(){}
  Point(ushort index, uint x, uint y) {
    input_index = index;
    this->x = x;
    this->y = y;
    checked = false;
    priority = 4294967295;
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

uint calculate_priority(Point* a, Point* b) {
  uint x,y;
  if(a->x > b->x) {
    x = a->x - b->x;
  } else {
    x = b->x - a->x;
  }
  if(a->y > b->y) {
    y = a->y - b->y;
  } else {
    y = b->y - a->y;
  }
  return x > y ? y : x;
}

void print_queue(priority_queue <Point*,vector<Point*>,Compare_Points> queue)
{
  while (!queue.empty())
  {
    Point* a = queue.top();
    std::cout <<a->input_index<<" - "<< a->priority << " ";
    queue.pop();
  }
  std::cout << std::endl;
}

inline void traverse_graph(vector <Point*> &points, ushort point_count, uint start_index, uint end_index) {
  Point* current_point = points[start_index];
  vector <uint> distance_arr;
  for(int i=0;i<point_count;++i) {
    //max uint
    distance_arr.push_back(4294967295);
  }
  distance_arr[start_index] = 0;

  priority_queue <Point*,vector<Point*>,Compare_Points> queue;

  //startowy punkt
  current_point->priority = 0;
  //oznaczenie ze zostal odwiedzony zeby sie nie zapetlic
  current_point->checked = true;
  queue.push(current_point);
  
  Point* neighbour;
  uint priority;

  while(current_point != points[end_index]) {
    // print_queue(queue);
    //sciagniecie elementu z poczatku kolejki
    current_point = queue.top();
    
    //przejscie po sasiadach
    for(int i=0;i<current_point->neighbours.size();++i) {
      neighbour = current_point->neighbours[i];
      //obliczenie odleglosci sasiada od current_pointa (a w zasadzie od startu)
      priority = calculate_priority(current_point,neighbour);
      neighbour->priority = priority + distance_arr[current_point->input_index];
      //nadpisanie aktualnie najkrotszej trasy do danego punktu
      if(neighbour->priority < distance_arr[neighbour->input_index]) {
        distance_arr[neighbour->input_index] = neighbour->priority;
      }
      //dodanie do kolejki jezeli jeszcze nie sprawdzony
      if(!neighbour->checked) {
        neighbour->checked = true;
        queue.push(neighbour);
      }
    }
    //wyrzucenie elementu z poczatku kolejki
    queue.pop();
    //NAPRAWIENIE KOLEJKI PIORYTETOWEJ Z STL :/
    // make_heap(const_cast<Point**>(&queue.top()), const_cast<Point**>(&queue.top()) + queue.size(), Compare_Points());
  }
  cout<<distance_arr[end_index];
  distance_arr.clear();
}

//stworzenie polaczen grafu ostatecznego - tu idzie kopia
inline void create_graph(vector <Point*> points, ushort point_count) {
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

inline void find_shortest_path(vector <Point*> &points, ushort point_count, uint start_index, uint end_index) {
  //stworzenie powiazan grafu (sortuje tylko kopie)
  create_graph(points,point_count);

  //przejscie po grafie
  traverse_graph(points,point_count,start_index,end_index);
}

int main() {
  ushort n; //liczba wspolrzednych postojow
  uint x, y, s, d; //x, y punktu, indeks startowy i koncowy w tablicy wpisanych danych (numer punktu)
  
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