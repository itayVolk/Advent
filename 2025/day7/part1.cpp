/* 
   Author: Itay Volk
   Date: 12/06/2025
*/

#include <iostream>
#include <vector>

using namespace std;

void ins(vector<int> &cur, int pos) {
    if (!cur.size() || cur[cur.size()-1] != pos) {
        cur.push_back(pos);
    }
}

int main(void) {
    vector<string> grid;
    string cur;
    while (cin >> cur)
        grid.push_back(cur);

    int count = 0;
    vector<int> x(1, grid[0].find('S'));
    for (auto y = 1; y < grid.size(); ++y) {
        vector<int> cur;
        for (auto &pos : x) {
            if (grid[y][pos] == '^') {
                ++count;
                ins(cur, pos-1);
                ins(cur, pos+1);
            } else {
                ins(cur, pos);
            }
        }
        x = cur;
    }

    cout << count << endl;
    return 0;
}