#ifndef DUPLICATECHECKER_HPP
#define DUPLICATECHECKER_HPP

#include <string>
#include <vector>
using namespace std;

class AttendanceRecord;

class DuplicateChecker {
public:
    DuplicateChecker();
    bool checkDuplicate(vector<AttendanceRecord>& records, string email, string eventTitle, string eventDate);
};

#endif
