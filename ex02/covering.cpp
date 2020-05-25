#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>
#define INPUT cin

using namespace std;

template <typename T>
bool contains(vector<T> A, vector<T> B);
pair<long, vector<int>> getset(string s);

int main() {
    fstream file("2.in");

    vector<pair<long, vector<int>>> sets;
    string s;
    auto start = chrono::high_resolution_clock::now();

    while (getline(INPUT, s)) {
        pair<long, vector<int>> newset(getset(s));
        for (auto &set : sets) {
            if (set.second.size() > newset.second.size()) {
                if (contains<int>(set.second, newset.second)) set.first++;
            }
            else if (set.second.size() < newset.second.size()) {
                if (contains<int>(newset.second, set.second)) newset.first++;
            }
            else if (set.second == newset.second) {
                set.first++;
                newset.first++;
            }
        }
        sets.push_back(newset);
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
    //cout << "Time taken: " << duration.count() << " microseconds" << endl;

    const auto p = minmax_element(sets.begin(), sets.end());
    cout << p.second->first << endl;
    //sort(sets.begin(), sets.end());
    //for (int i = 1; i <= sets.size() && i <= 10; ++i) cout << sets[sets.size()-i].first << " ";
    /*for (auto set : sets) {
        for (auto ele : set.second) cout << ele << " ";
        cout << "subsetnum: " << set.first << endl;
    }*/
    
    return 0;
}

pair<long, vector<int>> getset(string s) {
    string num("");
    vector<int> set;
    for (auto c : s) {
        if (!isdigit(c)) {
            if (!num.empty()) {
                int tmp = stoi(num);
                auto it = find(set.begin(), set.end(), tmp);
                if (it == set.end()) set.push_back(tmp);
                num.clear();
            }
        }
        else {
            num += c;
        }
    }
    sort(set.begin(), set.end());
    return {0, set};
}

template <typename T>
bool contains(vector<T> A, vector<T> B) {
    return includes(A.begin(), A.end(), B.begin(), B.end());
}

