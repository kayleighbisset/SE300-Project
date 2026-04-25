#include "Management.hpp"
#include "FileIOandAttendanceProcessor.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Management::Management() {        // [SDD_HLD_MGMT_001]
}

void Management::start() {        // [SDD_HLD_MGMT_002]
    char date[50], club[50], otherinfo[50][50], menuChoice[50];
    char inputfile[100], outputfile[100];
    char line[128];
    int i = 0, j = 0, k = 0;
    int choice = 1;

    printf("\n\nWhat is the date of your meeting? ");
    fgets(date, sizeof(date), stdin);

    printf("\n\nWhat club/organization is this for? ");
    fgets(club, sizeof(club), stdin);

    printf("\n\nDo you have other relevant meeting information? (1 for No, 2 for Yes): ");
    fgets(menuChoice, sizeof(menuChoice), stdin);
    choice = strtol(menuChoice, NULL, 10);

    while (choice != 1 && choice != 2) {
        printf("\n\nInvalid input. Please enter either 1 or 2: ");
        fgets(menuChoice, sizeof(menuChoice), stdin);
        choice = strtol(menuChoice, NULL, 10);
    }

    if (choice != 1) {
        printf("\n\nContinue adding items or enter 1 when finished: ");

        while (choice != 1) {
            fgets(menuChoice, sizeof(menuChoice), stdin);
            choice = strtol(menuChoice, NULL, 10);

            if (choice != 1) {
                strcpy(otherinfo[i], menuChoice);
                i++;
            }
        }
    }
    // [SDD_HLD_CONFIG_001]
    printf("\nEnter the name of the file with your attendance data: ");
    fgets(inputfile, sizeof(inputfile), stdin);
    inputfile[strcspn(inputfile, "\n")] = '\0';
    // [SDD_HLD_RECORDS_001]
    FILE *AttInputTest = fopen(inputfile, "r");

    while (AttInputTest == NULL) {
        printf("Error: Could not open input file.\n");
        printf("Enter the name of the file with your attendance data: ");
        fgets(inputfile, sizeof(inputfile), stdin);
        inputfile[strcspn(inputfile, "\n")] = '\0';
        AttInputTest = fopen(inputfile, "r");
    }

    fclose(AttInputTest);

    printf("\nFinally, which file should we write to? ");
    fgets(outputfile, sizeof(outputfile), stdin);
    outputfile[strcspn(outputfile, "\n")] = '\0';

    FILE *AttInput = fopen(inputfile, "r");

    if (AttInput == NULL) {
        printf("Error: Could not open input file.\n");
        return;
    }

    while (fgets(line, sizeof(line), AttInput) != NULL && j < 100) {
        if (sscanf(line, "%127[^,],%127[^,],%127[^\n]", timestamps[j], names[j], emails[j]) == 3) {
            j++;
        }
    }

    fclose(AttInput);

    int badPositions[100];
    // [SDD_HLD_SYST_002]
    int badCount = attendanceProcessor(j, badPositions);

    // [SDD_HLD_EXPORT_001]
    FILE *AttForm = fopen(outputfile, "w");

    if (AttForm == NULL) {
        printf("Error: Could not open output file.\n");
        return;
    }

    for (k = 0; k < j; k++) {
        if (badPositions[k] == 0) {
            fprintf(AttForm, "\"%s\",\"%s\",\"%s\"\n", timestamps[k], names[k], emails[k]);
        }
    }

    fprintf(AttForm, "\nDate: %s", date);
    fprintf(AttForm, "Club: %s", club);

    if (i > 0) {
        fprintf(AttForm, "\nOther Info:\n");

        for (k = 0; k < i; k++) {
            fprintf(AttForm, "%s", otherinfo[k]);
        }
    }

    fclose(AttForm);

    printf("\nProcessing complete. %d invalid entries found.\n", badCount);
}
