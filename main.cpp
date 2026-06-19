// ============================================================
// main.cpp - Smart Cybersecurity Threat Detection Platform
//
// Academic DSA Project
// Demonstrates: Queue, Stack, AVL Tree, Hash Table, Graph,
//               BFS, DFS, Merge Sort, Binary Search
// ============================================================

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <vector>

#include "Alert.h"
#include "Threat.h"
#include "Alertqueue.h"
#include "Recoverystack.h"
#include "Avltree.h"
#include "Threathashtable.h"
#include "Networkgraph.h"
#include "Mergesort.h"
#include "Binarysearch.h"

using namespace std;

// ---- Utility helpers ----------------------------------------

// Get a simple timestamp string
string getTimestamp() {
    time_t now = time(nullptr);
    char   buf[32];
    struct tm t;
#ifdef _WIN32
    localtime_s(&t, &now);
#else
    localtime_r(&now, &t);
#endif
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &t);
    return string(buf);
}

// Clear screen (cross-platform)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pressEnterToContinue() {
    cout << "\nPress Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}

// Input validation: read an integer within [lo, hi]
int readInt(const string& prompt, int lo, int hi) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= lo && val <= hi) {
            cin.ignore(1000, '\n');
            return val;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "  [!] Please enter a number between " << lo << " and " << hi << ".\n";
    }
}

// Read a non-empty string
string readString(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    while (s.empty()) {
        cout << "  [!] Input cannot be empty. " << prompt;
        getline(cin, s);
    }
    return s;
}

// ---- Display Banner -----------------------------------------

void showBanner() {
    cout << "\n";
    cout << "====================================================\n";
    cout << "   SMART CYBERSECURITY THREAT DETECTION PLATFORM\n";
    cout << "====================================================\n";
}

void showMenu() {
    showBanner();
    cout << "\n--- ALERT MANAGEMENT (Queue) ---\n";
    cout << "  1.  Add Security Alert\n";
    cout << "  2.  Process Next Alert\n";
    cout << "  3.  Display Pending Alerts\n";

    cout << "\n--- THREAT INTELLIGENCE (AVL Tree) ---\n";
    cout << "  4.  Add Threat Record\n";
    cout << "  5.  Search Threat Record\n";
    cout << "  6.  Delete Threat Record\n";
    cout << "  7.  Display Threat Database\n";

    cout << "\n--- FAST LOOKUP (Hash Table) ---\n";
    cout << "  8.  Fast Threat Lookup (Hash Table)\n";

    cout << "\n--- ALGORITHMS ---\n";
    cout << "  9.  Sort Threats By Severity (Merge Sort)\n";
    cout << "  10. Binary Search Threat\n";

    cout << "\n--- NETWORK TOPOLOGY (Graph) ---\n";
    cout << "  11. Add Network Device\n";
    cout << "  12. Add Network Connection\n";
    cout << "  13. Display Network\n";
    cout << "  14. Analyze Attack Spread (BFS)\n";
    cout << "  15. Trace Attack Path (DFS)\n";

    cout << "\n--- RECOVERY (Stack) ---\n";
    cout << "  16. Add Recovery Action\n";
    cout << "  17. Rollback Last Recovery Action\n";
    cout << "  18. Display Recovery History\n";

    cout << "\n  19. Exit\n";
    cout << "====================================================\n";
}

// ---- Collect all threats from AVL into an array ------------
// (Used by Sort and Binary Search which operate on arrays)

void collectThreats(AVLTree& avl, vector<Threat>& out) {
    // We store a small shadow list for sort/search operations.
    // In production this would be an iterator; here we use the
    // user-entered IDs.  Instead, we let main track insertions.
    (void)avl;
    (void)out;
}

// ============================================================
// MAIN
// ============================================================

