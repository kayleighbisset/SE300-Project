#include "AttendanceProcessor.hpp"

AttendanceProcessor::AttendanceProcessor() {
}

bool AttendanceProcessor::duplicateNameChecker(string name) {
    for (int i = 0; i < validNames.size(); i++) {
        if (validNames[i] == name) {
            return true;
        }
    }

    return false;
}

bool AttendanceProcessor::duplicateEmailChecker(string email) {
    for (int i = 0; i < validEmails.size(); i++) {
        if (validEmails[i] == email) {
            return true;
        }
    }

    return false;
}

bool AttendanceProcessor::validEmailDomain(string email) {
    string testDomain = "@my.erau.edu";

    if (email.length() < testDomain.length()) {
        return false;
    }

    return email.compare(email.length() - testDomain.length(), testDomain.length(), testDomain) == 0;
}

bool AttendanceProcessor::processEntry(string name, string email) {
    bool valid = true;

    if (duplicateNameChecker(name)) {
        valid = false;
    }

    if (duplicateEmailChecker(email)) {
        valid = false;
    }

    if (!validEmailDomain(email)) {
        valid = false;
    }

    if (valid) {
        validNames.push_back(name);
        validEmails.push_back(email);
    }

    return valid;
}

vector<string> AttendanceProcessor::getValidNames() {
    return validNames;
}

vector<string> AttendanceProcessor::getValidEmails() {
    return validEmails;
}