#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <iomanip>

using namespace std;

string formatName(string str) {
    if (str.empty()) return str;

    // Remove leading/trailing spaces if any
    while(!str.empty() && isspace(str.front())) str.erase(str.begin());
    while(!str.empty() && isspace(str.back())) str.pop_back();

    if (str.empty()) return "";

    str[0] = toupper(str[0]);
    for (size_t i = 1; i < str.length(); i++) {
        if (str[i - 1] == ' ') {
            str[i] = toupper(str[i]);
        } else {
            str[i] = tolower(str[i]);
        }
    }
    return str;
}

bool isValidGrade(double grade) {
    // List of valid grades from 1.00 to 5.00 with 0.25 increments
    double validGrades[] = {1.00, 1.25, 1.50, 1.75, 2.00, 2.25, 2.50, 2.75, 3.00, 5.00};
    
    // Check if the input grade matches any of the valid registrar grades
    for (double g : validGrades) {
        // Using a small epsilon (0.001) to safely compare floating-point numbers
        if (abs(grade - g) < 0.001) {
            return true;
        }
    }
    return false;
}

void createStudentRecord() {
    string rawName, rawCourse;
    double grade;

    cout << "\n--- Create Student Record ---\n";
    
    cout << "Enter Student Name: ";
    getline(cin, rawName);
    string name = formatName(rawName);

    cout << "Enter Course: ";
    getline(cin, rawCourse);
   
    string course = formatName(rawCourse); 

    cout << "Enter Grade (1.00, 1.25, 1.50... to 5.00): ";
    if (!(cin >> grade)) {
        cout << "\n[ERROR] Invalid grade format entered. Record NOT saved.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    cin.ignore(); // Clear newline from buffer

 
    if (name.empty() || course.empty()) {
        cout << "\n[ERROR] Name or Course cannot be blank. Record NOT saved.\n";
        return;
    }

    if (!isValidGrade(grade)) {
        cout << "\n[ERROR] Grade " << fixed << setprecision(2) << grade 
             << " is invalid! Must be 1.00, 1.25, 1.50, up to 5.00. Record NOT saved.\n";
        return;
    }

  
    ofstream outFile("registrar.txt", ios::app);
    if (!outFile) {
        cout << "\n[ERROR] Could not open database file!\n";
        return;
    }

    outFile << name << "|" << course << "|" << fixed << setprecision(2) << grade << "\n";
    outFile.close();

    cout << "\nSUCCESS: Record safely stored for " << name << "!\n";
}


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