#ifndef QRCODEGENERATOR_HPP
#define QRCODEGENERATOR_HPP

#include <cstring>
#include <iostream>
using namespace std;

class QRCodeGenerator {
public:
    QRCodeGenerator();
    string generate(string eventTitle, string eventDate);

    
    //refer back on how to use API Key with create QR QRCodeGenerator (mention how this was still in progress)
};

#endif
