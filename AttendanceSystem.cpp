#include "AttendanceSystem.hpp"

AttendanceSystem::AttendanceSystem() {
}

void AttendanceSystem::submitAttendance(string name, string email, string eventTitle, string eventDate, vector<string> customFields) {
    attendanceRecord = AttendanceRecord(name, email, eventTitle, eventDate, customFields);
}

AttendanceRecord& AttendanceSystem::getRecord() {
    return attendanceRecord;
}