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

// comment
/*#include "../functions.hpp"
void generate_test() {
    ofstream file("test.in");
    ll n, m, s, d;
    n = random<ll>(2, 1E+5);
    m = random<ll>(1, 1E+6);
    s = random<ll>(1, n);
    d = random<ll>(1, n);
    file << n << " " << m << " " << s << " " << d << endl;
    for (ll i = 0, u, v; i < m; ++i) {
        u = random<ll>(1, n);
        v = random<ll>(1, n);
        file << u << " " << v << endl;
    } 
}*/

// bfs
void func() {
    ll nd, edg, inf, dst;
    // – n (2 ≤ n ≤ E+5 ), the number of nodes in the social graph
    // – m (1 ≤ m ≤ E+6 ), the number of edges in the social graph
    // – s (1 ≤ s ≤ n), the newly infected person
    // – d (1 ≤ d ≤ n), the distance we are interested in

    INPUT >> nd >> edg >> inf >> dst;
    //vector<ll> adj[nd];
    //vector<ll> *adj = new vector<ll>[nd];
    vector<vector<ll>> adj(nd);
    vector<int> it(nd, 0);
    ++it[inf-1];

    for (ll i = 0, u, v; i < edg; ++i) {
        INPUT >> u >> v;
        adj[u-1].emplace_back(v-1);
        adj[v-1].emplace_back(u-1);
    }
    queue<pair<ll, ll>> q;
    q.push({inf-1, dst});

    while (!q.empty()) {
        auto fr = q.front();
        q.pop();

        if (fr.second) {
            for (auto &nb : adj[fr.first]) {
                if (!it[nb]) {
                    q.push({nb, fr.second-1});
                    ++it[nb];
                }
            }
        }
    }
    
    ll res = 0;
    for (auto &elm : it) if (elm) ++res;
    cout << res << endl;

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

/*
test
6 5 2 3
2 4
4 3
3 1
1 5
4 6

5 10 5 1
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
4 5

9 10 4 3
1 2
2 3
1 7
2 4
3 4
4 7
7 8
9 7
7 6
5 6
*/
