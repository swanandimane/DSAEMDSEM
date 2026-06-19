#include "Avltree.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

// ============================================================
// AVLTree.cpp - Self-Balancing Binary Search Tree
// Keyed on Threat::threatID
// ============================================================

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() { destroyTree(root); }

void AVLTree::destroyTree(AVLNode* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// ---- Utility -----------------------------------------------

int AVLTree::height(AVLNode* n) const {
    return n ? n->height : 0;
}

int AVLTree::balanceFactor(AVLNode* n) const {
    return n ? height(n->left) - height(n->right) : 0;
}

void AVLTree::updateHeight(AVLNode* n) {
    if (n)
        n->height = 1 + max(height(n->left), height(n->right));
}

// ---- Rotations ---------------------------------------------

// Right rotation (for left-heavy subtree)
AVLTree::AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x  = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left  = T2;
    updateHeight(y);
    updateHeight(x);
    return x;   // New root of this subtree
}

// Left rotation (for right-heavy subtree)
AVLTree::AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y  = x->right;
    AVLNode* T2 = y->left;
    y->left  = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

// Apply the correct rotation(s) to restore AVL property
AVLTree::AVLNode* AVLTree::rebalance(AVLNode* n) {
    updateHeight(n);
    int bf = balanceFactor(n);

    // Left-Left case
    if (bf > 1 && balanceFactor(n->left) >= 0)
        return rotateRight(n);

    // Left-Right case
    if (bf > 1 && balanceFactor(n->left) < 0) {
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }

    // Right-Right case
    if (bf < -1 && balanceFactor(n->right) <= 0)
        return rotateLeft(n);

    // Right-Left case
    if (bf < -1 && balanceFactor(n->right) > 0) {
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }

    return n;   // Already balanced
}

// ---- Insert ------------------------------------------------

AVLTree::AVLNode* AVLTree::insert(AVLNode* node, const Threat& t) {
    if (!node) return new AVLNode(t);

    if (t.threatID < node->data.threatID)
        node->left = insert(node->left, t);
    else if (t.threatID > node->data.threatID)
        node->right = insert(node->right, t);
    else {
        // Duplicate ID: update existing record
        node->data = t;
        return node;
    }

    return rebalance(node);
}

void AVLTree::insertThreat(const Threat& t) {
    root = insert(root, t);
    cout << "[AVL] Threat \"" << t.threatName
         << "\" (ID: " << t.threatID << ") inserted/updated.\n";
}

// ---- Delete ------------------------------------------------

AVLTree::AVLNode* AVLTree::minNode(AVLNode* node) const {
    while (node->left) node = node->left;
    return node;
}

AVLTree::AVLNode* AVLTree::deleteNode(AVLNode* node, int id) {
    if (!node) return nullptr;

    if (id < node->data.threatID)
        node->left = deleteNode(node->left, id);
    else if (id > node->data.threatID)
        node->right = deleteNode(node->right, id);
    else {
        // Node found
        if (!node->left || !node->right) {
            AVLNode* tmp = node->left ? node->left : node->right;
            delete node;
            return tmp;
        }
        // Two children: replace with inorder successor
        AVLNode* successor = minNode(node->right);
        node->data         = successor->data;
        node->right        = deleteNode(node->right, successor->data.threatID);
    }

    return rebalance(node);
}

bool AVLTree::deleteThreat(int id) {
    AVLNode* check = search(root, id);
    if (!check) {
        cout << "[AVL] Threat ID " << id << " not found.\n";
        return false;
    }
    root = deleteNode(root, id);
    cout << "[AVL] Threat ID " << id << " deleted.\n";
    return true;
}

// ---- Search ------------------------------------------------

AVLTree::AVLNode* AVLTree::search(AVLNode* node, int id) const {
    if (!node)                  return nullptr;
    if (id == node->data.threatID) return node;
    if (id  < node->data.threatID) return search(node->left,  id);
    return search(node->right, id);
}

Threat* AVLTree::searchThreat(int id) const {
    AVLNode* found = search(root, id);
    return found ? &found->data : nullptr;
}

// ---- Display (Inorder = sorted by ID) ----------------------

void AVLTree::inorder(AVLNode* node) const {
    if (!node) return;
    inorder(node->left);
    const Threat& t = node->data;
    cout << left
         << setw(6)  << t.threatID
         << setw(22) << t.threatName
         << setw(10) << t.severity
         << setw(18) << t.category
         << setw(22) << t.status
         << "\n";
    inorder(node->right);
}

void AVLTree::displayThreats() const {
    if (!root) {
        cout << "[AVL] Threat database is empty.\n";
        return;
    }
    cout << "\n============================================================\n";
    cout << "            THREAT INTELLIGENCE DATABASE (AVL Tree)\n";
    cout << "============================================================\n";
    cout << left
         << setw(6)  << "ID"
         << setw(22) << "Name"
         << setw(10) << "Severity"
         << setw(18) << "Category"
         << setw(22) << "Status"
         << "\n";
    cout << string(78, '-') << "\n";
    inorder(root);
    cout << "============================================================\n";
}