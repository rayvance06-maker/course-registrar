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
	//Prompts for the user's name
	std::cout << "Enter your full name: ";
	std::getline(std::cin >> std::ws, s.name);

	//Prompts for the user's course
	std::cout << "Enter your course: ";
	std::getline(std::cin >> std::ws, s.course);

	//Prompts for the user's prelim grade
	std::cout << "Enter prelim grade: ";
	while (!(std::cin >> s.prelim) || s.prelim < 1.0 || s.prelim > 5.0) {
		std::cout << "Invalid input. Enter your grade(1.0-5.0): ";
		clearInput();
	}
	roster.push_back(s);

	std::cout << "Record added successfully" << '\n';
}
void viewRecord() {
	std::cout << "Hello World.";
}
void updateRecord() {

}
void deleteRecord() {

}