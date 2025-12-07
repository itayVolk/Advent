/*
   Author: Itay Volk
   Date: 12/06/2025
*/

#include <iostream>
#include <vector>

using namespace std;

void ins(vector<pair<int, long long>> &cur, int pos, long long count) {
    if (!cur.size() || cur[cur.size()-1].first != pos) {
        cur.push_back({pos, count});
    } else {
       cur[cur.size()-1].second += count;
    }
}

int main(void) {
    vector<string> grid;
    string cur;
    while (cin >> cur)
        grid.push_back(cur);

    vector<pair<int, long long>> x(1, {grid[0].find('S'), 1});
    for (auto y = 1; y < grid.size(); ++y) {
        vector<pair<int, long long>> cur;
        for (auto &pos : x) {
            if (grid[y][pos.first] == '^') {
                ins(cur, pos.first-1, pos.second);
                ins(cur, pos.first+1, pos.second);
            } else {
                ins(cur, pos.first, pos.second);
            }
        }
        x = cur;
    }

    long long count = 0;
    for (auto p : x)
        count += p.second;
    cout << count << endl;
    return 0;
}