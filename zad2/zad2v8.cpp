#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Pawn;

struct Edge {
  Pawn* opposite;
  bool free_edge;

  Edge(){}
  Edge(Pawn* opposite) {
    this->opposite = opposite;
    free_edge = true;
  }
};

struct Pawn {
  int id;
  pair <int,int> position;
  int function;
  vector <Edge> hits;
  bool free;
  Pawn(){}
  Pawn(int id, int i, int j, int function) {
    this->id = id;
    this->function = function;
    position.first = i;
    position.second = j;
    free = true;
  }

  void add_edge(Pawn* opposite) {
    bool already_added = false;
    for(int i=0;i<hits.size();++i) {
      if(hits[i].opposite->id == opposite->id) {
        already_added = true;
        break;
      }
    }
    if(!already_added) {
      hits.push_back(Edge(opposite));
    }
  }
};

inline void add_anwser(vector <pair <int,int> > &final_anwser, vector <pair <int,int> > &temp_anwser) {
  bool no_duplicates = true;
  for(int i=0;i<temp_anwser.size();++i) {
    for(int j=0;j<final_anwser.size();++j) {
      if(final_anwser[j].first == temp_anwser[i].first && final_anwser[j].second == temp_anwser[i].second) {
        final_anwser.erase(final_anwser.begin()+j);
        j--;
        no_duplicates = false;
      }
    }
    if(no_duplicates) {
      final_anwser.push_back(temp_anwser[i]);
    }
  }
}

bool black_hit(vector <vector <Pawn> > &pawns, int y, int x, int size) {
  int reach_x, reach_y;
  bool connected = false;
  int attack_mode = pawns[y][x].function;
  if (attack_mode == 0) {
    return false;

    //atak o 3 na wprost lub o 2 na wprost i jedno w bok
  } else if (attack_mode == 1) {
    //o 3 na wprost
    reach_x = x + 3;
    reach_y = y;
    if(reach_x < size) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w gore
    reach_x = x + 2;
    reach_y = y - 1;
    if(reach_x < size && reach_y >= 0) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w dol
    reach_y = y + 1;
    if(reach_x < size && reach_y < size) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //atak o 1 na wprost lub o 1 w bok
  } else if (attack_mode == 2) {
    //o 1 na wprost
    reach_x = x + 1;
    reach_y = y;
    if(reach_x < size) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //o 1 w gore
    reach_x = x;
    reach_y = y - 1;
    if(reach_x < size && reach_y >= 0) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //o 1 w dol
    reach_y = y + 1;
    if(reach_y < size) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //atak o 1 na wprost lub o 2 na wprost i 1 w bok
  } else {
    //o 1 na wprost
    reach_x = x + 1;
    reach_y = y;
    if(reach_x < size) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }
    
    //o 2 na wprost i 1 w gore
    reach_x = x + 2;
    reach_y = y - 1;
    if(reach_x < size && reach_y >= 0) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w dol
    reach_y = y + 1;
    if(reach_x < size && reach_y < size) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }
  }
  return connected;
}

bool white_hit(vector <vector <Pawn> > &pawns, int y, int x, int size) {
  int reach_x, reach_y;
  bool connected = false;
  int attack_mode = pawns[y][x].function;
  if (attack_mode == 0) {
    return false;

    //atak o 3 na wprost lub o 2 na wprost i jedno w bok
  } else if (attack_mode == 1) {
    //o 3 na wprost
    reach_x = x - 3;
    reach_y = y;
    if(reach_x >= 0) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w gore
    reach_x = x - 2;
    reach_y = y - 1;
    if(reach_x >= 0 && reach_y >= 0) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w dol
    reach_y = y + 1;
    if(reach_x >= 0 && reach_y < size) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //atak o 1 na wprost lub o 1 w bok
  } else if (attack_mode == 2) {
    //o 1 na wprost
    reach_x = x - 1;
    reach_y = y;
    if(reach_x >= 0) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //o 1 w gore
    reach_x = x;
    reach_y = y - 1;
    if(reach_x >= 0 && reach_y >= 0) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //o 1 w dol
    reach_y = y + 1;
    if(reach_y < size) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //atak o 1 na wprost lub o 2 na wprost i 1 w bok
  } else {
    //o 1 na wprost
    reach_x = x - 1;
    reach_y = y;
    if(reach_x >= 0) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }
    
    //o 2 na wprost i 1 w gore
    reach_x = x - 2;
    reach_y = y - 1;
    if(reach_x >= 0 && reach_y >= 0) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }

    //o 2 na wprost i 1 w dol
    reach_y = y + 1;
    if(reach_x >= 0 && reach_y < size) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].add_edge(&pawns[reach_y][reach_x]);
        pawns[reach_y][reach_x].add_edge(&pawns[y][x]);
        connected = true;
      }
    }
  }
  return connected;
}

