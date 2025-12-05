/*
   Author: Itay Volk
   Date: 12/04/2025
*/

#include <algorithm>
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

    sort(fresh.begin(), fresh.end());
    for (auto i = 0; i < fresh.size(); i++) {
        for (int j = i+1; j < fresh.size(); j++) {
            if (fresh[j].first <= fresh[i].second) {
                fresh[i].second = max(fresh[i].second, fresh[j].second);
                fresh.erase(fresh.begin()+j);
                j = i;
            } else if (fresh[i].first <= fresh[j].second && fresh[j].second <= fresh[i].second) {
                fresh[i].first = min(fresh[i].first, fresh[j].first);
                fresh.erase(fresh.begin()+j);
                j = i;
            } else if (fresh[i].first == fresh[j].second+1) {
                fresh[i].first = fresh[j].first;
                fresh.erase(fresh.begin()+j);
                j = i;
            }
        }
    }

    long long count = 0;
    for (auto &p : fresh) {
        count += p.second-p.first+1;
    }

    cout << count << endl;
    return 0;
}