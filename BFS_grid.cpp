#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using vvi = vector<vector<int>>;

// グリッド上で、スタート地点から各マスまでの最短距離を求める
// grid: '#' が壁、それ以外が通行可能なマス
// start: スタート座標 (行, 列)、0-indexed
// 戻り値: 各マスまでの最短距離。到達不能なら -1
vvi bfs_grid(const vector<string>& grid, pii start) {
    int R = grid.size();
    int C = grid[0].size();

    vvi dist(R, vector<int>(C, -1));
    queue<pii> que;

    int sy = start.first;
    int sx = start.second;

    dist[sy][sx] = 0;
    que.push({sy, sx});

    int dy[] = {-1, 1, 0, 0};
    int dx[] = {0, 0, -1, 1};

    while (!que.empty()) {
        auto [y, x] = que.front();
        que.pop();

        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d];
            int nx = x + dx[d];

            // グリッドの範囲外
            if (ny < 0 || ny >= R || nx < 0 || nx >= C) continue;

            // 壁
            if (grid[ny][nx] == '#') continue;

            // 訪問済み
            if (dist[ny][nx] != -1) continue;

            dist[ny][nx] = dist[y][x] + 1;
            que.push({ny, nx});
        }
    }

    return dist;
}
