/* 
   Author: Itay Volk
   Date: 12/01/2025
*/

#include <iostream>
using namespace std;

int main() {
    int cur = 50;
    int count = 0;
    char dir;
    int s;
    while (cin >> dir >> s) {
        int prev = cur;
        cur += dir=='L'?-s:s;
        if (cur >= 100) {
            count += cur/100;
        }
        if (!prev && cur < 0) {
            count--;
        }
        while (cur <= 0) {
            cur += 100;
            count++;
        }
        cur %= 100;
    }
    cout << "Clicked through 0 " << count+!cur << " times.";
    return 0;
}