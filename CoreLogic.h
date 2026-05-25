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

void clearInput();
double getGrade(const std::string& prompt);
bool duplicateNameExists(const std::string& first, const std::string& last, int currentId = -1);
void viewClassAverages(const std::vector<Student>& roster);
void sortByTerm(std::vector<Student>& roster, int term);
std::string sanitizeName(std::string name);
std::string sanitizeProgram(std::string program);
bool isValidProgram(const std::string& program);
std::string formatFullName(const Student& s);
void createRecords();
void updateRecords();
void deleteRecords();