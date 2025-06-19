#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>  
#include "Employee.h"
#include "Project.h"
#include "Factory.h"
#include "Personal.h"  
#include "Engineer.h"  
using namespace std;

vector<Employee*> staff;
vector<Project> projects;

void loadProjects(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Предупреждение: Не удалось открыть файл проектов " << filename << endl;
        return;
    }

    string line;
    getline(file, line); 

    while (getline(file, line)) {
        istringstream iss(line);
        string name, budgetStr;

        if (getline(iss, name, ';') && getline(iss, budgetStr)) {
            try {
                projects.push_back({ name, stod(budgetStr) });
            }
            catch (const exception& e) {
                cerr << "Ошибка обработки проекта: " << line << " - " << e.what() << endl;
            }
        }
    }
}

void saveProjects(const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Ошибка: Не удалось создать файл проектов " << filename << endl;
        return;
    }

    file << "name;budget\n";
    for (const auto& p : projects) {
        file << p.name << ";" << fixed << setprecision(2) << p.budget << "\n";
    }
}

void inputWorkData() {
    for (Employee* emp : staff) {
        cout << "Введите отработанное время для " << emp->getName() << " (" << emp->getPosition() << "): ";
        double hours;
        cin >> hours;
        emp->setWorkTime(hours);

        if (auto driver = dynamic_cast<Driver*>(emp)) {
            cout << "Введите ночные часы: ";
            double nightHours;
            cin >> nightHours;
            driver->setNightHours(nightHours);
        }
        else if (auto programmer = dynamic_cast<Programmer*>(emp)) {
            cout << "Досрочное завершение (1-да, 0-нет): ";
            int flag;
            cin >> flag;
            programmer->setEarlyCompletion(flag == 1);
        }
        else if (auto tester = dynamic_cast<Tester*>(emp)) {
            cout << "Введите количество найденных ошибок: ";
            int errors;
            cin >> errors;
            tester->setErrorCount(errors);
        }
    }
}

void calculateSalaries() {
    for (Employee* emp : staff) {
        emp->calc(projects, staff);
    }
    cout << "Зарплаты успешно рассчитаны!\n";
}

void printAllStaff() {
    cout << "\nID   Имя                Должность            Часы     Зарплата\n";
    cout << "----------------------------------------------------------------\n";
    for (const auto& emp : staff) {
        emp->printInfo();
    }
    cout << "----------------------------------------------------------------\n";
}

void printByProject(const string& projectName) {
    cout << "\nСотрудники проекта '" << projectName << "':\n";
    bool found = false;
    for (const auto& emp : staff) {
        if (emp->getProject() == projectName) {
            emp->printInfo();
            found = true;
        }
    }
    if (!found) {
        cout << "Сотрудники по проекту не найдены.\n";
    }
}

void findByPosition(const string& position) {
    cout << "\nСотрудники с должностью '" << position << "':\n";
    bool found = false;
    for (const auto& emp : staff) {
        if (emp->getPosition() == position) {
            emp->printInfo();
            found = true;
        }
    }
    if (!found) {
        cout << "Сотрудники с указанной должностью не найдены.\n";
    }
}

void findByName(const string& name) {
    cout << "\nСотрудники с именем '" << name << "':\n";
    bool found = false;
    for (const auto& emp : staff) {
        if (emp->getName().find(name) != string::npos) {
            emp->printInfo();
            found = true;
        }
    }
    if (!found) {
        cout << "Сотрудники с указанным именем не найдены.\n";
    }
}

void findBySalary(double threshold, bool greater) {
    cout << "\nСотрудники с зарплатой " << (greater ? "> " : "< ") << threshold << ":\n";
    bool found = false;
    for (const auto& emp : staff) {
        if ((greater && emp->getPayment() > threshold) ||
            (!greater && emp->getPayment() < threshold)) {
            emp->printInfo();
            found = true;
        }
    }
    if (!found) {
        cout << "Сотрудники в указанном диапазоне зарплат не найдены.\n";
    }
}

