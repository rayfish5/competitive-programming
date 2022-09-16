struct BIT {
  int n;
  vector<ll> arr;
  // BIT with only 0's
  BIT(int _n) : n(_n) { arr = vector<ll>(n + 1); }
  // 1-indexed
  void update(int i, ll inc) {
    for (; i <= n; i += (i & -i)) arr[i] += inc;
  }
  // prefix sum
  ll psum(int i) {
    ll s = 0;
    for (; i > 0; i -= (i & -i)) s += arr[i];
    return s;
  }
};
