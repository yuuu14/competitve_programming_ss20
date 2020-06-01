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

// remember to comment
//#include "functions.hpp"

using namespace std;

template <class T>
void print_vector(const std::vector<T>& v) {
    for (T e : v) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

int main() {
    fstream file("4.in");

    long long n;
    INPUT >> n;
    vector<long long> ln, col; // index of existing 0
    multimap<long long, pair<long long, long long>> shrln, shrcol;
    // order by the rightmost element;
    for (long long i = 0; i < n; ++i) {
        long long a, b, c, d;
        INPUT >> a >> b >> c >> d;
        shrln.emplace(c, make_pair(a, i));
        shrcol.emplace(d, make_pair(b, i));
        ln.emplace_back(i+1);
        col.emplace_back(i+1);
    }
    
    map<long long, long long> line, column;
    auto l = shrln.begin();
    auto c = shrcol.begin();
    for (; l != shrln.end() && c != shrcol.end(); ++l, ++c) {
        long long idxl = lower_bound(ln.begin(), ln.end(), l->second.first) - ln.begin();
        long long idxc = lower_bound(col.begin(), col.end(), c->second.first) - col.begin();
        if ((idxl < n && ln[idxl] <= l->first) && (idxc < n && col[idxc] <= c->first)) {
            line.insert(l->second.second, ln[idxl]);
            ln.erase(ln.begin()+idxl);
            column.insert(c->second.second, col[idxc]);
            col.erase(col.begin()+idxc);
        }
        else { cout << "NI\n"; return 0; }
    }

    for (long long i = 0; i < n; ++i)
        cout << line[i] << " " << column[i] << endl;
    
    return 0;
}

