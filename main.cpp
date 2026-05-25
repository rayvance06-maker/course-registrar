#include <iostream>
#include "CoreLogic.h"
#include "FileHandler.h"

void showMenu() {
    std::cout << "\n===== STUDENT REGISTRAR SYSTEM =====\n";
    std::cout << "1. Create Record\n";
    std::cout << "2. Update Record\n";
    std::cout << "3. Delete Record\n";
    std::cout << "4. View All Records\n";
    std::cout << "5. Sort by Term\n";
    std::cout << "6. View Class Averages\n";
    std::cout << "7. Save Data\n";
    std::cout << "8. Exit\n";
    std::cout << "Choice: ";
}

int main() {
    loadState();

    int choice;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            createRecord();
            break;
        case 2:
            updateRecord();
            break;
        case 3:
            deleteRecord();
            break;
        case 4:
            for (const auto& s : roster) {
                std::cout << s.id << " | "
                          << s.last_name << ", "
                          << s.first_name << " | "
                          << s.program << " | "
                          << s.getAverage()
                          << "\n";
            }
            break;
        case 5: {
            int term;
            std::cout << "Enter term (1=Prelim, 2=Midterm, 3=Finals, 4=Average): ";
            std::cin >> term;
            sortByTerm(roster, term);
            std::cout << "Sorted successfully.\n";
            break;
        }
        case 6:
            viewClassAverages(roster);
            break;
        case 7:
            saveState();
            break;
        case 8:
            saveState();
            std::cout << "Exiting program...\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    return 0;
}