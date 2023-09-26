/* Author: Matheus Oliveira
 * Codeforces problem: 1873/H
 * Based upon the tutorial answer: https://codeforces.com/blog/entry/120634
 * 
 * Solução:
 * Pelo enunciado, o grafo é não-direcional, conectado e possui sempre o número de arestas igual ao número de nós; isso garante que o grafo sempre possuirá um ciclo.
 * Valeriu inicia-se na posição b e Marcel na posição a.
 * Valeriu busca entrar no ciclo o mais rapido possível, onde ele sempre conseguirá escapar de Marcel.
 * O único modo de Valeriu não conseguir fugir de Marcel, é se Marcel alcançar o nó de entrada do ciclo de Valeriu antes dele.
 * 
*/

#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int N = (int) 2e5 + 5;

vector <vector <int>> G(N);
vector <bool> visited(N);

int entry_node;

// DFS com o propósito de encontrar o ponto de entrada do ciclo para Valeriu, que começa no ponto b.
// Encontra-se o nó de entrada do ciclo, por procurar por qualquer nó que já tenha sido visitado e que não seja o nó pai desse respectivo nó.
// Ou seja, quando a DFS terminar de percorrer o ciclo, encontrará o nó que serviu de entrada ao ciclo.
bool dfs (int vertex, int parent) {
    visited[vertex] = true;
    for (auto v : G[vertex]) {
        if (v != parent && visited[v]) {
            entry_node = v;
            return true;
        } else if (v != parent && !visited[v]) {
            if (dfs(v, vertex)) return true;
        }
    }
    return false;
}
// ---------------

// DFS com o propósito de encontrar a distancia de Marcel e Valeriu do nó de entrada.
// Se a distancia de Marcel for menor que a distancia de Valeriu, Valeriu não conseguirá escapar.
int distance_dfs (int vertex) {
    visited[vertex] = true;
    int dist = N;
    for (auto v : G[vertex]) {
        if (v == entry_node) return 1;
        if (!visited[v]) {
            int aux = distance_dfs(v) + 1;
            dist = min(dist, aux);
        }
    }
    return dist;
}
// ---------------

void solve() {
    
    // Leitura de valores e preenchimento da lista de adjacencias
    int n, a, b;
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    // ---------------
    
    // Primeira DFS entre b e um nó pai não existente (já que o ponto b, onde Valeriu se inicia, é uma ponta (folha)), para encontrar o nó de entrada do ciclo.
    // Conforme o DFS funcionar, o nó pai vai atualizando para os nós que estão no grafo.
    dfs(b, -1);
    // ---------------
    
    // Reseta os valores da lista de nós visitados.
    // Usa a função distance_dfs para encontrar a distancia de Marcel, depois de Valeriu, até o nó de entrada.
    visited.assign(n + 1, false);
    int distMarcel = N, distValeriu = 0;
    if (entry_node == a) distMarcel = 0;
    else distMarcel = distance_dfs(a);

    visited.assign(n + 1, false);
    if (entry_node == b) distValeriu = 0;
    else distValeriu = distance_dfs(b);
    // ---------------

    if (distValeriu < distMarcel) cout << "YES\n";
    else cout << "NO\n";

    // Zera a lista de adjacências e a lista de nós visitados para o próximo caso de teste.
    for (int i = 1; i <= n; i++) {
        G[i].clear();
        visited[i] = false;
    }
    // ---------------

}

// Main apenas busca os vários casos de teste.
int main () {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
// ---------------