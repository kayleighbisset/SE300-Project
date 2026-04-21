#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <string>
#include <vector>
#include "QRCodeGenerator.hpp"
using namespace std;

class Event {
private:
    string title;
    string date;
    string qrLink;

public:
    Event();
    Event(string eventTitle, string eventDate, string link);

    string getTitle();
    string getDate();
    string getQRLink();
};

class EventManager {
private:
    vector<Event> events;
    QRCodeGenerator qrCodeGenerator;

public:
    EventManager();

    void createEvent(string title, string date);
    void displayEvents();
    vector<Event>& getEvents();
};

#endif
