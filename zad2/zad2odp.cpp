#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Pawn;

struct Edge {
  //wskazniki na czarny i bialy pionek na krawedzi
  Pawn* black;
  Pawn* white;
  //oznaczenie czy krawedz jest zajeta
  bool free_edge;

  Edge(){}
  Edge(Pawn* black,Pawn* white) {
    this->black = black;
    this->white = white;
    free_edge = true;
  }
};

struct Pawn {
  int id;
  //wejsciowy tryb ataku
  int function;
  //tablica sasiedztwa (jako tablica krawedzi z pionkami w srodku)
  vector <Edge*> hits;
  //czy wierzcholek jest zajety
  bool free;
  Pawn(){}
  Pawn(int id, int function) {
    this->id = id;
    this->function = function;
    free = true;
  }
};

//algebraiczne dodanie zbiorow - bez powtorzen - jak sie powtorza to usuwa
inline void add_anwser(vector <Edge*> &final_anwser, vector <Edge*> &temp_anwser) {
  //czy sa duplikaty = czy po sprawdzeniu dodac do finalnej listy odpowiedzi
  bool no_duplicates = true;
  for(int i=0;i<temp_anwser.size();++i) {
    no_duplicates = true;
    for(int j=0;j<final_anwser.size();++j) {
      if(final_anwser[j]->black == temp_anwser[i]->black && final_anwser[j]->white == temp_anwser[i]->white) {
        //zwolnienie wierzcholkow po usunieciu krawedzi z odpowiedzi
        final_anwser[j]->black->free = true;
        final_anwser[j]->white->free = true;
        final_anwser.erase(final_anwser.begin()+j);
        no_duplicates = false;
        continue;
      }
    }
    if(no_duplicates) {
      //dodanie do odpowiedzi i zajecie wierzcholkow
      temp_anwser[i]->black->free = false;
      temp_anwser[i]->white->free = false;
      final_anwser.push_back(temp_anwser[i]);
    }
  }
  //upewnienie zajecia wszystkich pionkow z odpowiedzi
  for(int i=0;i<final_anwser.size();++i) {
    final_anwser[i]->black->free = false;
    final_anwser[i]->white->free = false;
  }
}

