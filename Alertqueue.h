#pragma once
#include "Alert.h"

// ============================================================
// AlertQueue.h - Linked List based Queue for Security Alerts
//
// WHY QUEUE?
//   Alerts arrive continuously and must be handled in FIFO order
//   (First In, First Out) -- just like a real SOC (Security
//   Operations Centre) triage process.
//
// TIME COMPLEXITY:
//   enqueueAlert  : O(1)  -- insert at tail
//   processAlert  : O(1)  -- remove from head
//   displayAlerts : O(n)  -- traverse all nodes
//
// SPACE COMPLEXITY: O(n) -- one node per alert
// ============================================================

class AlertQueue {
private:
    // Internal linked list node
    struct Node {
        Alert data;
        Node* next;
        explicit Node(const Alert& a) : data(a), next(nullptr) {}
    };

    Node* front;   // Points to oldest (next-to-process) alert
    Node* rear;    // Points to newest (last-added) alert
    int   count;   // Number of pending alerts

public:
    AlertQueue();
    ~AlertQueue();

    // Add a new alert to the back of the queue
    void enqueueAlert(const Alert& alert);

    // Remove and return the front alert (FIFO processing)
    bool processAlert(Alert& outAlert);

    // Show all pending alerts without removing them
    void displayAlerts() const;

    bool isEmpty() const;
    int  size()    const;
};