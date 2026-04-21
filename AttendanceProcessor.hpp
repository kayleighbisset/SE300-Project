#ifndef ATTENDANCEPROCESSOR_HPP
#define ATTENDANCEPROCESSOR_HPP

#include <string>
#include <vector>
#include "DuplicateChecker.hpp"
using namespace std;

class AttendanceRecord {
private:
    string attendeeName;
    string attendeeEmail;
    string eventTitle;
    string eventDate;
    vector<string> customFields;

public:
    AttendanceRecord();
    AttendanceRecord(string name, string email, string title, string date, vector<string> fields);

    string getAttendeeName();
    string getAttendeeEmail();
    string getEventTitle();
    string getEventDate();
    vector<string> getCustomFields();
};

class AttendanceProcessor {
private:
    vector<AttendanceRecord> records;
    DuplicateChecker duplicateChecker;

public:
    AttendanceProcessor();

    bool validate(string email);
    bool store(AttendanceRecord record);
    void exportCSV(string fileName);
    vector<AttendanceRecord>& getRecords();
};

#endif
