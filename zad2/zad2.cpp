#include <iostream>
#include <vector>
#include <queue>
using namespace std;
/*
  "szczegolny graf" - nie na wykladzie ???

  z pary bijacych sie znika jeden

  bierki sie nie ruszaja, a tylko analizujemy statyczna plansze
  szukamy ile najwiecej bierek zniknie - ma byc najwiecej par znalezionych - najwiecej zbic
  
  MAKSYMALNE SKOJARZENIE - PROBLEM DO SPRAWDZENIA Z TYM ALGOSEM ~ problem malzenstw

  pionki zawsze zajmuja cala szachownice
  w przykladzie 25 - 6 to wynik, bo 6 par znaleziono


  najpierw trzeba zbudowac graf
  pola czarne i biale maja polaczenia krawedziami, ale kazdy element ze zbioru danego koloru nie laczy sie ze soba krawedziami
  robimy graf dwudzielny - np. czarne po lewej, a biale po prawej i polaczone sa tylko "przez srodek"

  szukamy najwiecej par w tym grafie - maksymalnych skojarzen moze byc wiele, ale nas interesuje tylko liczba

  najpierw szukamy wierzcholkow czarnych ktore moga cokolwiek zrobic
  i adekwatnie do tego szukamy potem wierzcholkow bialych, ktore mozna podpiac

  sprawdzam pole i sprawdzam jego krawedzie i dodaje do grafu
  i teraz na grafie zbudowanym algorytm rozwiacujacy problem max skojarzenia

  jak rozwiazac problem max skojarzenia:
    - sieci przeplywowe - fort fuxelle??? - algorytm edmondsona-karpa - iteracyjny ~ z kazdym razem znajduje tylko jedno skojarzenie - sciezka rozszerzajaca -
      przez co jest mocno zlozony (EV^2) - TEGO NIE UZYJEMY TUTAJ ale warto znac
    - algorytm hopcrofta-karpa - zloz E*pierw(V) - TEN UZYWAMY!!!!!
    - algorytm dinic - lepszy do grafow gestych

  <<< najwiekszy test w czasie 0.00 moze sie wykonac >>>

  hopcroft-karp:
  sklada sie z bfs i dfs - wywolanie najpierw bfs a potem na znalezionych sciezkach wywolanie dfs
  algorytm iteracyjny
  znajduje iles par w jednej iteracji

  sciezka naprzemienna - idziemy od wolnego wierzcholka do zajetego wierzcholka, a potem z zajetego zajeta krawedzia do wierzcholka zajetego a potem wolna krawedzia do wierzcholka wolnego
  ^ idziemy na zmiane krawedziami wolnymi i zajetymi -
  jest sciezka rozszerzajaca gdy zaczynamy z wolnego wierzhloka i konczymy na wolnym z drugiej grupy
  te ktore zajete oznaczamy jako wolne i na odwrot
  ten algos tego szuka

  potem potrzebujemy bfs i dfs
  bfs mozna spowadzic do kolejki fifo
  wrzucam wierzcholek na kolejke, przetwarzam go, a potem wrzucam jego sasiadow itd az wszyskie sprawdzimy

  zeby ulatwic budowanie sciezki naprzemiennej korzystamy z bfs - lecimy warstwami
  tam szukamy sciezek naprzemiennych

  a potem dfs bo moga byc sciezki naprzemienne polaczone jednym wierzcholkiem
  przeszukujac ustawiamy przeciwne stany sciezek (zajeta/wolna) - zapewna rozlacznosc sciezek rozszerzajacych

  bfs wywolany raz a dfs na kazym wolnym wierzcholku

  trzymamy zbior wierzcholkow, krawedzi (sciezek rozszerzajacych) i zbior wierzcholkow wynikowy - dodajemy do niego po kazdej iteracji
  oraz wysokosc z bfs

  pierwszy krok: uruchamiamy bfs:

  do bfs bierzemy wszystkie wolne wierzcholki z V (czarne)
  bierzemy 1 wierzcolek
  potem bierzemy wierzcholek 2 - polaczony z D,E (oba wolne)
  3 jest polaczone z B,C
  4 z D i 5 z C
  bfs zbudowal jednowarstwowa strukture
  <kolejka byla A,C,D,E,B>

  drugi krok: uruchamiamy na tej kolejce dfs

  dfs dla A - zaczynamy z wierzcholka A, oznaczam ze krawedz do 1 jest zajeta i wierzcholek 1 oraz A zajety
  zapisuje do listy krawedzi A-1 i wyrzucam z grafu

  potem dfs dla C - z C ide do 3 i oznaczam adekwatnie oraz dopisuje do listy krawedzi i wyrzucam

  potem dfs dla D ide do 2 i oznaczam, dopisuje i wyrzucam

  potem dfs dla E, ale nie ma wiec pomijam
  tak samo dla B

  ten zbior krawedzi dodaje (kolko z plusem - cos oznacza z alegebry) do zbioru ogolnego

  po tym algorytm iteruje sie kolejny raz

  1: uruchamiam bfs dla wierzcholkow niezajetych - 4 i 5
  robi sie 4-D-2-E na zmiane wolne i zajete krawedzie - wysokosc wychodzi 3
  teraz biore 5 - robi sie 5-C-3-B  
  (E,B do kolejki w trakcie dodaje)

  2: uruchamiam dfs z wierzcholkow z kolejki i robie to samo co wyzej
  dfs na E: E-2,2-D,D-4
  dfs na B: B-3,3-C,C-5
  robie operacje plusa w kolku - JEZELI MAM KRAWEDZIE W ODWROTNEJ KOLEJNOSCI (C-3, 3-C) TO JE SKRACAM (WYWALAM)

  potem robie koljena iteracje (najpierw aktualizuje graf)
  uruchamiam dfs dla wolnych wierzcholkow - nie ma wiec koniec

  algosa przerywamy kiedy po iteracji jezeli poprzedni rozmiar tablicy odpowiedzi jest taki sam jak przed iteracja

  polaczenia miedzy polami to bicie - jak 0 to pomijamy wgl z grafu najlepiej
  i na tym grafie odpalamy ten algorytm

  nie mozna robic 2 grafu obok w pamieci !!!!!!
  do dfs patrzymy na wierzcholki z tamtej znalezionej wysokosci

  skracanie z iteracji jest wolne wiec cos inaczej
  mozna sie wzorowac z neta niby jak jest problem - chatgpt or sth

*/

