#ifndef ATTENDANCERECORD_HPP
#define ATTENDANCERECORD_HPP

#include <string>
#include <vector>
using namespace std;

// [SDD_HLD_RECORDS_001]
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

#endif
