#include <iostream>
using namespace std;

/*
  algorytm knutha-morrisa-pratta - szukanie wzorcow

  przy wpisywaniu warto od razu parsowac - zamieniac znaki na Aa0.

  I. stworzenie tablicy prefixo sufiksow O(wielkosc_wzorca) - niby najtrudniejsze
  II. wykorzystanie

  sytuacje przy pierwszym kroku:
  - takie same znaki
  - rozne znaki:
    - pomocnicza zmienna jest 0
    - pomocnicza zmienna nie jest 0

  1. 
  ps[0] = l = 0   <- l to pomocnicza zmienna
  ps.size = |M| = |wzorzec|
  i = 1

  inicjalizacja dla wzorca p = AABBAAA:
  0xxxxxx

  2. petla
    a) jezeli p[l] == p[i] to l++, aktualizacja ps[i] = l i przechodze do kolejnego kroku iteracji
    b) jezeli p[l] != p[i] i:
      b') l > 0 to l = ps[l-1]
      b'') l == 0 to ps[i] = l; i dalsza iteracja

(p - pattern)
  Przyklad z wzorcem p = AABBAAA:
  1. ps: 0xxxxxx, l=0, i=1
  2. p[0] == p[1], l++ ps: 01xxxxx, i++ -> i=2
    p[1] == p[2], l>0->Tak l=ps[1-1]=ps[0]=0
    p[0] == p[2], l>0->Nie ps[i]=l=0 ps: 010xxxx, i++ -> i=3
    p[0] == p[3], l>0->Nie ps[i]=l=0 ps: 0100xxx, i++ -> i=4
    p[0] == p[4], l++ ps: 01001xx, i=5
    p[1] == p[5], l++, ps: 010012x, i=6
    ps[2] == p[6], l>0, l=ps[1]=1
    p[1] == p[6], l++, ps: 0100122, i=7==|M|

    i juz mamy tablice prefiksow sufiksow

    teraz porownujemy tekst ze wzorcem - zlozonosc to przejscie po tekscie tylko

    i=0,j=0 - iteracja po tekscie i po wzorcu

    a) text[i] == pattern[j] -> i++, j++ - jedynie musimy sprawdzac czy nie wyszlismy za wzorzec
     - if j == |pattern| to koniec algorytmu i zwrocenie T lub i == |text| to zwrocenie N
    b) text[i] != pattern[j]:
      b') j > 0 -> j = ps[j-1], i
      b'') j == 0 -> j, i++

*/

inline void parse_char(char &character) {
  if (character >= 97 && character <=122) {
    character = 'a';
  } else if(character >= 65 && character <=90) {
    character = 'A';
  } else if (character >= 48 && character <=57) {
    character = '0';
  } else if (character == ' ') {
    character = ' ';
  } else {
    character = '.';
  }
}

int* make_pre_suf_arr(string &pattern) {
  int l = 0, i = 1, p_size = pattern.size();
  int* pre_suf_arr = new int(p_size);
  pre_suf_arr[0] = 0;
  while(i !=  p_size) {
    if(pattern[l] == pattern[i]) {
      ++l;
      pre_suf_arr[i] = l;
      ++i;
    } else {
      if(l > 0) {
        l = pre_suf_arr[l-1];
      } else if (l == 0) {
        pre_suf_arr[i] = l;
        ++i;
      }
    }
  }
  return pre_suf_arr;
}

bool find_pattern(string &text, string &pattern) {
  int l = 0, i = 0, j = 0, p_size = pattern.size(), t_size = text.size();
  int* pre_suf_arr = make_pre_suf_arr(pattern);
  while(i < t_size && j < p_size) {
    if(text[i] == pattern[j]) {
      ++i; ++j;
    } else {
      if(j > 0) {
        j = pre_suf_arr[j-1];
      } else if (j == 0) {
        ++i;
      }
    }
  }
  if(j == p_size) {
    return true;
  } else {
    return false;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.tie(nullptr);

  string pattern, text;
  char character;
  //wczytanie wzorca
  character = getchar();
  while(character != '\n') {
    parse_char(character);
    pattern += character;
    character = getchar();
  }

  //wczytanie tekstu
  character = getchar();
  while(character != '\n') {
    parse_char(character);
    text += character;
    character = getchar();
  }
  // cout<<pattern<<endl;
  // cout<<text<<endl;

  if(find_pattern(text,pattern)) {
    cout<<"T";
  } else {
    cout<<"N";
  }

  return 0;
}