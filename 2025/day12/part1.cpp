/* 
   Author: Itay Volk
   Date: 12/12/2025
*/

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(void) {
    vector<vector<vector<bool>>> shapes;
    vector<int> nums;
    string cur;
    int count = 0;
    getline(cin, cur);
    while (cin) {
        // cout << cur << endl;
        if (cur == "") {
            getline(cin, cur);
            continue;
        }
        if (cur[1] == ':') {
            getline(cin, cur);
            shapes.push_back(vector<vector<bool>>());
            nums.push_back(0);
            continue;
        }
        if (!isdigit(cur[0])) {
            shapes[shapes.size()-1].push_back(vector<bool>());
            for (auto c : cur) {
                shapes[shapes.size()-1][shapes[shapes.size()-1].size()-1].push_back(c=='#');
                nums[nums.size()-1] += c=='#';
            }
        } else {
            int x = cur.find('x'), s = cur.find(':');
            vector<vector<bool>> grid(stoi(cur.substr(x+1, s)), vector<bool>(stoi(cur.substr(0, x)), false));
            vector<int> counts;
            int num = 0;
            int num_shapes = 0;
            for (cur = cur.substr(s+1); cur.find(' ') != -1;) {
                cur = cur.substr(cur.find(' ')+1);
                counts.push_back(stoi(cur.substr(0, cur.find(' '))));
                num_shapes += counts[counts.size()-1];
                num += counts[counts.size()-1]*nums[counts.size()-1];
            }
            if ((grid.size()/shapes[0].size())*(grid[0].size()/shapes[0][0].size()) >= num_shapes)
                ++count;
            else if (num <= grid.size()*grid[0].size())
                cout << grid.size() << "x" << grid[0].size() << "|" << num_shapes << "|" << num << endl;
        }
        getline(cin, cur);
    }
    cout << count << endl;
    return 0;
}