#ifndef FILEIOANDATTENDANCEPROCESSOR_HPP
#define FILEIOANDATTENDANCEPROCESSOR_HPP

#include <stdbool.h>

extern char nameList[100][128];
extern char emailList[100][128];
extern char timestamps[100][128];
extern char names[100][128];
extern char emails[100][128];

// [SDD_HLD_DUP_001]
bool duplicateChecker(char list[][128], char *value, int count);

// [SDD_HLD_PRO_001]
// [SDD_HLD_PRO_002]
// [SDD_HLD_PRO_003] 
int attendanceProcessor(int count, int badPositions[]);

#endif
