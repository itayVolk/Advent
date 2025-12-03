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
        long long tot = 0;
        int max = 0;
        for (int i = 1; i <= 12; i++) {
            for (int j = max+1; j < cur.length()-12+i; j++) {
                if (cur[j] > cur[max]) {
                    max = j;
                }
            }
            tot = tot*10 + cur[max]-'0';
            max++;
        }
        sum += tot;
    }

    cout << sum << endl;
    return 0;
}