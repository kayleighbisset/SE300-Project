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

// [SDD_HLD_MGMT_001]
Management::Management() {
    myEvent = new EventManager();
    myAttend = new AttendanceSystem();
}

// [SDD_HLD_MGMT_002]
void Management::start() {
    int choice = 0;

    while (1) {
        cout << "\n==============================\n";
        cout << "ARATS Main Menu\n";
        cout << "==============================\n";
        cout << "1. Create Event\n";
        cout << "2. View Events\n";
        cout << "3. Submit Attendance\n";
        cout << "4. View Attendance Submissions\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            myEvent->createEvent();
        }
        else if (choice == 2) {
            myEvent->displayEvents();
        }
        else if (choice == 3) {
            if (!myEvent->hasEvents()) {
                cout << "No events exist yet.\n";
            }
            else {
                int eventNumber;
                myEvent->displayEvents();

                cout << "Select event number: ";
                cin >> eventNumber;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input.\n";
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                Event* selectedEvent = myEvent->getEvent(eventNumber - 1);

                if (selectedEvent == nullptr) {
                    cout << "Invalid event number.\n";
                }
                else {
                    myAttend->submitAttendance(*selectedEvent);
                }
            }
        }
        else if (choice == 4) {
            myAttend->displaySubmissions();
        }
        else if (choice == 5) {
            cout << "Exiting ARATS.\n";
            break;
        }
        else {
            cout << "Invalid menu option.\n";
        }
    }
}

Management::~Management() {
    delete myEvent;
    delete myAttend;
}

/ =====================================================
// 3.2 EventManager
// =====================================================

EventManager::EventManager() {
}

// [SDD_HLD_EVENT_001]
void EventManager::createEvent() {
    Event newEvent;

    cout << "\nEnter event title: ";
    getline(cin, newEvent.title);

    cout << "Enter event date: ";
    getline(cin, newEvent.date);

    cout << "Enter event location: ";
    getline(cin, newEvent.location);

    cout << "Enter event description: ";
    getline(cin, newEvent.description);

    if (newEvent.title.empty() || newEvent.date.empty()) {
        cout << "Event title and date are required.\n";
        return;
    }

    while (1) {
        string answer;
        cout << "Would you like to add a custom event field? (y/n): ";
        getline(cin, answer);

        if (answer == "y" || answer == "Y") {
            customDetail(newEvent);
        }
        else if (answer == "n" || answer == "N") {
            break;
        }
        else {
            cout << "Please enter y or n.\n";
        }
    }

    generateQRCode(newEvent);
    events.push_back(newEvent);

    cout << "\nEvent created.\n";
    cout << "Attendance Link: " << newEvent.attendanceLink << "\n";
    cout << "QR Code: " << newEvent.qrCode << "\n";
}

void EventManager::customDetail(Event& newEvent) {
    string fieldTitle;

    cout << "Enter custom field title: ";
    getline(cin, fieldTitle);

    if (!fieldTitle.empty()) {
        newEvent.customFields.push_back(fieldTitle);
    }
    else {
        cout << "Custom field title cannot be empty.\n";
    }
}

// [SDD_HLD_EVENT_002]
void EventManager::generateQRCode(Event& newEvent) {
    QRCodeGenerator myQR;
    myQR.generateQR(newEvent);
    myQR.storeQR(newEvent);
}

bool EventManager::hasEvents() const {
    return !events.empty();
}

void EventManager::displayEvents() const {
    if (events.empty()) {
        cout << "No events available.\n";
        return;
    }

    cout << "\n===== Events =====\n";
    for (int i = 0; i < (int)events.size(); i++) {
        cout << i + 1 << ". "
             << events[i].title << " | "
             << events[i].date << " | "
             << events[i].location << "\n";
    }
}

Event* EventManager::getEvent(int index) {
    if (index < 0 || index >= (int)events.size()) {
        return nullptr;
    }

    return &events[index];
}

// QRCodeGenerator
// [SDD_HLD_QR_001]
QRCodeGenerator::QRCodeGenerator() {
    attendanceLink = "";
    qrCode = "";
}

// [SDD_HLD_QR_002]
void QRCodeGenerator::generateQR(Event& eventInfo) {
    attendanceLink =
        "https://arats.local/checkin?title=" +
        eventInfo.title +
        "&date=" +
        eventInfo.date;

    qrCode = "QR[" + attendanceLink + "]";
}

void QRCodeGenerator::storeQR(Event& eventInfo) {
    eventInfo.attendanceLink = attendanceLink;
    eventInfo.qrCode = qrCode;
}

// AttendanceSystem

// [SDD_HLD_SYST_001]
AttendanceSystem::AttendanceSystem() {
}

bool AttendanceSystem::isValidEmail(const string& email) const {
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);

    return !email.empty() &&
           atPos != string::npos &&
           dotPos != string::npos &&
           atPos > 0 &&
           dotPos > atPos + 1 &&
           dotPos < email.size() - 1;
}

// [SDD_HLD_SYST_002]
void AttendanceSystem::submitAttendance(Event eventInfo) {
    AttendanceSubmission submission;

    submission.eventTitle = eventInfo.title;
    submission.eventDate = eventInfo.date;

    cout << "\nEnter attendee name: ";
    getline(cin, submission.attendeeName);

    cout << "Enter attendee email: ";
    getline(cin, submission.email);

    if (submission.attendeeName.empty()) {
        cout << "Attendee name is required.\n";
        return;
    }

    if (!isValidEmail(submission.email)) {
        cout << "Valid email is required.\n";
        return;
    }

    for (int i = 0; i < (int)eventInfo.customFields.size(); i++) {
        string response;
        cout << "Enter " << eventInfo.customFields[i] << ": ";
        getline(cin, response);
        submission.customResponses.push_back(response);
    }

    submissions.push_back(submission);

    cout << "Attendance submitted.\n";
    cout << "Submission sent to AttendanceProcessor.\n";
}

void AttendanceSystem::displaySubmissions() const {
    if (submissions.empty()) {
        cout << "No attendance submissions recorded.\n";
        return;
    }

    cout << "\n===== Attendance Submissions =====\n";
    for (int i = 0; i < (int)submissions.size(); i++) {
        cout << i + 1 << ". "
             << submissions[i].attendeeName << " | "
             << submissions[i].email << " | "
             << submissions[i].eventTitle << " | "
             << submissions[i].eventDate << "\n";
    }
}

// main
int main() {
    Management myManagement;
    myManagement.start();
    return 0;
}


