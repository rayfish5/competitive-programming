// To solve string matching, calculate borders of (pattern + "#" + string)
// Then find positions where border = |pattern|

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<int> border(const string& s) {
  int n = s.size();
  vector<int> bd (n);
  for (int i = 1, j = 0; i < n; i++) {
    while (j > 0 && s[j] != s[i]) {
      j = bd[j - 1];
    }
    if (s[j] == s[i]) j++;
    bd[i] = j;
  }
  return bd;
}
