#include <iostream>
using namespace std;

// funkcja na sprawdzarce jest dodana wiec to jest tylko do przykladu
// double butelka(double cm) {
// 	return 10 - (cm-2) * (cm-2);
// }

// (yi^2 + yj^2 + yk^2...) * pi * pole calki
// te y to sa wysokosci prostokatow w calce - suma promieni na tych wysokosciach jakby - objetosc fig obrotowej

// czy lepiej wszystko wczytac czy od razu - dzielimy najwiekszy przedzial na wspolne np. 20 czy kazdy przedzial na swoje 20

// przyklad:
/*
  obj butelek:
  512,12 771,22 971,26 1018,23 213,01
  iteracja po objetosciach i sprawdzanie czy juz przekroczylismy naczynie - jak pasuje to dokladamy ja
  w przykladzie wychodzi ze po 3 sie przepelni
*/

double calculate_aquarium_volume(int x,int y,int z) {
  return x * y * z;
}

double calculate_bottle_volume(double j) {
  int regions_count = 1000;
  double a, b,step = j / regions_count;
  double heights_pow_total = 0;
  b = butelka(0);
  for(int i=1;i<regions_count;++i) {
    a = b;
    b = butelka(i * step);
    heights_pow_total += a * a;
  }
  heights_pow_total += b*b;
  return heights_pow_total/regions_count * 3.14 * j;
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
      // cout<<"B "<<bottle_volume<<endl;
    }
    start_volume += bottle_volume;
    // cout<<"S "<<start_volume<<endl;
    if(start_volume > max_volume) {
      // cout<<"! "<<counter;
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