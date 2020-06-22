// compile (for debugging): g++ -Wall -Wextra -fsanitize=undefined,address -D_GLIBCXX_DEBUG -g <file>
// compile (as on judge): g++ -x c++ -Wall -O2 -static -pipe <file>
// Output file will be a.out in both cases
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <cmath>

using namespace std;

typedef long long ll;

#define debug(x) (cerr << #x << ": " << (x) << endl)

// change to cin
#define INPUT cin
fstream file("test.in");
// to comment
/*#include "../functions.hpp"
void generate_test() {
    ofstream file("test.in");
}*/

class UnionFind {
    vector<ll> parent, rank;
public:
    UnionFind(ll N) {
        rank.assign(N, 0);
        parent.resize(N);
        for (ll i = 0; i < N; ++i) parent[i] = i;
    }
    ll findSet(ll i) {
        if (parent[i] == i) return i;
        else return parent[i] = findSet(parent[i]);
    }
    void unionSet(ll i, ll j) {
        i = findSet(i), j = findSet(j);
        if (i != j) {
            if (rank[i] > rank[j]) parent[j] = i;
            else {
                parent[j] = i;
                if (rank[i] == rank[j]) rank[j]++;
            }
        }
    }
    bool isSameSet(ll u, ll v) { return findSet(u) == findSet(v); }
};

void func() {
    ll V, E;
    INPUT >> V >> E;
    auto UF = UnionFind(V);
    //vector<tuple<ll, ll, ll>> edges;
    multimap<ll, pair<ll, ll>, greater<ll>> edges;

    for (ll i = 0, u ,v, w; i < E; ++i) {
        INPUT >> u >> v >> w;
        //edges.emplace_back(w, u, v);
        edges.insert({w, {u, v}});
    }
    //sort(edges.begin(), edges.end(),
    //     [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) { return get<0>(a) > get<0>(b); });

    ll res = 0;
    for (auto e : edges) {
        ll u, v, w;
        //tie(w, u, v) = e;
        u = e.second.first, v = e.second.second, w = e.first;

        if (w >= 0 || !UF.isSameSet(u, v)) {
            res += w;
            UF.unionSet(u, v);
        }
    }

    cout << res << endl;
}

int main() {

    //generate_test();

    auto start = chrono::high_resolution_clock::now();
    func();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
    //cout << "Time taken: " << duration.count() << " microseconds" << endl;

    return 0;
}

/*
4 6
1 2 15
1 3 3
2 3 1
2 4 -1
3 4 -2
1 1 5

4 6
1 2 -4
1 3 -2
1 4 -3
2 4 -2
3 4 -5
2 4 -3
*/
