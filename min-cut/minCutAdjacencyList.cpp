    #include <iostream>
    #include <vector>
    #include <random>
    #include <climits>
    #include <cmath>
    #include <algorithm>
    #include <unordered_set>

    /*
        Graph is represented by adj list
    */

    using namespace std;

    mt19937 gen(random_device{}());

    void contractEdge(vector<vector<int>>& graph,
                    vector<bool>& active,
                    int& vertices)
    {
        //Choose a random active vertex u that has edges
        vector<int> candidates;

        for (int i = 0; i < graph.size(); ++i) {
            if (active[i] && !graph[i].empty()) {
                candidates.push_back(i);
            }
        }

        if (candidates.empty()) return;

        uniform_int_distribution<int> distu(0, candidates.size() - 1);
        int u = candidates[distu(gen)];

        //Choose random neighbor v of u
        uniform_int_distribution<int> distv(0, graph[u].size() - 1);
        int v = graph[u][distv(gen)];

        //Replace v with u in all of v's neighbors
        //---
        for (int neighbor : graph[v]) { 
            for (int& x : graph[neighbor]) {
                if (x == v) {
                    x = u;
                }
            }
        }

        // Add v's edges to u
        graph[u].insert(
            graph[u].end(),
            graph[v].begin(),
            graph[v].end()
        );

        // Deactivate v
        graph[v].clear();
        active[v] = false;
        vertices--;

        // Remove self-loops from u
        graph[u].erase(
            remove(graph[u].begin(), graph[u].end(), u),
            graph[u].end()
        );
    }



    int karger(vector<vector<int>>& graph, vector<bool>& active, int targetVertices) 
    {
        int n = graph.size();
        int currentVertices = 0;
        for (int i = 0; i < n; i++) {
            if (active[i]) currentVertices++;
        }

        while (currentVertices > targetVertices) {
            contractEdge(graph, active, currentVertices);
        }
        
        if (targetVertices == 2) {
            for (int i = 0; i < n; i++) {
                if (!active[i]) continue;
                return graph[i].size();
            }
            return 0;
        }

        return 0;
    }
    int mincut(vector<vector<int>> graph)
    {
        int n = graph.size();

        int iterations = n*log2(n);
        int best = INT_MAX;

        for (int i = 0; i < iterations; i++) {
            vector<bool> active(n, true);
            vector<vector<int>> cGraph = graph;
            int cut = karger(cGraph, active, 2);
            best = min(best, cut);
        }
        return best;
    }


    int fastCutRecursive(vector<vector<int>>& graph, vector<bool>& active, int numActive) 
    {
        // base case 6 or less nodes left
        if (numActive <= 6) {
            int best = INT_MAX;
            
            // Brute Force
            for (int rep = 0; rep < 15; rep++) {
                int cut = karger(graph, active, 2);
                best = min(best, cut);
            }
            
            return (best == INT_MAX) ? 0 : best;
        }

        // t = ceil(n / sqrt(2))
        int t = ceil(numActive / sqrt(2.0));

        // First recursive call graph preparation
        vector<vector<int>> g1 = graph;
        vector<bool> a1 = active;
        karger(g1, a1, t); 
        int v1 = t;

        // Second recursive call graph preparation
        vector<vector<int>> g2 = graph;
        vector<bool> a2 = active;
        karger(g2, a2, t);
        int v2 = t;

        // Calls
        int cut1 = fastCutRecursive(g1, a1, v1);
        int cut2 = fastCutRecursive(g2, a2, v2);

        return min(cut1, cut2);
    }

    int fastCut(vector<vector<int>> graph) 
    {
        int n = graph.size();
        vector<bool> active(n, true);
        return fastCutRecursive(graph, active, n);
    }

    int main() 
    {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n, vector<int>());

        // read input
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].insert(adj[u].begin(), v);
            adj[v].insert(adj[v].begin(), u);

        }

        //int best = fastCut(adj);
        int best = mincut(adj);
        cout << best;

        return 0;
    }   