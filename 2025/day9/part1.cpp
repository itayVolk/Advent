/* 
   Author: Itay Volk
   Date: 12/08/2025
*/

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main(void) {
    vector<pair<int, int>> tiles;
    int x, y;
    char c;
    while (cin >> x >> c >> y) {
        tiles.push_back({x, y});
    }

    long long max = 0;
    for (int i = 0; i < tiles.size()-1; i++) {
        for (int j = i+1; j < tiles.size(); j++) {
            long long area = (long long)(tiles[i].first-tiles[j].first+1)*(tiles[i].second-tiles[j].second+1);
            if (area > max) {
                max = area;
            }
        }
    }

    cout << max << endl;
    return 0;
}