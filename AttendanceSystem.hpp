#ifndef ATTENDANCESYSTEM_HPP
#define ATTENDANCESYSTEM_HPP

#include "AttendanceRecord.hpp"
#include <string>
#include <vector>
using namespace std;

class AttendanceSystem {
private:
    AttendanceRecord attendanceRecord;

public:
    AttendanceSystem();

    void submitAttendance(string name, string email, string eventTitle, string eventDate, vector<string> customFields);
    AttendanceRecord& getRecord();
};

#endif