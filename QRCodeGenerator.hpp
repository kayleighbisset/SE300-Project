#ifndef QRCODEGENERATOR_HPP
#define QRCODEGENERATOR_HPP

#include <string>
using namespace std;

class QRCodeGenerator {
public:
    QRCodeGenerator();
    string generate(string eventTitle, string eventDate);
};

#endif
