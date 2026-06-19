#include "Recoverystack.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ============================================================
// RecoveryStack.cpp - Linked List Stack Implementation
// ============================================================

RecoveryStack::RecoveryStack() : top(nullptr), count(0) {}

RecoveryStack::~RecoveryStack() {
    RecoveryAction dummy;
    while (!isEmpty()) rollbackAction(dummy);
}

// O(1) - Push to top
void RecoveryStack::pushRecoveryAction(const RecoveryAction& action) {
    Node* newNode = new Node(action);
    newNode->next = top;
    top = newNode;
    count++;
    cout << "[STACK] Recovery action \"" << action.actionName
         << "\" pushed (ID: " << action.actionID << ").\n";
}

// O(1) - Pop from top
bool RecoveryStack::rollbackAction(RecoveryAction& outAction) {
    if (top == nullptr) {
        cout << "[STACK] No recovery actions to rollback.\n";
        return false;
    }
    outAction = top->data;
    Node* tmp = top;
    top = top->next;
    delete tmp;
    count--;
    return true;
}

// O(n) - Display from top to bottom
void RecoveryStack::displayRecoveryActions() const {
    if (top == nullptr) {
        cout << "[STACK] Recovery history is empty.\n";
        return;
    }

    cout << "\n============================================================\n";
    cout << "          RECOVERY ACTION HISTORY (" << count << " actions)\n";
    cout << "============================================================\n";
    cout << left
         << setw(6)  << "ID"
         << setw(28) << "Action"
         << setw(15) << "Target"
         << setw(22) << "Timestamp"
         << "\n";
    cout << string(71, '-') << "\n";

    Node* curr = top;
    int   pos  = 1;
    while (curr) {
        const RecoveryAction& a = curr->data;
        cout << left
             << setw(6)  << a.actionID
             << setw(28) << a.actionName
             << setw(15) << a.targetDevice
             << setw(22) << a.timestamp
             << "\n";
        curr = curr->next;
        pos++;
    }
    cout << "============================================================\n";
    cout << "(Top of stack = most recent action)\n";
}

bool RecoveryStack::isEmpty() const { return count == 0; }
int  RecoveryStack::size()    const { return count; }