/* 
   Author: Itay Volk
   Date: 12/03/2025
*/

#include <cctype>
#include <iostream>

using namespace std;

int main(void) {
    long long sum = 0;
    string cur;
    while (cin >> cur) {
        if (!isdigit(cur[0])) {
            break;
        }
        int max = 0;
        for (int i = 1; i < cur.length()-1; i++) {
            if (cur[i] > cur[max]) {
                max = i;
            }
        }
        int second = max+2;
        for (int i = max+1; i < cur.length(); i++) {
            if (cur[i] > cur[second]) {
                second = i;
            }
        }

        sum += (cur[max]-'0')*10+cur[second]-'0';
    }

    cout << sum << endl;
    return 0;
}