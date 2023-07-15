#include <iostream>
using namespace std;

void parse_text(string &text) {
  for(int i=0;i<text.size();++i) {
    if (text[i] >= 97 && text[i] <= 122) {
      text[i] = 'a';
    } else if(text[i] >= 65 && text[i] <= 90) {
      text[i] = 'A';
    } else if (text[i] >= 48 && text[i] <= 57) {
      text[i] = '0';
    } else if (text[i] == ' ') {
      text[i] = ' ';
    } else if (text[i] == '.' || text[i] == '?' || text[i] == '!' || text[i] == ',' || text[i] == ';' || text[i] == ':' || text[i] == '-') {
      text[i] = '.';
    }
  }
}

int* make_pre_suf_arr(string &pattern) {
  int l = 0, i = 1, p_size = pattern.size();
  int* pre_suf_arr = new int[p_size];
  pre_suf_arr[0] = 0;
  while(i != p_size) {
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
  delete[] pre_suf_arr;
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
  //wczytanie wzorca i tekstu
  getline(cin,pattern);
  getline(cin,text);
  parse_text(text);

  if(find_pattern(text,pattern)) {
    cout<<"T";
  } else {
    cout<<"N";
  }

  return 0;
}