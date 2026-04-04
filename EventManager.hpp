#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <vector>
#include <string>
#include "QRCodeGenerator.h"
using namespace std;

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
