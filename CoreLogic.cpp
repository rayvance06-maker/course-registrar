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
	int id;

	std::cout << "Enter ID to update: ";
	while (!(std::cin >> id) || id < 1000) {
		std::cout << "Invalid input, Enter number > 1000: ";
		clearInput();
	}

	clearInput();
	for (auto& s : roster) {
		if (s.id == id) {
			std::cout << "Enter new last name: ";
			std::getline(std::cin, s.last_name);

			std::cout << "\nEnter new first name: ";
			std::getline(std::cin, s.first_name);

			s.prelim = getGrade("\nEnter new prelim grade: ");
			s.midterm = getGrade("\nUpdated midterm grade: ");
			s.finals = getGrade("\nUpdated finals grade: ");
				
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

	for (auto it = roster.begin(); it != roster.end(); ++it) {
		if (it->id == id) {
			roster.erase(it);
			std::cout << "Record removed.\n";
			return;
		}
	}
	std::cout << "Record not found.\n";
}