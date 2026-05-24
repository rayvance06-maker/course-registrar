#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "CoreLogic.h"

int nextId = 1000;
std::vector<Student> roster;
const std::string FILENAME = "students.txt";

//Utility Functions
void clearInput() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double getGrade(const std::string& prompt) {
	double grade;

	while (true) {
		std::cout << prompt;
		if (std::cin >> grade && grade >= 1.0 && grade <= 5.0) {
			return grade;
		}

		std::cout << "Invalid input. Enter grade (1.0 - 5.0).\n";
		clearInput();
	}
}

void createRecord() {
	Student s;
	s.id = nextId++;

	std::cout << "Please enter the following:\n";
	std::cout << "Surname: ";
	std::getline(std::cin, s.last_name);

	std::cout << "\nFirst name: ";
	std::getline(std::cin, s.first_name);

	std::cout << "\nProgram: ";
	std::getline(std::cin, s.program);

	s.prelim = getGrade("\nPrelim grade: ");
	s.midterm = getGrade("\nMidterm grade: ");
	s.finals = getGrade("\nFinals grade: ");

	roster.push_back(s);

	std::cout << "Record added successfully\n";
}

void updateRecord() {
	std::string last_name;
	Student s;

	std::cout << "Enter surname to update: ";
	while (!(std::cin >> last_name)) {
		std::cout << "Invalid input, try again: ";
		clearInput();
	}
	for (auto& s : roster) {
		if (s.last_name == last_name) {
			clearInput();
			std::cout << "Enter new surname: ";
			std::getline(std::cin, s.last_name);

			std::cout << "Enter new first name: ";
			std::getline(std::cin, s.first_name);

			std::cout << "Enter new prelim grade: ";
			while (!(std::cin >> s.prelim) || s.prelim < 1.0 || s.prelim > 5.0) {
				std::cout << "Invalid input, try again: ";
				clearInput();
			}

			std::cout << "Enter new midterm grade: ";
			while (!(std::cin >> s.midterm) || s.midterm < 1.0 || s.midterm > 5.0) {
				std::cout << "Invalid input, try again: ";
				clearInput();
			}

			std::cout << "Enter new prelim grade: ";
			while (!(std::cin >> s.finals) || s.finals < 1.0 || s.finals > 5.0) {
				std::cout << "Invalid input, try again: ";
				clearInput();
			}
			std::cout << "Record updated.\n";
			return;
		}
		std::cout << "Surname not found.\n";
	}
}
void deleteRecord() {
	std::string last_name;
	std::cout << "Enter surname to delete: ";
	std::getline(std::cin >> std::ws, last_name);

	for (auto it = roster.begin(); it != roster.end(); ++it) {
		if (it->last_name == last_name) {
			roster.erase(it);
			std::cout << "Record removed.\n";
			return;
		}
	}
	std::cout << "Record not found.\n";
}