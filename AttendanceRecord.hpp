#ifndef ATTENDANCERECORD_HPP
#define ATTENDANCERECORD_HPP

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class AttendanceRecord {
private:
  string attendeeName;
  string attendeeEmail;
  string eventTitle;
  string eventDate;
  vector<string> customFields;
public:
  AttendanceRecord();
  AttendanceRecord(string name, string email, string title, string date, vector<string> fields); //default constructor

  //getter functions
  string getAttendeeName();
  string getAttendeeEmail();
  string getEventTitle();
  string getEventDate();
  vector<string> getCustomeFields();
};
#endif
