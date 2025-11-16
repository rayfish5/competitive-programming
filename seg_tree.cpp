struct SegTree {
  // 1-indexed, closed intervals
  // WARNING: SegTree breaks if sets to 0 or negative numbers! (PushDown function and mod)
  // To convert sum to min / max tree, modify func
  ll MOD;
  int *si, *l_end, *r_end; ll *val, *mult, *addt, *sett;
  // N = size of array
  SegTree(int N, ll MOD = (ll) 1e18) {
    N = 1 << (__lg(N - 1) + 1);
    int V = 2 * N;
    this->MOD = MOD;
    si = new int[V]{};
    l_end = new int[V]{};
    r_end = new int[V]{};
    val = new ll[V]{};
    mult = new ll[V]{};
    addt = new ll[V]{};
    sett = new ll[V]{};
    fill(mult, mult + V, 1);
    for (int i = V - 1; i >= (V >> 1); i--) {
      si[i] = 1;
      l_end[i] = r_end[i] = i - (N - 1);
    }
    for (int i = (V >> 1) - 1; i > 0; i--) {
      si[i] = si[i << 1] + si[i << 1 | 1];
      l_end[i] = l_end[i << 1];
      r_end[i] = r_end[i << 1 | 1];
    }
  }
  void settag(int v, ll z) {
    val[v] = si[v] * z; val[v] %= MOD;
    sett[v] = z;
    addt[v] = 0;
    mult[v] = 1;
  }
  void multag(int v, ll z) {
    val[v] *= z; val[v] %= MOD;
    mult[v] *= z; mult[v] %= MOD;
    addt[v] *= z; addt[v] %= MOD;
  }
  void addtag(int v, ll z) {
    val[v] += si[v] * z; val[v] %= MOD;
    addt[v] += z; addt[v] %= MOD;
  }
  void push_down(int v) {
    if (sett[v]) settag(v << 1, sett[v]), settag(v << 1 | 1, sett[v]), sett[v] = 0;
    if (mult[v] > 1) multag(v << 1, mult[v]), multag(v << 1 | 1, mult[v]), mult[v] = 1;
    if (addt[v]) addtag(v << 1, addt[v]), addtag(v << 1 | 1, addt[v]), addt[v] = 0;
  }
  ll func(ll x, ll y) {
    return (x + y) % MOD;
  }
  void push_up(int v) {
    val[v] = func(val[v << 1], val[v << 1 | 1]);
  }

  void modify_add(int x, int y, ll z, int v = 1) {
    if (x > r_end[v] || y < l_end[v]) return;
    if (x <= l_end[v] && r_end[v] <= y) {
      addtag(v, z);
      return;
    }
    push_down(v);
    modify_add(x, y, z, v << 1);
    modify_add(x, y, z, v << 1 | 1);
    push_up(v);
  }
  void modify_mul(int x, int y, ll z, int v = 1) {
    if (x > r_end[v] || y < l_end[v]) return;
    if (x <= l_end[v] && r_end[v] <= y) {
      multag(v, z);
      return;
    }
    push_down(v);
    modify_mul(x, y, z, v << 1);
    modify_mul(x, y, z, v << 1 | 1);
    push_up(v);
  }
  void modify_set(int x, int y, ll z, int v = 1) {
    if (x > r_end[v] || y < l_end[v]) return;
    if (x <= l_end[v] && r_end[v] <= y) {
      settag(v, z);
      return;
    }
    push_down(v);
    modify_set(x, y, z, v << 1);
    modify_set(x, y, z, v << 1 | 1);
    push_up(v);
  }

  ll query(int x, int y, int v = 1) {
    if (x > r_end[v] || y < l_end[v]) return 0;
    if (x <= l_end[v] && r_end[v] <= y) return val[v];
    push_down(v);
    return func(query(x, y, v << 1), query(x, y, v << 1 | 1));
  }
};
