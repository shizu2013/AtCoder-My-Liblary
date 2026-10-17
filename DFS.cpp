#include <bits/stdc++.h>
using namespace std;

void dfs(int v,
         const vector<vector<int>>& graph,
         vector<bool>& visited) {
    visited[v] = true;

    for (int nv : graph[v]) {
        if (visited[nv]) continue;
        dfs(nv, graph, visited);
    }
}
