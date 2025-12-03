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
        cur += dir=='L'?-s:s + 100;
        cur %= 100;
        count += !cur;
    }
    cout << "Pointed at 0 " << count << " times.";
    return 0;
}