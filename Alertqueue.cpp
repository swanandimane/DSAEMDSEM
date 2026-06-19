#include "Alertqueue.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ============================================================
// AlertQueue.cpp - Implementation of Linked List Queue
// ============================================================

AlertQueue::AlertQueue() : front(nullptr), rear(nullptr), count(0) {}

AlertQueue::~AlertQueue() {
    // Free all nodes to prevent memory leaks
    Node* curr = front;
    while (curr) {
        Node* tmp = curr->next;
        delete curr;
        curr = tmp;
    }
}

// O(1) - Insert at tail
void AlertQueue::enqueueAlert(const Alert& alert) {
    Node* newNode = new Node(alert);
    if (rear == nullptr) {
        // Queue was empty
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    count++;
    cout << "[QUEUE] Alert #" << alert.alertID
         << " (" << alert.alertType << ") enqueued successfully.\n";
}

// O(1) - Remove from head
bool AlertQueue::processAlert(Alert& outAlert) {
    if (front == nullptr) {
        cout << "[QUEUE] No pending alerts to process.\n";
        return false;
    }
    outAlert = front->data;
    Node* tmp = front;
    front = front->next;
    if (front == nullptr) rear = nullptr;  // Queue became empty
    delete tmp;
    count--;
    return true;
}

// O(n) - Display all pending alerts
void AlertQueue::displayAlerts() const {
    if (front == nullptr) {
        cout << "[QUEUE] No pending alerts.\n";
        return;
    }

    cout << "\n============================================================\n";
    cout << "             PENDING SECURITY ALERTS (" << count << ")\n";
    cout << "============================================================\n";
    cout << left
         << setw(8)  << "ID"
         << setw(20) << "Type"
         << setw(10) << "Severity"
         << setw(22) << "Timestamp"
         << "\n";
    cout << string(60, '-') << "\n";

    Node* curr = front;
    while (curr) {
        const Alert& a = curr->data;
        cout << left
             << setw(8)  << a.alertID
             << setw(20) << a.alertType
             << setw(10) << a.severity
             << setw(22) << a.timestamp
             << "\n";
        curr = curr->next;
    }
    cout << "============================================================\n";
}

bool AlertQueue::isEmpty() const { return count == 0; }
int  AlertQueue::size()    const { return count; }