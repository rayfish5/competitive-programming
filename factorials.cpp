ll bpow(ll b, ll e) {
  b %= MOD;
  ll res = 1;
  while (e > 0) {
    if (e & 1) res = res * b % MOD;
    b = b * b % MOD;
    e >>= 1;
  }
  return res;
}
ll inv(ll x) {
  return bpow(x, MOD-2);
}

const int MAX_A = 1e6;
vector<ll> fact (MAX_A+1);
vector<ll> fact_inv (MAX_A+1);

void setup() {
  fact[0] = 1;
  for (int i = 1; i <= MAX_A; i++) {
    fact[i] = fact[i-1] * i % MOD;
  }
  fact_inv[MAX_A] = inv(fact[MAX_A]);
  for (int i = MAX_A; i > 0; i--) {
    fact_inv[i-1] = fact_inv[i] * i % MOD;
  }
}
ll binom(int a, int b) {
  return fact[a] * fact_inv[b] % MOD * fact_inv[a-b] % MOD;
}
