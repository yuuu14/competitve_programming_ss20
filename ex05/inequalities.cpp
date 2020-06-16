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

/*class Graph {
    ll vtx;
    vector<vector<ll>> adj;

public:
    Graph(ll size) { vtx = size; adj.resize(size); }
    void addEdge(ll u, ll v) { adj[u].emplace_back(v); }
};*/

// topological sort
void func() {
    // no circle
    ll n;
    INPUT >> n;
    map<string, ll> var;
    map<ll, vector<ll>> adj;
    map<ll, ll> in_degree;
    ll V = 0; // number of vertex
    for (ll i = 0, u, v; i < n; ++i) {
        string a, islg, b;
        INPUT >> a >> islg >> b;
        if (var.count(a)) u = var[a];
        else { u = V++; var.insert({a, u}); }
        if (var.count(b)) v = var[b];
        else { v = V++; var.insert({b, v}); }
        if (islg == "<") swap(u, v);
        if (adj.count(u)) adj[u].emplace_back(v);
        else adj.insert({u, vector<ll>(1, v)});

        if (!in_degree.count(u)) in_degree.insert({u, 0});
        if (!in_degree.count(v)) in_degree.insert({v, 1});
        else ++in_degree[v];
    }

    // topo sort
    queue<ll> q;
    for (ll i = 0; i < V; ++i) 
        if (in_degree[i] == 0) q.push(i);
    
    ll cnt = 0; // count of visited vertex
    vector<ll> topo_order;

    while (!q.empty()) {
        ll fr = q.front();
        q.pop();
        topo_order.emplace_back(fr);

        for (auto &nb : adj[fr]) 
            if (--in_degree[nb] == 0) q.push(nb);
        
        cnt++;
    }

    // circle exits
    if (cnt != V) { cout << "impossible\n"; return; }
    else cout << "possible\n";
    // swap key and value in var
    map<ll, string> var_;
    for (auto &p : var) var_.insert({p.second, p.first});
    for (auto &elm : topo_order) cout << var_[elm] << " ";
    cout << endl;
    return;
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

/* Test case:
3
a > b
b > c
a < c

3
theta > omega
omega > alpha
theta > alpha

*/