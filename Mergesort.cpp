#include "Mergesort.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ============================================================
// MergeSort.cpp
// ============================================================

void MergeSort::merge(Threat arr[], int left, int mid, int right, bool ascending) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary arrays (dynamic allocation to support large n)
    Threat* L = new Threat[n1];
    Threat* R = new Threat[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        bool pick;
        if (ascending)
            pick = (L[i].severity <= R[j].severity);
        else
            pick = (L[i].severity >= R[j].severity);

        if (pick) arr[k++] = L[i++];
        else       arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void MergeSort::mergeSort(Threat arr[], int left, int right, bool ascending) {
    if (left >= right) return;   // Base case: single element
    int mid = left + (right - left) / 2;
    mergeSort(arr, left,    mid,   ascending);
    mergeSort(arr, mid + 1, right, ascending);
    merge    (arr, left,    mid,   right, ascending);
}

void MergeSort::mergeSortThreats(Threat arr[], int n, bool ascending) {
    if (n <= 0) return;
    mergeSort(arr, 0, n - 1, ascending);

    // Display sorted result
    string order = ascending ? "ASCENDING (Low -> Critical)" : "DESCENDING (Critical -> Low)";
    cout << "\n============================================================\n";
    cout << "    THREATS SORTED BY SEVERITY (" << order << ")\n";
    cout << "============================================================\n";
    cout << left
         << setw(6)  << "ID"
         << setw(22) << "Name"
         << setw(10) << "Severity"
         << setw(18) << "Category"
         << setw(22) << "Status"
         << "\n";
    cout << string(78, '-') << "\n";
    for (int i = 0; i < n; i++) {
        cout << left
             << setw(6)  << arr[i].threatID
             << setw(22) << arr[i].threatName
             << setw(10) << arr[i].severity
             << setw(18) << arr[i].category
             << setw(22) << arr[i].status
             << "\n";
    }
    cout << "============================================================\n";
}