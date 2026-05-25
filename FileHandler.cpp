#include <iostream>
#include <fstream>

void loadState() {
    std::ifstream file(FILENAME);
    if (!file) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string s_id, s_name, s_gwa;

        std::getline(ss, s_id, '|');
        std::getline(ss, s_name, '|');
        std::getline(ss, s_gwa, '|');

        try {
            Student s;
            s.id = std::stoi(s_id);
            s.name = s_name;
            s.gwa = std::stod(s_gwa);

            if (s.gwa < 1.0 || s.gwa > 5.0) continue;

            if (s.id >= nextId) {
                nextId = s.id + 1;
            }
            roster.push_back(s);
        }
        catch (...) { continue; }
    }
    file.close();
}

void saveState() {
    std::ofstream file(FILENAME, std::ios::trunc);
    for (const auto& s : roster) {
        file << s.id << "|" << s.name << "|" << s.gwa << "\n";
    }
    file.close();
}
