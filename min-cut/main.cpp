#include <iostream>
#include <vector>
#include <random>
#include <climits>
#include <cmath>

using namespace std;

mt19937 gen(random_device{}());

void contractEdge(vector<vector<int>>& graph, vector<bool>& active, 
                  vector<int>& degrees, int& totalEdges, int& vertices) 
{
    int n = graph.size();
    if (totalEdges == 0) return;

    uniform_int_distribution<int> dist(0, 2*totalEdges - 1);
    int r = dist(gen); //random number
    
    int u,v;
    
    // Choose u node
    for (int i = 0; i < n; i++) {
        if (!active[i]) continue;
        if (r < degrees[i]) {
            u = i;
            break;
        }
        r -= degrees[i];
    }

    // Choose v 
    for (int j = 0; j < n; j++) {
        if (!active[j] || graph[u][j] == 0) continue;
        if (r < graph[u][j]) {
            v = j;
            break;
        }
        r -= graph[u][j];
    }

    // Store cycles to keep track of totalEdges
    int edgesBetweenUV = graph[u][v];

    // Contract v into u
    for (int k = 0; k < n; k++) {
        if (active[k] && k != u && k != v) {
            graph[u][k] += graph[v][k]; // Edges from v to u
            graph[k][u] = graph[u][k]; 
        }
        graph[v][k] = 0;
        graph[k][v] = 0;
    }

    // Remove cycles
    graph[u][u] = 0;

    // Update degrees of u and v. Also totalEdges
    degrees[u] = degrees[u] + degrees[v] - (2 * edgesBetweenUV);
    degrees[v] = 0;
    totalEdges -= edgesBetweenUV;

    // Remove v
    active[v] = false;
    vertices--;
}

int karger(vector<vector<int>>& graph, vector<bool>& active, int targetVertices) 
{
    int n = graph.size();
    int currentVertices = 0;
    for (int i = 0; i < n; i++) {
        if (active[i]) currentVertices++;
    }

    //Precompute degrees and totalEdges
    vector<int> degrees(n,0);
    int totalEdges = 0;

    for(int u = 0; u < n; u++){
        if (!active[u]) continue;
        for(int v = 0; v < n; v++){
            degrees[u] += graph[u][v];
            totalEdges += graph[u][v];
        }
    }

    totalEdges = totalEdges >> 1; //We count em twice

    while (currentVertices > targetVertices) {
        contractEdge(graph, active, degrees, totalEdges, currentVertices);
    }

    if (targetVertices == 2) {
        for (int i = 0; i < n; i++) {
            if (!active[i]) continue;
            for (int j = i + 1; j < n; j++) {
                if (active[j] && graph[i][j] > 0) {
                    return graph[i][j];
                }
            }
        }
        return 0;
    }

    return 0;
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

int main() 
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n, vector<int>(n, 0));

    // read input
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u][v]++;
        adj[v][u]++;
    }


    //int best = fastCut(adj);
    int best = mincut(adj);
    cout << best;

    return 0;
}