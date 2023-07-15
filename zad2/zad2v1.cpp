#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

struct Edge;

struct Pawn {
  int id;
  int function;
  //tablca sasiadow danego punktu
  vector <Edge*> hits;
  //czy odwiedzony przy przejsciu przez graf
  bool visited;
  //czy wierzcholek jest jeszcze wolny
  bool free;

  Pawn(){}
  Pawn(int id, int function) {
    this->id = id;
    this->function = function;
    visited = false;
    free = true;
  }
};

struct Edge {
  Pawn* black;
  Pawn* white;
  bool free;
  
  Edge(){}
  Edge(Pawn* black, Pawn* white) {
    this->black = black;
    this->white = white;
    free = true;
  }
};

//testowe
void print_graph(vector <Pawn*> pawns) {
  for(int i=0;i<pawns.size();++i) {
    cout<<pawns[i]->id<<": ";
    for(int j=0;j<pawns[i]->hits.size();++j) {
      cout<<pawns[i]->hits[j]->white->id<<" ";
    }
    cout<<endl;
  }
}
void print_used_paths(vector <Pawn*> pawns) {
  for(int i=0;i<pawns.size();++i) {
    cout<<pawns[i]->id<<": ";
    for(int j=0;j<pawns[i]->hits.size();++j) {
      if(!pawns[i]->hits[j]->free)
        cout<<pawns[i]->hits[j]->black->id<<"->"<<pawns[i]->hits[j]->white->id<<" ";
    }
    cout<<endl;
  }
}
void print_free_pawns(vector <Pawn*> pawns) {
  cout<<"Free: ";
  for(int i=0;i<pawns.size();++i) {
    if(pawns[i]->free)
      cout<<pawns[i]->id<<" ";
  }
  cout<<endl;
}

inline void reset_visits(vector <Pawn*> &pawns) {
  for(int i=0;i<pawns.size();++i) {
    pawns[i]->visited = false;
    for(int j=0;j<pawns[i]->hits.size();++j) {
      pawns[i]->hits[j]->white->visited = false;
    }
  }
}

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

bool bfs(vector <Pawn*> &pawns, queue <Pawn*> &pawn_queue,  int &height) {
  cout<<"BFS:\n";
  reset_visits(pawns);
  for(int i=0;i<pawns.size();++i) {
    if(pawns[i]->free) {
      pawns[i]->visited = true;
      pawn_queue.push(pawns[i]);
    }
  }
  bool found_any = false;
  bool found_any_on_level = false;

  //droga dla danego poziomu
  int current_route = 0;
  Pawn* current;
  Pawn* current_opposite;
  //licznik elementow na poziomie
  int level_counter = 0;
  //rozmiar poziomu
  int level_cap = pawn_queue.size();
  //przyszly rozmiar poziomu
  int future_level_cap = 0;
        
  while(!pawn_queue.empty()) {
    bool on_black = !(current_route & 1);
    level_counter++;
    current = pawn_queue.front();
    pawn_queue.pop();

    cout<<current->id<<": "<<endl;

    for(int i=0;i<current->hits.size();i++) {
      current_opposite = on_black ? current->hits[i]->white : current->hits[i]->black;
      if(current->hits[i]->free == on_black) {
        if(!found_any) {
          cout<<current->hits[i]->black->id<<"=="<<current->hits[i]->white->id<<endl;
          current->hits[i]->free = false;
          if(current_opposite->free) {
            found_any_on_level = true;
          }
        }
        if(!current_opposite->visited) {
          current_opposite->visited = true;
          pawn_queue.push(current_opposite);
          future_level_cap++;
        }
        found_any = true;
      }
    }
    found_any = false;

    if(level_counter == level_cap) {
      current_route++;
      level_counter = 0;
      level_cap = future_level_cap;
      future_level_cap = 0;
      if(found_any_on_level && on_black) {
        break;
      }
      found_any_on_level = false;
    }
  }
  height = current_route;
  cout<<"BFS END\n";
  return found_any_on_level;
}

bool dfs(Pawn* current, int current_height, int &height, unordered_set <int> &temp_set) {
  Pawn* current_opposite;
  current->visited = true;
  current->free = false;
  bool is_white = !(current_height & 1);
  cout<<"h:"<<current_height<<endl;
  cout<<current->id<<" -> ";
  
  for(int i=0;i<current->hits.size();++i) {
    current_opposite = is_white ? current->hits[i]->black : current->hits[i]->white;
    if(!current_opposite->visited && current_opposite->free && (!current->hits[i]->free && is_white) && current_height <= height) {
      int x = current->id;
      int y = current_opposite->id;
      if(x > y) {
        int tmp = x;
        x = y;
        y = tmp;
      }
      //kodowanie Cantora
      int value = (((x + y) * (x + y + 1)) / 2) + y;
      temp_set.insert(value);
      dfs(current_opposite,current_height + 1,height,temp_set);
      return true;
    }
  }
  return false;
}

int hopkroft_karp(vector <Pawn*> &pawns,int N) {
  int height;
  queue <Pawn*> pawn_queue;
  Pawn* current;
  int value;
  unordered_set <int> anwser_set;
  unordered_set <int> temp_set;
  while(true) {
    // cout<<"Q: "<<pawn_queue.size()<<endl;
    print_free_pawns(pawns);
    print_graph(pawns);
    if(!bfs(pawns,pawn_queue,height)) {
      break;
    }
    print_used_paths(pawns);
    cout<<"Q: "<<pawn_queue.size()<<endl;
    while(!pawn_queue.empty()) {
      reset_visits(pawns);
      current = pawn_queue.front();
      pawn_queue.pop();
      if(dfs(current,0,height,temp_set)) {
        anwser_set.insert(temp_set.begin(),temp_set.end());
        temp_set.clear();
      }
      cout<<endl;
    }
  }

  //odpowiedz
  return (N*N) - anwser_set.size();
}

inline void max_left_pawns(vector <vector <Pawn*> > &pawns, int size) {
  vector <Pawn*> graph;
  int counter = 0;

  //przejscie po szachownicy po czarnych polach, sprawdzenie atakow i stworzenie grafu dwudzielnego
  for(int i=0;i<size;++i) {
    for(int j= i&1 ;j<size;j+=2) {
      if(hit(pawns,i,j,size)) {
        graph.push_back(pawns[i][j]);
        ++counter;
      }
    }
  }

  // print_graph(graph);

  //zwolnienie pamieci dla pozniejszych kolejek itp.
  for(int i=0;i<size;++i) {
    pawns[i].clear();
  }
  pawns.clear();

  //algorytm hopkroft-karp na grafie
  cout<<hopkroft_karp(graph,size);

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