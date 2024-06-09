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

int color = 0;

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

    int n, m;
    cin >> n >> m;

    g.resize(n);
    r_g.resize(n);
    vector<int> in(n, 0);
    vector<int> out(n, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        --u;
        --v;

        g[u].push_back(v);
        r_g[v].push_back(u);

        ++out[u];
        ++in[v];
    }

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }

    int v = 0;
    for (int u = 0; u < n; u++) {
        if (in[u] == 0) {
            v = u;
        }
    }

    dfs(v); 

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

    for (int v = 0; v < n; v++) {
        cout << CSS[v] << ' ';
    }

    return 0;
}