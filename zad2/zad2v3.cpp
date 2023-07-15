#include <iostream>
#include <vector>
#include <queue>
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

  bool processed;

  Pawn(){}
  Pawn(int id, int function) {
    this->id = id;
    this->function = function;
    visited = false;
    free = true;
    processed = false;
  }
};

struct Edge {
  Pawn* black;
  Pawn* white;
  bool free_edge;
  
  Edge(){}
  Edge(Pawn* black, Pawn* white) {
    this->black = black;
    this->white = white;
    free_edge = true;
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
      if(!pawns[i]->hits[j]->free_edge)
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
void print_anwer(vector <Edge*> anwser) {
  for(int i=0;i<anwser.size();++i) {
    cout<<anwser[i]->black->id<<"-"<<anwser[i]->white->id<<" ";
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

inline void reset_processed(vector <Pawn*> &pawns) {
  for(int i=0;i<pawns.size();++i) {
    pawns[i]->processed = false;
    for(int j=0;j<pawns[i]->hits.size();++j) {
      pawns[i]->hits[j]->white->processed = false;
    }
  }
}

inline void add_anwser(vector <Edge*> &final_anwsers, vector <Edge*> &temp_anwsers) {
  bool ok = true;
  for(int i=0;i<temp_anwsers.size();++i) {
    for(int j=0;j<final_anwsers.size();++j) {
      if(final_anwsers[j]->black == temp_anwsers[i]->black && final_anwsers[j]->white == temp_anwsers[i]->white) {
        final_anwsers.erase(final_anwsers.begin()+j);
        j--;
        ok = false;
      }
        
    }
    if(ok)
      final_anwsers.push_back(temp_anwsers[i]);
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
  reset_visits(pawns);
  
  queue <Pawn*> queue;
  for(int i=0;i<pawns.size();++i) {
    if(pawns[i]->free) {
      pawns[i]->visited = true;
      queue.push(pawns[i]);
    }
  }
  // reset_free(pawns);
  Pawn* current;
  Pawn* current_opposite;
  int current_height = 0;
  int level_cap = queue.size();
  int future_level_cap = 0;
  int level_counter = 0;
  bool finish_search = false;
  bool found_match = false;

  while(!queue.empty()) {
    bool on_black = !(1 & current_height);
    level_counter++;
    current = queue.front();
    queue.pop();
    cout<<current->id<<" -> ";

    for(int i=0;i<current->hits.size();++i) {
      //na zmiane "wolnosc" krawedzi musi byc
      if(current->hits[i]->free_edge == on_black) {
        current_opposite = on_black ? current->hits[i]->white : current->hits[i]->black;
        if(!current_opposite->visited) {
          current_opposite->visited = true;
          queue.push(current_opposite);
          future_level_cap++;
          if(current_opposite->free) {
            pawn_queue.push(current_opposite);
            finish_search = true;
          }
        }
      }
    }
    if(level_counter == level_cap) {
      current_height++;
      level_counter = 0;
      level_cap = future_level_cap;
      future_level_cap = 0;
      if(finish_search && on_black) {
        break;
      }
      finish_search = false;
      cout<<"H: "<<current_height<<endl;
    } 
  }
  height = current_height;
  return finish_search;
}

bool dfs(Pawn* current, int current_height, int &height, vector <Edge*> &temp_anwser) {
  current->free = false;
  bool on_white = !(current_height & 1);
  Pawn* current_opposite;
  // cout<<endl<<"h:"<<current_height<<" ";
  cout<<current->id<<" -> ";
  for(int i=0;i<current->hits.size();++i) {
    current_opposite = on_white ? current->hits[i]->black : current->hits[i]->white;
    if(current->hits[i]->free_edge == on_white && !current_opposite->processed && current_height < height) {
      bool found_anwser = current_opposite->free;
      current->hits[i]->free_edge = !current->hits[i]->free_edge;
      current_opposite->free = false;
      temp_anwser.push_back(current->hits[i]);
      if(found_anwser && on_white) {
        current_opposite->processed = true;
        cout<<"A";
        return true;
      }
      
      if(dfs(current_opposite,current_height + 1,height,temp_anwser)) {
        return true;
      }
    } else if (current_height == height) {
      cout<<" << ";
      return false;
    }
  }
  return false;
  
}

int hopkroft_karp(vector <Pawn*> &pawns,int N) {
  int height = 0;
  queue <Pawn*> pawn_queue;
  Pawn* current;
  int value;
  vector <Edge*> final_anwser;
  vector <Edge*> temp_anwser;
  print_graph(pawns);
  while(true) {
    // cout<<"Q: "<<pawn_queue.size()<<endl;
    print_free_pawns(pawns);
    // print_graph(pawns);
    cout<<endl<<"B F S:"<<endl;
    if(!bfs(pawns,pawn_queue,height)) {
      break;
    }
    cout<<endl;
    
    cout<<"Q: "<<pawn_queue.size()<<endl;
    cout<<"H: "<<height<<endl; 
    cout<<endl<<"D F S:"<<endl;
    while(!pawn_queue.empty()) {
      reset_visits(pawns);
      current = pawn_queue.front();
      cout<<current->id<<": ";
      pawn_queue.pop();
      dfs(current,0,height,temp_anwser);
      add_anwser(final_anwser,temp_anwser);
      temp_anwser.clear();
      cout<<"!"<<endl;
    }
    cout<<endl;
    print_used_paths(pawns);
    cout<<"Anwser: "<<endl;
    print_anwer(final_anwser);
  }
  cout<<endl<<"FINAL Anwser: "<<endl;
  print_anwer(final_anwser);

  //odpowiedz
  return (N*N) - final_anwser.size();
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