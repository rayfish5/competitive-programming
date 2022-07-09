#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

// nodes numbered 1 - n
bool dfs(int cur, int n, vector<int>* adj, bool* vis, int* match) {
  if (vis[cur]) return false;
  vis[cur] = true;
  for (auto nxt : adj[cur]) if (!match[nxt] || dfs(match[nxt], n, adj, vis, match)) {
    match[nxt] = cur;
    return true;
  }
  return false;
}
int max_matching(int n, vector<int>* adj) {
  int match[n+1] {}; // for right nodes
  bool vis[n+1];
  int max_match = 0;
  for (int left = 1; left <= n; left++) {
    fill_n(vis, n+1, false);
    max_match += dfs(left, n, adj, vis, match);
  }
  return max_match;
}
