#pragma once
#include <string>

// ============================================================
// NetworkGraph.h - Adjacency List Graph for Network Topology
//
// WHY GRAPH?
//   A network is naturally modelled as a graph: devices are
//   vertices and connections (cables/links) are edges.
//   Adjacency lists use O(V+E) space vs O(V^2) for a matrix.
//
// TIME COMPLEXITY:
//   addVertex     : O(1)
//   addEdge       : O(1)
//   displayGraph  : O(V + E)
//   BFS / DFS     : O(V + E)
//
// SPACE COMPLEXITY: O(V + E)
// ============================================================

class NetworkGraph {
private:
    static const int MAX_VERTICES = 50;

    // Adjacency list node
    struct AdjNode {
        int      vertexIdx;   // Index into vertices[]
        AdjNode* next;
        explicit AdjNode(int v) : vertexIdx(v), next(nullptr) {}
    };

    struct Vertex {
        std::string name;
        bool        used;
        Vertex() : name(""), used(false) {}
    };

    Vertex   vertices[MAX_VERTICES];
    AdjNode* adjList[MAX_VERTICES];  // Head of adjacency list per vertex
    int      vertexCount;

    // Internal helpers
    int  findVertex(const std::string& name) const;
    int  addVertexInternal(const std::string& name);

    // BFS/DFS helpers
    void bfsHelper(int start) const;
    void dfsHelper(int start, bool visited[]) const;

public:
    NetworkGraph();
    ~NetworkGraph();

    // Vertex / Edge management
    bool addVertex(const std::string& name);
    bool addEdge(const std::string& from, const std::string& to);
    void displayGraph() const;

    // Attack analysis
    void bfsAttackSpread(const std::string& startDevice) const;
    void dfsAttackTrace(const std::string& startDevice) const;

    int  getVertexCount() const;
};