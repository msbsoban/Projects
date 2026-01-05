#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "Attendance.h"
using namespace std;
namespace AttendanceSys {
   struct Student {
      int id;
      int stattend;
      int totalattend;
      string name;
   };


   void addstudent(vector<Student> &SectionA) {
      Student a;
      cout << "Enter Student ID: \n";
      cin >> a.id;
      cin.ignore();
      cout << "Enter Student Name: \n";
      getline(cin, a.name);

      a.stattend = 0;
      a.totalattend = 0;
      SectionA.push_back(a);
      cout << "Student Added Successfully.\n";
   }

   void markattendance(vector<Student> &SectionA) {
      if (SectionA.empty()) {
         cout << "No Student In List\n";
         return;
      }
      char attendance;
      cout << "Enter P For Present Or A For Absent.\n";
      for (auto &a : SectionA) {
         cout << "ID: " << a.id << " | Name: " << a.name << " : ";
         cin >> attendance;

         cin.ignore(1000, '\n');

         if ( attendance == 'p' || attendance == 'P') {
            a.stattend++;
         }
         a.totalattend++;
      }
      cout << "Attendance For Today Has Been Recorded Successfully.\n";
   }

   void viewreport(const vector<Student> &SectionA){
      if(SectionA.empty()) {
         cout << "Nothing To View.\n";
         return;
      }
      cout << "ID\tNmae\t\tPresent\tTotal\tPercentage\n";
      cout << "--------------------------------------------------------\n";
      for (const auto &a : SectionA) {
         double percentage;
         percentage = (a.totalattend == 0) ? 0.0 : (double)a.stattend / a.totalattend *100;
      
         /* This Works the Same ->
         if (a.totalattend == 0){
            percentage = 0.0;
         }else{
            percentage = (double)a.stattend / a.totalattend * 100;
         }
         */   
         cout << a.id << "\t" << a.name << "\t\t" << a.stattend << "\t" << a.totalattend << "\t" << percentage << "%\n";

      }
   }

   void savetofile(const vector<Student> &SectionA){
      ofstream outfile("Attendance_data.txt");
      for (auto &a : SectionA){
         outfile << a.id << "|" << a.name << "|" << a.stattend << "|" << a.totalattend << "|\n";
      } 
      outfile.close();
   }

   void loadfile(vector<Student> &SectionA) {
      ifstream infile("Attendance_data.txt");
      if (!infile) {
         return;
      }
      Student a;
      while (infile >> a.id) {
         infile.ignore(); 
         getline(infile, a.name, '|');
         infile >> a.stattend;
         infile.ignore();
         infile >> a.totalattend;

         infile.ignore();

         SectionA.push_back(a);
      }
      infile.close();
   }

   void runAttendance(){
      vector<Student> SectionA;
      loadfile(SectionA);
      int choice;

      do {
         cout << "\n----Student Attendance System----\n";
         cout << "1. Add New Student\n";
         cout << "2. Mark Attendace Of Class\n";
         cout << "3. View Attendace Report\n";
         cout << "4. Save & Exit\n";
         cout << "Enter Number from 1-4\n";
         cin >> choice;
         if (choice > 4 || choice < 1) {
            break;
         }else {
            switch (choice) {
               case 1: 
               addstudent(SectionA);
               break;
               case 2:
               markattendance(SectionA);
               break;
               case 3:
               viewreport(SectionA);
               break;
               case 4: 
               savetofile(SectionA);
               break;
               default: 
               cout << "Invalid Choice\n Try Again.\n";
            }
         }
      } while (choice != 4);
   }
};