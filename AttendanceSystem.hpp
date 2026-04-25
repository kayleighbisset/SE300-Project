#ifndef ATTENDANCESYSTEM_HPP
#define ATTENDANCESYSTEM_HPP

#include "AttendanceRecord.hpp"
#include <string>
#include <vector>
using namespace std;

// [SDD_HLD_SYST_001]
// [SDD_HLD_SYST_002]
class AttendanceSystem {
private:
    AttendanceRecord attendanceRecord;

public:
    AttendanceSystem();

    void submitAttendance(string name, string email, string eventTitle, string eventDate, vector<string> customFields);
    AttendanceRecord& getRecord();
};

#endif
