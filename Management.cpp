#include <iostream>
#include <cstring>
#include <vector>
#include "Management.hpp"
using namespace std;

Management::Management() {
}

void Management::start() {
    char date[50], club[50], otherinfo[50][50], menuChoice[50];
    char timestamps[100][128];
    char names[100][128];
    char emails[100][128];
    char line[128];   // for reading in from file
    int i = 0, j = 0, k = 0, l = 0;   // iterators
    int choice = 1;   // for while loops

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
        choice = 0;
        printf("\n\nEnter other meeting information one line at a time.\n");
        printf("Enter 1 when finished: \n");

        while (choice != 1 && i < 50) {
            fgets(menuChoice, sizeof(menuChoice), stdin);
            choice = strtol(menuChoice, NULL, 10);

            if (choice != 1) {
                strcpy(otherinfo[i], menuChoice);
                i++;
            }
        }
    }

    FILE *AttInput;
    AttInput = fopen("SampleAttendanceData.csv", "r");

    if (AttInput == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    while (fgets(line, sizeof(line), AttInput) != NULL && j < 100) {
        if (sscanf(line, "\"%127[^\"]\",\"%127[^\"]\",\"%127[^\"]\"",
                   timestamps[j], names[j], emails[j]) == 3) {
            j++;
        }
    }

    fclose(AttInput);

    // Opens file in write mode
    FILE *AttForm;
    AttForm = fopen("FileIOTest.csv", "w");

    if (AttForm == NULL) {
        printf("Error: Could not open output file.\n");
        return;
    }

    // Writes attendance records
    for (k = 0; k < j; k++) {
        fprintf(AttForm, "%s,%s,%s\n", timestamps[k], names[k], emails[k]);
    }

    // Writes other info at the bottom
    fprintf(AttForm, "\n\nDate: %s", date);
    fprintf(AttForm, "Club: %s", club);

    if (i > 0) {
        fprintf(AttForm, "\nOther Info:\n");
        for (l = 0; l < i; l++) {
            fprintf(AttForm, "%s", otherinfo[l]);
        }
    }

    // Closes file
    fclose(AttForm);

    printf("\nAttendance form created successfully as FileIOTest.csv\n");
}