struct Pawn {
  int id;
  int function;
  //tablca sasiadow danego punktu
  vector <Pawn*> hits;
  
  bool visited;
  bool free;

  Pawn(){}
  Pawn(int id, int function) {
    this->id = id;
    this->function = function;
    visited = false;
    free = true;
  }
};

//testowe
void print_graph(vector <Pawn*> pawns) {
  for(int i=0;i<pawns.size();++i) {
    cout<<pawns[i]->id<<": ";
    for(int j=0;j<pawns[i]->hits.size();++j) {
      cout<<pawns[i]->hits[j]->id<<" ";
    }
    cout<<endl;
  }
}

inline void reset_visits(vector <Pawn*> &pawns) {
  for(int i=0;i<pawns.size();++i) {
    pawns[i]->visited = false;
  }
}

bool hit(vector <vector <Pawn*> > &pawns, int y, int x, int size) {
  int reach_x, reach_y;
  bool connected = false;
  int attack_mode = pawns[y][x]->function;
  if (attack_mode == 0) {
    return false;

    //atak o 3 na wprost lub o 2 na wprost i jedno w bok
  } else if (attack_mode == 1) {
    //o 3 na wprost
    reach_x = x + 3;
    reach_y = y;
    if(reach_x < size) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->hits.push_back(pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x]->hits.push_back(pawns[y][x]);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w gore
    reach_x = x + 2;
    reach_y = y - 1;
    if(reach_x < size && reach_y >= 0) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->hits.push_back(pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x]->hits.push_back(pawns[y][x]);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w dol
    reach_y = y + 1;
    if(reach_x < size && reach_y < size) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->hits.push_back(pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x]->hits.push_back(pawns[y][x]);
        connected = true;
      }
    }

    //atak o 1 na wprost lub o 1 w bok
  } else if (attack_mode == 2) {
    //o 1 na wprost
    reach_x = x + 1;
    reach_y = y;
    if(reach_x < size) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->hits.push_back(pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x]->hits.push_back(pawns[y][x]);
        connected = true;
      }
    }

    //o 1 w gore
    reach_x = x;
    reach_y = y - 1;
    if(reach_x < size && reach_y >= 0) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->hits.push_back(pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x]->hits.push_back(pawns[y][x]);
        connected = true;
      }
    }

    //o 1 w dol
    reach_y = y + 1;
    if(reach_y < size) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->hits.push_back(pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x]->hits.push_back(pawns[y][x]);
        connected = true;
      }
    }

    //atak o 1 na wprost lub o 2 na wprost i 1 w bok
  } else {
    //o 1 na wprost
    reach_x = x + 1;
    reach_y = y;
    if(reach_x < size) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->hits.push_back(pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x]->hits.push_back(pawns[y][x]);
        connected = true;
      }
    }
    
    //o 2 na wprost i 1 w gore
    reach_y = y - 1;
    if(reach_x < size && reach_y >= 0) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->hits.push_back(pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x]->hits.push_back(pawns[y][x]);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w dol
    reach_x = x + 2;
    reach_y = y + 1;
    if(reach_x < size && reach_y < size) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->hits.push_back(pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x]->hits.push_back(pawns[y][x]);
        connected = true;
      }
    }
  }

  return connected;
}

