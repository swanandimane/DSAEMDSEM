#include "Threathashtable.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ============================================================
// ThreatHashTable.cpp - Separate Chaining Hash Table
// ============================================================

ThreatHashTable::ThreatHashTable() : count(0) {
    for (int i = 0; i < TABLE_SIZE; i++)
        table[i] = nullptr;
}

ThreatHashTable::~ThreatHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ChainNode* curr = table[i];
        while (curr) {
            ChainNode* tmp = curr->next;
            delete curr;
            curr = tmp;
        }
    }
}

// Division method: simple and effective for integer keys
int ThreatHashTable::hashFunction(int id) const {
    return (id % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE;
}

// O(1) average - Insert at head of chain for O(1)
void ThreatHashTable::hashInsert(const Threat& t) {
    int idx = hashFunction(t.threatID);

    // Check for duplicate key and update
    ChainNode* curr = table[idx];
    while (curr) {
        if (curr->data.threatID == t.threatID) {
            curr->data = t;
            cout << "[HASH] Threat ID " << t.threatID << " updated in bucket " << idx << ".\n";
            return;
        }
        curr = curr->next;
    }

    // Insert at head of chain
    ChainNode* newNode = new ChainNode(t);
    newNode->next = table[idx];
    table[idx]    = newNode;
    count++;
    cout << "[HASH] Threat \"" << t.threatName
         << "\" inserted at bucket " << idx << ".\n";
}

// O(1) average
Threat* ThreatHashTable::hashSearch(int id) {
    int        idx  = hashFunction(id);
    ChainNode* curr = table[idx];
    while (curr) {
        if (curr->data.threatID == id) return &curr->data;
        curr = curr->next;
    }
    return nullptr;
}

// O(1) average
bool ThreatHashTable::hashDelete(int id) {
    int        idx  = hashFunction(id);
    ChainNode* curr = table[idx];
    ChainNode* prev = nullptr;

    while (curr) {
        if (curr->data.threatID == id) {
            if (prev) prev->next  = curr->next;
            else       table[idx] = curr->next;
            delete curr;
            count--;
            cout << "[HASH] Threat ID " << id << " deleted.\n";
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "[HASH] Threat ID " << id << " not found.\n";
    return false;
}

// Display every bucket and its chain
void ThreatHashTable::displayHashTable() const {
    cout << "\n============================================================\n";
    cout << "         THREAT HASH TABLE (Size=" << TABLE_SIZE << ", Count=" << count << ")\n";
    cout << "============================================================\n";

    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "Bucket[" << setw(2) << i << "] : ";
        ChainNode* curr = table[i];
        if (!curr) {
            cout << "(empty)\n";
        } else {
            while (curr) {
                cout << "[ID:" << curr->data.threatID
                     << " " << curr->data.threatName
                     << " Sev:" << curr->data.severity << "]";
                if (curr->next) cout << " -> ";
                curr = curr->next;
            }
            cout << "\n";
        }
    }
    cout << "============================================================\n";
}

int  ThreatHashTable::size()    const { return count; }
bool ThreatHashTable::isEmpty() const { return count == 0; }