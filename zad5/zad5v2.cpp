#include <iostream>
using namespace std;

inline void parse_char(char &character) {
  if (character >= 97 && character <=122) {
    character = 'a';
  } else if(character >= 65 && character <=90) {
    character = 'A';
  } else if (character >= 48 && character <=57) {
    character = '0';
  } else if (character == ' ') {
    character = ' ';
  } else if (character == '.' || character == '?' || character == '!' || character == ',' || character == ';' || character == ':' || character == '-'){
      character = '.';
    }
}

int* make_pre_suf_arr(char* &pattern, int &size) {
  int l = 0, i = 1;
  int* pre_suf_arr = new int[size];
  pre_suf_arr[0] = 0;
  while(i !=  size) {
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

bool find_pattern(char* &text, char* &pattern, int &t_size, int &p_size) {
  int l = 0, i = 0, j = 0;
  int* pre_suf_arr = make_pre_suf_arr(pattern,p_size);
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

void resize(char* &arr, int &size) {
  char* new_arr = new char[size+100000];
  for(int i=0;i<size;++i) {
    new_arr[i] = arr[i];
  }
  delete[] arr;
  size+=100000;
  arr = new_arr;
}

int main() {
  char* pattern, *text;
  char character;
  int text_size = 0, pattern_size = 0;
  int max_size = 100000;
  pattern = new char[max_size];
  //wczytanie wzorca
  character = getchar();
  while(character != '\n') {
    parse_char(character);
    pattern[pattern_size] = character;
    ++pattern_size;
    if(pattern_size == max_size) {
      resize(pattern,max_size);
    }
    character = getchar();
  }

  text = new char[max_size];
  //wczytanie tekstu
  character = getchar();
  while(character != '\n') {
    parse_char(character);
    text[text_size] = character;
    ++text_size;
    if(text_size == max_size) {
      resize(text,max_size);
    }
    character = getchar();
  }

  if(find_pattern(text,pattern,text_size,pattern_size)) {
    cout<<"T";
  } else {
    cout<<"N";
  }

  return 0;
}