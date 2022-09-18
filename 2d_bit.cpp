struct BIT {
  static const int MAX_N = 1005, MAX_M = 1005;
  int n, m;
  ll arr[MAX_N][MAX_M];
  // BIT with only 0's
  BIT(int _n, int _m) : n(_n), m(_m) {}
  // 1-indexed
  void update(int i, int j, ll inc) {
    for (; i <= n; i += (i & -i)) {
      for (int _j = j; _j <= m; _j += (_j & -_j)) {
        arr[i][_j] += inc;
      }
    }
  }
  // prefix sum
  ll psum(int i, int j) {
    ll s = 0;
    for (; i > 0; i -= (i & -i)) {
      for (int _j = j; _j > 0; _j -= (_j & -_j)) {
        s += arr[i][_j];
      }
    }
    return s;
  }
  ll rectsum(int i1, int j1, int i2, int j2) {
    return psum(i2, j2) - psum(i1 - 1, j2) - psum(i2, j1 - 1) + psum(i1 - 1, j1 - 1);
  }
};
