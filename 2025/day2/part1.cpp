/* 
   Author: Itay Volk
   Date: 12/02/2025
*/

#include <cmath>
#include <iostream>

using namespace std;

inline int digit(long long num) {return floor(log10(num))+1;};

int main(void) {
    long long min, max, sum = 0;
    char trash;
    while (cin >> min >> trash >> max) {
        cout << min << "-" << max << endl;
        int num = digit(min);
        long long first = min/pow(10, num/2);
        if (num%2) {
            first = pow(10, num/2);
        } else if (first < min%int(pow(10, num/2))) {
            first++;
        }
        for (long long mul = pow(10, digit(first)); first*(mul+1) <= max; mul = pow(10, digit(++first))) {
            sum += first*(mul+1);
        }
        cin >> trash;
    }
    cout << "The sum is " << sum << endl;
    return 0;
}
