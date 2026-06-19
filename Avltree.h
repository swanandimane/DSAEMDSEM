#pragma once
#include "Threat.h"

// ============================================================
// AVLTree.h - Self-Balancing AVL Tree for Threat Intelligence
//
// WHY AVL TREE INSTEAD OF BST?
//   A plain BST degrades to O(n) on sorted insertions (skewed
//   tree).  AVL guarantees O(log n) for all operations by
//   maintaining a balance factor (-1, 0, +1) at every node and
//   performing rotations on insertion/deletion.
//
// TIME COMPLEXITY:
//   insertThreat  : O(log n)
//   deleteThreat  : O(log n)
//   searchThreat  : O(log n)
//   displayThreats (inorder) : O(n)
//
// SPACE COMPLEXITY: O(n)
// ============================================================

class AVLTree {
private:
    struct AVLNode {
        Threat   data;
        AVLNode* left;
        AVLNode* right;
        int      height;

        explicit AVLNode(const Threat& t)
            : data(t), left(nullptr), right(nullptr), height(1) {}
    };

    AVLNode* root;

    // Helper utilities
    int      height(AVLNode* n) const;
    int      balanceFactor(AVLNode* n) const;
    void     updateHeight(AVLNode* n);

    // Rotations
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* rebalance(AVLNode* n);

    // Recursive helpers
    AVLNode* insert(AVLNode* node, const Threat& t);
    AVLNode* deleteNode(AVLNode* node, int id);
    AVLNode* minNode(AVLNode* node) const;
    AVLNode* search(AVLNode* node, int id) const;

    void     inorder(AVLNode* node) const;
    void     destroyTree(AVLNode* node);

public:
    AVLTree();
    ~AVLTree();

    void    insertThreat(const Threat& t);
    bool    deleteThreat(int id);
    Threat* searchThreat(int id) const;
    void    displayThreats() const;
};