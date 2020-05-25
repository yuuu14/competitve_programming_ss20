#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cstring>
#include <fstream>
#include <numeric>
#include <chrono>

#define INPUT file_read
#define OUTPUT file_write
#define OR "+"
#define AND "*"

using namespace std;

string simplify_(string&);
bool is_num(string);

int main() {
    ifstream file_read("3.in");
    ofstream file_write("3.out");

    string s("");
    getline(INPUT, s);
    auto start = chrono::high_resolution_clock::now();
    OUTPUT << simplify_(s) << endl;
    
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
    
    
    return 0; 
}

/* return string removed first level of 1 and 0*/
string simplify_(string& str) {
    //cout << "cur_tree:" << tree << endl;
    if (is_num(str)) { return str; }
    
    string andor = str.substr(0, 1);
    str = str.substr(2, str.size()-3) + ","; // remove andor '(' ')'
    //cout << "remove andor '(' ')': " << str << endl;
    long sub = 0, num = 0; // sub = #( - #);
    vector<string> strees;
    auto idx = str.begin();
    string res("");
    for (auto c = str.begin(); c != str.end(); ++c) {
        if (*c ==  '(') ++sub;
        else if (*c == ')') --sub;
        else if (*c == ',' && sub == 0) {
            string s = string(idx, c);
            s = simplify_(s);
            //cout << "subtree: " << s << endl;
            if (c+1 != str.end()) idx = c + 1;
            if ((andor == AND && s == "0") || (andor == OR && s == "1")) return s;
            if (!(andor == AND && s == "1") && !(andor == OR && s == "0")) { res += s + ","; ++num; }
        }
    }
    if (res.size() == 0) return andor == OR ? "0" : "1";
    res.pop_back();
    if (num >= 2) return andor + "(" + res + ")";
    else return res;
}

bool is_num(string s) {
    for (unsigned int i = 0; i < s.size(); ++i)
        if (!isdigit(s[i])) return false;
    return true;
}

