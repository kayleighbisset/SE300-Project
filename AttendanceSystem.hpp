#ifndef ATTENDANCESYSTEM_HPP
#define ATTENDANCESYSTEM_HPP

#include <cstring>
#include <vector>
#include "AttendanceRecord.hpp"
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
