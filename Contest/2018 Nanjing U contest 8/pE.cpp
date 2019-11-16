#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int arr[3][3];
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        char c;
        cin >> c;
        arr[i][j] = c - '0';
      }
    }
    while (n--) {
      string str;
      cin >> str;
      int *a, *b, *c, *d;
      switch (str[0]) {
        case '1':
          a = &arr[0][0];
          b = &arr[0][1];
          c = &arr[1][1];
          d = &arr[1][0];
          break;
        case '2':
          a = &arr[0][1];
          b = &arr[0][2];
          c = &arr[1][2];
          d = &arr[1][1];
          break;
        case '3':
          a = &arr[1][0];
          b = &arr[1][1];
          c = &arr[2][1];
          d = &arr[2][0];
          break;
        case '4':
          a = &arr[1][1];
          b = &arr[1][2];
          c = &arr[2][2];
          d = &arr[2][1];
          break;
      }
      if (str[1] == 'C') {
        auto tmp = *a;
        *a = *d, *d = *c, *c = *b, *b = tmp;
      } else {
        auto tmp = *a;
        *a = *b, *b = *c, *c = *d, *d = tmp;
      }
    }
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) cout << arr[i][j];
      cout << '\n';
    }
  }
}
