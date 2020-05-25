#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cstring>
#include <fstream>
#include <numeric>
#define INPUT cin

using namespace std;

long long parser(string);
bool is_num(string);

int main() {
    // write a parser
    ifstream file("1.in");
    long long to_sumup = 0;
    string s;
   
    while (getline(INPUT, s)) to_sumup += parser(s);
    //cout << "Result: ";
    cout << to_sumup << endl;
    return 0;
}

/* to parse to given tree and return its value */
long long parser(string tree) {  
    if (is_num(tree)) {
        return (long long)stoi(tree);
    }
    vector<long long> subtree;

    long lpn = 0, rpn = 0; // num of left/right parenthesis
    string stree("");
    for (unsigned int i = 1; i < tree.size(); ++i) {
        if (tree[i] == '(') {
            lpn++;
            if (lpn-rpn != 1) stree += '(';
        }
        else if (tree[i] == ')') {
            rpn++;
            if (lpn-rpn <= 1) {
                stree = lpn-rpn == 0? stree: stree + ')';
                if (lpn-rpn == 0 && stree.empty()) break;
                long long stree_res = parser(stree);
                subtree.push_back(stree_res);
                stree.erase();
            }
            else stree += ')';
        }
        else if (tree[i] == ',' && (lpn-rpn == 1)) {
            if (stree.empty()) continue; // important!!! if having multiple subtree
            long long stree_res = parser(stree);
            subtree.push_back(stree_res);
            stree.erase();
        }
        else stree += tree[i];
    }
    long long res;
    if (tree[0] == '*') {
        res = 1;
        for (auto it = subtree.begin(); it != subtree.end(); ++it) res *= *it;
    }
    else {
        res = 0;
        res = accumulate(subtree.begin(), subtree.end(), (long long)0);
    }
    return res;
}

bool is_num(string s) {
    for (unsigned int i = 0; i < s.size(); ++i)
        if (!isdigit(s[i])) return false;
    return true;
}