#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    using namespace std;

    long long size;
    vector<long long> nums, res;
    cin >> size;
    for (unsigned long long i = 0; i < size; ++i) {
        long long n;
        cin >> n;
        nums.push_back(n);
    }

    sort(nums.begin(), nums.end());
    for (unsigned long long i = 0, l, r; i <= size-3; ++i) {
        l = i + 1;
        r = size - 1;
        while (l < r) {
            long long sum = nums[i] + nums[l] + nums[r];
            if (sum == 42) {
                cout << nums[i] << " " << nums[l] << " " << nums[r] << endl;
                return 0;
            }
            else if (sum > 42) r--;
            else l++; 
        }
    }
    cout << "impossible\n";

    return 0;
}