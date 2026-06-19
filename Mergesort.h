#pragma once
#include "Threat.h"

// ============================================================
// MergeSort.h - Merge Sort for Threat Prioritization
//
// WHY MERGE SORT?
//   Merge Sort is stable and guarantees O(n log n) in all
//   cases, unlike Quick Sort (O(n^2) worst case).  Stability
//   ensures threats with equal severity preserve relative
//   insertion order -- important for audit trails.
//
// TIME COMPLEXITY  : O(n log n) - all cases
// SPACE COMPLEXITY : O(n)       - temporary merge array
// ============================================================

class MergeSort {
private:
    // Merge two sorted halves back into arr[left..right]
    static void merge(Threat arr[], int left, int mid, int right, bool ascending);

    // Recursive divide step
    static void mergeSort(Threat arr[], int left, int right, bool ascending);

public:
    // Sort a flat array of Threat objects
    static void mergeSortThreats(Threat arr[], int n, bool ascending = true);
};