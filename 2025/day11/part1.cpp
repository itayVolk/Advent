/* 
   Author: Itay Volk
   Date: 12/12/2025
*/

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct node{
    vector<struct node *> next;
};

int traverse(struct node * cur, struct node * out) {
    if (cur == out) {
        return 1;
    }
    if (cur->next.empty()) {
        return 0;
    }

    int sum = 0;
    for (auto p : cur->next) {
        sum += traverse(p, out);
    }
    return sum;
}

int main(void) {
    map<string, struct node *> graph;
    struct node * you = nullptr;
    struct node * out = nullptr;
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

        if (name == "you") {
            you = prime;
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
                if (name == "out") {
                    out = add;
                }
                graph[name] = add;
            }
            prime->next.push_back(add);
        }
        getline(cin, cur);
    }

    cout << traverse(you, out) << endl;
    return 0;
}