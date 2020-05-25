#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <cmath>
#include <numeric>

#define INPUT cin

using namespace std;

int main() {
    fstream file("3.in");

    long long n, q;
    INPUT >> n >> q;
    long long size = ceil(sqrt(n));
    vector<long long> ori, comp;

    for (long long i = 0, odd = 0, tmp = 0; i < n; ++i) {
        INPUT >> tmp;
        tmp = tmp % 2;
        if (tmp) ++odd;
        ori.push_back(tmp);
        if ((i+1)%size == 0 || i+1 == n) {
            comp.push_back(odd);
            odd = 0;
        }
    }

    for (long long i = 0, a = 0, b = 0; i < q; ++i) {
        char qry;
        INPUT >> qry >> a >> b;
        if (qry == 'U') {
            // ori[a] --> b
            b = b%2 ? 1 : 0;
            if (ori[a-1] != b) {
                comp[(a-1)/size] += b - ori[a-1];
                ori[a-1] = b;
            }
        }
        else {
            long long res = 0;
            --a; --b;
            long long l = (a/size+1)*size-1, u = b/size * size;
            if (l > u) for (long long j = a; j != b+1; ++j) res += ori[j];
            else {
                for (long long j = a; j <= l; ++j) res += ori[j];
                for (long long j = (l+1)/size; j < u/size; ++j) res += comp[j];
                for (long long j = u; j <= b; ++j) res += ori[j];
            }
            cout << res << endl;

        }
    }
}