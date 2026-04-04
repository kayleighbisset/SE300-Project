#ifndef MANAGEMENT_HPP
#define MANAGEMENT_HPP

#include "EventManager.hpp"
#include "AttendanceSystem.hpp"

class Management {
private:
    EventManager eventManager;
    AttendanceSystem attendanceSystem;

public:
    Management();
    void start();
};

#endif
