#include <bits/stdc++.h>
using namespace std;

vector<int> bfs_dist(
    int start,
    const vector<vector<int>>& graph
) {
    int n = graph.size();
    vector<int> dist(n, -1);
    queue<int> que;

    dist[start] = 0;
    que.push(start);

    while (!que.empty()) {
        int v = que.front();
        que.pop();

        for (int nv : graph[v]) {
            if (dist[nv] != -1) continue;

            dist[nv] = dist[v] + 1;
            que.push(nv);
        }
    }

    return dist;
}
