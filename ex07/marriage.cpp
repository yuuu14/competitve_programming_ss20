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
};

class Tree {
    ll N; // number of nodes
    vector<vector<ll>> adj;
    vector<set<ll>> query;
    vector<pair<ll, ll>> qry_id;
    vector<ll> level, ancestor;
    vector<bool> visited;

    map<string, ll> id;
    map<ll, string> names;
    map<pair<ll, ll>, pair<ll, ll>> qry;

    UnionFind UF;

public:
    Tree(ll N) : UF(N) {
        this->N = N;
        adj.resize(N), query.resize(N), level.resize(N, -1), ancestor.resize(N);
        for (ll i = 0; i < N; ++i) ancestor[i] = i;
        visited.assign(N, false);
    }
    void addName(string name, ll i) {
        id.insert({name, i});
        names.insert({i, name});
    }
    void buildTree() {
        string name;
        for (ll i = 1; i < N; ++i) {
            INPUT >> name;
            adj[id[name]].emplace_back(i);
        }
    }
    void addQuery(string name1, string name2) {
        query[id[name1]].insert(id[name2]);
        query[id[name2]].insert(id[name1]);
        ll id1 = id[name1], id2 = id[name2];
        if (id1 > id2) swap(id1, id2);
        qry.insert({{id1, id2}, {-1, -1}}); // each query is unique
        qry_id.emplace_back(id1, id2);
    }
    void print_names() {
        for (auto i : names) cout << i.first << " " << i.second << endl;
    }
    void print_tree() {
        for (ll i = 0; i < N; ++i) {
            cout << i << " -> ";
            for (auto v : adj[i]) cout << v << " ";
            cout << endl;
        }
    }
    void dfs(ll u) {
        for (auto v : adj[u]) {
            dfs(v);
            UF.unionSet(u, v);
            ancestor[UF.findSet(u)] = u;
        }
        visited[u] = true;
        for (auto v : query[u]) {
            if (visited[v]) {
                ll id1 = u, id2 = v, lca = ancestor[UF.findSet(v)];
                if (id1 > id2) swap(id1, id2);
                qry[{id1, id2}].first = lca;
                qry[{id1, id2}].second = level[id1] + level[id2] - 2 * level[lca];
            }
        }
    }
    
    void distance() {
        queue<pair<ll ,ll>> q;
        q.push({0, 0});

        while (!q.empty()) {
            auto fr = q.front();
            q.pop();
            level[fr.first] = fr.second;

            for (auto n : adj[fr.first]) q.push({n, fr.second+1});
        }
    }

    ll findLevel(ll r, ll k, ll level) {
        if (r == k) return level;
        if (adj[r].size() == 0) return -1;
        ll res = -1;
        for (auto child : adj[r]) {
            res = findLevel(child, k, level+1);
            if (res != -1) break;
        }
        return res;
    }
    void output() {
        /*for (auto &q : qry) {
            //if (level[q.first.first] == -1) level[q.first.first] = findLevel(0, q.first.first, 0);
            //if (level[q.first.second] == -1) level[q.first.second] = findLevel(0, q.first.second, 0);
            //if (level[q.second.first] == -1) level[q.first.second] = findLevel(0, q.second.first, 0);
            //q.second.second = level[q.first.first] + level[q.first.second] - 2 * level[q.second.first];
            q.second.second = findLevel(q.second.first, q.first.first, 0) + findLevel(q.second.first, q.first.second, 0);
        }*/
        for (auto q : qry_id) 
            cout << names[qry[q].first] << " " << qry[q].second << endl;
    }
};

void func() {
    
    ll n, q;
    INPUT >> n >> q;
    Tree tree(n);

    string name, name_;
    for (ll i = 0; i < n; ++i) {
        INPUT >> name;
        tree.addName(name, i);
    }
    tree.buildTree();
    for (ll i = 0; i < q; ++i) {
        INPUT >> name >> name_;
        tree.addQuery(name, name_);
    }
    //tree.print_names();
    //tree.print_tree();
    tree.distance();
    tree.dfs(0);
    tree.output();
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
6 4
Gertrude Annegret Elisabeth Lea Jule Dieter
Gertrude Gertrude Elisabeth Annegret Annegret
Dieter Jule
Dieter Annegret
Dieter Lea
Jule Gertrude
*/