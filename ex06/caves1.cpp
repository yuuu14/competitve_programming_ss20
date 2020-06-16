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
    vector<ll> vals, circle;
    vector<vector<ll>> adj;
    map<ll, ll> cir_val;

public:
    Graph(ll V) { this->V = V; adj.resize(V); }
    void addVal(ll val) {vals.emplace_back(val); }
    void addEdge(ll u, ll v) { adj[u].emplace_back(v); }
    void rmCircle() {
        
    }
};

void func() {
    ll V, E;
    INPUT >> V >> E;
    Graph g(V);
    for (ll i = 0, val; i < V; ++i) { INPUT >> val; g.addVal(val); }
    for (ll i = 0, u, v; i < E; ++i) { INPUT >> u >> v; g.addEdge(u, v); }
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
