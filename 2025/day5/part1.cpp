/* 
   Author: Itay Volk
   Date: 12/04/2025
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(void) {
    vector<pair<long long, long long>> fresh;
    string cur;
    while (cin >> cur) {
        auto dash = cur.find('-');
        if (dash > cur.length()) {
            break;
        }
        fresh.push_back({stoll(cur.substr(0, dash)), stoll(cur.substr(dash+1))});
    }

    int count = 0;
    do {
        auto n = stoll(cur);
        for (auto &r : fresh) {
            if (r.first <= n && n <= r.second) {
                count++;
                break;
            }
        }
    } while(cin >> cur);
    cout << count << endl;
    return 0;
}