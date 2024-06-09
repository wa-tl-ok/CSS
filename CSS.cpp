#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <deque>
#include <array>
#include <list>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <cstring>
#include <random>
#include <bitset>
#include <functional>
#include <random>

using namespace std;

vector<int> top_sort;
vector<int> CSS;
vector<int> vis;
vector<vector<int>> g;
vector<vector<int>> r_g;

void dfs(int v) {
    vis[v] = true;
    for (auto u : g[v]) {
        if (vis[u] == true) {
            continue;
        }
        dfs(u);
    }
    top_sort.push_back(v);
}

int color = -1;

void Go(int v) {
    CSS[v] = color;
    for (auto u : r_g[v]) {
        if (CSS[u] == -1) {
            Go(u);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    set<pair<int, int>> edges;

    g.resize(n);
    r_g.resize(n);

    vector<int> in(n, 0);
    vector<int> out(n, 0);

    for (int i = 1; i <= n; i++) {
        int u; u = i;
        int v; cin >> v;

        --u;
        --v;

        if (u != v) {
            edges.insert({ u, v });

            g[u].push_back(v);
            r_g[v].push_back(u);

            ++out[u];
            ++in[v];
        }
    }

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }

    int v = 0;
    for (int u = 0; u < n; u++) {
        if (vis[u] == false) {
            dfs(u);
        }
    }

    reverse(top_sort.begin(), top_sort.end());

    CSS.resize(n);
    for (int i = 0; i < n; i++) {
        CSS[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        if (CSS[top_sort[i]] == -1) {
            ++color;
            Go(top_sort[i]);
        }
    }

    vector<set<int>> G(color);

    for (auto p : edges) {
        int u = p.first;
        int v = p.second;
        if (CSS[u] != CSS[v]) {
            G[CSS[u]].insert(CSS[v]);
        }
    }

    map<int, int> nodes_in_CSS_component;

    for (int i = 0; i < n; i++) {
        ++nodes_in_CSS_component[CSS[i]];
    }

    int Components = color;

    return 0;
}
