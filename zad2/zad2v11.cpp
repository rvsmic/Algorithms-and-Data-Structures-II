#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Pawn;

struct Edge {
  Pawn* black;
  Pawn* white;
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
  int function;
  vector <Edge*> hits;
  bool free;
  Pawn(){}
  Pawn(int id, int function) {
    this->id = id;
    this->function = function;
    free = true;
  }

  void add_white_edge(Pawn* opposite) {
    bool already_added = false;
    for(int i=0;i<hits.size();++i) {
      if(hits[i]->black == opposite) {
        already_added = true;
        break;
      }
    }
    if(!already_added) {
      Edge* edge = new Edge(opposite,this);
      hits.push_back(edge);
      opposite->hits.push_back(edge);
    }
  }

  void add_black_edge(Pawn* opposite) {
    bool already_added = false;
    for(int i=0;i<hits.size();++i) {
      if(hits[i]->white == opposite) {
        already_added = true;
        break;
      }
    }
    if(!already_added) {
      Edge* edge = new Edge(this,opposite);
      hits.push_back(edge);
      opposite->hits.push_back(edge);
    }
  }
};

//testowe
void print_anwser(vector <Edge*> anwser) {
  for(int i=0;i<anwser.size();++i) {
    cout<<anwser[i]->black->id<<"-"<<anwser[i]->white->id<<" ";
  }
}

void print_free_edges(vector <vector <Pawn*> > pawns) {
  cout<<endl;
  cout<<"FREE EDGES:\n";
  for(int i=0;i<pawns.size();++i) {
    for(int j=0;j<pawns.size();++j) {
      cout<<pawns[i][j]->id<<": ";
      for(int k=0;k<pawns[i][j]->hits.size();++k) {
        if(pawns[i][j]->hits[k]->free_edge) {
          cout<<pawns[i][j]->hits[k]->black->id<<"->"<<pawns[i][j]->hits[k]->white->id<<" ";
        }
      }
      cout<<endl;
    }
  }
  cout<<endl;
}

inline void add_anwser(vector <Edge*> &final_anwser, vector <Edge*> &temp_anwser) {
  bool no_duplicates = true;
  for(int i=0;i<temp_anwser.size();++i) {
    for(int j=0;j<final_anwser.size();++j) {
      if(final_anwser[j]->black == temp_anwser[i]->black && final_anwser[j]->white == temp_anwser[i]->white) {
        // cout<<final_anwser[j]->black->id<<"A";
        final_anwser[j]->black->free = true;
        final_anwser[j]->white->free = true;
        final_anwser.erase(final_anwser.begin()+j);
        no_duplicates = false;
        continue;
      }
    }
    if(no_duplicates) {
      temp_anwser[i]->black->free = false;
      temp_anwser[i]->white->free = false;
      final_anwser.push_back(temp_anwser[i]);
    }
  }
  for(int i=0;i<final_anwser.size();++i) {
    final_anwser[i]->black->free = false;
    final_anwser[i]->white->free = false;
  }
}

bool black_hit(vector <vector <Pawn*> > &pawns, int y, int x, int size) {
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
        pawns[y][x]->add_black_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x]->add_edge(pawns[y][x]);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w gore
    reach_x = x + 2;
    reach_y = y - 1;
    if(reach_x < size && reach_y >= 0) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->add_black_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x]->add_edge(pawns[y][x]);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w dol
    reach_y = y + 1;
    if(reach_x < size && reach_y < size) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->add_black_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x]->add_edge(pawns[y][x]);
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
        pawns[y][x]->add_black_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x]->add_edge(pawns[y][x]);
        connected = true;
      }
    }

    //o 1 w gore
    reach_x = x;
    reach_y = y - 1;
    if(reach_x < size && reach_y >= 0) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->add_black_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x]->add_edge(pawns[y][x]);
        connected = true;
      }
    }

    //o 1 w dol
    reach_y = y + 1;
    if(reach_y < size) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->add_black_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x]->add_edge(pawns[y][x]);
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
        pawns[y][x]->add_black_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x]->add_edge(pawns[y][x]);
        connected = true;
      }
    }
    
    //o 2 na wprost i 1 w gore
    reach_x = x + 2;
    reach_y = y - 1;
    if(reach_x < size && reach_y >= 0) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->add_black_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x]->add_edge(pawns[y][x]);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w dol
    reach_y = y + 1;
    if(reach_x < size && reach_y < size) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->add_black_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x]->add_edge(pawns[y][x]);
        connected = true;
      }
    }
  }
  return connected;
}

