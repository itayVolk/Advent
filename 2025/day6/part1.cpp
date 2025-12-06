/* 
   Author: Itay Volk
   Date: 12/05/2025
*/

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main(void) {
    vector<vector<int>> nums;
    string cur;
    while (getline(cin, cur)) {
        istringstream iss(cur);
        if (cur[0] == '*' || cur[0] == '+') {
            int i = 0;
            char c;
            long long total = 0;
            while (iss >> c) {
                long long res = c == '*';
                for (auto &r : nums) {
                    if (c == '*') {
                        res *= r[i];
                    } else {
                        res += r[i];
                    }
                }
                total += res;
                ++i;
            }
            cout << total << endl;
            break;
        }
        nums.push_back(vector<int>());
        int n;
        while (iss >> n) {
            nums[nums.size()-1].push_back(n);
        }
    }
    return 0;
}