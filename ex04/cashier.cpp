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

#define INPUT cin

typedef long long ll;
using namespace std;


// remember to comment
//#include "../functions.hpp"
//fstream file("test.in");

int main() {
    ll chg, len;
    INPUT >> chg >> len;
    vector<ll> cur;
    for (ll i = 0, tmp; i < len; ++i) {
        INPUT >> tmp;
        if (tmp <= chg) cur.emplace_back(tmp);
    }
    len = (ll)cur.size();
    sort(cur.begin(), cur.end());
    // c[i, j] = min{ c[i-1, j], c[i, j-cur[i-1]]+1 }
    vector<vector<ll>> c(len+1, vector<ll> (chg+1, 0));
    for (ll i = 0; i <= chg; ++i) c[0][i] = __LONG_LONG_MAX__ - 1;

    for (ll chgs = 1; chgs <= chg; ++chgs) {
        for (ll coin = 1; coin <= len; ++coin) {
            if (chgs < cur[coin-1]) c[coin][chgs] = c[coin-1][chgs];
            else c[coin][chgs] = min(c[coin-1][chgs], c[coin][chgs-cur[coin-1]]+1);
        }
    }

    if (c[len][chg] == (__LONG_LONG_MAX__-1)) cout << "impossible\n";
    else cout << c[len][chg] << endl;
    

    return 0;
}