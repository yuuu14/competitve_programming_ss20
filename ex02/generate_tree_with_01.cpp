#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <boost/algorithm/string/join.hpp>

using namespace std;


int getrandom(int range);
string generate_stree(int i, int size);

int main() {
    srand(time(nullptr));
    string s = generate_stree(0, 4);
    ofstream file("3.in");
    file << s << endl;
    file.close();
    
    return 0;
}

int getrandom(int range) {
    int tmp = range;
    while (tmp >= range) 
        tmp = rand() / ((RAND_MAX + 1u) / range);
    return tmp;
}

string generate_stree(int level, int size) {
    int max_level = 28;
    vector<string> stree;
    string res;
    if (size == 1) return to_string(getrandom(100));
    else {
        res = getrandom(2) == 1 ? "*(" : "+(";
        if (level == max_level) {
            for (unsigned int i = 0; i != size; ++i)
                stree.push_back(to_string(getrandom(100)));
            return res + boost::algorithm::join(stree, ",") + ")";
        }
        else {
            for (unsigned int i = 0; i < size; ++i) {
                int new_level = level + 1 + getrandom(2);
                stree.push_back(generate_stree(min(new_level, max_level), 1+getrandom(4)));
    
            }
            return res + boost::algorithm::join(stree, ",") + ")";
        }
    }
}