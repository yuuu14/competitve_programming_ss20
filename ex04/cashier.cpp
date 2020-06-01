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


// remember to comment
/*#include "../functions.hpp"
fstream file("test.in");
void generate_test(ll c, ll n) {
    ofstream file("test.in");
    file << c << " " << n << endl;
    for (ll i = 0; i < n; ++i) file << random<ll>(1, 100000) << " ";
}
*/

int main() {
    // to comment
    //generate_test(100000, 500);

    ll chg, len;
    INPUT >> chg >> len;
    vector<ll> cur;
    for (ll i = 0, tmp; i < len; ++i) {
        INPUT >> tmp;
        if (tmp <= chg) cur.emplace_back(tmp);
    }
    if (chg == 0) { cout << "0\n"; return 0; }

    len = (ll)cur.size();
    sort(cur.begin(), cur.end());

    //auto start = chrono::high_resolution_clock::now();
    // c[i, j] = min{ c[i-1, j], c[i, j-cur[i-1]]+1 }
    vector<vector<ll>> c(len+1, vector<ll> (chg+1, 0));
    for (ll i = 0; i <= chg; ++i) c[0][i] = (ll)10e+6;

    /*for (ll chgs = 1; chgs <= chg; ++chgs) {
        for (ll coin = 1; coin <= len; ++coin) {
            if (chgs < cur[coin-1]) c[coin][chgs] = c[coin-1][chgs];
            else c[coin][chgs] = min(c[coin-1][chgs], c[coin][chgs-cur[coin-1]]+1);
        }
    }*/

    // !remember the storage of 2d vector
    for (ll coin = 1; coin <= len; ++coin) {
        for (ll chgs = 1; chgs <= chg; ++chgs) {
            if (chgs < cur[coin-1]) c[coin][chgs] = c[coin-1][chgs];
            else c[coin][chgs] = min(c[coin-1][chgs], c[coin][chgs-cur[coin-1]]+1);
        }
    }

    //auto stop = chrono::high_resolution_clock::now();
    //auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
    //cout << "Time taken: " << duration.count() << " microseconds" << endl;

    if (c[len][chg] == (ll)10e+6) cout << "impossible\n";
    else cout << c[len][chg] << endl;

    return 0;
}