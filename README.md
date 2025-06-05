# Smart-city-Simulator
A C++ simulation that builds an optimal infrastructure layout for a smart city using:
- Kruskal’s Algorithm for minimum cost road construction (MST)
- Dijkstra’s Algorithm for fastest path queries (shortest travel time)

# Features
- Build a cost-efficient road network connecting all zones.
- Simulate shortest travel times between zones.
- Uses DSU (Union by Size) and Priority Queue.

# Algorithms Used
 1. ## Kruskal’s Algorithm  – For Infrastructure Planning (MST)
- Purpose:
To connect all zones of the smart city with minimum possible cost, avoiding cycles.
- How it works:
Treat each zone as a node and each possible road as an edge with a construction cost.
Sort all roads based on cost.
Use Disjoint Set Union (DSU) to avoid cycles.
Add the lowest cost edges to the network unless it creates a cycle.
- DSU (Union by Size):
Helps track connected components efficiently.

- Result:
We get a Minimum Spanning Tree (MST) which is the most cost-efficient infrastructure to connect all zones

2. ## Dijkstra’s Algorithm – For Travel Time Optimization
- Purpose:
To simulate shortest travel time from any zone to all others in the smart city.
- How it works:
Uses a priority queue (min-heap) to greedily select the shortest distance node.
For every adjacent zone, relax the edge if a shorter path is found.
Keeps updating the shortest distances from the source node.

- Result:
We obtain fastest travel times from a zone to all others, helping citizens and logistics.
  
