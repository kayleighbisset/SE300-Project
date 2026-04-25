#include <string.h>
#include <stdio.h>
#include <stdbool.h>

char processedNames[100][128];
char processedEmails[100][128];

bool duplicateChecker(char list[][128], int count, char value[]) {
    int i;

    for (i = 0; i < count; i++) {
        if (strcmp(list[i], value) == 0) {
            return true;
        }
    }

    return false;
}

int attendanceProcessor(
    const char* names[],
    const char* emails[],
    int count,
    int badPositions[]
) {
    int badCount = 0;
    int goodCount = 0;
    int i;

    char testDomain[] = "@my.erau.edu";

    for (i = 1; i < count; i++) {
        bool valid = true;

        char currentName[128];
        char currentEmail[128];

        strcpy(currentName, names[i]);
        strcpy(currentEmail, emails[i]);

        if (duplicateChecker(processedNames, goodCount, currentName)) {
            valid = false;
        }

        if (strstr(currentEmail, testDomain) == NULL) {
            valid = false;
        }

        if (duplicateChecker(processedEmails, goodCount, currentEmail)) {
            valid = false;
        }

        if (valid) {
            strcpy(processedNames[goodCount], currentName);
            strcpy(processedEmails[goodCount], currentEmail);

            printf("Valid Entry: %s | %s\n", currentName, currentEmail);

            goodCount++;
        }
        else {
            badPositions[badCount] = i;
            badCount++;

            printf("Invalid entry at position %d\n", i);
        }
    }

    return badCount;
}