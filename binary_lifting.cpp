// 2^jth ancestor of node i
// 1-indexed
const int MAX_N = 1<<18;
const int LOG_N = 18;
int lift[MAX_N][LOG_N];

void build_blift(vi& par) {
  for (int i = 2; i < par.size(); i++) lift[i][0] = par[i];
  for (int i = 1; i < par.size(); i++) {
    for (int j = 1; j < LOG_N; j++) {
      lift[i][j] = lift[lift[i][j-1]][j-1];
    }
  }
}