//laczenie wierzcholkow zgodnie z zasadami z zadania
bool hit(vector <vector <Pawn*> > &pawns, int y, int x, int size) {
  int reach_x, reach_y;
  bool connected = false;
  int attack_mode = pawns[y][x]->function;
  Edge* edge;
  if (attack_mode == 0) {
    return false;

    //atak o 3 na wprost lub o 2 na wprost i jedno w bok
  } else if (attack_mode == 1) {
    //o 3 na wprost
    reach_x = x + 3;
    reach_y = y;
    if(reach_x < size) {
      //jezeli przeciwny pionek nie ma trybu 0
      if(pawns[reach_y][reach_x]->function != 0) {
        //dodanie wspolnej krawedzi dla czarnego i bialego wierzcholka
        edge = new Edge(pawns[y][x],pawns[reach_y][reach_x]);
        pawns[y][x]->hits.push_back(edge);
        pawns[reach_y][reach_x]->hits.push_back(edge);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w gore
    reach_x = x + 2;
    reach_y = y - 1;
    if(reach_x < size && reach_y >= 0) {
      if(pawns[reach_y][reach_x]->function != 0) {
        edge = new Edge(pawns[y][x],pawns[reach_y][reach_x]);
        pawns[y][x]->hits.push_back(edge);
        pawns[reach_y][reach_x]->hits.push_back(edge);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w dol
    reach_y = y + 1;
    if(reach_x < size && reach_y < size) {
      if(pawns[reach_y][reach_x]->function != 0) {
        edge = new Edge(pawns[y][x],pawns[reach_y][reach_x]);
        pawns[y][x]->hits.push_back(edge);
        pawns[reach_y][reach_x]->hits.push_back(edge);
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
        edge = new Edge(pawns[y][x],pawns[reach_y][reach_x]);
        pawns[y][x]->hits.push_back(edge);
        pawns[reach_y][reach_x]->hits.push_back(edge);
        connected = true;
      }
    }

    //o 1 w gore
    reach_x = x;
    reach_y = y - 1;
    if(reach_x < size && reach_y >= 0) {
      if(pawns[reach_y][reach_x]->function != 0) {
        edge = new Edge(pawns[y][x],pawns[reach_y][reach_x]);
        pawns[y][x]->hits.push_back(edge);
        pawns[reach_y][reach_x]->hits.push_back(edge);
        connected = true;
      }
    }

    //o 1 w dol
    reach_y = y + 1;
    if(reach_y < size) {
      if(pawns[reach_y][reach_x]->function != 0) {
        edge = new Edge(pawns[y][x],pawns[reach_y][reach_x]);
        pawns[y][x]->hits.push_back(edge);
        pawns[reach_y][reach_x]->hits.push_back(edge);
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
        edge = new Edge(pawns[y][x],pawns[reach_y][reach_x]);
        pawns[y][x]->hits.push_back(edge);
        pawns[reach_y][reach_x]->hits.push_back(edge);
        connected = true;
      }
    }
    
    //o 2 na wprost i 1 w gore
    reach_x = x + 2;
    reach_y = y - 1;
    if(reach_x < size && reach_y >= 0) {
      if(pawns[reach_y][reach_x]->function != 0) {
        edge = new Edge(pawns[y][x],pawns[reach_y][reach_x]);
        pawns[y][x]->hits.push_back(edge);
        pawns[reach_y][reach_x]->hits.push_back(edge);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w dol
    reach_y = y + 1;
    if(reach_x < size && reach_y < size) {
      if(pawns[reach_y][reach_x]->function != 0) {
        edge = new Edge(pawns[y][x],pawns[reach_y][reach_x]);
        pawns[y][x]->hits.push_back(edge);
        pawns[reach_y][reach_x]->hits.push_back(edge);
        connected = true;
      }
    }
  }
  return connected;
}

//stworzenie grafu z wejsciowej szachownicy
vector <Pawn*> make_graph(vector <vector <Pawn*> > &pawns, int size) {
  //tablica wskaznikow na wszystkie czarne piony w grafie
  vector <Pawn*> black_pawns;
  //wszystkie wiersze
  for(int i=0;i<size;++i) {
    //szachownica w wierszu
    for(int j=i&1;j<size;j+=2) {
      //jak jest trafienie to dodajemy do grafu
      if(hit(pawns,i,j,size)) {
        black_pawns.push_back(pawns[i][j]);
      }
    }
  }
  return black_pawns;
}

//przejscie wszerz
bool bfs(vector <vector <Pawn*> > &pawns, vector <Pawn*> &black_pawns, queue <Pawn*> &pawn_queue, int &height, int size) {
  queue <Pawn*> queue;
  //tablica odwiedzin
  vector <bool> visited(size*size,false);
  //dodanie wszyskich wolnych czarnych do kolejki i ustawienie ze sa odwiedzone
  for(int i=0;i<black_pawns.size();++i) {
    if(black_pawns[i]->free) {
      queue.push(black_pawns[i]);
      visited[black_pawns[i]->id] = true;
    }
  }
  //aktualny przegladany pionek
  Pawn* current;
  //aktualna "wysokosc"
  int current_height = 0;
  //ilosc pionkow na poziomie
  int level_cap = queue.size();
  //ilosc pionkow na przyszlym poziomie
  int future_level_cap = 0;
  //licznik aktualnego poziomu
  int level_counter = 0;
  //czy znaleziono jakis wolny pionek po bialej stronie
  bool found_any = false;

  while(!queue.empty()) {
    ++level_counter;
    //czy jestesmy na poziomie z czarnymi pionkami
    bool on_black = !(current_height & 1);
    current = queue.front();
    queue.pop();
    //przejscie po atakach danego pionka
    for(int i=0;i<current->hits.size();++i) {
      //pionek po przeciwnej stronie od aktualnego
      Pawn* opposite = on_black ? current->hits[i]->white : current->hits[i]->black;
      //jezeli krawedz jest dobra (wolna jak idziemy od czarnych)
      if(current->hits[i]->free_edge == on_black) {
        //jezeli przeciwny wierzcholek nieodwiedzony
        if(!visited[opposite->id]) {
          visited[opposite->id] = true;
          queue.push(opposite);
          ++future_level_cap;
          //jezeli przeciwny pionek jest wolny i jest bialy
          if(opposite->free && on_black) {
            pawn_queue.push(opposite);
            found_any = true;
          }
        }
      }
    }

    //jak przeszlismy caly poziom
    if(level_counter == level_cap) {
      ++current_height;
      level_counter = 0;
      level_cap = future_level_cap;
      future_level_cap = 0;

      //jezeli znaleziono jakikolwiek pionek wolny u bialych i jestesmy na czarnych
      if(found_any && on_black) {
        break;
      }
      found_any = false;
    }
  }
  //ustawiamy max wysokosc do dfs
  height = current_height;
  return found_any;
}

//przejscie wglab
bool dfs(Pawn* current, int &height, int current_height, vector <Edge*> &temp_anwser) {
  //jak doszlismy do max 
  if(height == current_height) {
    return false;
  }
  //czy jestesmy na bialych
  bool on_white = !(current_height & 1);

  //przejscie po sasiadach
  for(int i=0;i<current->hits.size();++i) {
    //przeciwny pionek
    Pawn* opposite = on_white ? current->hits[i]->black : current->hits[i]->white;
    //jezeli krawedz jest dobra (wolna jak idziemy od bialych)
    if(current->hits[i]->free_edge == on_white) {
      bool found_anwser = opposite->free;
      //rekurencjyjne dfs ze zwiekszona wysokoscia
      if(dfs(opposite,height,current_height + 1,temp_anwser)) {
        //zamiana zajecia krawedzi
        current->hits[i]->free_edge = !current->hits[i]->free_edge;
        //dodanie krawedzi do odpowiedzi
        temp_anwser.push_back(current->hits[i]);
        return true;
      }
      //jezeli znaleziono odpowiedz i jestesmy na bialym
      if(found_anwser && on_white) {
        //zamiana zajecia krawedzi
        current->hits[i]->free_edge = !current->hits[i]->free_edge;
        //dodanie krawedzi do odpowiedzi
        temp_anwser.push_back(current->hits[i]);
        return true;
      }
    }
  }
  return false;
}

//algorytm
int hopcroft_karp(vector <vector <Pawn*> > &pawns, vector <Pawn*> &black_pawns, int size) {
  //finalna odpowiedz
  vector <Edge*> final_anwser;
  //tymczasowe odpowiedz
  vector <Edge*> temp_anwser;
  //kolejka pionow do dfs
  queue <Pawn*> pawn_queue;
  //wysokosc na jaka doszedl bfs
  int height = 0;
  Pawn* current;

  while(true) {
    //jezeli bfs cos znajdzie to idzemy dalej
    if(!bfs(pawns,black_pawns,pawn_queue,height,size)) {
      break;
    }
    //dfs na wszystkich bialych z kolejki znalezionych
    while(!pawn_queue.empty()) {
      current = pawn_queue.front();
      pawn_queue.pop();
      dfs(current,height,0,temp_anwser);
      //dodanie odpowiedzi
      add_anwser(final_anwser,temp_anwser);
      //wyczyszczenie tymczasowej odpowiedzi
      temp_anwser.clear();
    }
  }
  //zwrocenie ilosci maksymalnych skojarzen
  return final_anwser.size();
}

int main() {
  int N; //wymiar planszy
  int space; //dane pole
  int counter = 0; //licznik id

  cin>>N;

  //szachownica
  vector <vector <Pawn*> > pawns(N);

  for(int i=0;i<N;++i) {
    for(int j=0;j<N;++j) {
      cin>>space;
      pawns[i].push_back(new Pawn(counter,space));
      ++counter;
    }
  }

  //czarne piony - graf
  vector <Pawn*> black_pawns = make_graph(pawns, N);

  cout<<(N*N) - hopcroft_karp(pawns,black_pawns,N)<<endl;

  return 0;
}