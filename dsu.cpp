// Nodes numbered 0 to N - 1
struct DSU {
    // stores negation of size if root, parent if not
    vector<int> p;
    DSU(int num_nodes) {
        p = vector<int>(num_nodes, -1);
    }
    
    int get(int n) {
        return p[n] < 0 ? n : p[n] = get(p[n]);
    }
    bool same_set(int a, int b) {
        return get(a) == get(b);
    }
    int size(int n) {
        return -p[get(n)];
    }
    bool unite(int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b)
            return false;
        if (p[a] > p[b])
            swap(a, b);
        p[a] += p[b];
        p[b] = a;
        return true;
    }
};
