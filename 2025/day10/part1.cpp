/* 
   Author: Itay Volk
   Date: 12/09/2025
*/

#include <iostream>
#include <vector>

using namespace std;

bool press(vector<vector<int>> &buttons, vector<bool> &goal, int count, int i, vector<bool> cur) {
    if (!count) {
        return cur == goal;
    }

    --count;
    for (; i < buttons.size(); ++i) {
        for (auto b : buttons[i]) {
            cur[b] = !cur[b];
        }
        if (press(buttons, goal, count, i+1, cur))
            return true;
        for (auto b : buttons[i]) {
            cur[b] = !cur[b];
        }
    }
    return false;
}

int main(void) {
    string ind;
    long long sum = 0;
    while (cin >> ind) {
        vector<bool> goal(ind.size()-2, false);
        for (int i = 0; i < goal.size(); i++) {
            goal[i] = ind[i+1]=='#';
        }
        if (goal == vector<bool> (goal.size(), false)) {
            continue;
        }

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
        cin >> ind;

        int count = 1;
        while(!press(buttons, goal, count, 0, vector<bool>(goal.size()))) {
            ++count;
        }
        sum += count;
    }
    cout << sum << endl;
    return 0;
}