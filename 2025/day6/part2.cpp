/* 
   Author: Itay Volk
   Date: 12/05/2025
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(void) {
    vector<string> lines;
    string cur;
    while (getline(cin, cur) && cur[0] != '*' && cur[0] != '+')
        lines.push_back(cur);

    long long total = 0;
    for (auto i = 0; i < cur.length(); ++i) {
        bool mul = cur[i] == '*';
        long long res = mul;
        while (i < cur.length()) {
            int num = 0;
            for (auto l : lines)
                if (l[i] != ' ')
                    num = num*10 + l[i]-'0';
            if (!num)
                break;
            if (mul)
                res *= num;
            else
                res += num;
            ++i;
        }
        total += res;
    }
    cout << total << endl;
    return 0;
}