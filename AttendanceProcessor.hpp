#ifndef ATTENDANCEPROCESSOR_HPP
#define ATTENDANCEPROCESSOR_HPP

#include <string>
#include <vector>
using namespace std;

class AttendanceProcessor {
private:
    vector<string> validNames;
    vector<string> validEmails;

    bool duplicateNameChecker(string name);
    bool duplicateEmailChecker(string email);
    bool validEmailDomain(string email);

public:
    AttendanceProcessor();

    bool processEntry(string name, string email);
    vector<string> getValidNames();
    vector<string> getValidEmails();
};

#endif