void createProject() {
    string name;
    double budget;
    cout << "Введите название проекта: ";
    cin.ignore();
    getline(cin, name);
    cout << "Введите бюджет проекта: ";
    cin >> budget;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Некорректное значение бюджета!\n";
        return;
    }

    projects.push_back({ name, budget });
    saveProjects("data/projects.txt");
    cout << "Проект успешно создан!\n";
}

void addToProject() {
    int id;
    string project;
    cout << "Введите ID сотрудника: ";
    cin >> id;
    cout << "Введите название проекта: ";
    cin.ignore();
    getline(cin, project);

    auto it = find_if(staff.begin(), staff.end(),
        [id](Employee* emp) { return emp->getId() == id; });

    if (it != staff.end()) {
        if ((*it)->getPosition() == "senior_manager") {
            cout << "Нельзя добавить старшего менеджера на проект.\n";
        }
        else {
            (*it)->setProject(project);
            cout << "Сотрудник добавлен на проект.\n";
        }
    }
    else {
        cout << "Сотрудник не найден.\n";
    }
}

void changeProject() {
    int id;
    string newProject;
    cout << "Введите ID сотрудника: ";
    cin >> id;
    cout << "Введите новый проект: ";
    cin.ignore();
    getline(cin, newProject);

    auto it = find_if(staff.begin(), staff.end(),
        [id](Employee* emp) { return emp->getId() == id; });

    if (it != staff.end()) {
        if ((*it)->getPosition() == "senior_manager") {
            cout << "Нельзя изменить проект для старшего менеджера.\n";
        }
        else {
            (*it)->setProject(newProject);
            cout << "Проект сотрудника успешно изменен.\n";
        }
    }
    else {
        cout << "Сотрудник не найден.\n";
    }
}

int main() {
    setlocale(0, "");
    cout << "Загрузка данных о сотрудниках...\n";
    staff = StaffFactory::makeStaff("data/staff.txt");

    cout << "Загрузка данных о проектах...\n";
    loadProjects("data/projects.txt");

    int choice;
    do {
        cout << "\n===== Система управления персоналом =====\n"
            << "1. Ввод рабочих данных\n"
            << "2. Расчет зарплат\n"
            << "3. Вывод всех сотрудников\n"
            << "4. Сотрудники по проекту\n"
            << "5. Поиск по должности\n"
            << "6. Поиск по имени\n"
            << "7. Поиск по зарплате (выше)\n"
            << "8. Поиск по зарплате (ниже)\n"
            << "9. Создать новый проект\n"
            << "10. Добавить сотрудника на проект\n"
            << "11. Изменить проект сотрудника\n"
            << "12. Сохранить и выйти\n"
            << "Выберите действие: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }

        switch (choice) {
        case 1:
            inputWorkData();
            break;
        case 2:
            calculateSalaries();
            break;
        case 3:
            printAllStaff();
            break;
        case 4: {
            string project;
            cout << "Введите название проекта: ";
            cin.ignore();
            getline(cin, project);
            printByProject(project);
            break;
        }
        case 5: {
            string position;
            cout << "Введите должность: ";
            cin.ignore();
            getline(cin, position);
            findByPosition(position);
            break;
        }
        case 6: {
            string name;
            cout << "Введите имя: ";
            cin.ignore();
            getline(cin, name);
            findByName(name);
            break;
        }
        case 7: {
            double salary;
            cout << "Введите порог зарплаты: ";
            if (cin >> salary) {
                findBySalary(salary, true);
            }
            else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректный ввод!\n";
            }
            break;
        }
        case 8: {
            double salary;
            cout << "Введите порог зарплаты: ";
            if (cin >> salary) {
                findBySalary(salary, false);
            }
            else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректный ввод!\n";
            }
            break;
        }
        case 9:
            createProject();
            break;
        case 10:
            addToProject();
            break;
        case 11:
            changeProject();
            break;
        case 12:
            StaffFactory::saveStaff("data/staff_updated.txt", staff);
            cout << "Данные сохранены. Выход...\n";
            break;
        default:
            cout << "Некорректный выбор. Попробуйте снова.\n";
        }
    } while (choice != 12);

    
    for (auto emp : staff) {
        delete emp;
    }
    staff.clear();

    return 0;
}

