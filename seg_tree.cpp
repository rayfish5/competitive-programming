// 1-indexed, closed intervals
// WARNING: SegTree breaks if sets to 0 or negative numbers! (PushDown function and mod)
// To convert sum to min / max tree, modify val and Func

const int V = 1<<18; // 2 * N
const int N = 1<<17; // smallest power of two at least array size

int si[V], l_end[V], r_end[V]; ll val[V], mult[V], addt[V], sett[V];
// call at start
void init() {
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

void SetTag(int v, ll z) {
  val[v] = si[v] * z; val[v] %= MOD;
  sett[v] = z;
  addt[v] = 0;
  mult[v] = 1;
}
void MulTag(int v, ll z) {
  val[v] *= z; val[v] %= MOD;
  mult[v] *= z; mult[v] %= MOD;
  addt[v] *= z; addt[v] %= MOD;
}
void AddTag(int v, ll z) {
  val[v] += si[v] * z; val[v] %= MOD;
  addt[v] += z; addt[v] %= MOD;
}
void PushDown(int v) {
  if (sett[v]) SetTag(v << 1, sett[v]), SetTag(v << 1 | 1, sett[v]), sett[v] = 0;
  if (mult[v] > 1) MulTag(v << 1, mult[v]), MulTag(v << 1 | 1, mult[v]), mult[v] = 1;
  if (addt[v]) AddTag(v << 1, addt[v]), AddTag(v << 1 | 1, addt[v]), addt[v] = 0;
}
ll Func(ll x, ll y) {
  return (x + y) % MOD;
}
void PushUp(int v) {
  val[v] = Func(val[v << 1], val[v << 1 | 1]);
}

void Modify_Add(int x, int y, ll z, int v = 1, int l = 1, int r = N) {
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
void Modify_Mul(int x, int y, ll z, int v = 1, int l = 1, int r = N) {
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
void Modify_Set(int x, int y, ll z, int v = 1, int l = 1, int r = N) {
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

ll Query(int x, int y, int v = 1, int l = 1, int r = N) {
  if (x > r || y < l) return 0;
  if (x <= l && r <= y) return val[v];
  PushDown(v);
  int mid = (l + r) >> 1;
  return Func(Query(x, y, v << 1, l, mid), Query(x, y, v << 1 | 1, mid + 1, r));
}
