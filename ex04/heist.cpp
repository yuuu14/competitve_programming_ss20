// remember to replace
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <cmath>

// change to cin
#define INPUT cin

typedef long long ll;
using namespace std;

// start comment
/*#include "../functions.hpp"
fstream file("test.in");
void generate_test(ll n, ll m) {
    ofstream file("test.in");
    file << n << " " << m << endl;
    for (ll i = 0; i < n; ++i) file << random<ll>(1, 32) << " ";
}*/
// end comment

template <class T>
void print_vector_(const std::vector<T>& v) {
    for (T e : v) std::cout << e << " ";
    std::cout << std::endl;
}

void function() {
    ll day, zw; // day~[1, 300000] zw~[1, 10] haus~[0, 32]
    INPUT >> day >> zw;
    vector<ll> haus;
    for (ll i = 0, tmp; i < day; ++i) {
        INPUT >> tmp;
        haus.emplace_back(tmp);
    }
    
    vector<ll> maxi, isin; // max; isin: larger than before or not
    for (ll i = 0, in = 0, mx = 0; i < zw; ++i) {
        if (haus[i] >= mx) { mx = haus[i]; in = 1; }
        else in = 0;
        isin.emplace_back(in);
        maxi.emplace_back(mx);
    }
    // to comment
    //for (auto &p : pr) { print_vector<ll>(p); }

    // maxi[i] = max {maxi[i-1], maxi[i-zw]+haus[i]}
    for (ll tg = zw; tg < day; ++tg) {
        if (maxi[tg-1] > maxi[tg-zw] + haus[tg]) {
            isin.emplace_back(0);
            maxi.emplace_back(maxi[tg-1]);
        }
        else {
            isin.emplace_back(1);
            maxi.emplace_back(maxi[tg-zw] + haus[tg]);
        }
    }

    vector<ll> res;
    for (ll idx = day-1; idx >= 0;) {
        if (isin[idx]) { res.emplace_back(idx+1); idx -= zw; }
        else --idx;
    }
    reverse(res.begin(), res.end());

    cout << maxi[day-1] << " " << res.size() << endl;
    print_vector_<ll>(res);
}


int main() {
    // to comment
    //generate_test(300000, 10);

    auto start = chrono::high_resolution_clock::now();
    function();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
    //cout << "Time taken: " << duration.count() << " microseconds" << endl;

    return 0;
}