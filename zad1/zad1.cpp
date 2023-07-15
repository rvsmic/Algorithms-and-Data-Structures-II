#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef unsigned short ushort;
typedef unsigned int uint;

/*
  poruszamy sie w pionie i poziomie tylko
  teleportacja ma koszt 0 - zwykle przejscie ma koszt
  odleglosc miedzy punktami liczymy przez - minmum z wart bezwzgl roznic wspolrzednych
  czyli min(|Ax - Bx|,|Ay - By|)

  zeby optymalnie znalezc to sortujemy wzgledem osi i patrzymy po kolei
  2 listy krawedzi - uporzadkowane zbiory - po polaczeniu dadza najlepsze wyniki

  algorytm diekstry - graf spojny, rzadki
  E * log(V) - zlozonosc

  kolejka priorytetowa - mozna z stl

  z danych:
  "0 4" - zerowy i czwarty punkt sa kluczowe

  wpisujemy dane do tablicy i sortujemy po x - budujemy graf - trzyma sasiada i odleglosc
  laczymy w drugim kierunku rowniez

  potem robimy to samo wzgledem osi y
  (implementacyjnie od razu sprawdzamy lepsze wspolrzedne tamtym wzorem)

  potem laczymy te grafy w jeden - piszemy wszystkie polaczenia

  i na tym wykonujemy alg diekstry

  do kolejki wrzucamy punkt startowy
  dodatkowo robimy tablice odleglosci - odleglosc od A to 0 a reszta nieskonczonosc
  robimy kroki az kolejka nie bedzie pusta - LUB do momentu znalezienia i przetworzenia szukanego celu - bo alg. zachlanny
  tam jest instrukcja warunkowa, wiec moze byc wolniejsze - mozna zmienic warunek na koniec kolejki na ten warunek

  kroki:
  literki jak po kolei w zadaniu
  bierzemy z kolejki A i sprawdzamy krawedzie - dla A (1 do B, 1 do D, 2 do C), dla B (0 do D, 1 do A), dla C (2 do A, 2 do E),
  dla D (0 do B, 1 do A, 1 do E), dla E (1 do D, 2 do C)

  sprawdzam czy moja odleglosc (A w tablicy odleglosci) i odleglosc do sasiada jest mniejsza niz nieskonczonosc (wartosc w tablicy odleglosci) i potem kolejna krawedz
  i dodajemy do kolejki sasiadow
  potem sprawdzamy sasiadow tego kolejnego sasiada itd az skonczymy wierzcholki
*/

struct Point {
  ushort input_index;
  uint x;
  uint y;
  vector <Point*> neighbours;
  bool* added_neighbours;
  //dystans od danego sprawdzanego punktu z kolejki
  uint priority;
  //odwiedzone
  bool checked;
  Point(){}
  Point(ushort index, uint x, uint y, ushort neighbours_max_count) {
    input_index = index;
    this->x = x;
    this->y = y;
    added_neighbours = new bool[neighbours_max_count];
    checked = false;
    priority = 2000000001;
  }

  void add_neighbour(Point* point) {
    if(!added_neighbours[point->input_index]) {
      neighbours.push_back(point);
      added_neighbours[point->input_index] = true;
    }
  }

  void free_space() {
    delete[] added_neighbours;
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

bool sort_by_input(Point* a, Point* b) {
  return a->input_index < b->input_index;
}

//testowe
void test_print(vector <Point*> points, string text) {
  cout<<text<<":\n";
  for(int i=0;i<points.size();++i) {
    cout<<">"<<points[i]->input_index<<": "<<points[i]->x<<" "<<points[i]->y<<endl;
    for(int j=0;j<points[i]->neighbours.size();++j) {
      cout<<points[i]->neighbours[j]->input_index<<" ";
    }
    cout<<endl;
  }
}
//test
void test_print_priority(vector <Point*> points) {
  cout<<"priority:\n";
  for(int i=0;i<points.size();++i) {
    cout<<points[i]->input_index<<" = "<<points[i]->priority<<endl;
  }
  cout<<endl;
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

inline void traverse_graph(vector <Point*> &points, uint point_count, uint start_index, uint end_index) {
  Point* current_point = points[start_index];
  vector <uint> distance_arr;
  for(int i=0;i<point_count;++i) {
    //ta startowa wartosc jest jak nieskonczonosc przez ograniczenie w zadaniu
    distance_arr.push_back(2000000001);
  }
  distance_arr[start_index] = 0;

  priority_queue <Point*,vector<Point*>,Compare_Points> queue;

  //startowy punkt
  current_point->priority = 0;
  //oznaczenie ze zostal odwiedzony zeby sie nie zapetlic
  current_point->checked = true;
  queue.push(current_point);
  Point* neighbour;

  while(current_point != points[end_index]) {
    //sciagniecie elementu z poczatku kolejki
    current_point = queue.top();
    // cout<<"cur "<<current_point->input_index<<":\n";
    //wyrzucenie elementu z poczatku kolejki
    queue.pop();
    
    
    //przejscie po sasiadach
    for(int i=0;i<current_point->neighbours.size();++i) {
      neighbour = current_point->neighbours[i];
      //obliczenie odleglosci sasiada od current_pointa (a w zasadzie od startu)
      
        uint priority = calculate_priority(current_point,neighbour);
        // cout<<"PR: "<<priority<<endl;
        neighbour->priority = priority + current_point->priority;
        // cout<<neighbour->input_index<<" - "<<neighbour->priority<<endl;
        if(neighbour->priority < distance_arr[neighbour->input_index]) {
          distance_arr[neighbour->input_index] = neighbour->priority;
        }
        if(!neighbour->checked) {
          neighbour->checked = true;
          queue.push(current_point->neighbours[i]);
        }
    }
    // test_print_priority(points);
  }

  //odpowiedz
  // for(int i=0;i<point_count;++i) {
  //   cout<<distance_arr[i]<<" ";
  // }
  // cout<<endl;
  cout<<distance_arr[end_index];
}

//stworzenie polaczen grafu ostatecznego
inline void create_graph(vector <Point*> &points, uint point_count) {

  // test_print(points,"Before");

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
      points[point_count - 1]->add_neighbour(points[point_count - 2]);
    }
  }
  

  // test_print(points,"Sort x");

  //sort po y
  sort(points.begin(),points.end(),sort_by_y);

  //laczenie sasiadow grafu
  if(point_count > 1) {
    points[0]->add_neighbour(points[1]);
    points[0]->free_space();
    if(point_count > 2) {
      for(int i=1;i<point_count - 1;++i) {
        points[i]->add_neighbour(points[i-1]);
        points[i]->add_neighbour(points[i+1]);
        points[i]->free_space();
      }
      points[point_count - 1]->add_neighbour(points[point_count - 2]);
      points[point_count - 1]->free_space();
    }
  }
  

  // test_print(points,"Sort y");
}

inline void find_shortest_path(vector <Point*> &points, uint point_count, uint start_index, uint end_index) {
  //stworzenie powiazan grafu
  create_graph(points,point_count);

  //posortowanie po indeksie startowym - latwiej potem po grafie przechodzic i oznaczac
  sort(points.begin(),points.end(),sort_by_input);

  // test_print(points,"Before");

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
    point = new Point(i,x,y,n);
    points.push_back(point);
  }

  cin>>s>>d;

  find_shortest_path(points, n, s, d);

  return 0;
}