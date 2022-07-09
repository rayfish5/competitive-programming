#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

// nodes numbered 1 - n
bool dfs(int cur, vector<int>* adj, bool* vis, int* match) {
  if (vis[cur]) return false;
  vis[cur] = true;
  for (auto nxt : adj[cur]) if (!match[nxt] || dfs(match[nxt], adj, vis, match)) {
    match[nxt] = cur;
    return true;
  }
  return false;
}
int max_matching(int l_cnt, int r_cnt, vector<int>* adj) {
  int match[r_cnt+1] {}; // for right nodes
  bool vis[l_cnt+1];
  int max_match = 0;
  for (int left = 1; left <= l_cnt; left++) {
    fill_n(vis, l_cnt+1, false);
    max_match += dfs(left, adj, vis, match);
  }
  return max_match;
}
