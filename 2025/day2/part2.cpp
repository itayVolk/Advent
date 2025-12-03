/* 
   Author: Itay Volk
   Date: 12/03/2025
*/

#include <cmath>
#include <iostream>
#include <set>

using namespace std;

int digit(long long num) {return floor(log10(num))+1;};

long long repeat(long long first, long long mul, int split) {
    long long initial = first;
    for (split--; split > 0; split--) {
        first *= mul;
        first += initial;
    }
    return first;
}

int main(void) {
    long long min, max;
    char trash;
    set<long long> invalid;
    while (cin >> min >> trash >> max) {
        cout << min << "-" << max << endl;
        int num = digit(min);
        int split = 1;
        while (++split <= digit(max)) {
            long long first = min/pow(10, num-num/split);
            if (num%split) {
                first = pow(10, num/split);
            } else if (repeat(first, pow(10, digit(first)), split) < min) {
                first++;
            }
            for (long long mul = pow(10, digit(first)), val = repeat(first, mul, split); val <= max; mul = pow(10, digit(++first)), val = repeat(first, mul, split)) {
                invalid.insert(val);
            }
        }
        cin >> trash;
    }
    long long sum = 0;
    for (auto &v : invalid) {
        sum += v;
    }
    cout << "The sum is " << sum << endl;
    return 0;
}
