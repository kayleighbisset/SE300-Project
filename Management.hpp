#ifndef MANAGEMENT_HPP
#define MANAGEMENT_HPP

#include <string>
#include <vector>
using namespace std;

class Management {
public:
    Management();
    void start();

private:
    string removeQuotes(string text);
};

#endif