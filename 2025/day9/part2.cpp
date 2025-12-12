/* 
   Author: Itay Volk
   Date: 12/08/2025
*/


#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

void setLine(vector<vector<bool>> &grid, const vector<int> &x_vals, const vector<int> &y_vals, pair<int, int> p1, pair<int, int> p2) {
    int ix = find(x_vals.begin(), x_vals.end(), p1.first)-x_vals.begin();
    int iy = find(y_vals.begin(), y_vals.end(), p1.second)-y_vals.begin();
    grid[iy][ix] = true;
    if (p1.first == p2.first) {
        int is = find(y_vals.begin(), y_vals.end(), p2.second)-y_vals.begin();
        for (int j = min(iy, is)+1; j < max(iy, is); ++j) {
            grid[j][ix] = true;
        }
    } else {
        int is = find(x_vals.begin(), x_vals.end(), p2.first)-x_vals.begin();
        for (int j = min(ix, is)+1; j < max(ix, is); ++j) {
            grid[iy][j] = true;
        }
    }
}

int main(void) {
    vector<pair<int, int>> tiles;
    vector<int> x_vals(1, 0), y_vals(1, 0);
    int x, y;
    char c;
    while (cin >> x >> c >> y) {
        tiles.push_back({x, y});
        x_vals.push_back(x);
        x_vals.push_back(x+1);
        y_vals.push_back(y);
        y_vals.push_back(y+1);
    }

    sort(x_vals.begin(), x_vals.end());
    auto last = std::unique(x_vals.begin(), x_vals.end());
    x_vals.erase(last, x_vals.end());
    sort(y_vals.begin(), y_vals.end());
    last = std::unique(y_vals.begin(), y_vals.end());
    y_vals.erase(last, y_vals.end());

    vector<vector<bool>> grid(y_vals.size(), vector<bool>(x_vals.size(), false));
    for (int i = 0; i < tiles.size()-1; i++) {
        setLine(grid, x_vals, y_vals, tiles[i], tiles[i+1]);
    }
    setLine(grid, x_vals, y_vals, {x, y}, tiles[0]);
    x = 1;
    while (!grid[1][x]) {
        ++x;
    }
    for (int i = 1; i < grid.size()-1; i++) {
        int last = 0;
        bool add = false;
        bool prev = false;
        for (int j = 1; j < grid[i].size()-1; j++) {
            bool cur = grid[i][j];
            if (grid[i][j]) {
                if (!grid[i][j+1] && (!prev || last && (grid[i+1][j] != grid[i+1][last]))) {
                    last = 0;
                    add = !add;
                } else if (!last) {
                    last = j;
                }
            } else if (add) {
                grid[i][j] = true;
            }
            prev = cur;
        }
    }

    long long res = 0;
    for (int i = 0; i < tiles.size()-1; i++) {
        int ix = find(x_vals.begin(), x_vals.end(), tiles[i].first)-x_vals.begin();
        int iy = find(y_vals.begin(), y_vals.end(), tiles[i].second)-y_vals.begin();
        for (int j = i+1; j < tiles.size(); j++) {
            int jx = find(x_vals.begin(), x_vals.end(), tiles[j].first)-x_vals.begin();
            int jy = find(y_vals.begin(), y_vals.end(), tiles[j].second)-y_vals.begin();
            bool valid = true;
            for (int k = min(ix, jx)+1; k < max(ix, jx); ++k) {
                if (!grid[iy][k] || !grid[jy][k]) {
                    valid = false;
                    break;
                }
            }
            if (!valid)
                continue;
            for (int k = min(iy, jy)+1; k < max(iy, jy); ++k) {
                if (!grid[k][ix] || !grid[k][jx]) {
                    valid = false;
                    break;
                }
            }
            if (!valid)
                continue;
            long long area = (long long)(abs(tiles[i].first-tiles[j].first)+1)*(abs(tiles[i].second-tiles[j].second)+1);
            if (area > res) {
                res = area;
            }
        }
    }
    cout << res << endl;
    return 0;
}