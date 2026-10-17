競プロで使う「再帰DFS」「スタックDFS」「キューBFS」は、いずれもグラフや木を探索するアルゴリズムです。違いは主に、**どの順番で頂点を探索するか**と、**探索する頂点をどう管理するか**にあります。

AtCoderのABCでグラフ問題を解くことを想定して、それぞれの特徴・使い分け・実装例を整理します。

## 1. 3種類の比較

| 項目 | 再帰DFS | スタックDFS | キューBFS |
|---|---|---|---|
| 探索方式 | 深さ優先 | 深さ優先 | 幅優先 |
| 管理方法 | 関数呼び出し | `stack` / `vector` | `queue` |
| 探索順序 | 可能な限り深く進む | 可能な限り深く進む | 近い頂点から進む |
| 最短距離の計算 | 単独では不向き | 単独では不向き | 得意 |
| 木の部分木サイズ計算 | 得意 | 可能 | あまり向かない |
| 深い探索への対応 | 再帰が深いと危険 | 比較的安全 | 比較的安全 |
| 主な用途 | 木DP、帰りがけ順 | 深いグラフの探索 | 最短経路、距離計算 |

3種類とも、隣接リストで実装した場合の計算量は通常 **`O(N + M)`** です。`N` は頂点数、`M` は辺数を表します。

## 2. 共通の準備：グラフの構築

まず、3種類の探索で共通して使うグラフを用意します。

例えば、次のような無向グラフを考えます。

```text
0 --- 1 --- 3
|     |
2 --- 4
```

入力された辺を隣接リストに格納します。

```cpp
int n, m;
cin >> n >> m;

vector<vector<int>> graph(n);

for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    graph[u].push_back(v);
    graph[v].push_back(u);
}
```

`graph[v]` には、頂点 `v` と直接つながっている頂点が格納されます。

なお、この例は無向グラフなので両方向に辺を追加しています。有向グラフなら、問題の指定に従って必要な方向だけを追加します。

頂点番号を `0` 始まりに統一しているため、入力が `1` 始まりなら `u--, v--` で変換します。

## 3. 再帰DFS（Recursive DFS）

### 仕組み

DFSは Depth-First Search（深さ優先探索）の略です。

現在の頂点から、まだ訪問していない隣接頂点へ進み、さらにその先へ進みます。進める頂点がなくなったら、呼び出し元に戻ります。

例えば、次の順番で探索するイメージです。

```text
0 → 1 → 3
    ↑
    戻る
    ↓
    4 → 2
```

実際の探索順は、隣接リストに頂点を追加した順番によって変わります。

### テンプレート

```cpp
void dfs(int v,
         const vector<vector<int>>& graph,
         vector<bool>& visited) {
    visited[v] = true;

    // 頂点 v に対する処理

    for (int nv : graph[v]) {
        if (visited[nv]) continue;
        dfs(nv, graph, visited);
    }
}
```

呼び出すときは、次のようにします。

```cpp
vector<bool> visited(n, false);
dfs(0, graph, visited);
```

頂点 `0` から探索を開始します。

### コードの解説

**① 訪問済みにする**

```cpp
visited[v] = true;
```

同じ頂点を何度も探索しないために、訪問した頂点を記録します。

**② 隣接頂点を調べる**

```cpp
for (int nv : graph[v]) {
    if (visited[nv]) continue;
    dfs(nv, graph, visited);
}
```

隣接頂点 `nv` が訪問済みならスキップし、未訪問なら再帰的にDFSを呼び出します。

この処理によって、探索が自然に深い方向へ進みます。

### どういう問題で使う？

再帰DFSは、特に次のような問題に向いています。

- 木の部分木サイズを計算する
- 木の深さや各頂点の親を求める
- 木DPなど、子の計算結果を使って親の値を計算する
- グラフの連結成分を調べる
- 帰りがけ順に処理する

例えば、木の部分木サイズを計算するなら、次のように書けます。

```cpp
vector<int> subtree_size(n, 1);

void dfs(int v, int parent,
         const vector<vector<int>>& graph) {
    for (int nv : graph[v]) {
        if (nv == parent) continue;

        dfs(nv, v, graph);
        subtree_size[v] += subtree_size[nv];
    }
}
```

