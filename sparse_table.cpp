const int MAX_N = 1<<19;
const int LOG_N = 20;
ll stmax[LOG_N][MAX_N];
ll stmin[LOG_N][MAX_N];

void build_st(vector<ll>& arrmax, vector<ll>& arrmin, int n) {
    int h = __lg(n);
    for (int j = 0; j < n; j++) {
        stmax[0][j] = arrmax[j];
        stmin[0][j] = arrmin[j];
    }
    for (int i = 1; i <= h; i++) {
        for (int j = 0; j + (1<<i) <= n; j++) {
            stmax[i][j] = max(stmax[i-1][j], stmax[i-1][j + (1<<(i-1))]);
            stmin[i][j] = min(stmin[i-1][j], stmin[i-1][j + (1<<(i-1))]);
        }
    }
}
// 0-indexed, [l, r)
ll r_max(int l, int r) {
    int p = __lg(r-l);
    return max(stmax[p][l], stmax[p][r-(1<<p)]);
}
ll r_min(int l, int r) {
    int p = __lg(r-l);
    return min(stmin[p][l], stmin[p][r-(1<<p)]);
}
