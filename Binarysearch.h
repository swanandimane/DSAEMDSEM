#pragma once
#include "Threat.h"

// ============================================================
// BinarySearch.h - Binary Search on sorted Threat arrays
//
// WHY BINARY SEARCH?
//   After sorting with Merge Sort, Binary Search reduces lookup
//   from O(n) linear scan to O(log n) -- critical when the
//   analyst needs to find a specific threat under pressure.
//
// PRECONDITION: Array must be sorted by the target field.
//
// TIME COMPLEXITY  : O(log n)
// SPACE COMPLEXITY : O(1)
// ============================================================

class BinarySearch {
public:
    // Search by exact Threat ID (array sorted by threatID ascending)
    static int binarySearchByID(const Threat arr[], int n, int targetID);

    // Search by severity -- returns first match index
    // (array sorted by severity ascending)
    static int binarySearchBySeverity(const Threat arr[], int n, int targetSeverity);
};