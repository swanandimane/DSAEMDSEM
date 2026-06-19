#pragma once
#include <string>

// ============================================================
// Threat.h - Data model for threat intelligence records
// Used by AVL Tree, Hash Table, Merge Sort, Binary Search
// ============================================================

struct Threat {
    int threatID;
    std::string threatName;
    int severity;               // 1 (Low) to 5 (Critical)
    std::string category;       // e.g., "Ransomware", "Phishing", "Zero-Day"
    std::string status;         // "Active", "Mitigated", "Under Investigation"

    Threat() : threatID(0), threatName(""), severity(0), category(""), status("") {}

    Threat(int id, const std::string& name, int sev,
           const std::string& cat, const std::string& stat)
        : threatID(id), threatName(name), severity(sev), category(cat), status(stat) {}
};