This repository documents the design for an Automated RSO Attendance Tracking System (ARATS). The Automated RSO Attendance Tracking System (ARATS) is a C++ program designed to help RSO officers organize attendance records for club or organization meetings. The current implementation reads attendance data from a CSV file, collects meeting information from the user, and exports the processed attendance records into a new CSV file. Attendance data is imported through a local CSV file.

Build Instructions:
Open an online C++ compiler.
Upload or create the following files:
main.cpp
Management.cpp
Management.hpp
SampleAttendanceData.csv
Make sure all files are in the same folder/project.
Compile and run the program.
Enter the meeting date, club name, and any extra meeting information when prompted.
After the program runs, check for the output file named 

How to Run
After starting the program, the user will be prompted to enter:

The date of the meeting
The club or organization name
Any other relevant meeting information

Limitations
This implementation does not currently support:

QR code generation
Google Forms integration
Login or role-based access control

Expected Output
If the program runs correctly, it will display:


The output CSV file will include the attendance records, meeting date, club name, and any additional meeting information entered by the user.

These features were included in the original design but were not implemented in the final code due to project scope and time constraints.
