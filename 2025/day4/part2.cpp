/* 
   Author: Itay Volk
   Date: 12/03/2025
*/

#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    vector<vector<bool>> grid;
    string cur;
    while (cin >> cur) {
        grid.push_back(vector<bool>());
        for (char &c : cur) {
            grid[grid.size()-1].push_back(c == '@');
        }
    }
    
    int total = 0, count;
    do {
        count = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (!grid[i][j]) {
                    continue;
                }
                int n = 0;
                if (i) {
                    n += grid[i-1][j];
                    if (j) {
                        n += grid[i-1][j-1];
                    }
                    if (j < grid[i-1].size()-1) {
                        n += grid[i-1][j+1];
                    }
                }
                if (j) {
                    n += grid[i][j-1];
                }
                if (j < grid[i].size()-1) {
                    n += grid[i][j+1];
                }
                if (i < grid.size()-1) {
                    n += grid[i+1][j];
                    if (j) {
                        n += grid[i+1][j-1];
                    }
                    if (j < grid[i+1].size()-1) {
                        n += grid[i+1][j+1];
                    }
                }
                
                if (n < 4) {
                    ++count;
                    grid[i][j] = false;
                }
            }
        }
        total += count;
    } while(count);

    cout << total << endl;
    return 0;
}