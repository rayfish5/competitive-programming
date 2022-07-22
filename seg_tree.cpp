#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

// WARNING: SegTree breaks if sets to 0 or negative numbers! (PushDown function and mod)
// To convert sum to min / max tree, modify ALL sm, pushup and query
const int MOD = 1e9+7;
const int V = 1<<18;
int n = 1<<17;
int si[V]; ll sm[V], mu[V], ad[V], st[V];
// call at start
void init() {
  fill(mu, mu + V, 1);
  for (int i = V - 1; i >= (V >> 1); i--) {
    si[i] = 1;
  }
  for (int i = (V >> 1) - 1; i > 0; i--) {
    si[i] = si[i << 1] + si[i << 1 | 1];
  }
}

void SetTag(int v, ll z) {
  sm[v] = si[v] * z; sm[v] %= MOD;
  st[v] = z;
  ad[v] = 0;
  mu[v] = 1;
}
void MulTag(int v, ll z) {
  sm[v] *= z; sm[v] %= MOD;
  mu[v] *= z; mu[v] %= MOD;
  ad[v] *= z; ad[v] %= MOD;
}
void AddTag(int v, ll z) {
  sm[v] += si[v] * z; sm[v] %= MOD;
  ad[v] += z; ad[v] %= MOD;
}
void PushDown(int v) {
  if (st[v]) SetTag(v << 1, st[v]), SetTag(v << 1 | 1, st[v]), st[v] = 0;
  if (mu[v] > 1) MulTag(v << 1, mu[v]), MulTag(v << 1 | 1, mu[v]), mu[v] = 1;
  if (ad[v]) AddTag(v << 1, ad[v]), AddTag(v << 1 | 1, ad[v]), ad[v] = 0;
}
void PushUp(int v) {
  sm[v] = (sm[v << 1] + sm[v << 1 | 1]) % MOD; // change if min / max tree
}

void Modify_Add(int x, int y, int z, int v = 1, int l = 1, int r = n) {
  if (x > r || y < l) return;
  if (x <= l && r <= y) {
    AddTag(v, z);
    return;
  }
  PushDown(v);
  int mid = (l + r) >> 1;
  Modify_Add(x, y, z, v << 1, l, mid);
  Modify_Add(x, y, z, v << 1 | 1, mid + 1, r);
  PushUp(v);
}
void Modify_Mul(int x, int y, int z, int v = 1, int l = 1, int r = n) {
  if (x > r || y < l) return;
  if (x <= l && r <= y) {
    MulTag(v, z);
    return;
  }
  PushDown(v);
  int mid = (l + r) >> 1;
  Modify_Mul(x, y, z, v << 1, l, mid);
  Modify_Mul(x, y, z, v << 1 | 1, mid + 1, r);
  PushUp(v);
}
void Modify_Set(int x, int y, int z, int v = 1, int l = 1, int r = n) {
  if (x > r || y < l) return;
  if (x <= l && r <= y) {
    SetTag(v, z);
    return;
  }
  PushDown(v);
  int mid = (l + r) >> 1;
  Modify_Set(x, y, z, v << 1, l, mid);
  Modify_Set(x, y, z, v << 1 | 1, mid + 1, r);
  PushUp(v);
}

ll Query(int x, int y, int v = 1, int l = 1, int r = n) {
  if (x > r || y < l) return 0;
  if (x <= l && r <= y) return sm[v];
  PushDown(v);
  int mid = (l + r) >> 1;
  return (Query(x, y, v << 1, l, mid) + Query(x, y, v << 1 | 1, mid + 1, r)) % MOD; // change if min / max tree
}
