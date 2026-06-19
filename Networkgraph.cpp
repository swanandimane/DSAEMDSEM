#include "Networkgraph.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

// ============================================================
// NetworkGraph.cpp - Adjacency List Graph + BFS + DFS
// ============================================================

NetworkGraph::NetworkGraph() : vertexCount(0) {
    for (int i = 0; i < MAX_VERTICES; i++)
        adjList[i] = nullptr;
}

NetworkGraph::~NetworkGraph() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        AdjNode* curr = adjList[i];
        while (curr) {
            AdjNode* tmp = curr->next;
            delete curr;
            curr = tmp;
        }
    }
}

// ---- Vertex helpers ----------------------------------------

int NetworkGraph::findVertex(const string& name) const {
    for (int i = 0; i < vertexCount; i++)
        if (vertices[i].used && vertices[i].name == name) return i;
    return -1;
}

int NetworkGraph::addVertexInternal(const string& name) {
    int existing = findVertex(name);
    if (existing != -1) return existing;
    if (vertexCount >= MAX_VERTICES) return -1;
    vertices[vertexCount].name = name;
    vertices[vertexCount].used = true;
    return vertexCount++;
}

bool NetworkGraph::addVertex(const string& name) {
    if (findVertex(name) != -1) {
        cout << "[GRAPH] Device \"" << name << "\" already exists.\n";
        return false;
    }
    if (vertexCount >= MAX_VERTICES) {
        cout << "[GRAPH] Maximum device limit reached.\n";
        return false;
    }
    addVertexInternal(name);
    cout << "[GRAPH] Device \"" << name << "\" added to network.\n";
    return true;
}

// ---- Edge --------------------------------------------------

bool NetworkGraph::addEdge(const string& from, const string& to) {
    int u = addVertexInternal(from);
    int v = addVertexInternal(to);
    if (u == -1 || v == -1) {
        cout << "[GRAPH] Could not add edge (vertex limit).\n";
        return false;
    }

    // Add undirected edge: u -> v and v -> u
    AdjNode* newU = new AdjNode(v);
    newU->next    = adjList[u];
    adjList[u]    = newU;

    AdjNode* newV = new AdjNode(u);
    newV->next    = adjList[v];
    adjList[v]    = newV;

    cout << "[GRAPH] Connection added: " << from << " <--> " << to << "\n";
    return true;
}

// ---- Display -----------------------------------------------

void NetworkGraph::displayGraph() const {
    if (vertexCount == 0) {
        cout << "[GRAPH] Network is empty.\n";
        return;
    }
    cout << "\n============================================================\n";
    cout << "               NETWORK TOPOLOGY (Adjacency List)\n";
    cout << "============================================================\n";
    for (int i = 0; i < vertexCount; i++) {
        if (!vertices[i].used) continue;
        cout << setw(15) << vertices[i].name << " : ";
        AdjNode* curr = adjList[i];
        while (curr) {
            cout << vertices[curr->vertexIdx].name;
            if (curr->next) cout << " -> ";
            curr = curr->next;
        }
        cout << "\n";
    }
    cout << "============================================================\n";
}

// ---- BFS ---------------------------------------------------
// WHY BFS? It explores level-by-level, showing how an attack
// spreads hop-by-hop from the infected device -- ideal for
// containment analysis.
// TIME: O(V + E)

void NetworkGraph::bfsHelper(int start) const {
    bool visited[MAX_VERTICES] = {};

    // Manual queue using an array (or could reuse AlertQueue)
    int queue[MAX_VERTICES];
    int qFront = 0, qRear = 0;

    visited[start] = true;
    queue[qRear++] = start;

    int level = 0;
    cout << "\n[BFS] Attack Spread from \"" << vertices[start].name << "\":\n";
    cout << string(50, '-') << "\n";

    // We track level boundaries with two counters
    int currLevelCount = 1;
    int nextLevelCount = 0;

    while (qFront < qRear) {
        int u = queue[qFront++];
        currLevelCount--;
        cout << "  Level " << level << " : " << vertices[u].name << "\n";

        AdjNode* curr = adjList[u];
        while (curr) {
            int v = curr->vertexIdx;
            if (!visited[v]) {
                visited[v]       = true;
                queue[qRear++]   = v;
                nextLevelCount++;
            }
            curr = curr->next;
        }

        if (currLevelCount == 0) {
            level++;
            currLevelCount = nextLevelCount;
            nextLevelCount = 0;
        }
    }
    cout << string(50, '-') << "\n";
    cout << "[BFS] Total devices reachable: " << qRear << "\n";
}

void NetworkGraph::bfsAttackSpread(const string& startDevice) const {
    int idx = findVertex(startDevice);
    if (idx == -1) {
        cout << "[BFS] Device \"" << startDevice << "\" not found.\n";
        return;
    }
    bfsHelper(idx);
}

// ---- DFS ---------------------------------------------------
// WHY DFS? Deep traversal follows the full attack path to its
// origin -- used for forensic investigation and root-cause
// analysis.
// TIME: O(V + E)

void NetworkGraph::dfsHelper(int u, bool visited[]) const {
    visited[u] = true;
    cout << "  -> " << vertices[u].name << "\n";

    AdjNode* curr = adjList[u];
    while (curr) {
        if (!visited[curr->vertexIdx])
            dfsHelper(curr->vertexIdx, visited);
        curr = curr->next;
    }
}

void NetworkGraph::dfsAttackTrace(const string& startDevice) const {
    int idx = findVertex(startDevice);
    if (idx == -1) {
        cout << "[DFS] Device \"" << startDevice << "\" not found.\n";
        return;
    }

    bool visited[MAX_VERTICES] = {};
    cout << "\n[DFS] Attack Trace from \"" << startDevice << "\":\n";
    cout << string(50, '-') << "\n";
    dfsHelper(idx, visited);
    cout << string(50, '-') << "\n";
    cout << "[DFS] Trace complete.\n";
}

int NetworkGraph::getVertexCount() const { return vertexCount; }