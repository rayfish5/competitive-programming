struct SparseTable {
  ll** _st;
  function<ll(ll, ll)> comp;

  SparseTable(vector<ll>& arr, bool is_min) {
    int n = arr.size();
    int h = __lg(n);
    _st = new ll*[h + 1];
    for (int i = 0; i <= h; i++) {
      _st[i] = new ll[n] {};
    }
    if (is_min) {
      comp = [](ll a, ll b) { return min(a, b); };
    } else {
      comp = [](ll a, ll b) { return max(a, b); };
    }

    for (int j = 0; j < n; j++) {
        _st[0][j] = arr[j];
    }
    for (int i = 1; i <= h; i++) {
        for (int j = 0; j + (1<<i) <= n; j++) {
            _st[i][j] = comp(_st[i-1][j], _st[i-1][j + (1<<(i-1))]);
        }
    }
  }
  // 0-indexed, [l, r)
  ll query(int l, int r) {
    int p = __lg(r-l);
    return comp(_st[p][l], _st[p][r-(1<<p)]);
  }
};