void bfs(vector <Pawn*> &pawns, int size, int &height) {
  reset_visits(pawns);
  queue <Pawn*> pawn_queue;
  for(int i=0;i<pawns.size();++i) {
    if(pawns[i]->free) {
      pawns[i]->visited = true;
      pawn_queue.push(pawns[i]);
    }
  }
  bool none_found = false;
  bool stop_height = false;

  //droga dla danego poziomu
  int current_route = 0;
  Pawn* current;
  //licznik elementow na poziomie
  int level_counter = 0;
  //rozmiar poziomu
  int level_cap = 1;
  //przyszly rozmiar poziomu
  int future_level_cap = 0;
        
  while(!pawn_queue.empty() && !stop_height) {
    //odwiedzenie wioski
    level_counter++;
    //sciagniecie wioski z kolejki
    current = pawn_queue.front();
    pawn_queue.pop();
    //przejscie po sasiadach sciagnietej wioski
    for(int j=0;j<current->hits.size();j++) {
      //jezeli sasiad jeszcze nie byl odwiedzony
      if(!current->hits[j]->visited && !current->hits[j]->free == current_route & 1) {   //???????
        //odwiedzenie
        current->hits[j]->visited = true;
        //dodanie do kolejki
        pawn_queue.push(current->hits[j]);
        //zwiekszenie przyszlego rozmiaru poziomu
        future_level_cap++;
      }
    }
    //restart zliczania poziomu w wypadku skonczenia aktualnego
    if(level_counter == level_cap) {
      current_route++;
      level_counter = 0;
      level_cap = future_level_cap;
      future_level_cap = 0;
    }
  }
  height = current_route;
}

void dfs(vector <Pawn*> &pawns) {
  // Pawn* start = graph[];
  // for(int i=0;i<graph.size();++i) {
  //   if(!graph[i]->visited) {
      
  //   }
  // }
}

inline void hopkroft_karp(vector <Pawn*> &pawns) {
  // reset_visits()
  // bfs();
  // reset_visits()
  // dfs();
}

inline void max_left_pawns(vector <vector <Pawn*> > &pawns, int size) {
  vector <Pawn*> graph;

  //przejscie po szachownicy po czarnych polach, sprawdzenie atakow i stworzenie grafu dwudzielnego
  for(int i=0;i<size;++i) {
    for(int j= i&1 ;j<size;j+=2) {
      if(hit(pawns,i,j,size)) {
        graph.push_back(pawns[i][j]);
      }
    }
  }

  //zwolnienie pamieci dla pozniejszych kolejek itp.
  for(int i=0;i<size;++i) {
    pawns[i].clear();
  }
  pawns.clear();

  //algorytm hopkroft-karp na grafie
  hopkroft_karp(graph);

  // print_graph(graph);

  graph.clear();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.tie(nullptr);

  int N; //wymiar szachownicy
  int counter = 0; //licznik id
  int space; //wartosc danego pola

  cin>>N;

  vector < vector <Pawn*> > pawns(N);
  for(int i=0;i<N;++i) {
    for(int j=0;j<N;++j) {
      cin>>space;
      pawns[i].push_back(new Pawn(counter,space));
      counter++;
    }
  }

  max_left_pawns(pawns,N);

  return 0;
}