呼び出し方：

```cpp
dfs(0, -1, graph);
```

各頂点の部分木サイズを `subtree_size[v]` に格納します。

この実装は**木であることを前提**にしています。一般のグラフにそのまま使う場合は、`parent` だけでは訪問管理が不十分になるため、`visited` などを使います。

また、再帰の深さが大きくなると、コールスタックの上限に達する可能性があります。頂点数が非常に多い場合は注意してください。

---

## 4. スタックDFS（Iterative DFS）

### 仕組み

スタックDFSも深さ優先探索ですが、再帰関数を使わず、**自分でスタックを管理して探索する**方法です。

スタックは LIFO（Last In, First Out）、つまり最後に追加した要素を先に取り出すデータ構造です。

### テンプレート

```cpp
void dfs_stack(int start,
               const vector<vector<int>>& graph,
               vector<bool>& visited) {
    stack<int> st;

    st.push(start);
    visited[start] = true;

    while (!st.empty()) {
        int v = st.top();
        st.pop();

        // 頂点 v に対する処理

        for (int nv : graph[v]) {
            if (visited[nv]) continue;

            visited[nv] = true;
            st.push(nv);
        }
    }
}
```

呼び出すときは、次のようにします。

```cpp
vector<bool> visited(n, false);
dfs_stack(0, graph, visited);
```

### コードの解説

**① スタックに開始頂点を入れる**

```cpp
st.push(start);
visited[start] = true;
```

開始頂点をスタックに入れ、訪問済みにします。

**② スタックから頂点を取り出す**

```cpp
int v = st.top();
st.pop();
```

最後に追加した頂点を取り出して処理します。

**③ 未訪問の隣接頂点を追加する**

```cpp
for (int nv : graph[v]) {
    if (visited[nv]) continue;

    visited[nv] = true;
    st.push(nv);
}
```

隣接頂点をスタックに追加し、次のループで探索します。

### 再帰DFSとの違い

再帰DFSでは、関数呼び出しが探索途中の状態を保持してくれます。

一方、スタックDFSでは、自分で頂点をスタックに格納して管理します。

どちらも深さ優先探索ですが、**探索順序が完全に一致するとは限りません**。例えば、隣接頂点を `1, 2, 3` の順にスタックへ追加すると、次に取り出されるのは `3` です。

再帰DFSと同じような順序にしたければ、隣接頂点を逆順に追加する方法があります。ただし、問題によっては探索順序そのものが重要でない場合も多いです。

### どういう問題で使う？

- 再帰が深くなりすぎる可能性があるグラフの探索
- 到達可能な頂点の列挙
- 連結成分の探索
- 再帰を使わずにDFSを実装したい場合

ただし、再帰DFSと同じように、スタックDFSだけで木DPなどの帰りがけ処理を行うには工夫が必要です。

なお、`std::stack` の代わりに `vector<int>` を使っても実装できます。

```cpp
vector<int> st;
st.push_back(start);

int v = st.back();
st.pop_back();
```

`push_back()` で追加し、`back()` で最後の要素を取得し、`pop_back()` で取り出します。競プロでは、この方法もよく使われます。

---

## 5. キューBFS（Breadth-First Search）

### 仕組み

BFSは Breadth-First Search（幅優先探索）の略です。

DFSが深い方向へ進むのに対して、BFSは**開始地点からの距離が近い頂点を優先して探索**します。

例えば、開始地点を `0` とすると、次のような順番になります。

```text
距離 0：0
距離 1：1, 2
距離 2：3, 4
```

これは各辺の重みがすべて等しいグラフの場合です。

### テンプレート

```cpp
void bfs(int start,
         const vector<vector<int>>& graph,
         vector<bool>& visited) {
    queue<int> que;

    que.push(start);
    visited[start] = true;

    while (!que.empty()) {
        int v = que.front();
        que.pop();

        // 頂点 v に対する処理

        for (int nv : graph[v]) {
            if (visited[nv]) continue;

            visited[nv] = true;
            que.push(nv);
        }
    }
}
```

