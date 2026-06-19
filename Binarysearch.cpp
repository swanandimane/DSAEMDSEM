#include "Binarysearch.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ============================================================
// BinarySearch.cpp
// ============================================================

// O(log n) - Iterative binary search by Threat ID
int BinarySearch::binarySearchByID(const Threat arr[], int n, int targetID) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;   // Avoids integer overflow

        if (arr[mid].threatID == targetID) {
            return mid;   // Found
        } else if (arr[mid].threatID < targetID) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;   // Not found
}

// O(log n) - Binary search by severity (sorted ascending)
// Returns the leftmost index with matching severity
int BinarySearch::binarySearchBySeverity(const Threat arr[], int n, int targetSeverity) {
    int low = 0, high = n - 1, result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid].severity == targetSeverity) {
            result = mid;       // Found, but keep looking left for first occurrence
            high   = mid - 1;
        } else if (arr[mid].severity < targetSeverity) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}