vector <Pawn*> make_graph(vector <vector <Pawn> > &pawns, int size) {
  vector <Pawn*> black_pawns;

  for(int i=0;i<size;++i) {
    for(int j=!(i&1);j<size;j+=2) {
      white_hit(pawns,i,j,size);
    }
  }

  for(int i=0;i<size;++i) {
    for(int j=i&1;j<size;j+=2) {
      if(black_hit(pawns,i,j,size)) {
        black_pawns.push_back(&pawns[i][j]);
      }
    }
  }
  return black_pawns;
}

bool bfs(vector <vector <Pawn> > &pawns, vector <Pawn*> &black_pawns, queue <Pawn*> &pawn_queue, int &height, int size) {
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

    for(int i=0;i<current->hits.size();++i) {
      if(current->hits[i].free_edge == on_black) {
        if(!visited[current->hits[i].opposite->id]) {
          visited[current->hits[i].opposite->id] = true;
          queue.push(current->hits[i].opposite);
          ++future_level_cap;
          if(current->hits[i].opposite->free) {
            pawn_queue.push(current->hits[i].opposite);
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

      if(found_any & on_black) {
        break;
      }
      found_any = false;
    }
  }
  height = current_height;
  return found_any;
}

bool dfs(Pawn* current, int &height, int current_height, vector <pair <int,int> > &temp_anwser) {
  if(height == current_height) {
    return false;
  }
  bool on_white = !(current_height & 1);

  for(int i=0;i<current->hits.size();++i) {
    if(current->hits[i].free_edge == on_white) {
      bool found_anwser = current->hits[i].opposite->free;

      if(dfs(current->hits[i].opposite,height,current_height + 1,temp_anwser) && current->hits[i].opposite->free) {
        current->free = false;
        current->hits[i].free_edge = !current->hits[i].free_edge;
        current->hits[i].opposite->hits[current->id].free_edge = !current->hits[i].opposite->hits[current->id].free_edge;

        pair <int,int> anwser;
        if(current->id > current->hits[i].opposite->id) {
          anwser.first = current->hits[i].opposite->id;
          anwser.second = current->id;
        } else {
          anwser.first = current->id;
          anwser.second = current->hits[i].opposite->id;
        }
        temp_anwser.push_back(anwser);
        return true;
      }
      if(found_anwser && on_white) {
        current->free = false;
        // cout<<current->id<<" -> "<<current->hits[i].opposite->id<<endl;

        pair <int,int> anwser;
        if(current->id > current->hits[i].opposite->id) {
          anwser.first = current->hits[i].opposite->id;
          anwser.second = current->id;
        } else {
          anwser.first = current->id;
          anwser.second = current->hits[i].opposite->id;
        }
        temp_anwser.push_back(anwser);
        return true;
      }
    }
  }
  return false;
}

int hopcroft_karp(vector <vector <Pawn> > &pawns, vector <Pawn*> &black_pawns, int size) {
  vector <pair <int,int> > final_anwser;
  vector <pair <int,int> > temp_anwser;
  queue <Pawn*> pawn_queue;
  int height = 0;
  Pawn* current;

  while(true) {
    if(!bfs(pawns,black_pawns,pawn_queue,height,size)) {
      break;
    }
    cout<<"Q: "<<pawn_queue.size()<<endl;
    while(!pawn_queue.empty()) {
      current = pawn_queue.front();
      pawn_queue.pop();

      dfs(current,height,0,temp_anwser);
      for(int i=0;i<black_pawns.size();++i) {
        if(black_pawns[i]->free) {
          cout<<black_pawns[i]->id<<" ";
        }
      }
      cout<<endl;
    }
    cout<<"TEMP:"<<endl;
    for(int i=0;i<temp_anwser.size();++i) {
      cout<<temp_anwser[i].first<<"-"<<temp_anwser[i].second<<" ";
    }
    add_anwser(final_anwser,temp_anwser);
    temp_anwser.clear();
  }
  cout<<endl<<"FINAL:"<<endl;
    for(int i=0;i<final_anwser.size();++i) {
      cout<<final_anwser[i].first<<"-"<<final_anwser[i].second<<" ";
    }


  return final_anwser.size();
}

int main() {
  int N; //wymiar planszy
  int space; //dane pole
  int counter = 0; //licznik id

  cin>>N;

  vector <vector <Pawn> > pawns(N);

  for(int i=0;i<N;++i) {
    for(int j=0;j<N;++j) {
      cin>>space;
      pawns[i].push_back(Pawn(counter,i,j,space));
      ++counter;
    }
  }

  vector <Pawn*> black_pawns = make_graph(pawns,N);

  cout<<(N*N) - hopcroft_karp(pawns,black_pawns,N);

  return 0;
}