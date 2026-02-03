#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

// Problem: Flight Discount (CSES)
// Description: Find the shortest path from node 1 to node n with a 50% discount on one edge.
// Algorithm: Use 2 Dijkstra: from start and from end (reversed graph)
// Time complexity: O((n+m) log n)
// Author: Hung Dang Pham

constexpr int kMaxNode = 1e5;
constexpr long long kInf = 1e18;

int num_node, num_edge;
vector<pair<int, int>> adj[kMaxNode + 1], radj[kMaxNode + 1];

void Input() {
    cin >> num_node >> num_edge;
    for(int i = 1; i <= num_edge; ++i){
        int u, v, c;
        cin >> u >> v >> c;

        adj[u].push_back({c, v});
        radj[v].push_back({c, u});
    }
}

long long dist[2][kMaxNode + 1];

void Dijkstra(int s, long long dist[], const vector<pair<int, int>> g[]){
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, s});

    while(!pq.empty()){
        long long du = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(du != dist[u]){
            continue;
        }
        
        for(auto e : g[u]){
            int c = e.first, v = e.second;

            if(dist[v] > 0ll + du + c){
                dist[v] = 0ll + du + c;
                pq.push({dist[v], v});
            }
        }
    }
}

void Solve() {
    memset(dist, 0x3f, sizeof dist);
    dist[0][1] = 0; 
    dist[1][num_node] = 0;
    
    Dijkstra(1, dist[0], adj);
    Dijkstra(num_node, dist[1], radj);

    long long ans = kInf;
    for(int u = 1; u <= num_node; ++u){
        for(auto e : adj[u]){
            int c = e.first, v = e.second;
            ans = min(ans, 0ll + dist[0][u] + (c / 2) + dist[1][v]);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Input();
    Solve();
    return 0;
}