const int MAX_N = 1<<18;
const int LOG_N = 19;
ll st1[LOG_N][MAX_N];
ll st2[LOG_N][MAX_N];

void build(vector<ll>& arr1, vector<ll>& arr2, int n) {
    int h = floor(log2(n));
    for (int j = 0; j < n; j++) {
        st1[0][j] = arr1[j];
        st2[0][j] = arr2[j];
    }
    for (int i = 1; i <= h; i++) {
        for (int j = 0; j + (1<<i) <= n; j++) {
            st1[i][j] = max(st1[i-1][j], st1[i-1][j + (1<<(i-1))]);
            st2[i][j] = min(st2[i-1][j], st2[i-1][j + (1<<(i-1))]);
        }
    }
}
// 0-indexed, [l, r)
ll r_max1(int l, int r) {
    int p = 31 - __builtin_clz(r-l);
    return max(st1[p][l], st1[p][r-(1<<p)]);
}
ll r_min2(int l, int r) {
    int p = 31 - __builtin_clz(r-l);
    return min(st2[p][l], st2[p][r-(1<<p)]);
}
