#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cctype>
#include "CoreLogic.h"

int nextId = 1000;
std::vector<Student> roster;
const std::string FILENAME = "data/students.txt";

void clearInput() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double getGrade(const std::string& prompt) {
	double grade;

	while (true) {
		std::cout << prompt;
		if (std::cin >> grade && grade >= 1.0 && grade <= 5.0) {
			clearInput();
			return grade;
		}
		std::cout << "Invalid input. Enter grade (1.0 - 5.0).\n";
		clearInput();
	}
}

bool duplicateNameExists(const std::string& first, const std::string& last, int currentId) {
    for (const auto& student : roster) {
        if (student.id != currentId &&
            student.first_name == first &&
            student.last_name == last) {
            return true;
        }
    }
    return false;
}

void viewClassAverages(const std::vector<Student>& roster) {
    if(roster.empty()) {
		std::cout << "No records found.\n";
		return;
	}
    double p = 0, m = 0, f = 0, o = 0;

    for(const auto& s : roster) {
        p += s.prelim;
        m += s.midterm;
        f += s.finals;
        o += s.getAverage();
    }
    int n = roster.size();

    std::cout << "\nPrelim: " << p / n << std::endl;
    std::cout << "Midterm: " << m / n << std::endl;
    std::cout << "Finals: " << f / n << std::endl;
    std::cout << "Overall: " << o / n << std::endl;
}

void sortByTerm(std::vector<Student>& roster, int term) {
    int n = roster.size();

    for (int i = 0; i < n - 1; i++) {
        int bestIndex = i;

        for (int j = i + 1; j < n; j++) {
            bool better = false;

            if (term == 1) {
                better = roster[j].prelim < roster[bestIndex].prelim;
            } else if (term == 2) {
                better = roster[j].midterm < roster[bestIndex].midterm;
            } else if (term == 3) {
                better = roster[j].finals < roster[bestIndex].finals;
            } else {
                better = roster[j].getAverage() < roster[bestIndex].getAverage();
            }
			
            if (better) {
                bestIndex = j;
            }
        }
        Student temp = roster[i];
        roster[i] = roster[bestIndex];
        roster[bestIndex] = temp;
    }
}

std::string sanitizeName(std::string name) {
	if (name.empty()) {
        return "Unknown";
    }

    size_t start = name.find_first_not_of(" \t\n\r");
    size_t end = name.find_last_not_of(" \t\n\r");

    if (start == std::string::npos) {
        return "Unknown";
    }

    name = name.substr(start, end - start + 1);

    std::string result;
    bool lastWasSpace = false;
    bool newWord = true;

    for (char c : name) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            if (!lastWasSpace) {
                result += ' ';   // keep only ONE space
                lastWasSpace = true;
            }
            newWord = true;
        } else {
            if (newWord) {
                result += std::toupper(static_cast<unsigned char>(c));
                newWord = false;
            } else {
                result += std::tolower(static_cast<unsigned char>(c));
            }
            lastWasSpace = false;
        }
    }
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    if (result.length() > 25) {
        result = result.substr(0, 25);
    }
    return result;
}

std::string sanitizeProgram(std::string program) {
    if (program.empty()) { 
		return "UNKNOWN";
	}
    size_t start = program.find_first_not_of(" \t\n\r");
    size_t end   = program.find_last_not_of(" \t\n\r");

    if (start == std::string::npos) {
        return "UNKNOWN";
    }
    program = program.substr(start, end - start + 1);

    std::string result;
    for (char c : program) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            result += std::toupper(static_cast<unsigned char>(c));
        }
    }
    return result;
}

bool isValidProgram(const std::string& program) {
    return program == "BSBA" ||
           program == "BSCS" ||
           program == "BSHM" ||
           program == "BSTM" ||
		   program == "BSPSY" ||
		   program == "BSED" ||
		   program == "BSA" ||
		   program == "BSIT" ||
		   program == "BEED" ||
		   program == "BSN" ||
		   program == "BSCE" ||
		   program == "BSEE" ||
		   program == "BSME" ||
		   program == "BSIE" ||
		   program == "BSMT" ||
		   program == "BSCRIM" ||
		   program == "BSB" ||
		   program == "ACT" ||
		   program == "BSENTREP" ||
		   program == "BSHRM" ||
		   program == "BSECE"||
		   program == "BSCPE";
}

std::string formatFullName(const Student& s) {
    return s.last_name + ", " + s.first_name;
}

void createRecord() {
	Student s; 
	s.id = nextId++;

	clearInput();

	while (true) {
		std::cout << "Enter last name: ";
		std::getline(std::cin, s.last_name);

		std::cout << "Enter first name: ";
		std::getline(std::cin, s.first_name);

		s.first_name = sanitizeName(s.first_name);
        s.last_name  = sanitizeName(s.last_name);

		if (!duplicateNameExists(s.first_name, s.last_name)) {
			break;
		}
		std::cout << "Duplicate name detected. Please enter other name.\n";
	}

	while (true) { 
		std::cout << "Program (e.g BSCS): ";
		std::getline(std::cin, s.program);

		s.program = sanitizeProgram(s.program);

		if (isValidProgram(s.program)) {
			break;
		}
		std::cout << "Invalid program. Try again.\n";  
	}

	s.prelim = getGrade("Prelim grade: ");
	s.midterm = getGrade("Midterm grade: ");
	s.finals = getGrade("Finals grade: ");

	roster.push_back(s);

	std::cout << "Record added successfully\n";
}

void updateRecord() {
	int id;

	std::cout << "Enter ID to update: ";
	while (!(std::cin >> id) || id < 1000) {
		std::cout << "Invalid input, Enter number > 1000: ";
		clearInput();
	}
	clearInput();

	for (auto& s : roster) {
		if (s.id == id) {
			std::cout << "\nCurrent Record:\n";
			std::cout << s.last_name << ", " << s.first_name << "\n";
			std::cout << "Program: " << s.program << "\n";

			while (true) {
				std::cout << "\nEnter new last name: ";
				std::getline(std::cin, s.last_name);

				std::cout << "Enter new first name: ";
				std::getline(std::cin, s.first_name);

				s.first_name = sanitizeName(s.first_name);
				s.last_name  = sanitizeName(s.last_name);

				if (!duplicateNameExists(s.first_name, s.last_name, id)) {
					break;
				}
				std::cout << "\nDuplicate name detected. Please enter other name.";
		}

			std::cout << "Enter new program (e.g BSCS): ";
			std::getline(std::cin, s.program);

			s.program = sanitizeProgram(s.program);

			while (!isValidProgram(s.program)) {
				std::cout << "Invalid program. Follow the format (e.g BSCS): ";
				std::getline(std::cin, s.program);
				s.program = sanitizeProgram(s.program);
			}

			s.prelim = getGrade("Enter new prelim grade: ");
			s.midterm = getGrade("Enter midterm grade: ");
			s.finals = getGrade("Enter finals grade: ");
				
			std::cout << "Record updated.\n";
			return;
		}
	}
	std::cout << "ID not found.\n";
}

void deleteRecord() {
	int id;

	std::cout << "Enter ID to delete: ";
	while (!(std::cin >> id) || id < 1000) {
		std::cout << "Invalid input, Enter number > 1000: ";
		clearInput();
	}
	clearInput();

	for (auto it = roster.begin(); it != roster.end(); ++it) {
		if (it->id == id) {
			roster.erase(it);
			std::cout << "Record removed.\n";
			return;
		}
	}
	std::cout << "Record not found.\n";
}