// compile (for debugging): g++ -Wall -Wextra -fsanitize=undefined,address -D_GLIBCXX_DEBUG -g <file>
// compile (as on judge): g++ -x c++ -Wall -O2 -static -pipe <file>
// Output file will be a.out in both cases
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <map>
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

//#include "../functions.hpp"

void generate_test() {
    ofstream file("test.in");
}

void func() {
    ios::sync_with_stdio(false);
    ll h, w, H, W;
    INPUT >> h >> w;
    vector<vector<int>> tray;
    for (ll i = 0; i < h; ++i) {
        vector<int> tmpv;
        for (ll j = 0, tmp; j < w; ++j) { INPUT >> tmp; tmpv.emplace_back(tmp); }
        tray.emplace_back(tmpv);
    }
    INPUT >> H >> W;
    


}

int main() {
    /*
    generate_test();
    fstream file("test.in");
    */

    auto start = chrono::high_resolution_clock::now();
    func();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
    //cout << "Time taken: " << duration.count() << " microseconds" << endl;

    return 0;
}
