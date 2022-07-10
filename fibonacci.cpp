#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
using Matrix = array<array<ll, 2>, 2>;

const ll MOD = 1e9+7;

Matrix mul(Matrix a, Matrix b) {
  Matrix res = {{{0, 0}, {0, 0}}};
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      for(int k = 0; k < 2; k++) {
        res[i][j] += a[i][k] * b[k][j];
        res[i][j] %= MOD;
      }
    }
  }
  return res;
}

ll fib(ll n) {
  Matrix ans = {{{1,0}, {0,1}}};
  Matrix mplier = {{{1,1}, {1,0}}};
  // use n's binary representation
  for (; n > 0; n /= 2, mplier = mul(mplier, mplier)) {
    if (n & 1) ans = mul(ans, mplier);
  }
  return ans[0][1];
}
