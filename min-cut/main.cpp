#include <iostream>
#include <vector>
#include <random>
#include <climits>
#include <cmath>

using namespace std;


mt19937 gen(random_device{}());
// Contrae una arista aleatoria
void contractEdge(vector<vector<int>>& graph, int& vertices) 
{

    int n = graph.size();

    // Contar aristas
    int totalEdges = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            totalEdges += graph[i][j];
        }
    }
    

    // cout << vertices<<endl;
    // {
    //     for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout<< graph[i][j] << " ";
    //     }
    //     cout<<endl;
    // }
    // }cout<<endl;


    // Elegir una arista aleatoria
    uniform_int_distribution<int> dist(0, totalEdges - 1);

    int randomEdge = dist(gen);

    int u = -1;
    int v = -1;

    for (int i = 0; i < n && u == -1; i++) {
        for (int j = i + 1; j < n; j++) {

            randomEdge -= graph[i][j];

            if (randomEdge < 0) {
                u = i;
                v = j;
                break;
            }
        }
    }

    // Contraer v -> u
    for (int k = 0; k < n; k++) {

        if (k != u && k != v) {

            graph[u][k] += graph[v][k];
            graph[k][u] = graph[u][k];
        }
    }

    // Eliminar self-loop
    graph[u][u] = 0;

    // Eliminar v
    for (int k = 0; k < n; k++) {
        graph[v][k] = 0;
        graph[k][v] = 0;
    }

    vertices--;
}

int kargerMinCut(vector<vector<int>> graph) 
{
    int n = graph.size();

    // Cantidad de supernodos que quedan
    int vertices = n;

    while (vertices > 2) {
        contractEdge(graph, vertices);
    }

    // Contar las aristas restantes
    // entre los dos supernodos
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] > 0) {
                return graph[i][j];
            }
        }
    }

    return 0;
}

int fastCut(vector<vector<int>> graph) 
{

    int n = graph.size();

    // Caso base
    if (n <= 6) {

        int best = INT_MAX;

        // Hacemos varias ejecuciones de Karger normal
        for (int i = 0; i < 10; i++) {

            vector<vector<int>> copy = graph;

            int vertices = n;

            while (vertices > 2) {
                contractEdge(copy, vertices);
            }

            // Encontrar las aristas restantes
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {

                    if (copy[i][j] > 0) {
                        best = min(best, copy[i][j]);
                    }
                }
            }
        }

        return best;
    }


    // Número objetivo de vértices
    int t = ceil(n / sqrt(2.0));


    // Primera copia
    vector<vector<int>> graph1 = graph;
    int vertices1 = n;
    while (vertices1 > t) {
        contractEdge(graph1, vertices1);
    }

    // Segunda copia
    vector<vector<int>> graph2 = graph;
    int vertices2 = n;
    while (vertices2 > t) {
        contractEdge(graph2, vertices2);
    }

    // Recursión
    int cut1 = fastCut(graph1);
    int cut2 = fastCut(graph2);

    return min(cut1, cut2);
}

int main() 
{

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n, vector<int>(n, 0));

    // Leer las aristas
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        u--;
        v--;

        adj[u][v]++;
        adj[v][u]++;
    }

    int best = INT_MAX;

    // Ejecutar Karger n*lg(n)
    int iterations = n*log2(n);

    for (int i = 0; i < iterations; i++) {
        int cut = kargerMinCut(adj);

        best = min(best, cut);
    }

    cout << best << endl;

    best = fastCut(adj);

    cout << best << endl;

    return 0;
}