#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>

#define INPUT cin

using namespace std;

int main() {
    fstream file("1.in");
    long long num = 0;

    INPUT >> num;
    long long gain = 0;
    multimap<long long, long long> profit;
    for (long long c = 0, a = 0; num != 0; --num) {
        INPUT >> c >> a;
        if (c < a) { profit.insert({c, a}); gain += a - c; }
    }
    long long sum = profit.begin()->second, init = profit.begin()->first;
    for (auto i = next(profit.begin(), 1); i != profit.end(); ++i) {
        if (i->first > sum) init += i->first - sum;
        sum += i->second - i->first;
    }
    /*for (auto const& p : profit) {
        if (p.first > max) init += p.first - max;
        if (p.second > max) max = p.second;
    }*/
    cout << init << " " << gain << endl;

    return 0;
}