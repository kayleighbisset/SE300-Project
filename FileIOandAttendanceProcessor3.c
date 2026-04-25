#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

char nameList[100][128], emailList[100][128];                        //arrays of valid names and emails
char timestamps[100][128], names[100][128], emails[100][128];        //temporary data arrays, to be sorted through in attendanceProcessor

// Check whether a string already exists in a vector
bool duplicateChecker(char list[][128], char *value, int count) {
  int j=0;
    
  for (j=0; j < count; j++) {
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

int attendanceProcessor(int count, int badPositions[]) {
    int badCount = 0, goodCount=1, i=0, start=0;
    const char testDomain[20] = "@my.erau.edu";
    
    //Checks first line and adds without verification if it is a header
    if ((strstr(names[0], "Name") == NULL && strstr(names[0], "name") == NULL)) {
      start = 0;
    }
    else {
      strcpy(nameList[0], names[0]);
      strcpy(emailList[0], emails[0]);
      badPositions[0] = 0;
      start = 1;
    }
    
    //Loops through the rest
    for (i = start; i < count; i++) {
      bool valid = true;

      char currentName[100], currentEmail[100];
      strcpy(currentName, names[i]);
      strcpy(currentEmail, emails[i]);

      // Check duplicate name
      if (duplicateChecker(nameList, currentName, count)) {
        valid = false;
      }

      // Check email domain
      if (strstr(currentEmail, testDomain) == NULL) {
        valid = false;
      }

      // Check duplicate email
      if (duplicateChecker(emailList, currentEmail, count)) {
        valid = false;
      }

      if (valid) {
        strcpy(nameList[goodCount], currentName);
        strcpy(emailList[goodCount], currentEmail);

        printf(" Name successfully added: %s \n", currentName);
        printf(" Email succcessfully added: %s \n", currentEmail);
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

int main() {
  //Reads in input
  char date[50], club[50], otherinfo[50][50], menuChoice[50];
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
  FILE *AttInputTest = fopen(inputfile, "r");
  while (AttInputTest == NULL) {
    printf("Error: Could not open input file.\n");
    printf("Enter the name of the file (with extension) that contains your attendance data: ");
    fgets(inputfile, sizeof(inputfile), stdin);
    inputfile[strcspn(inputfile, "\n")] = '\0';
    AttInputTest = fopen(inputfile, "r");
  }
  fclose(AttInputTest);
  
  printf("\nFinally, which file should we write to? ");
  fgets(outputfile, sizeof(outputfile), stdin);
  outputfile[strcspn(outputfile, "\n")] = '\0';
  FILE *AttOutputTest = fopen(outputfile, "r");
  while (AttOutputTest == NULL) {
    printf("Error: Could not open output file.\n");
    printf("Which file should we write to? ");
    fgets(outputfile, sizeof(outputfile), stdin);
    outputfile[strcspn(outputfile, "\n")] = '\0';
    AttOutputTest = fopen(outputfile, "r");
  }
  fclose(AttOutputTest);
  
  //Reads in from file
  FILE *AttInput = fopen(inputfile, "r");
  if (AttInput == NULL) {
    printf("Error: Could not open input file.\n");
    return 1;
  }

  while (fgets(line, sizeof(line), AttInput) != NULL && j < 100) {
    //if (sscanf(line, "\"%127[^\"]\",\"%127[^\"]\",\"%127[^\"]\"", timestamps[j], names[j], emails[j]) == 3) {
    if (sscanf(line, "%127[^,],%127[^,],%127[^\n]", timestamps[j], names[j], emails[j]) == 3) {
      j++;
    }
  }
  fclose(AttInput);


  //Validates attendance submissions
  int badPositions[100];
  int badCount = attendanceProcessor(j, badPositions);

  // Opens file in write mode
  FILE *AttForm = fopen(outputfile, "w");
  if (AttForm == NULL) {
    printf("Error: Could not open output file.\n");
    return 1;
  }

  // Write only valid entries
  for (k = 0; k < j; k++) {
    if (badPositions[k] == 0) {
      fprintf(AttForm, "\"%s\",\"%s\",\"%s\"\n", timestamps[k], names[k], emails[k]);
    }
  }
  
  //Prints other info
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