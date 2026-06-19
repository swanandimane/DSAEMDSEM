#pragma once
#include <string>

// ============================================================
// RecoveryStack.h - Linked List based Stack for Recovery Actions
//
// WHY STACK?
//   Recovery/rollback operations are inherently LIFO (Last In,
//   First Out).  If you apply action A then B, you must undo B
//   before A -- exactly what a stack models.
//
// TIME COMPLEXITY:
//   pushRecoveryAction   : O(1)
//   rollbackAction       : O(1)
//   displayRecoveryActions: O(n)
//
// SPACE COMPLEXITY: O(n)
// ============================================================

struct RecoveryAction {
    int         actionID;
    std::string actionName;    // e.g., "Isolate PC1", "Block IP 192.168.1.5"
    std::string targetDevice;
    std::string timestamp;

    RecoveryAction() : actionID(0) {}
    RecoveryAction(int id, const std::string& name,
                   const std::string& dev, const std::string& ts)
        : actionID(id), actionName(name), targetDevice(dev), timestamp(ts) {}
};

class RecoveryStack {
private:
    struct Node {
        RecoveryAction data;
        Node* next;
        explicit Node(const RecoveryAction& a) : data(a), next(nullptr) {}
    };

    Node* top;    // Top of the stack (most recent action)
    int   count;

public:
    RecoveryStack();
    ~RecoveryStack();

    // Push a new recovery action onto the stack
    void pushRecoveryAction(const RecoveryAction& action);

    // Pop (undo) the last recovery action
    bool rollbackAction(RecoveryAction& outAction);

    // Display full recovery history (top to bottom)
    void displayRecoveryActions() const;

    bool isEmpty() const;
    int  size()    const;
};