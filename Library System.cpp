#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Library.h"
#include <iomanip>
using namespace std;
namespace LibrarySys{
    struct Book {
    int id;
    string title;
    string author;
    bool isIssued;
    };

    void addBook(vector<Book> &lib) {
        Book b;
        cout << "Enter Book ID: ";
        cin >> b.id;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, b.title);
        cout << "Enter Author Name: ";
        getline(cin, b.author);
        b.isIssued = false;
        lib.push_back(b);
        cout << "Book added successfully!\n";
    }

    void displayBooks(const vector<Book> &lib) {
        if (lib.empty()) {
            cout << "No books in the library.\n";
            return;
        }
        cout << "\n-------------------------------------------------\n";
        cout << "ID\tTitle\t\tAuthor\t\tStatus\n";
        cout << "-------------------------------------------------\n";
        for (const auto &b : lib) {
            cout << b.id << "\t" << b.title << "\t\t" << b.author << "\t\t" 
            << (b.isIssued ? "Issued" : "Available") << endl;
        }
        cout << "-------------------------------------------------\n";
    }

    void searchBook(const vector<Book> &lib) {
        int id;
        cout << "Enter Book ID to search: ";
        cin >> id;
        bool found = false;
        for (const auto &b : lib) {
            if (b.id == id) {
                cout << "\nBook Found!\n";
                cout << "ID: " << b.id << "\nTitle: " << b.title 
                << "\nAuthor: " << b.author 
                << "\nStatus: " << (b.isIssued ? "Issued" : "Available") << endl;
                found = true;
                break;
            }
        }
        if (!found) cout << "Book not found.\n";
    }

    void issueBook(vector<Book> &lib) {
        int id;
        cout << "Enter Book ID to issue: ";
        cin >> id;

        for (auto &b : lib) {
            if (b.id == id) {
                if (!b.isIssued) {
                    b.isIssued = true;
                    cout << "Book issued successfully!\n";
                } else {
                    cout << "Book is already issued.\n";
                }
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void returnBook(vector<Book> &lib) {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;

        for (auto &b : lib) {
            if (b.id == id) {
                if (b.isIssued) {
                    b.isIssued = false;
                    cout << "Book returned successfully!\n";
                } else {
                    cout << "Book Is Already In The Library.\n";
                }
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void saveData(const vector<Book> &lib) {
        ofstream outFile("Library_data.txt");
        if (!outFile) {
            cout << "Error" << endl;
            return;
        }

        for (const auto &b : lib) {
            outFile << b.id << "|" << b.title << "|" << b.author << "|" << b.isIssued << "|" << endl;
        }
        outFile.close();
    }

    void loadData(vector<Book> &lib) {
        ifstream inFile("Library_data.txt");
        if (!inFile) {
            return;
        }
        Book b;
        while (inFile >> b.id) {
            inFile.ignore();
            getline(inFile, b.title);
            getline(inFile, b.author);
            inFile >> b.isIssued;
            inFile.ignore();
            lib.push_back(b);
        }
        inFile.close();
    }

    void runLibrary() {
        vector<Book> library; 
        loadData(library);
        int choice;
        do {
            cout << "\n=== LIBRARY MANAGEMENT SYSTEM ===\n";
            cout << "1. Add New Book\n";
            cout << "2. Display All Books\n";
            cout << "3. Search Book by ID\n";
            cout << "4. Issue Book\n";
            cout << "5. Return Book\n";
            cout << "6. Save & Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: addBook(library); break;
                case 2: displayBooks(library); break;
                case 3: searchBook(library); break;
                case 4: issueBook(library); break;
                case 5: returnBook(library); break;
                case 6: 
                    saveData(library); 
                    cout << "Data saved. Exiting...\n"; 
                    break;
                default: cout << "Invalid choice! Please try again.\n";
            }
        }while (choice != 6);
    }
}

