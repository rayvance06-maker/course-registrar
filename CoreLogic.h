#pragma once

struct Student {
	int id;
	std::string last_name;
	std::string first_name;
	std::string program;
	double prelim;
	double midterm;
	double finals;

	double getAverage() const {
		return (prelim + midterm + finals) / 3.0;
	}
};

void createRecords();
void updateRecords();
void deleteRecords();