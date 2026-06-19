#pragma once
#include "Threat.h"

// ============================================================
// ThreatHashTable.h - Custom Hash Table with Separate Chaining
//
// WHY HASHING?
//   The AVL Tree gives O(log n) lookups.  Hashing provides
//   O(1) average-case lookup, making it ideal for real-time
//   threat identification during active incidents.
//
// COLLISION RESOLUTION: Separate Chaining with Linked Lists
//
// TIME COMPLEXITY:
//   hashInsert : O(1) average, O(n) worst (all in one bucket)
//   hashSearch : O(1) average
//   hashDelete : O(1) average
//
// SPACE COMPLEXITY: O(n + TABLE_SIZE)
// ============================================================

class ThreatHashTable {
private:
    static const int TABLE_SIZE = 17;  // Prime number reduces collisions

    struct ChainNode {
        Threat     data;
        ChainNode* next;
        explicit ChainNode(const Threat& t) : data(t), next(nullptr) {}
    };

    ChainNode* table[TABLE_SIZE];
    int        count;

    // Hash function: maps threatID to a bucket index
    int hashFunction(int id) const;

public:
    ThreatHashTable();
    ~ThreatHashTable();

    void    hashInsert(const Threat& t);
    Threat* hashSearch(int id);
    bool    hashDelete(int id);
    void    displayHashTable() const;

    int  size()    const;
    bool isEmpty() const;
};