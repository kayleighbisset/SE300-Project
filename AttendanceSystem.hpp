#ifndef ATTENDANCESYSTEM_HPP
#define ATTENDANCESYSTEM_HPP

#include <string>
#include <vector>
#include "AttendanceProcessor.hpp"
using namespace std;

class AttendanceSystem {
private:
    AttendanceProcessor attendanceProcessor;

public:
    AttendanceSystem();

    void submitAttendance(string name, string email, string eventTitle, string eventDate, vector<string> customFields);
    AttendanceProcessor& getProcessor();
};

#endif
