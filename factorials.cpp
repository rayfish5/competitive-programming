// 0 <= b < MOD
ll bpow(ll b, ll e) {
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
  fact[0] = fact_inv[0] = 1;
  for (int i = 1; i <= MAX_A; i++) {
    fact[i] = fact[i-1] * i % MOD;
    fact_inv[i] = inv(fact[i]);
  }
}
ll binom(int a, int b) {
  return fact[a] * fact_inv[b] % MOD * fact_inv[a-b] % MOD;
}