呼び出すときは、次のようにします。

```cpp
vector<bool> visited(n, false);
bfs(0, graph, visited);
```

### コードの解説

**① キューに開始頂点を入れる**

```cpp
que.push(start);
visited[start] = true;
```

開始頂点をキューに入れます。

**② キューの先頭から取り出す**

```cpp
int v = que.front();
que.pop();
```

キューは FIFO（First In, First Out）、つまり先に追加した要素を先に取り出すデータ構造です。

**③ 未訪問の隣接頂点を追加する**

```cpp
for (int nv : graph[v]) {
    if (visited[nv]) continue;

    visited[nv] = true;
    que.push(nv);
}
```

未訪問の頂点をキューに追加します。

先に発見した頂点ほど先に処理されるため、開始地点から近い頂点から順番に探索できます。

### どういう問題で使う？

BFSは、特に次のような問題に向いています。

- 重みなしグラフの最短距離
- マス目の迷路の最短経路
- 頂点から各頂点までの距離
- 各頂点が何段目にあるかを求める
- 最短手数を求める状態探索

DFSでも到達可能な頂点は調べられますが、最短距離を求める場合はBFSが適しています。

### 最短距離を求めるテンプレート

競プロでは、単なる訪問管理よりも、距離を記録する実装のほうが使いやすいことがあります。

```cpp
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
```

使用例：

```cpp
vector<int> dist = bfs_dist(0, graph);

cout << dist[3] << '\n';
```

`dist[3]` に、頂点 `0` から頂点 `3` までの最短距離が格納されます。

到達できない頂点は `-1` のままです。

この方法で最短距離を求められるのは、各辺のコストが等しい場合です。辺に異なる重みがある場合は、通常、ダイクストラ法など別のアルゴリズムを使います。

---

## 6. どれを使うべきか？

実際の競プロでは、問題の条件から使うアルゴリズムを選びます。

| 問題の内容 | おすすめ |
|---|---|
| グラフで到達できる頂点を調べる | 再帰DFS / スタックDFS |
| 連結成分の個数を数える | 再帰DFS / スタックDFS |
| 木の部分木サイズを求める | 再帰DFS |
| 木DPを解く | 再帰DFS |
| 頂点間の最短距離を求める（辺の重みが等しい） | キューBFS |
| 迷路の最短手数を求める | キューBFS |
| 頂点数が多く、再帰の深さが心配 | スタックDFS |
| 各頂点の深さを求める | DFS / BFS |

例えば、ABCの問題文に「最小何回の操作で到達できるか」と書かれていたら、BFSを検討します。

一方、「ある頂点から到達可能な頂点をすべて列挙せよ」なら、DFSでもBFSでも対応できます。

## 7. 競プロ用テンプレートとしての最終的な構成

今のC++23環境なら、次の3つを用意しておくとよいでしょう。

**① `dfs`：再帰DFS**

```cpp
void dfs(int v,
         const vector<vector<int>>& graph,
         vector<bool>& visited) {
    visited[v] = true;

    for (int nv : graph[v]) {
        if (visited[nv]) continue;
        dfs(nv, graph, visited);
    }
}
```

**② `dfs_stack`：スタックDFS**

```cpp
void dfs_stack(int start,
               const vector<vector<int>>& graph,
               vector<bool>& visited) {
    stack<int> st;
    st.push(start);
    visited[start] = true;

    while (!st.empty()) {
        int v = st.top();
        st.pop();

        for (int nv : graph[v]) {
            if (visited[nv]) continue;

            visited[nv] = true;
            st.push(nv);
        }
    }
}
```

**③ `bfs_dist`：最短距離を求めるBFS**

```cpp
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
```

この3つをテンプレートに入れておけば、基本的なグラフ探索には十分対応できます。

なお、これらは**グラフを受け取って探索するための部品**です。実際の問題では、入力形式に合わせてグラフを構築し、必要に応じて頂点に対する処理を追加してください。

特にABCのB・C問題に取り組む段階では、まず「DFSで到達可能性を調べる問題」と「BFSで最短距離を求める問題」を見分けられるようになると、グラフ問題への対応力が上がります。
