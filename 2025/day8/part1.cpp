/* 
   Author: Itay Volk
   Date: 12/07/2025
*/

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

bool contain(set<int> v, int a) {
    return find(v.begin(), v.end(), a) != v.end();
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cerr << "Need num connections!" << endl;
        return 1;
    }
    int iter = stoi(argv[1]);

    vector<array<int, 3>> points;
    int x, y, z;
    char comma;
    while (cin >> x >> comma >> y >> comma >> z)
        points.push_back({x, y, z});

    vector<tuple<double, int, int>> lengths;
    vector<set<int>> circuits;
    for (int i = 0; i < points.size()-1; i++) {
        for (int j = i+1; j < points.size(); j++) {
            lengths.push_back({(1.0*points[i][0]-points[j][0])*(points[i][0]-points[j][0]) + (1.0*points[i][1]-points[j][1])*(points[i][1]-points[j][1]) + (1.0*points[i][2]-points[j][2])*(points[i][2]-points[j][2]), i, j});
        }
        circuits.push_back({i});
    }

    sort(lengths.begin(), lengths.end());
    for (int c = 0; c < iter; c++) {
        int a = get<1>(lengths[c]), b = get<2>(lengths[c]);
        auto setA = find_if(circuits.begin(), circuits.end(), bind(contain, placeholders::_1, a));
        auto setB = find_if(circuits.begin(), circuits.end(), bind(contain, placeholders::_1, b));
        if (setA != setB) {
            setB->insert(setA->begin(), setA->end());
            circuits.erase(setA);
        }
    }
    
    sort(circuits.begin(), circuits.end(), [=](set<int> a, set<int> b) {return a.size() > b.size();});
    cout << circuits[0].size()*circuits[1].size()*circuits[2].size() << endl;
    return 0;
}