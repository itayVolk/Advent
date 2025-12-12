/* 
   Author: Itay Volk
   Date: 12/12/2025
*/

#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct node{
    vector<struct node *> next;
};

long long traverse(struct node * cur, bool d, bool f, struct node * out, struct node * dac, struct node * fft, map<tuple<struct node *, bool, bool>, long long> &cache) {
    if (cur == out)
        return d && f;
    if (cur->next.empty())
        return 0;
    if (cur == dac)
        d = true;
    if (cur == fft)
        f = true;
    auto it = cache.find(tuple<struct node *, bool, bool>(cur, d, f));
    if (it != cache.end())
        return it->second;

    long long sum = 0;
    for (auto p : cur->next) {
        sum += traverse(p, d, f, out, dac, fft, cache);
    }
    cache[tuple<struct node *, bool, bool>(cur, d, f)] = sum;
    return sum;
}

int main(void) {
    map<string, struct node *> graph;
    string cur;
    getline(cin, cur);
    while(cur != "") {
        string name = cur.substr(0,3);
        struct node * prime;
        auto it = graph.find(name);
        if (it != graph.end()) {
            prime = it->second;
        } else {
            prime = new struct node();
            graph[name] = prime;
        }

        for (cur = cur.substr(1); cur.length() >= 4; ) {
            cur = cur.substr(4);
            name = cur.substr(0, 3);
            struct node * add;
            it = graph.find(name);
            if (it != graph.end()) {
                add = it->second;
            } else {
                add = new struct node();
                graph[name] = add;
            }
            prime->next.push_back(add);
        }
        getline(cin, cur);
    }
    map<tuple<struct node *, bool, bool>, long long> cache;
    cout << traverse(graph["svr"], false, false, graph["out"], graph["dac"], graph["fft"], cache) << endl;
    return 0;
}