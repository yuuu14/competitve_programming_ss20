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

class Graph { // DAG
    ll V, E; // V ~ [2, 1E+5]
    vector<vector<ll>> adj;
    vector<ll> degree, out; // out, in

public:
    Graph(ll V, ll E) { 
        this->V = V;
        this->E = E;
        adj.resize(V);
        degree.resize(V, 0);
        out.resize(V, 0);
    }
    void addEdge(ll u, ll v) { 
        adj[u].emplace_back(v);
        degree[u]++; out[u]++;
        degree[v]--;
    }
    bool hasEulerPath() {
        if (degree[0] == 1 && degree[V-1] == -1) {
            for (ll i = 1; i < V-1; ++i) if (degree[i]) return false;

            // add n -> 1
            adj[V-1].emplace_back(0);
            out[V-1]++;
            //for (auto v : adj) { for (auto e : v) cout << e << " "; cout << endl; } 
            
            // Hierholz's Alg : find Euler circuit
            stack<ll> cur_path;
            vector<ll> circuit; // in reverse order
            ll cur_v = 0;
            cur_path.push(cur_v);
            
            while (!cur_path.empty()) {
                if (out[cur_v]) {
                    cur_path.push(cur_v);

                    ll nxt_v = adj[cur_v].back();
                    out[cur_v]--;
                    adj[cur_v].pop_back();

                    cur_v = nxt_v;
                }
                else {
                    circuit.emplace_back(cur_v);

                    // backtracking
                    cur_v = cur_path.top();
                    cur_path.pop();
                }
            }
            //for (auto v : circuit) cout << v << " "; cout << endl;

            if ((ll)circuit.size()-2 == E) return true;
            else return false;
        }
        else return false;
    } 
};

void func() {
    ll V, edg;
    INPUT >> V >> edg;
    Graph g(V, edg);
    for (ll i = 0, u, v; i < edg; ++i) {
        INPUT >> u >> v;
        g.addEdge(u-1, v-1);
    }
    if (g.hasEulerPath()) cout << "POSSIBLE\n";
    else cout << "IMPOSSIBLE\n";
    
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
3 3
1 2
2 1
1 3

3 3
1 2
2 1
2 3

4 4
1 2
2 1
3 4
4 3

2 5
1 2
2 1
1 2
2 1
1 2
*/