const int MAX_N = 1e6;
vector<int> p; // primes
bool comp[MAX_N+1]; // initial assume prime
void sieve(int n) {
  for (int i = 2; i <= n; i++) {
    if (!comp[i]) p.push_back(i);
    for (int j = 0; j < p.size() && i * p[j] <= n; j++) {
      comp[i * p[j]] = true;
      if (i % p[j] == 0) break;
    }
  }
}
