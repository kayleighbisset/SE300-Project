#include "FileIOandAttendanceProcessor.hpp"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

char nameList[100][128], emailList[100][128];
char timestamps[100][128], names[100][128], emails[100][128];

// [SDD_HLD_DUP_001]
// [SDD_HLD_DUP_002]
bool duplicateChecker(char list[][128], char *value, int count) {
    int j = 0;

    for (j = 0; j < count; j++) {
        if (strcmp(value, list[j]) == 0) {
            return true;
        }
    }

    return false;
}

// [SDD_HLD_PRO_001]
// [SDD_HLD_PRO_002]
int attendanceProcessor(int count, int badPositions[]) {
    int badCount = 0;
    int goodCount = 1;
    int i = 0;
    int start = 0;
    const char testDomain[20] = "@my.erau.edu";

    
    if ((strstr(names[0], "Name") == NULL && strstr(names[0], "name") == NULL)) {
        start = 0;
        goodCount = 0;
    }
    else {
        strcpy(nameList[0], names[0]);
        strcpy(emailList[0], emails[0]);
        badPositions[0] = 0;
        start = 1;
        goodCount = 1;
    }

    for (i = start; i < count; i++) {
        bool valid = true;

        char currentName[100];
        char currentEmail[100];

        strcpy(currentName, names[i]);
        strcpy(currentEmail, emails[i]);

        // [SDD_HLD_DUP_002]
        if (duplicateChecker(nameList, currentName, goodCount)) {
            valid = false;
        }

        // [SDD_HLD_PRO_001]
        if (strstr(currentEmail, testDomain) == NULL) {
            valid = false;
        }

        // [SDD_HLD_DUP_002]
        if (duplicateChecker(emailList, currentEmail, goodCount)) {
            valid = false;
        }

        // [SDD_HLD_PRO_002]
        if (valid) {
            strcpy(nameList[goodCount], currentName);
            strcpy(emailList[goodCount], currentEmail);

            printf("Name successfully added: %s \n", currentName);
            printf("Email successfully added: %s \n", currentEmail);

            badPositions[i] = 0;
            goodCount++;
        }
        else {
            badPositions[i] = 1;
            badCount++;
            printf("Invalid entry at position %d \n", i);
        }
    }

    return badCount;
}
