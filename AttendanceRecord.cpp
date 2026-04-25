#include "AttendanceRecord.hpp"

AttendanceRecord::AttendanceRecord() {
    attendeeName = "";
    attendeeEmail = "";
    eventTitle = "";
    eventDate = "";
}
// [SDD_HLD_RECORDS_001]
AttendanceRecord::AttendanceRecord(string name, string email, string title, string date, vector<string> fields) {
    attendeeName = name;
    attendeeEmail = email;
    eventTitle = title;
    eventDate = date;
    customFields = fields;
}

string AttendanceRecord::getAttendeeName() {
    return attendeeName;
}

string AttendanceRecord::getAttendeeEmail() {
    return attendeeEmail;
}

string AttendanceRecord::getEventTitle() {
    return eventTitle;
}

string AttendanceRecord::getEventDate() {
    return eventDate;
}

vector<string> AttendanceRecord::getCustomFields() {
    return customFields;
}
