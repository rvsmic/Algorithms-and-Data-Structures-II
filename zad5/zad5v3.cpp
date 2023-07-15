#include <iostream>
using namespace std;

// funkcja do parsowania pojedynczego znaku do schematu z zadania
inline void parse_char(char &character) {
  if (character >= 97 && character <= 122) {
    character = 'a';
  } else if (character >= 65 && character <= 90) {
    character = 'A';
  } else if (character >= 48 && character <= 57) {
    character = '0';
  } else if (character == ' ') {
    character = ' ';
  } else if (character == '.' || character == '?' || character == '!' || character == ',' || character == ';' || character == ':' || character == '-') {
    character = '.';
  }
}


// funkcja tworzaca tablice prefiksow-sufiksow wg schematu
int* make_pre_suf_arr(string &pattern) {
  int l = 0, i = 1, p_size = pattern.size();
  int* pre_suf_arr = new int[p_size];
  pre_suf_arr[0] = 0;
  while (i != p_size) {
    if (pattern[l] == pattern[i]) {
      ++l;
      pre_suf_arr[i] = l;
      ++i;
    } else {
      if (l > 0) {
        l = pre_suf_arr[l-1];
      } else if (l == 0) {
        pre_suf_arr[i] = l;
        ++i;
      }
    }
  }
  return pre_suf_arr;
}

// funkcja szukajaca schematu w tekscie - nie da sie pobrac normalnie ze wzgledu na limity pamieciowe na najwiekszych testach
bool find_pattern(string &pattern) {
  int j = 0, p_size = pattern.size();
  // tablica prefiksow-sufiksow
  int* pre_suf_arr = make_pre_suf_arr(pattern);
  // czytanie znak po znaku tekstu i porownywanie ze schematem
  char text_character;
  cin.get(text_character);
  parse_char(text_character);
  while (text_character != '\n' && j < p_size) {
    if (text_character == pattern[j]) {
      if (++j == p_size) {
        break;
      }
      cin.get(text_character);
      parse_char(text_character);
    } else {
      if(j > 0) {
        j = pre_suf_arr[j-1];
      } else if (j == 0) {
        cin.get(text_character);
        parse_char(text_character);
      }
    }
  }
  delete[] pre_suf_arr;
  // jak znalezlismy podciag to j doszlo do konca schematu
  if (j == p_size) {
    return true;
  } else {
    return false;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.tie(nullptr);

  string pattern;
  //wczytanie wzorca
  getline(cin,pattern);

  if (find_pattern(pattern)) {
    cout<<"T";
  } else {
    cout<<"N";
  }

  return 0;
}