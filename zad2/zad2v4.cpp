#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct Pawn {
  int id;
  int function;
  bool free;
  vector <int> hits;
  map <int,bool> edge_taken;

  Pawn(){}
  Pawn(int id, int function) {
    this->id = id;
    this->function = function;
    free = true;
  }
};

//testowe
void print_graph(vector <Pawn*> pawns) {
  for(int i=0;i<pawns.size();++i) {
    cout<<pawns[i]->id<<": ";
    for(int j=0;j<pawns[i]->hits.size();++j) {
      cout<<pawns[i]->hits[j]<<" ";
    }
    cout<<endl;
  }
}
void print_anwer(vector <pair<int,int> > anwser) {
  for(int i=0;i<anwser.size();++i) {
    cout<<anwser[i].first<<"-"<<anwser[i].second<<" ";
  }
  cout<<endl;
}

inline void update_anwser(vector <pair <int,int> > &final_anwser, vector <pair <int,int> > &temp_anwser) {
  bool duplicate = false;
  for(int i=0;i<temp_anwser.size();++i) {
    for(int j=0;j<final_anwser.size();++j) {
      if(temp_anwser[i].first == final_anwser[j].first && temp_anwser[i].second == final_anwser[j].second) {
        final_anwser.erase(final_anwser.begin() + j);
        --j;
        duplicate = true;   //nie dziala cholerka
        break;
      }
    }
    if(!duplicate) {
      final_anwser.push_back(temp_anwser[i]);
    }
    duplicate = false;
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
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
        connected = true;
      }
    }

    //o 2 na wprost i 1 w gore
    reach_x = x + 2;
    reach_y = y - 1;
    if(reach_x < size && reach_y >= 0) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
        connected = true;
      }
    }

    //o 2 na wprost i 1 w dol
    reach_y = y + 1;
    if(reach_x < size && reach_y < size) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
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
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
        connected = true;
      }
    }

    //o 1 w gore
    reach_x = x;
    reach_y = y - 1;
    if(reach_x < size && reach_y >= 0) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
        connected = true;
      }
    }

    //o 1 w dol
    reach_y = y + 1;
    if(reach_y < size) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
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
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
        connected = true;
      }
    }
    
    //o 2 na wprost i 1 w gore
    reach_x = x + 2;
    reach_y = y - 1;
    if(reach_x < size && reach_y >= 0) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
        connected = true;
      }
    }

    //o 2 na wprost i 1 w dol
    reach_y = y + 1;
    if(reach_x < size && reach_y < size) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
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
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
        connected = true;
      }
    }

    //o 2 na wprost i 1 w gore
    reach_x = x - 2;
    reach_y = y - 1;
    if(reach_x >= 0 && reach_y >= 0) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
        connected = true;
      }
    }

    //o 2 na wprost i 1 w dol
    reach_y = y + 1;
    if(reach_x >= 0 && reach_y < size) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
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
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
        connected = true;
      }
    }

    //o 1 w gore
    reach_x = x;
    reach_y = y - 1;
    if(reach_x >= 0 && reach_y >= 0) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
        connected = true;
      }
    }

    //o 1 w dol
    reach_y = y + 1;
    if(reach_y < size) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
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
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
        connected = true;
      }
    }
    
    //o 2 na wprost i 1 w gore
    reach_x = x - 2;
    reach_y = y - 1;
    if(reach_x >= 0 && reach_y >= 0) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
        connected = true;
      }
    }

    //o 2 na wprost i 1 w dol
    reach_y = y + 1;
    if(reach_x >= 0 && reach_y < size) {
      if(pawns[reach_y][reach_x].function != 0) {
        pawns[y][x].hits.push_back(pawns[reach_y][reach_x].id);
        pawns[y][x].edge_taken[pawns[reach_y][reach_x].id] = false;
        connected = true;
      }
    }
  }

  return connected;
}

bool bfs(vector <vector <Pawn> > &all_pawns, vector <Pawn*> &black_pawns, queue <int> &pawn_queue, int &height, int size) {
  vector <bool> visited(size * size,false);
  queue <int> queue;
  bool found_any = false;
  int current_height = 0;

  //dodanie do kolejki tylko wolnych czarnych wierzcholkow
  for(int i=0;i<black_pawns.size();++i) {
    if(black_pawns[i]->free) {
      // black_pawns[i]->id = 0;
      // cout<<black_pawns[i]->id<<" ";
      queue.push(black_pawns[i]->id);
      visited[black_pawns[i]->id] = true;
    }
  }

  Pawn* current;
  int level_size = queue.size();
  int new_level_size = 0;
  int size_counter = 0;

  while(!queue.empty()) {
    current = &all_pawns[queue.front() / size][queue.front() % size];
    queue.pop();
    ++size_counter;
    // cout<<current->id<<": ";
    //jestesmy na czarnym i przegladamy biale piony
    bool on_black = !(current_height & 1);
    //przejrzenie bitych pionow
    for(int i=0;i<current->hits.size();++i) {
      //jezeli krawedz jest zgodna z zasadami algorytmu (naprzemienna)
      if(on_black == !current->edge_taken[current->hits[i]]) {
        //jezeli jeszcze nieodwiedzony to dodajemy do kolejki
        if(!visited[current->hits[i]]) {
          visited[current->hits[i]] = true;
          queue.push(current->hits[i]);
          ++new_level_size;
          if(all_pawns[current->hits[i] / size][current->hits[i] % size].free) {
            // cout<<current->hits[i]<<" ";
            // current->edge_taken[current->hits[i]] = true;
            // all_pawns[current->hits[i] / size][current->hits[i] % size].edge_taken[current->id] = true;
            found_any = true;
            pawn_queue.push(current->hits[i]);
          }
        }
      }
    }
    // cout<<endl;

    if(size_counter == level_size) {
      // cout<<"^ HEIGHT: "<<current_height<<endl;
      level_size = new_level_size;
      new_level_size = 0;
      size_counter = 0;
      //schodzimy glebiej
      ++current_height;
      //jezeli juz znalezlismy wolnego piona na tamtym poziomie
      if(on_black && found_any) {
        break;
      }
      found_any = false;
    }
  }
  height = current_height;

  return found_any;
}

