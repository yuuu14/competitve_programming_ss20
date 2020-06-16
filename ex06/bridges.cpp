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

class Graph {
    ll V;
    vector<vector<ll>> adj;

    // parameters related to dfs
    ll ctr = 0, bdg = 0;
    const ll NIL = -1;
    vector<ll> dfs_min, dfs_num, dfs_prt;
    // dfs_num[v] : the timestamp at which v was explored
    // dfs_min[v] : the minimum dfs_num reachable from v using
    //      the directed Tree Edges and at most one Back Edge
    void dfs(ll u) {
        dfs_min[u] = dfs_num[u] = ctr++;
        for (auto v : adj[u]) {
            if (dfs_num[v] == NIL) {
                dfs_prt[v] = u;
                dfs(v);

                if (dfs_num[u] < dfs_min[v]) bdg++;
                dfs_min[u] = min(dfs_min[u], dfs_min[v]);
            }
            else if (v != dfs_prt[u]) 
                dfs_min[u] = min(dfs_min[u], dfs_num[v]); 
        }
    }

public:
    Graph(ll V) { 
        this->V = V; 
        adj.resize(V); 
        dfs_min.resize(V, NIL);
        dfs_num.resize(V, NIL);
        dfs_prt.resize(V, -1);
    }
    void addEdge(ll u, ll v) { 
        adj[u].emplace_back(v); 
        adj[v].emplace_back(u); 
    }
    ll bridge() {
        for (ll i = 0; i < V; ++i) {
            if (dfs_num[i] == NIL) dfs(i);
        }
        return bdg;
    }
};

void func() {
    ll V, edg, bdg;
    INPUT >> V >> edg;
    Graph g(V);
    for (ll i = 0, u, v; i < edg; ++i) {
        INPUT >> u >> v;
        g.addEdge(u-1, v-1);
    }
    cout << g.bridge() << endl;
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
5 5
1 2
2 3
2 4
3 4
4 5


4 4
1 2
2 3
3 4
4 1

4 3
1 2
2 3
3 4
*/