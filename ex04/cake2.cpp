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
fstream file("test.in");
// comment
/*#include "../functions.hpp"
void generate_test() {
    ofstream file("test.in");
    ll h, w, H, W;
    h = random<ll>(1, 1E+5);
    w = 15E+6 / h;
    H = random<ll>(1, h);
    W = random<ll>(1, w);
    file << h << " " << w << endl;
    for (ll i = 0; i < h; ++i) {
        for (ll j = 0; j < w; ++j) file << random<int>(0, 2) << " ";
        file << endl;
    }
    file << H << " " << W << endl;
}*/

void func() {
    ios::sync_with_stdio(false);
    ll h, w, H; // h, w~[1, 10E+5], hw~[1, 15*10E+6]
    INPUT >> h >> w;
    vector<vector<int>> hist(1, vector<int>(w, 1));
    for (ll i = 0, tmp; i < w; ++i) {
        INPUT >> tmp;
        hist[0][i] -= tmp; 
    }
    for (ll i = 1; i < h; ++i) {
        vector<int> tmpv;
        for (ll j = 0, tmp; j < w; ++j) { 
            INPUT >> tmp;
            if (tmp) tmp = 0;
            else tmp = hist[i-1][j] + 1;
            tmpv.emplace_back(tmp);
        }
        tmpv.emplace_back(-1); // sentinel
        hist.emplace_back(tmpv);
    }
    INPUT >> H;

    // must be sequential
    ll bri, brj, W = 0; //bottom right
    for (ll i = 0; i < h; ++i) {
        for (ll j = 0, len = 0; j < w+1; ++j) {
            if (hist[i][j] < H) {
                if (len > W) { W = len; bri = i; brj = j-1; }
                len = 0;
            }
            else ++len;
        }
    }
    if (W)
        cout << bri-H+2 << " " << brj-W+2 << " "<< bri+1 << " " << brj+1 << endl;
    else cout << "-1 -1 -1 -1\n";
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
test case:
5 4
1 0 0 1
1 1 0 0
1 0 0 0
1 0 0 0
1 1 1 1
3 2


6 5
0 0 0 0 0
1 0 0 0 1
0 0 0 0 0
0 0 0 0 0
0 1 0 0 0
0 0 0 0 0
3


4 4
1 1 1 1
1 0 0 1
1 0 0 1
1 1 1 1
3
*/