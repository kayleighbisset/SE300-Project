#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

char nameList[100][128];
char emailList[100][128];

// Check whether a string already exists in a vector
bool duplicateChecker(char list[][128], char *value) {
  int j=0, length = sizeof(list) / sizeof(list[0]);
    
  for (j=0; j < length; j++) {
    if (strcmp(value, list[j]) == 0) {
      return true;
    }
  }
  
  return false;
}

// names and emails are arrays of C strings
// count is how many entries are in both arrays
// badPositions is an output array
// return value = number of invalid positions

int attendanceProcessor(const char* names[], const char* emails[], int count, int badPositions[]) {
    int badCount = 0, goodCount=0, i=0;
    const char testDomain[20] = "@my.erau.edu";

    for (i = 1; i < count; i++) {
      bool valid = true;

      char currentName[100], currentEmail[100];
      strcpy(currentName, names[i]);
      strcpy(currentEmail, emails[i]);

      // Check duplicate name
      if (duplicateChecker(nameList, currentName)) {
        valid = false;
      }

      // Check email domain
      if (strstr(currentEmail, testDomain) == NULL) {
        valid = false;
      }

      // Check duplicate email
      if (duplicateChecker(emailList, currentEmail)) {
        valid = false;
      }

      if (valid) {
        strcpy(nameList[goodCount], currentName);
        strcpy(emailList[goodCount], currentEmail);

        printf("Name successfully added: %s \n", currentName);
        printf("Email succcessfully added: %s \n", currentEmail);
        goodCount++;
      }
      else {
        badPositions[badCount] = i;
        badCount++;
        printf("Invalid entry at position %d \n", i);
      }
    }

    return badCount;
}

int main() {
  //Reads in input
  char date[50], club[50], otherinfo[50][50], menuChoice[50];
  char timestamps[100][128];
  char inputfile[100], outputfile[100];                                //user's file names
  char line[128];                                                      //for reading in from file
  int i=0, j=0, k=0, l=0;                                              //iterators
  int choice=1;                                                        //for while loops
  
  
  //basic info
  printf("\n\nWhat is the date of your meeting? ");
  fgets(date, sizeof(date), stdin);
  printf("\n\nWhat club/organization is this for? ");
  fgets(club, sizeof(club), stdin);
  
  //extra info
  printf("\n\nDo you have other relevant meeting information? (1 for No, 2 for Yes): ");
  fgets(menuChoice, sizeof(menuChoice), stdin);
  choice = strtol(menuChoice, NULL, 10);
  while (choice!=1 && choice!= 2) {
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
  
  //file names
  printf("\nEnter the name of the file (with extension) that contains your attendance data: ");
  fgets(inputfile, sizeof(inputfile), stdin);
  inputfile[strcspn(inputfile, "\n")] = '\0';
  FILE *AttTest = fopen(inputfile, "r");
  while (AttTest == NULL) {
    printf("Error: Could not open input file.\n");
    printf("Enter the name of the file (with extension) that contains your attendance data: ");
    fgets(inputfile, sizeof(inputfile), stdin);
    inputfile[strcspn(inputfile, "\n")] = '\0';
    AttTest = fopen(inputfile, "r");
  }
  
  printf("\nFinally, which file should we write to? ");
  fgets(outputfile, sizeof(outputfile), stdin);
  outputfile[strcspn(outputfile, "\n")] = '\0';
  AttTest = fopen(outputfile, "r");
  while (AttTest == NULL) {
    printf("Error: Could not open output file.\n");
    printf("Which file should we write to? ");
    fgets(outputfile, sizeof(outputfile), stdin);
    outputfile[strcspn(outputfile, "\n")] = '\0';
    AttTest = fopen(outputfile, "r");
  }

  FILE *AttInput = fopen(inputfile, "r");
  if (AttInput == NULL) {
    printf("Error: Could not open input file.\n");
    return 1;
  }

  while (fgets(line, sizeof(line), AttInput) != NULL && j < 100) {
    if (sscanf(line, "\"%127[^\"]\",\"%127[^\"]\",\"%127[^\"]\"", timestamps[j], nameList[j], emailList[j]) == 3) {
      j++;
    }
  }
  fclose(AttInput);

  // Convert 2D char arrays into arrays of pointers for attendanceProcessor
  const char* namePtrs[100];
  const char* emailPtrs[100];

  for (k = 0; k < j; k++) {
    namePtrs[k] = nameList[k];
    emailPtrs[k] = emailList[k];
  }

  int badPositions[100];
  int badCount = attendanceProcessor(namePtrs, emailPtrs, j, badPositions);

  // Opens file in write mode
  FILE *AttForm = fopen(outputfile, "w");
  if (AttForm == NULL) {
    printf("Error: Could not open output file.\n");
    return 1;
  }

  // Write only valid entries
  for (k = 0; k < j; k++) {
    bool isBad = false;

    for (l = 0; l < badCount; l++) {
      if (badPositions[l] == k) {
        isBad = true;
        break;
      }
    }

    if (!isBad) {
      fprintf(AttForm, "\"%s\",\"%s\",\"%s\"\n", timestamps[k], nameList[k], emailList[k]);
    }
  }

    /*
    Write invalid positions summary
    fprintf(AttForm, "\nInvalid Positions:\n");
    for (k = 0; k < badCount; k++)
    {
        fprintf(AttForm, "%d\n", badPositions[k]);
    }
    */
   
  // Writes other info at the bottom
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

  return 0;
}
