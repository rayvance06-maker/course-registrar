#pragma once

struct Student {
	std::string surname;
	std::string first_name;
	std::string course;
	double prelim;
	double midterm;
	double finals;
};

void createRecords();
void updateRecords();
void deleteRecords();