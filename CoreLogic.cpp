#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "CoreLogic.h"

std::vector<Student> roster;
const std::string FILENAME = "students.txt";

//Utility Functions
void clearInput() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void createRecord() {
	Student s;
	//Prompts for the user's surname
	std::cout << "Enter your surname: ";
	std::getline(std::cin >> std::ws, s.surname);

	//Prompts for the user's first name
	std::cout << "Enter your first name: ";
	std::getline(std::cin >> std::ws, s.first_name);

	//Prompts for the user's course
	std::cout << "Enter your course: ";
	std::getline(std::cin >> std::ws, s.course);

	//Prompts for the user's prelim grade
	std::cout << "Enter prelim grade: ";
	while (!(std::cin >> s.prelim) || s.prelim < 1.0 || s.prelim > 5.0) {
		std::cout << "Invalid input. Enter your grade(1.0-5.0): ";
		clearInput();
	}

	//Prompts for the user's midterm grade
	std::cout << "Enter prelim grade: ";
	while (!(std::cin >> s.midterm) || s.midterm < 1.0 || s.midterm > 5.0) {
		std::cout << "Invalid input. Enter your grade(1.0-5.0): ";
		clearInput();
	}
	
	//Prompts for the user's finals grade
	std::cout << "Enter prelim grade: ";
	while (!(std::cin >> s.finals) || s.finals < 1.0 || s.finals > 5.0) {
		std::cout << "Invalid input. Enter your grade(1.0-5.0): ";
		clearInput();
	}
	roster.push_back(s);

	std::cout << "Record added successfully" << '\n';
}
void updateRecord() {
	std::string surname;
	Student s;

	std::cout << "Enter surname to update: ";
	while (!(std::cin >> surname)) {
		std::cout << "Invalid input, try again: ";
		clearInput();
	}
	for (auto& s : roster) {
		if (s.surname == surname) {
			clearInput();
			std::cout << "Enter new surname: ";
			std::getline(std::cin, s.surname);

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

}