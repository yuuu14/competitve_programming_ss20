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
    ll n, x;
    n = random<ll>(1, 2E+5);
    x = random<ll>(0, 1E+9);
    file << n << " " << x << endl;
    for (ll i = 0; i < n; ++i) file << random<ll>(1, 1E+9) << " ";
}*/

void LIS() {
    ll n, x; // n~[1, 2E+5], x~[0, 1E+9], t~[1, 1E+9]
    INPUT >> n >> x;

    vector<ll> tail(n, 0);
    ll fst, lgth = 1; INPUT >> fst; tail[0] = fst;
    for (ll i = 1, tmp; i < n; ++i) { 
        INPUT >> tmp;
        auto it = lower_bound(tail.begin(), tail.begin()+lgth, tmp);
        
        if (it == tail.begin() + lgth) tail[lgth++] = tmp;
        else *it = tmp;
    }
    cout << lgth << endl;
}

int main() {

    //generate_test();

    auto start = chrono::high_resolution_clock::now();
    LIS();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
    //cout << "Time taken: " << duration.count() << " microseconds" << endl;

    return 0;
}
