#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Prim 算法（基于 BFS 实现）
void prim(vector<vector<int>>& graph, int n, vector<int>& tree) {
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < n; i++) {
            if (graph[cur][i] != 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
                tree[i] = cur;
            }
        }
    }
}

int main() {
    int nodes, SDN_nodes, destinations, links, pairs;
    int nodes;
    cin >> nodes;
    vector<vector<int>> graph(nodes, vector<int>(nodes, 0));
    for (int i = 0; i < nodes; i++) {
        int from, to;
        cin >> from >> to;
        graph[from][to] = 1;
        graph[to][from] = 1;
    }
    vector<int> tree(nodes, -1);
    prim(graph, n, tree);
    for (int i = 0; i < n; i++) {
        cout << i << ": " << tree[i] << endl;
    }
    return 0;
}
