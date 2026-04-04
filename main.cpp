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
            eventManager.createEvent();
        }
        else if (choice == 2) {
            eventManager.displayEvents();
        }
        else if (choice == 3) {
            if (!eventManager.hasEvents()) {
                cout << "No events exist yet.\n";
            }
            else {
                int eventNumber;
                eventManager.displayEvents();

                cout << "Select event number: ";
                cin >> eventNumber;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input.\n";
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n')
// main
int main() {
    Management myManagement;
    myManagement.start();
    return 0;
}


