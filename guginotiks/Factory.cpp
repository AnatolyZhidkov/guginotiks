#include "Factory.h"
#include "Personal.h"
#include "Engineer.h"
#include "Manager.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// Создает персонал из CSV-файла
vector<Employee*> StaffFactory::makeStaff(const string& filename) {
    vector<Employee*> staff;
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        return staff;
    }

    string line;
    getline(file, line); // Пропуск заголовока

    while (getline(file, line)) {
        istringstream iss(line);
        vector<string> tokens;
        string token;

        // Разбитие строк по разделителю ';'
        while (getline(iss, token, ';')) {
            tokens.push_back(token);
        }

        // Проверка корректности формата
        if (tokens.size() < 5) {
            cerr << "Warning: Invalid line format: " << line << endl;
            continue;
        }

        try {
            // Парсим данные
            int id = stoi(tokens[0]);
            string name = tokens[1];
            string position = tokens[2];
            double salary = tokens[3] == "-" ? 0.0 : stod(tokens[3]);
            string project = tokens[4];

            Employee* emp = nullptr;

            // Создание объектов в зависимости от должности
            if (position == "cleaner") {
                emp = new Cleaner(id, name, position, project, salary);
            }
            else if (position == "driver") {
                emp = new Driver(id, name, position, project, salary);
            }
            else if (position == "programmer") {
                emp = new Programmer(id, name, position, project, salary);
            }
            else if (position == "tester") {
                emp = new Tester(id, name, position, project, salary);
            }
            else if (position == "team_leader") {
                emp = new TeamLeader(id, name, position, project, salary);
            }
            else if (position == "project_manager") {
                emp = new ProjectManager(id, name, position, project);
            }
            else if (position == "senior_manager") {
                emp = new SeniorManager(id, name, position);
            }

            if (emp) {
                staff.push_back(emp);
            }
            else {
                cerr << "Warning: Unknown position '" << position << "' in line: " << line << endl;
            }
        }
        catch (const exception& e) {
            cerr << "Error processing line: " << line << " - " << e.what() << endl;
        }
    }
    return staff;
}

// Сохранение данных о персонале в CSV-файл
void StaffFactory::saveStaff(const string& filename,
    const vector<Employee*>& staff) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Cannot create file " << filename << endl;
        return;
    }

    // Запись заголовока
    file << "id;name;position;salary;project\n";

    // Запись данных по каждому сотруднику
    for (auto emp : staff) {
        file << emp->getId() << ";"
            << emp->getName() << ";"
            << emp->getPosition() << ";"
            << emp->getSalary() << ";"
            << emp->getProject() << "\n";
    }
}