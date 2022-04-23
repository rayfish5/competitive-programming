#include <bits/stdc++.h>

// might have overflow errors :(
using namespace std;
typedef long long ll;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  // freopen(".in","r",stdin);
  // freopen(".out","w",stdout);
  int N, W; cin >> N >> W;
  vector<int> dp(W+1, INT_MIN / 2);
  dp[0] = 0;
  for (int i = 0; i < N; i++) {
    int w, v, k; cin >> v >> w >> k;
    for (int m = 0; m < w; m++) {
      // work on dp mod w, compress indices
      vector<int> f, g;
      for (int j = m; j <= W; j += w) {
        g.push_back(dp[j] - v * g.size());
      }
      // sliding window maximum on g, with size k + 1
      deque<int> mono;
      for (int t = 0; t < g.size(); t++) {
        if (t >= (k+1) && mono.front() == g[t-(k+1)]) mono.pop_front();
        while (!mono.empty() && mono.back() < g[t]) {
          mono.pop_back();
        }
        mono.push_back(g[t]);
        f.push_back(mono.front());
      }
      // update dp
      for (int t = 0; t < f.size(); t++) {
        dp[w * t + m] = f[t] + v * t;
      }
    }
  }
  int mv = -1;
  for (int val : dp) {
    mv = max(mv, val);
  }
  cout << mv << "\n";
}