bool dfs(vector <vector <Pawn> > &all_pawns, int current_id, vector <pair <int,int> > &temp_anwser, int current_height, int &height, int size) {
  //warunek na przerwanie
  if(height == current_height) {
    return false;
  }
  int y = current_id / size;
  int x = current_id % size;
  Pawn* current = &all_pawns[y][x];
  bool on_white = !(current_height & 1);
  bool found_anwser = false;
  // cout<<current->id<<" ";
  for(int i=0;i<current->hits.size();++i) {
    // cout<<current->hits[i]<<"? ";
    //sciezka naprzemienna - zaczyna od wolnej
    if(on_white == !current->edge_taken[current->hits[i]]) {
      // cout<<"OK";
      //zamiana zajecia krawedzi na przeciwna (dla obu stron tej krawedzi)
      current->edge_taken[current->hits[i]] = !current->edge_taken[current->hits[i]];
      all_pawns[current->hits[i] / size][current->hits[i] % size].edge_taken[current->id] = !all_pawns[current->hits[i] / size][current->hits[i] % size].edge_taken[current->id];
      //zapis czy nastepny wierzcholek byl wolny
      found_anwser = all_pawns[current->hits[i] / size][current->hits[i] % size].free;
      //zajecie wierzcholka
      // all_pawns[current->hits[i] / size][current->hits[i] % size].free = false;
      //zejscie glebiej
      if(dfs(all_pawns,current->hits[i],temp_anwser,current_height + 1,height,size)) {
        int smaller, bigger;
        if(current->id > current->hits[i]) {
          smaller = current->hits[i];
          bigger = current->id;
        } else {
          smaller = current->id;
          bigger = current->hits[i];
        }
        pair <int,int> temp;
        temp.first = smaller;
        temp.second = bigger;
        temp_anwser.push_back(temp);
        current->free = false;
        return true;
      }
      //jezeli znaleziono juz odpowiedz
      if(found_anwser) {
        // cout<<" -> "<<current->hits[i];
        int smaller, bigger;
        if(current->id > current->hits[i]) {
          smaller = current->hits[i];
          bigger = current->id;
        } else {
          smaller = current->id;
          bigger = current->hits[i];
        }
        pair <int,int> temp;
        temp.first = smaller;
        temp.second = bigger;
        temp_anwser.push_back(temp);
        current->free = false;
        return true;
      }
    }
  }
  return false;
}

int hopcroft_karp(vector <vector <Pawn> > &all_pawns, vector <Pawn*> &black_pawns, int size) {
  vector <pair <int,int> > final_anwser;
  vector <pair <int,int> > temp_anwser;
  queue <int> pawn_queue;
  int height = 0;
  int current_id;

  while(true) {
    // cout<<"BFS:"<<endl;
    if(!bfs(all_pawns,black_pawns,pawn_queue,height,size)) {
      break;
    }
    // cout<<"DFS:"<<endl;
    while(!pawn_queue.empty()) {
      current_id = pawn_queue.front();
      pawn_queue.pop();
      dfs(all_pawns,current_id,temp_anwser,0,height,size);
      // cout<<endl;
    }
    update_anwser(final_anwser,temp_anwser);
    // cout<<"ANWSER:"<<endl;
    // print_anwer(temp_anwser);
    temp_anwser.clear();
  }
  cout<<"FINAL ANWSER:"<<endl;
  print_anwer(final_anwser);

  return (size*size) - final_anwser.size();
}

inline void max_left_pawns(vector <vector <Pawn> > &pawns, int size) {
  vector <Pawn*> black_pawns;
  vector <Pawn*> white_pawns;
  int counter = 0;

  //przejscie po szachownicy po czarnych polach, sprawdzenie atakow i stworzenie grafu dwudzielnego
  for(int i=0;i<size;++i) {
    for(int j= i&1 ;j<size;j+=2) {
      if(black_hit(pawns,i,j,size)) {
        black_pawns.push_back(&pawns[i][j]);
        ++counter;
      }
    }
  }

  for(int i=0;i<size;++i) {
    for(int j= !(i&1) ;j<size;j+=2) {
      if(white_hit(pawns,i,j,size)) {
        white_pawns.push_back(&pawns[i][j]);
      }
    }
  }
  // cout<<graph.size();
  cout<<"BLACK:"<<endl;
  print_graph(black_pawns);
  cout<<endl;
  cout<<"WHITE:"<<endl;
  print_graph(white_pawns);

  //algorytm hopkroft-karp na grafie
  cout<<hopcroft_karp(pawns,black_pawns,size);

  black_pawns.clear();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.tie(nullptr);

  int N; //wymiar szachownicy
  int counter = 0; //licznik id
  int space; //wartosc danego pola

  cin>>N;

  vector <vector <Pawn> > pawns(N);

  for(int i=0;i<N;++i) {
    for(int j=0;j<N;++j) {
      cin>>space;
      pawns[i].push_back(Pawn(counter,space));
      counter++;
    }
  }

  max_left_pawns(pawns,N);

  return 0;
}