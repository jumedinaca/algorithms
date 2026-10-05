#include <iostream>
#include <random>
#include <unordered_set>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // Máximo de aristas en un grafo simple no dirigido
    long long maxEdges = 1LL * n * (n - 1) / 2;

    if (m > maxEdges) {
        cerr << "Error: demasiadas aristas para " << n << " vertices.\n";
        return 1;
    }

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dist(1, n);

    unordered_set<long long> edges;

    while ((int)edges.size() < m) {
        int u = dist(gen);
        int v = dist(gen);

        // Evitar bucles: u != v
        if (u == v)
            continue;

        // Ordenamos para que (1,2) y (2,1) sean la misma arista
        if (u > v)
            swap(u, v);

        // Codificamos la arista como un número
        long long id = 1LL * u * (n + 1) + v;

        edges.insert(id);
    }

    // Imprimir la entrada
    cout << n << " " << m << "\n";

    for (long long id : edges) {
        int v = id % (n + 1);
        int u = id / (n + 1);

        cout << u << " " << v << "\n";
    }

    return 0;
}
