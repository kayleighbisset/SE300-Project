#include "Management.hpp"
#include "AttendanceProcessor.hpp"
#include "FileIOandAttendanceProcessor.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

Management::Management() {
}

string Management::removeQuotes(string text) {
    string cleaned = "";

    for (int i = 0; i < text.length(); i++) {
        if (text[i] != '"') {
            cleaned += text[i];
        }
    }

    return cleaned;
}

void Management::start() {
    string date;
    string club;
    string menuChoice;
    string inputfile;
    string outputfile;
    vector<string> otherInfo;

    cout << "\nWhat is the date of your meeting? ";
    getline(cin, date);

    cout << "\nWhat club/organization is this for? ";
    getline(cin, club);

    cout << "\nDo you have other relevant meeting information? (1 for No, 2 for Yes): ";
    getline(cin, menuChoice);

    while (menuChoice != "1" && menuChoice != "2") {
        cout << "\nInvalid input. Please enter either 1 or 2: ";
        getline(cin, menuChoice);
    }

    if (menuChoice == "2") {
        string info = "";

        cout << "\nEnter other meeting information one line at a time.";
        cout << "\nEnter 1 when finished:\n";

        while (info != "1") {
            getline(cin, info);

            if (info != "1") {
                otherInfo.push_back(info);
            }
        }
    }

    cout << "\nEnter the name of the input file: ";
    getline(cin, inputfile);

    ifstream inputFile(inputfile);

    while (!inputFile) {
        cout << "Error: Could not open input file.\n";
        cout << "Enter the name of the input file: ";
        getline(cin, inputfile);
        inputFile.open(inputfile);
    }

    cout << "\nEnter the name of the output file: ";
    getline(cin, outputfile);

    ofstream outputFile(outputfile);

    if (!outputFile) {
        cout << "Error: Could not open output file.\n";
        return;
    }

    AttendanceProcessor processor;

    string line;
    string timestamp;
    string name;
    string email;
    int invalidCount = 0;
    int lineNumber = 0;

    outputFile << "\"Timestamp\",\"First and last name\",\"ERAU Email\"\n";

    while (getline(inputFile, line)) {
        stringstream ss(line);

        getline(ss, timestamp, ',');
        getline(ss, name, ',');
        getline(ss, email);

        timestamp = removeQuotes(timestamp);
        name = removeQuotes(name);
        email = removeQuotes(email);

        if (lineNumber != 0) {
            if (processor.processEntry(name, email)) {
                outputFile << "\"" << timestamp << "\",\"" << name << "\",\"" << email << "\"\n";
            }
            else {
                invalidCount++;
            }
        }

        lineNumber++;
    }

    outputFile << "\nDate: " << date << endl;
    outputFile << "Club: " << club << endl;

    if (otherInfo.size() > 0) {
        outputFile << "\nOther Info:\n";

        for (int i = 0; i < otherInfo.size(); i++) {
            outputFile << otherInfo[i] << endl;
        }
    }

    inputFile.close();
    outputFile.close();

    cout << "\nAttendance form created successfully as " << outputfile << endl;
    cout << invalidCount << " invalid entries were found.\n";
}