bool white_hit(vector <vector <Pawn*> > &pawns, int y, int x, int size) {
  int reach_x, reach_y;
  bool connected = false;
  int attack_mode = pawns[y][x]->function;
  if (attack_mode == 0) {
    return false;

    //atak o 3 na wprost lub o 2 na wprost i jedno w bok
  } else if (attack_mode == 1) {
    //o 3 na wprost
    reach_x = x - 3;
    reach_y = y;
    if(reach_x >= 0) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->add_white_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w gore
    reach_x = x - 2;
    reach_y = y - 1;
    if(reach_x >= 0 && reach_y >= 0) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->add_white_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w dol
    reach_y = y + 1;
    if(reach_x >= 0 && reach_y < size) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->add_white_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //atak o 1 na wprost lub o 1 w bok
  } else if (attack_mode == 2) {
    //o 1 na wprost
    reach_x = x - 1;
    reach_y = y;
    if(reach_x >= 0) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->add_white_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //o 1 w gore
    reach_x = x;
    reach_y = y - 1;
    if(reach_x >= 0 && reach_y >= 0) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->add_white_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //o 1 w dol
    reach_y = y + 1;
    if(reach_y < size) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->add_white_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //atak o 1 na wprost lub o 2 na wprost i 1 w bok
  } else {
    //o 1 na wprost
    reach_x = x - 1;
    reach_y = y;
    if(reach_x >= 0) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->add_white_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }
    
    //o 2 na wprost i 1 w gore
    reach_x = x - 2;
    reach_y = y - 1;
    if(reach_x >= 0 && reach_y >= 0) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->add_white_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w dol
    reach_y = y + 1;
    if(reach_x >= 0 && reach_y < size) {
      if(pawns[reach_y][reach_x]->function != 0) {
        pawns[y][x]->add_white_edge(pawns[reach_y][reach_x]);
        // pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }
  }
  return connected;
}

vector <Pawn*> make_graph(vector <vector <Pawn*> > &pawns, int size) {
  vector <Pawn*> black_pawns;
  for(int i=0;i<size;++i) {
    for(int j=!(i&1);j<size;j+=2) {
      white_hit(pawns,i,j,size);
    }
  }
  for(int i=0;i<size;++i) {
    for(int j=i&1;j<size;j+=2) {
      if(black_hit(pawns,i,j,size)) {
        black_pawns.push_back(pawns[i][j]);
      }
    }
  }
  return black_pawns;
}

bool bfs(vector <vector <Pawn*> > &pawns, vector <Pawn*> &black_pawns, queue <Pawn*> &pawn_queue, int &height, int size) {
  queue <Pawn*> queue;
  vector <bool> visited(size*size,false);
  for(int i=0;i<black_pawns.size();++i) {
    if(black_pawns[i]->free) {
      queue.push(black_pawns[i]);
      visited[black_pawns[i]->id] = true;
    }
  }
  Pawn* current;
  int current_height = 0;
  int level_cap = queue.size();
  int future_level_cap = 0;
  int level_counter = 0;

  bool found_any = false;

  while(!queue.empty()) {
    ++level_counter;
    bool on_black = !(current_height & 1);

    current = queue.front();
    queue.pop();
    // cout<<current->id<<"-";

    for(int i=0;i<current->hits.size();++i) {
      Pawn* opposite = on_black ? current->hits[i]->white : current->hits[i]->black;
      if(current->hits[i]->free_edge == on_black) {
        if(!visited[opposite->id]) {
          visited[opposite->id] = true;
          queue.push(opposite);
          ++future_level_cap;
          if(opposite->free && on_black) {
            // opposite->free = false;
            pawn_queue.push(opposite);
            found_any = true;
          }
        }
      }
    }

    if(level_counter == level_cap) {
      ++current_height;
      level_counter = 0;
      level_cap = future_level_cap;
      future_level_cap = 0;

      if(found_any && on_black) {
        break;
      }
      found_any = false;
    }
  }
  height = current_height;
  return found_any;
}

bool dfs(Pawn* current, int &height, int current_height, vector <Edge*> &temp_anwser) {
  if(height == current_height) {
    return false;
  }
  bool on_white = !(current_height & 1);

  for(int i=0;i<current->hits.size();++i) {
    Pawn* opposite = on_white ? current->hits[i]->black : current->hits[i]->white;
    if(current->hits[i]->free_edge == on_white) {
      bool found_anwser = opposite->free;
      // cout<<opposite->id<<" ";

      if(dfs(opposite,height,current_height + 1,temp_anwser)) {
        current->hits[i]->free_edge = !current->hits[i]->free_edge;
        temp_anwser.push_back(current->hits[i]);
        return true;
      }
      if(found_anwser && on_white && current_height == height - 1) {
        // cout<<"("<<opposite->id<<") ";
        current->hits[i]->free_edge = !current->hits[i]->free_edge;
        temp_anwser.push_back(current->hits[i]);
        return true;
      }
    }
  }
  return false;
}

int hopcroft_karp(vector <vector <Pawn*> > &pawns, vector <Pawn*> &black_pawns, int size) {
  vector <Edge*> final_anwser;
  vector <Edge*> temp_anwser;
  queue <Pawn*> pawn_queue;
  int height = 0;
  Pawn* current;

  while(true) {
    // print_free_edges(pawns);
    // cout<<"BFS:\n";
    if(!bfs(pawns,black_pawns,pawn_queue,height,size)) {
      break;
    }
    // cout<<"\nDFS:\n";
    while(!pawn_queue.empty()) {
      current = pawn_queue.front();
      pawn_queue.pop();
      // current->free = false;
      // cout<<current->id<<": ";
      dfs(current,height,0,temp_anwser);
      add_anwser(final_anwser,temp_anwser);
      // cout<<" TEMP: ";
      // print_anwser(temp_anwser);
      // cout<<endl;

      temp_anwser.clear();
    }
    // cout<<"FINAL:\n";
    // print_anwser(final_anwser);
    // cout<<endl;
  }

  // cout<<"FINAL:\n";
  // print_anwser(final_anwser);

  return final_anwser.size();
}

int main() {
  int N; //wymiar planszy
  int space; //dane pole
  int counter = 0; //licznik id

  cin>>N;

  vector <vector <Pawn*> > pawns(N);

  for(int i=0;i<N;++i) {
    for(int j=0;j<N;++j) {
      cin>>space;
      pawns[i].push_back(new Pawn(counter,space));
      ++counter;
    }
  }

  vector <Pawn*> black_pawns = make_graph(pawns, N);

  cout<<(N*N) - hopcroft_karp(pawns,black_pawns,N);

  return 0;
}