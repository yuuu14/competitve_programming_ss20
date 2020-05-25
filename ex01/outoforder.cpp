#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    using namespace std;

    long long size;
    cin >> size;
    vector<long> stamp, pos;
    for (unsigned int i = 0; i < size; ++i) {
        long tmp;
        cin >> tmp;
        stamp.push_back(tmp);
    }
    vector<long> stamp_sorted(stamp);
    sort(stamp_sorted.begin(), stamp_sorted.end());
    for (unsigned int i = 0; i < size; ++i)
        if (stamp[i] != stamp_sorted[i]) pos.push_back(i+1);
    if (pos.size() == 2) cout << pos[0] << " " << pos[1] << endl;
    else cout << "impossible" << endl;

    return 0;
    //int * stamp = new int[size];
    //for (unsigned int i = 0; i < size; ++i) cin >> stamp[i];
    // sorting

}