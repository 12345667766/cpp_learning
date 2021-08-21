#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    void dfs(unordered_map<int, vector<int>>& adjList, vector<bool>& visited, int n) {
        if (visited[n]) {
            return;
        }
        visited[n] = true;
        for (int x : adjList[n]) {
            dfs(adjList, visited, x);
        }
    }

    int countComponents(int n, vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> adjList;
        // 建立邻接表
        for (auto v : edges) {
            adjList[v[0]].emplace_back(v[1]);
            adjList[v[1]].emplace_back(v[0]);
        }
        vector<bool> visited(n, false);  // 访问标记vector
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                ans++;
                dfs(adjList, visited, i);
            }
        }
        return ans;
    }
};