int main() {
    // ---- Instantiate all DSA components --------------------
    AlertQueue      alertQueue;
    RecoveryStack   recoveryStack;
    AVLTree         avlTree;
    ThreatHashTable hashTable;
    NetworkGraph    network;

    // Shadow vector for sort/search (mirrors AVL Tree contents)
    vector<Threat> threatList;

    // ID counters
    int nextAlertID    = 1000;
    int nextActionID   = 1;

    // ---- Pre-load sample data ------------------------------
    cout << "\n[SYSTEM] Loading sample data...\n";

    // Sample threats
    Threat t1(101, "WannaCry",       5, "Ransomware",  "Active");
    Threat t2(102, "Phishing-2024",  3, "Phishing",    "Under Investigation");
    Threat t3(103, "Log4Shell",      4, "Zero-Day",    "Mitigated");
    Threat t4(104, "SQL-Injection",  2, "Web Attack",  "Active");
    Threat t5(105, "DDoS-Amplify",   4, "DDoS",        "Active");

    for (auto& t : {t1, t2, t3, t4, t5}) {
        avlTree.insertThreat(t);
        hashTable.hashInsert(t);
        threatList.push_back(t);
    }

    // Sample network
    network.addEdge("PC1",          "FIREWALL");
    network.addEdge("PC2",          "FIREWALL");
    network.addEdge("FIREWALL",     "SERVER");
    network.addEdge("SERVER",       "DATABASE");
    network.addEdge("SERVER",       "EMAIL_SERVER");

    cout << "[SYSTEM] Sample data loaded.\n\n";
    pressEnterToContinue();

    // ---- Main menu loop ------------------------------------
    bool running = true;
    while (running) {
        clearScreen();
        showMenu();

        int choice = readInt("Enter choice: ", 1, 19);

        cout << "\n";

        switch (choice) {

        // ================================================
        // 1. Add Security Alert
        // ================================================
        case 1: {
            cout << "--- ADD SECURITY ALERT ---\n\n";
            string type = readString("Alert Type (e.g. Intrusion/Malware/DDoS): ");
            int sev     = readInt("Severity (1=Low, 5=Critical): ", 1, 5);

            Alert a(nextAlertID++, type, sev, getTimestamp());
            alertQueue.enqueueAlert(a);
            break;
        }

        // ================================================
        // 2. Process Next Alert
        // ================================================
        case 2: {
            cout << "--- PROCESS NEXT ALERT ---\n\n";
            Alert processed;
            if (alertQueue.processAlert(processed)) {
                cout << "\n[+] Processing Alert:\n";
                cout << "    ID       : " << processed.alertID    << "\n";
                cout << "    Type     : " << processed.alertType  << "\n";
                cout << "    Severity : " << processed.severity   << "\n";
                cout << "    Time     : " << processed.timestamp  << "\n";
                cout << "[+] Alert dispatched to SOC analyst.\n";
            }
            break;
        }

        // ================================================
        // 3. Display Pending Alerts
        // ================================================
        case 3: {
            alertQueue.displayAlerts();
            break;
        }

        // ================================================
        // 4. Add Threat Record (AVL + Hash)
        // ================================================
        case 4: {
            cout << "--- ADD THREAT RECORD ---\n\n";
            int    id   = readInt("Threat ID   : ", 1, 99999);
            string name = readString("Threat Name : ");
            int    sev  = readInt("Severity (1-5): ", 1, 5);
            string cat  = readString("Category (e.g. Ransomware): ");
            string stat = readString("Status (Active/Mitigated/Under Investigation): ");

            Threat t(id, name, sev, cat, stat);
            avlTree.insertThreat(t);
            hashTable.hashInsert(t);

            // Update shadow list (add or replace)
            bool found = false;
            for (auto& x : threatList) {
                if (x.threatID == id) { x = t; found = true; break; }
            }
            if (!found) threatList.push_back(t);
            break;
        }

        // ================================================
        // 5. Search Threat Record (AVL)
        // ================================================
        case 5: {
            cout << "--- SEARCH THREAT (AVL Tree) ---\n\n";
            int id = readInt("Enter Threat ID to search: ", 1, 99999);
            Threat* result = avlTree.searchThreat(id);
            if (result) {
                cout << "\n[FOUND] Threat Record:\n";
                cout << "  ID       : " << result->threatID   << "\n";
                cout << "  Name     : " << result->threatName << "\n";
                cout << "  Severity : " << result->severity   << "\n";
                cout << "  Category : " << result->category   << "\n";
                cout << "  Status   : " << result->status     << "\n";
            } else {
                cout << "[AVL] Threat ID " << id << " not found.\n";
            }
            break;
        }

        // ================================================
        // 6. Delete Threat Record (AVL + Hash)
        // ================================================
        case 6: {
            cout << "--- DELETE THREAT RECORD ---\n\n";
            int id = readInt("Enter Threat ID to delete: ", 1, 99999);
            avlTree.deleteThreat(id);
            hashTable.hashDelete(id);
            // Remove from shadow list
            for (int i = 0; i < (int)threatList.size(); i++) {
                if (threatList[i].threatID == id) {
                    threatList.erase(threatList.begin() + i);
                    break;
                }
            }
            break;
        }

        // ================================================
        // 7. Display Threat Database (AVL inorder)
        // ================================================
        case 7: {
            avlTree.displayThreats();
            break;
        }

        // ================================================
        // 8. Fast Threat Lookup (Hash Table)
        // ================================================
        case 8: {
            cout << "--- FAST THREAT LOOKUP (Hash Table) ---\n\n";
            cout << "1. Search by ID\n";
            cout << "2. Display full hash table\n";
            int sub = readInt("Choice: ", 1, 2);

            if (sub == 1) {
                int id = readInt("Enter Threat ID: ", 1, 99999);
                Threat* r = hashTable.hashSearch(id);
                if (r) {
                    cout << "\n[HASH FOUND] Threat Record:\n";
                    cout << "  ID       : " << r->threatID   << "\n";
                    cout << "  Name     : " << r->threatName << "\n";
                    cout << "  Severity : " << r->severity   << "\n";
                    cout << "  Category : " << r->category   << "\n";
                    cout << "  Status   : " << r->status     << "\n";
                } else {
                    cout << "[HASH] Threat ID " << id << " not found.\n";
                }
            } else {
                hashTable.displayHashTable();
            }
            break;
        }

        // ================================================
        // 9. Sort Threats By Severity (Merge Sort)
        // ================================================
        case 9: {
            cout << "--- SORT THREATS BY SEVERITY (Merge Sort) ---\n\n";
            if (threatList.empty()) {
                cout << "No threats to sort.\n";
                break;
            }

            cout << "1. Ascending  (Low -> Critical)\n";
            cout << "2. Descending (Critical -> Low)\n";
            int sub = readInt("Choice: ", 1, 2);

            // Copy to array for sort
            vector<Threat> arr(threatList);
            MergeSort::mergeSortThreats(arr.data(), (int)arr.size(), sub == 1);
            break;
        }

        // ================================================
        // 10. Binary Search Threat
        // ================================================
        case 10: {
            cout << "--- BINARY SEARCH THREAT ---\n\n";
            if (threatList.empty()) {
                cout << "No threats available.\n";
                break;
            }

            cout << "1. Search by Threat ID   (requires sorted-by-ID array)\n";
            cout << "2. Search by Severity    (requires sorted-by-Severity array)\n";
            int sub = readInt("Choice: ", 1, 2);

            if (sub == 1) {
                // Sort by ID then search
                vector<Threat> arr(threatList);
                // Simple insertion sort by ID for precondition (n is small in demo)
                for (int i = 1; i < (int)arr.size(); i++) {
                    Threat key = arr[i];
                    int j = i - 1;
                    while (j >= 0 && arr[j].threatID > key.threatID) {
                        arr[j+1] = arr[j]; j--;
                    }
                    arr[j+1] = key;
                }

                int id  = readInt("Enter Threat ID to find: ", 1, 99999);
                int idx = BinarySearch::binarySearchByID(arr.data(), (int)arr.size(), id);
                if (idx != -1) {
                    cout << "\n[BINARY SEARCH] Found at index " << idx << ":\n";
                    cout << "  ID       : " << arr[idx].threatID   << "\n";
                    cout << "  Name     : " << arr[idx].threatName << "\n";
                    cout << "  Severity : " << arr[idx].severity   << "\n";
                    cout << "  Category : " << arr[idx].category   << "\n";
                    cout << "  Status   : " << arr[idx].status     << "\n";
                } else {
                    cout << "[BINARY SEARCH] Threat ID " << id << " not found.\n";
                }
            } else {
                // Sort by severity then search (reuse Merge Sort)
                vector<Threat> arr(threatList);
                MergeSort::mergeSortThreats(arr.data(), (int)arr.size(), true);

                int sev = readInt("Enter Severity to find (1-5): ", 1, 5);
                int idx = BinarySearch::binarySearchBySeverity(arr.data(), (int)arr.size(), sev);
                if (idx != -1) {
                    cout << "\n[BINARY SEARCH] First match at index " << idx << ":\n";
                    // Show all matches
                    cout << "\nAll threats with severity " << sev << ":\n";
                    for (int i = 0; i < (int)arr.size(); i++) {
                        if (arr[i].severity == sev) {
                            cout << "  [ID:" << arr[i].threatID
                                 << " " << arr[i].threatName << "]\n";
                        }
                    }
                } else {
                    cout << "[BINARY SEARCH] No threat with severity " << sev << " found.\n";
                }
            }
            break;
        }

        // ================================================
        // 11. Add Network Device
        // ================================================
        case 11: {
            cout << "--- ADD NETWORK DEVICE ---\n\n";
            string dev = readString("Device name (e.g. PC3): ");
            network.addVertex(dev);
            break;
        }

        // ================================================
        // 12. Add Network Connection
        // ================================================
        case 12: {
            cout << "--- ADD NETWORK CONNECTION ---\n\n";
            string from = readString("Source device      : ");
            string to   = readString("Destination device : ");
            network.addEdge(from, to);
            break;
        }

        // ================================================
        // 13. Display Network
        // ================================================
        case 13: {
            network.displayGraph();
            break;
        }

        // ================================================
        // 14. Analyze Attack Spread (BFS)
        // ================================================
        case 14: {
            cout << "--- ANALYZE ATTACK SPREAD (BFS) ---\n\n";
            cout << "BFS shows level-by-level spread from an infected device.\n\n";
            string start = readString("Enter infected device name: ");
            network.bfsAttackSpread(start);
            break;
        }

        // ================================================
        // 15. Trace Attack Path (DFS)
        // ================================================
        case 15: {
            cout << "--- TRACE ATTACK PATH (DFS) ---\n\n";
            cout << "DFS performs deep traversal for forensic investigation.\n\n";
            string start = readString("Enter starting device: ");
            network.dfsAttackTrace(start);
            break;
        }

        // ================================================
        // 16. Add Recovery Action (Stack push)
        // ================================================
        case 16: {
            cout << "--- ADD RECOVERY ACTION ---\n\n";
            string name   = readString("Action name   (e.g. Isolate PC1): ");
            string target = readString("Target device (e.g. PC1): ");

            RecoveryAction ra(nextActionID++, name, target, getTimestamp());
            recoveryStack.pushRecoveryAction(ra);
            break;
        }

        // ================================================
        // 17. Rollback Last Recovery Action (Stack pop)
        // ================================================
        case 17: {
            cout << "--- ROLLBACK LAST RECOVERY ACTION ---\n\n";
            RecoveryAction undone;
            if (recoveryStack.rollbackAction(undone)) {
                cout << "\n[ROLLBACK] Undone action:\n";
                cout << "  ID     : " << undone.actionID    << "\n";
                cout << "  Action : " << undone.actionName  << "\n";
                cout << "  Target : " << undone.targetDevice<< "\n";
                cout << "  Time   : " << undone.timestamp   << "\n";
            }
            break;
        }

        // ================================================
        // 18. Display Recovery History
        // ================================================
        case 18: {
            recoveryStack.displayRecoveryActions();
            break;
        }

        // ================================================
        // 19. Exit
        // ================================================
        case 19: {
            cout << "\n[SYSTEM] Shutting down Cybersecurity Platform...\n";
            cout << "[SYSTEM] All data cleared. Goodbye.\n\n";
            running = false;
            break;
        }

        default:
            cout << "Invalid choice.\n";
        }

        if (running) pressEnterToContinue();
    }

    return 0;
}