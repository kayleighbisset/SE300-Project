// SE300 Project!!!!!!!!!!!!!!!!!!!!!! IM GOONING RN
#include "Management.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

struct Event {
    string title;
    string date;
    string location;
    string description;
    vector<string> customFields;
    string attendanceLink;
    string qrCode;
};

struct AttendanceSubmission {
    string attendeeName;
    string email;
    string eventTitle;
    string eventDate;
    vector<string> customResponses;
};
Manager::Manager() {
    // [SDD_HLD_MGMT_001]
}

// Management Class
void start Management::() {
    // [SDD_HLD_MGMT_002]
    cout<<"ARATS Program has started."<< endl;
}

// EventManager
# include "EventManager.hpp"

EventManager::EventManager() {
    // [SDD_HLD_EVENT_001]
}

void EventManager::createEvent(const std::string& name, const std::string& date) {
    // [SDD_HLD_EVENT_001]
    events.push_back({name, date});
}

std::string EventManager::generateQRCode(const Event& event) {
    // [SDD_HLD_EVENT_002]
    return qrCodeGenerator.generate(event.name, event.date);
}

// QRCodeGenerator
#include "QRCodeGenerator.h"

QRCodeGenerator::QRCodeGenerator() {
    // [SDD_HLD_QR_001]
}

std::string QRCodeGenerator::generate(const std::string& eventName, const std::string& eventDate) {
    // [SDD_HLD_QR_002]
    return "QR_" + eventName + "_" + eventDate;
}
