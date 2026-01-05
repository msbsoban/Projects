#include <iostream>
#include "Attendance.h" 
#include "Library.h"    
#include "Grading.h"
using namespace std;

/* 
USE THIS TO RUN THE PROGRAMME
g++ menu.cpp "Library System.cpp" "Attendence System.cpp" "Grading System.cpp" -o main_program
./main_program
*/

int main() {
    int choice;
    do {
        cout << "\n======================================\n";
        cout << "      UNIVERSITY MANAGEMENT SYSTEM      \n";
        cout << "======================================\n";
        cout << "1. Enter Attendance System\n";
        cout << "2. Enter Library System\n";
        cout << "3. Enter Grading System\n";
        cout << "4. Exit Application\n";
        cout << "--------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1:
                AttendanceSys::runAttendance(); 
                break;
            case 2:
                LibrarySys::runLibrary(); 
                break;
            case 3 :
                GradingSys::runGrading();  
                break;  
            case 4 :
                cout << "Exiting Project :)\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        };

    } while (choice != 4);
    return 0;
}