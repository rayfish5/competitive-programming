struct HashedString {
  vector<ll> pow {1};
  vector<ll> p_hash;
  const ll M;
  const ll P;
  HashedString(const string& s, ll m, ll p) : p_hash(s.size()+1), M(m), P(p) {
    while (pow.size() <= s.size()) {
      pow.push_back((pow.back() * P) % M);
    }
    p_hash[0] = 0;
    for (int i = 0; i < s.size(); i++) {
      p_hash[i+1] = ((p_hash[i] * P) % M + s[i]) % M;
    }
  }
  // 0-indexed, closed interval
  ll get_hash(int b, int e) {
    ll raw_val = p_hash[e+1] - p_hash[b] * pow[e-b+1];
    return (raw_val % M + M) % M;
  }
};
