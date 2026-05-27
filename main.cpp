#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "CoreLogic.h"
#include "FileHandler.h"

void mainMenu();
void viewMenu();

int getValidInput(int min, int max) {
    int value;

    while (true) {
        if (std::cin >> value && value >= min && value <= max) {
            return value;
        }

        std::cout << "Invalid input. Enter " << min << " - " << max << ".\n";
        clearInput();
    }
}

void viewRecord() {
    if (roster.empty()) {
        std::cout << "No records available.\n";
        return;
    }
    std::cout << "\n"
              << std::setw(5) << "ID"
              << std::setw(25) << "NAME"
              << std::setw(10) << "PROGRAM"
              << std::setw(10) << "PRELIM"
              << std::setw(10) << "MIDTERM"
              << std::setw(10) << "FINALS"
              << std::setw(10) << "AVERAGE"
              << "\n";

    std::cout << std::string(80, '-') << "\n";

    for (const auto& s : roster) {
        std::cout
            << std::setw(5) << s.id
            << std::setw(25) << formatFullName(s)
            << std::setw(10) << s.program
            << std::setw(10) << s.prelim
            << std::setw(10) << s.midterm
            << std::setw(10) << s.finals
            << std::setw(10) << s.getAverage()
            << "\n";
    }
}

void viewTop10Students() {
    if (roster.empty()) {
        std::cout << "No records available.\n";
        return;
    }
    
    int term;

    std::cout << "\n===== VIEW TOP 10 STUDENTS =====\n";
    std::cout << "Select term:\n";
    std::cout << "[1] Prelim\n";
    std::cout << "[2] Midterm\n";
    std::cout << "[3] Finals\n";
    std::cout << "[4] Average\n";
    std::cout << "Choice: ";

    term = getValidInput(1, 4);
    
    std::vector<Student> sortedRoster = roster;
    sortByTerm(sortedRoster, term);

    int limit = (sortedRoster.size() < 10) ? sortedRoster.size() : 10;

    std::cout << "\n===== TOP " << limit << " STUDENTS =====\n";

    for (int i = 0; i < limit; i++) {
        std::cout << i + 1 << ". "
                  << formatFullName(sortedRoster[i])
                  << " (" << sortedRoster[i].program << ") - ";

        if (term == 1) {
            std::cout << "Prelim: " << sortedRoster[i].prelim;
        }
        else if (term == 2) {
            std::cout << "Midterm: " << sortedRoster[i].midterm;
        }
        else if (term == 3) {
            std::cout << "Finals: " << sortedRoster[i].finals;
        }
        else {
            std::cout << "Average: " << sortedRoster[i].getAverage();
        }

        std::cout << std::endl;
    }
}

void mainMenu() {
    int choice;

    do {
        std::cout << "\n===== STUDENT REGISTRAR SYSTEM =====\n";
        std::cout << "1. Create Record\n";
        std::cout << "2. View Records\n";
        std::cout << "3. Update Record\n";
        std::cout << "4. Delete Record\n";
        std::cout << "5. Save Data\n";
        std::cout << "6. Exit\n";
        std::cout << "Choice: ";

        choice = getValidInput(1, 6);

        switch (choice) {
        case 1:
            createRecord();
            break;
        case 2:
            viewMenu();
            break;
        case 3:
            updateRecord();
            break;
        case 4:
            deleteRecord();
            break;
        case 5:
            saveState();
            std::cout << "Data saved.\n";
            break;
        case 6:
            saveState();
            std::cout << "Exiting program...\n";
            break;
        }
    } while (choice != 6);
}

void viewMenu() {
    int choice;

    do {
        std::cout << "\n===== VIEW MENU =====\n";
        std::cout << "1. View All Records\n";
        std::cout << "2. View Class Average Per Term\n";
        std::cout << "3. View Top 10 Students Per Term\n";
        std::cout << "4. Back\n";
        std::cout << "Choice: ";

        choice = getValidInput(1, 4);

        switch (choice) {
        case 1:
            viewRecord();
            break;
        case 2:
            viewClassAverages(roster);
            break;
        case 3:
            viewTop10Students();
            break;
        case 4:
            std::cout << "Returning to Main Menu...\n";
            break;
        }
    } while (choice != 4);
}

int main() {
    loadState();
    mainMenu();
    
    return 0;
}