#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>

//#include "functions.hpp"

#define INPUT cin

using namespace std;

int main() {
    fstream file("2.in");

    long long num, x;
    vector<long long> s1, s2;
    INPUT >> num >> x;
    for (long long i = 0; i < num/2; ++i) {
        long long tmp;
        INPUT >> tmp;
        s1.push_back(tmp);
    }
    for (long long i = num/2; i < num; ++i) {
        long long tmp;
        INPUT >> tmp;
        s2.push_back(tmp);
    }
    if (num % 2) s1.push_back(1e+14); // get the same size
    
    // print_vector(s1); print_vector(s2);
    vector<int> sub;
    vector<long long> sum1, sum2;
    sum1.push_back(0); sum2.push_back(0);
    for (long long i = 0; i < s1.size(); ++i) sub.push_back(0);
    for (long long i = 0; i < sub.size(); ++i) {
        sub[sub.size()-1-i] = 1;
        
        do {
            long long tmp1 = 0, tmp2 = 0;
            for (long long k = 0; k < sub.size(); ++k) {
                tmp1 += sub[k] * s1[k];
                tmp2 += sub[k] * s2[k];
            }
            sum1.push_back(tmp1);
            sum2.push_back(tmp2);

        } while (next_permutation(sub.begin(), sub.end()));
    }

    sort(sum1.begin(), sum1.end()); sort(sum2.begin(), sum2.end());
    //print_vector(sum1); print_vector(sum2);
    long long res = 0, size = (num%2 == 0 ? sum1.size() : sum1.size()/2);
    for (long long i = 0; i < size; ++i) {
        // find (x - sum1[i]) in sum2
        // res += count(sum2.begin(), sum2.end(), x-sum1[i]);
        if (binary_search(sum2.begin(), sum2.end(), x-sum1[i])) {
            res += upper_bound(sum2.begin(), sum2.end(), x-sum1[i]) - lower_bound(sum2.begin(), sum2.end(), x-sum1[i]);
        }
    }
    cout << res << endl;
    


}