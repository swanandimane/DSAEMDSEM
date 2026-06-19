#pragma once
#include <string>

// ============================================================
// Alert.h - Data model for incoming security alerts
// Used by the Queue (AlertQueue) to represent each alert event
// ============================================================

struct Alert {
    int alertID;
    std::string alertType;   // e.g., "Intrusion", "Malware", "DDoS"
    int severity;            // 1 (Low) to 5 (Critical)
    std::string timestamp;   // e.g., "2024-01-15 10:30:00"

    Alert() : alertID(0), alertType(""), severity(0), timestamp("") {}

    Alert(int id, const std::string& type, int sev, const std::string& ts)
        : alertID(id), alertType(type), severity(sev), timestamp(ts) {}
};