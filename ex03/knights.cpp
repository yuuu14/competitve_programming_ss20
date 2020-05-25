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

struct rect {
    long long a, b, c, d;
    long long sq;
};

template <class T>
void print_vector(const std::vector<T>& v) {
    for (T e : v) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

bool compare_line(const rect &x, const rect &y) {
    if (x.c == y.c) return x.a < y.a;
    else return x.c < y.c;
}

bool compare_column(const rect &x, const rect &y) {
    if (x.d == y.d) return x.b < y.b;
    else return x.d < y.d;
}

int main() {
    fstream file("4.in");

    long long n;
    INPUT >> n;
    vector<long long> ln, col; // index of existing 0 
    vector<rect> shr;
    for (long long i = 0; i < n; ++i) {
        long long a, b, c, d;
        INPUT >> a >> b >> c >> d;
        rect tmp;
        tmp.a=a; tmp.b=b; tmp.c=c; tmp.d=d;
        tmp.sq = i;
        ln.emplace_back(i+1);
        col.emplace_back(i+1);
        shr.emplace_back(tmp);
    }

    // order by the rightmost element;
    
    map<long long, long long> line, column;

    sort(shr.begin(), shr.end(), compare_line);
    for (auto &elm : shr) {
        long long idx = lower_bound(ln.begin(), ln.end(), elm.a) - ln.begin();
        
        if (ln[idx] <= elm.c) {
            line.insert({elm.sq, ln[idx]});
            ln.erase(ln.begin()+idx);
        }
        else { cout << "NI\n"; return 0; }
    }
    
    sort(shr.begin(), shr.end(), compare_column);
    for (auto &elm : shr) {
        long long idx = lower_bound(col.begin(), col.end(), elm.b) - col.begin();
        if (col[idx] <= elm.d) {
            column.insert({elm.sq, col[idx]});
            col.erase(col.begin()+idx);
        }
        else { cout << "NI\n"; return 0; }
    }

    for (long long i = 0; i < n; ++i) {
        cout << line[i] << " " << column[i] << endl;
    }

    return 0;
}

