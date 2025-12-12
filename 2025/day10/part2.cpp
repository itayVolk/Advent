/* 
   Author: Itay Volk
   Date: 12/09/2025
*/

#include <iostream>
#include <map>
#include <vector>

using namespace std;

int solve(vector<int> &goal, vector<vector<int>> &buttons, map<vector<int>, int> &cache) {
    for (auto &n : goal)
        if (n < 0)
            return -1;
    auto it = cache.find(goal);

    if (it != cache.end()) {
        return it->second;
    }

    vector<bool> parity(goal.size(), false);
    for (int i = 0; i < goal.size(); i++)
        parity[i] = goal[i]%2;

    int best = -1;
    for (int i = 0; i <= (1 << buttons.size()); i++) {
        vector<int> cur;
        vector<bool> state(parity.size(), false);
        for (int j = 0; j < buttons.size(); j++)
            if (i&(1 << j)) {
                cur.push_back(j);
                for (auto b : buttons[j])
                    state[b] = !state[b];
            }
        
        if (state == parity) {
            vector<int> new_goal = goal;
            for (auto b : cur) {
                for (auto idx : buttons[b]) {
                    --new_goal[idx];
                }
            }
            bool valid = true;
            for (auto &n : new_goal) {
                if (n < 0) {
                    valid = false;
                    break;
                }
                n /= 2;
            }
            if (valid) {
                int res = solve(new_goal, buttons, cache);
                if (res != -1 && (best == -1 || 2*res + cur.size() < best)) {
                    best = 2*res + cur.size();
                }
            }
        }
    }
    return cache[goal] = best;
}

int main(void) {
    string ind;
    int sum = 0;
    int i = 0;
    while (cin >> ind) {
        char c;
        int b;
        vector<vector<int>> buttons;
        while (cin >> c && c != '{') {
            if (c == '(') {
                buttons.push_back(vector<int>());
            } else if (c != ',') {
                continue;
            }
            cin >> b;
            buttons[buttons.size()-1].push_back(b);
        }

        vector<int> goal;
        while(cin >> b >> c && c != '}') {
            goal.push_back(b);
        }
        goal.push_back(b);
        map<vector<int>, int> cache;
        cache[vector<int>(goal.size(), 0)] = 0;
        int res = solve(goal, buttons, cache);
        sum += res;
        cout << i++ << ", ";
    }
    cout << sum << endl;
    return 0;
}