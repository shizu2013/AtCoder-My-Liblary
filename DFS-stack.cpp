#include <bits/stdc++.h>
using namespace std;

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
