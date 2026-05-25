#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <iomanip>
#include "CoreLogic.h"
#include "FileHandler.h"

void viewStudentRecord() {
    ifstream inFile("registrar.txt");
    if (!inFile) {
        cout << "\nNo records found. The database file does not exist yet.\n";
        return;
    }

    string searchName;
    cout << "\n--- View Student Record ---\n";
    cout << "Enter Student Name to search: ";
    getline(cin, searchName);
    searchName = formatName(searchName);

    string line;
    bool found = false;

        while (getline(inFile, line)) {
        stringstream ss(line);
        string name, course, gradeStr;

        if (getline(ss, name, '|') && getline(ss, course, '|') && getline(ss, gradeStr, '|')) {
            if (name == searchName) {
                cout << "\nRecord Found in Stored Data:\n";
                cout << "-----------------------\n";
                cout << "Name:   " << name << "\n";
                cout << "Course: " << course << "\n";
                cout << "Grade:  " << gradeStr << "\n";
                cout << "-----------------------\n";
                found = true;
                break; 
            }
        }
    }
    inFile.close();

    if (!found) {
        cout << "\nStudent \"" << searchName << "\" not found in the stored data.\n";
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n==============================\n";
        cout << "   COURSE REGISTRAR SYSTEM    \n";
        cout << "==============================\n";
        cout << "1. Create Student Record\n";
        cout << "2. View Student Record\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";
        
        if (!(cin >> choice)) {
            cout << "\nInvalid selection type. Exiting.\n";
            break;
        }
        cin.ignore(); 

        if (choice == 1) {
            createStudentRecord();
        } else if (choice == 2) {
            viewStudentRecord();
        } else if (choice == 3) {
            cout << "\nExiting system. Goodbye!\n";
            break;
        } else {
            cout << "\nInvalid choice! Please select 1, 2, or 3.\n";
        }
    }

    return 0;
}