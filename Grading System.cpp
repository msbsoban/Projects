#include <iostream>
#include <vector>
#include <fstream>
#include "Grading.h"

using namespace std;

namespace GradingSys{
    

    struct Student {
        int rollNo;
        string name;
        int marks[5];        
        int total;
        int sum;
        float average;
        char grade;
    };
    void displayStudent(Student s) { 
        cout << "-------------------------------";
        cout << "\nRoll No: " << s.rollNo;
        cout << "\nName: " << s.name;
        cout << "\nTotal Marks: " << s.total;
        cout << "\nObtained Marks: " << s.sum;
        cout << "\nPercentage: " << s.average << "%";
        cout << "\nGrade: " << s.grade << endl;
        cout << "-------------------------------" << endl;
    }

    int calculateTotal(int marks[], int size) {
        int sum = 0;
        for (int i = 0; i < size; i++){
            sum += marks[i];
        }
        return sum;
    }

    float calculateTotal(int &sum, int &total) {
        if(total == 0) return 0; 
        return (float)(sum * 100) / total;
    }

    void calculateGrade(Student &s) {
        if (s.average >= 90) 
            s.grade = 'A';
        else if (s.average >= 75)
            s.grade = 'B';
        else if (s.average >= 60)
            s.grade = 'C';
        else if (s.average >= 50)
            s.grade = 'D';
        else
            s.grade = 'F';       
    }

    void displayall () {
        ifstream infile("students.txt");
        Student s;
        bool datafound = false;
        if(!infile || infile.peek() == EOF) {
            cout << "No Data Available" << endl;
            return;
        }
        cout << "----- Student Records -----" << endl;
        while (infile >> s.rollNo >> s.name) {
        datafound = true;
            for (int i = 0; i < 5; i++) {
                infile >> s.marks[i];
            }
            infile >> s.total >> s.sum >> s.average >> s.grade;
            displayStudent(s);
        }
        infile.close();
        if (!datafound) {
            cout << "No Data Found." << endl;
        }
    }

    void filesave(Student s) {
        ofstream outfile("students.txt", ios::app);
        if (outfile.is_open()) {
            outfile << s.rollNo << " " << s.name << " ";
            for(int i = 0; i < 5; i++) {
                outfile << s.marks[i] << " ";
            }
            outfile << s.total << " " << s.sum << " " << s.average << " " << s.grade << endl;
            outfile.close();
        } else {
            cout << "Error!";
        }
    }

    void runGrading() {
        vector<Student> students; 
        int choice;

        while (true) {   
            cout << "\n--- Student Grading System ---\n";
            cout << "1. Add Student\n";
            cout << "2. Display All Students\n";
            cout << "3. Exit Grading System\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) { 
                case 1: {
                    Student s;

                    cout << "Enter Roll Number: ";
                    cin >> s.rollNo;

                    cout << "Enter Name: ";
                    cin >> s.name;

                    for (int i = 0; i < 5; i++) {
                        cout << "Enter marks of subject: " << i+1 << endl;       
                        cin >> s.marks[i];
                    }
                    
                    cout << "Enter Total Marks: ";
                    cin >> s.total;

                    s.sum = calculateTotal(s.marks, 5);        
                    s.average = calculateTotal(s.sum, s.total);      
                    calculateGrade(s);                          

                    filesave(s);
                    cout << "Student added successfully!\n";
                    break;
                }

                case 2:{
                    displayall();
                    break;
                }    
                case 3:{
                    cout << "Exiting program...\n";
                    return;
                }    
                default: {
                    cout << "Invalid choice!\n";
                }    
            }
        }
    }   
}