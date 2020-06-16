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

// dijkstra
void func() {
    ll nd, bus, mtr, t;
    //n, b, m and t (2 ≤ n ≤ 100 000, 1 ≤ b, m ≤ 100 000, 0 ≤ t ≤ 10)
    INPUT >> nd >> bus >> mtr >> t;
    
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
