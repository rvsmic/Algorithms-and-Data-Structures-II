#include <iostream>
using namespace std;

// funkcja na sprawdzarce jest dodana wiec to jest tylko do przykladu
// double butelka(double cm) {
// 	return 10 - (cm-2) * (cm-2);
// }

double calculate_aquarium_volume(int x,int y,int z) {
  return x * y * z;
}

double calculate_bottle_volume(double j) {
  int regions_count = 1000;
  double b,step = j / regions_count;
  double heights_pow_total = 0;
  for(int i=0;i<regions_count;++i) {
    b = butelka(i * step);
    heights_pow_total += b * b;
  }
  return heights_pow_total / regions_count * 3.14 * j;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.tie(nullptr);
  int x,y,z; // rozmiary akwarium
  double p; // stopien wypelnienia naczynia
  int n; // ilosc butelek
  double j; // wysokosc do ktorej jest wypelnione naczynie

  cin>>x>>y>>z;
  cin>>p;
  double max_volume = calculate_aquarium_volume(x,y,z);
  double start_volume = max_volume * p;
  double bottle_volume;
  int counter = 0;
  bool fail = false;
  cin>>n;
  for(int i=0;i<n;++i) {
    cin>>j;
    if(!fail) {
      bottle_volume = calculate_bottle_volume(j);
    }
    start_volume += bottle_volume;
    if(start_volume > max_volume) {
      fail = true;
    } else {
      ++counter;
    }
  }
  if(fail) {
    cout<<counter+1;
  } else {
    cout<<"NIE";
  }

  return 0;
}