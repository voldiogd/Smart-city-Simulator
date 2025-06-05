#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
    vector<int> rank, parent, size;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
        return;
    }
};

// ========== Dijkstra’s Algorithm ==========
vector<int> dijkstra(int src, int V, vector<vector<pair<int, int>>> &adj) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first;
        int node= pq.top().second;
        pq.pop();

        for (auto it : adj[node]) {
            int adjNode= it.first;
            int wt =it.second;
            if (dist[adjNode] > d + wt) {
                dist[adjNode] = d + wt;
                pq.push({dist[adjNode], adjNode});
            }
        }
    }
    return dist;
}

// ========== Smart City Simulator ==========
class SmartCity {
public:
    int buildNetwork(int V, vector<tuple<int, int, int, int>> &roads, vector<vector<pair<int, int>>> &mstAdj) {
        // roads = {cost, time, u, v}
        sort(roads.begin(), roads.end());
        DisjointSet ds(V);
        int totalCost = 0;

        cout << " Roads selected for Smart City (Minimum Cost - Kruskal):\n";
        for (auto &it : roads) {
            int cost=get<0>(it), time=get<1>(it), u=get<2>(it), v=get<3>(it);
            if (ds.findUPar(u) != ds.findUPar(v)) {
                ds.unionBySize(u, v);
                totalCost += cost;
                mstAdj[u].push_back({v, time});
                mstAdj[v].push_back({u, time});
                cout << u << " <--> " << v << " | Cost: ₹" << cost << ", Time: " << time << " mins\n";
            }
        }

        return totalCost;
    }

    void showShortestPaths(int V, vector<vector<pair<int, int>>> &adj, int src) {
        cout << "\n Shortest Travel Times from Zone " << src << ":\n";
        vector<int> dist = dijkstra(src, V, adj);
        for (int i = 0; i < V; i++) {
            cout << " To Zone " << i << ": ";
            if (dist[i] == INT_MAX) cout << "Not reachable\n";
            else cout << dist[i] << " mins\n";
        }
        int sm = accumulate(dist.begin(), dist.end(),0);
        cout << "Total Time to go all zones = "<< sm << " mins \n";
    }
};

int main() {
    int V = 6; // Number of zones (nodes)
    vector<tuple<int, int, int, int>> roads = {
        // {construction_cost, travel_time, u, v}
        {4, 10, 0, 1}, {2, 5, 0, 2}, {3, 7, 1, 2},
        {7, 12, 1, 3}, {6, 8, 2, 4}, {5, 6, 3, 4}, {8, 9, 4, 5}
    };

    SmartCity city;
    vector<vector<pair<int, int>>> mstAdj(V); // Adjacency list for MST (used in Dijkstra)
    int total = city.buildNetwork(V, roads, mstAdj);

    cout << "\n Total Construction Cost: ₹" << total << "\n";

    // Run Dijkstra from a source zone
    for(int i=0; i<V; i++){
        int sourceZone = i;
        city.showShortestPaths(V, mstAdj, sourceZone);
    }

    return 0;
}
