#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "FileHandler.h"
#include "CoreLogic.h"

void loadState() {
    std::ifstream file(FILENAME);
    if (!file) return;

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);

        std::string s_id;
        std::string s_last_name;
        std::string s_first_name;
        std::string s_program;
        std::string s_prelim;
        std::string s_midterm;
        std::string s_finals;

        std::getline(ss, s_id, '|');
        std::getline(ss, s_last_name, '|');
        std::getline(ss, s_first_name, '|');
        std::getline(ss, s_program, '|');
        std::getline(ss, s_prelim, '|');
        std::getline(ss, s_midterm, '|');
        std::getline(ss, s_finals, '|');

        try {
            Student s;

            s.id = std::stoi(s_id);
            s.last_name = s_last_name;
            s.first_name = s_first_name;
            s.program = s_program;

            s.prelim = std::stod(s_prelim);
            s.midterm = std::stod(s_midterm);
            s.finals = std::stod(s_finals);

            if (s.id >= nextId) {
                nextId = s.id + 1;
            }

            roster.push_back(s);
        }
        catch (...) {
            continue;
        }
    }
    file.close();
}

void saveState() {
    std::ofstream file(FILENAME, std::ios::trunc);

    if (!file) return;
    for (const auto& s : roster) {
        file << s.id << "|"
             << s.last_name << "|"
             << s.first_name << "|"
             << s.program << "|"
             << s.prelim << "|"
             << s.midterm << "|"
             << s.finals << "\n";
    }
    file.close();
}
