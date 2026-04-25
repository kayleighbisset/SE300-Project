Automated RSO Attendance Tracking System (ARATS)

Project Overview: 

The Automated RSO Attendance Tracking System (ARATS) is designed to help Registered Student Organization (RSO) officers manage attendance records for events. The project was developed using C++ for system design and structure, following an object-oriented architecture defined in the Software Design Document (SDD). Due to time and integration constraints, the final working implementation of core functionality (file input/output, validation, and export) was completed using a C-based module. The output CSV file will include the attendance records, meeting date, club name, and any additional meeting information entered by the user. 

Our implemented features include file input and output using CSV files, duplicate detection (names and emails), email validation (@my.erau.edu), filtering of invalid attendance entries, user input for meeting details (date, club, notes), and export of processed attendance data to CSV.

Required Files:
For the working system, ensure FileIOandAttendanceProcessor3.c, SampleAttendanceData.csv, and FileIOTest.csv are all in the same folder, and main.cpp, Management.cpp, Management.hpp, and SampleAttendanceData.csv in the C++ version.

How to Run:
Open a terminal/command prompt and make sure all project files are in the same folder. Compile the program, run ARATS.exe, and enter prompts as needed.

Notes: The C implementation contains the complete working functionality (validation, duplicate checking, CSV export). The C++ files represent the SDD-based modular design. The input file (SampleAttendanceData.csv) must exist in the same directory or the program will fail to run.
