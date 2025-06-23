#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Employee.h"
#include "Project.h"
#include "Factory.h"
#include "Personal.h"
#include "Engineer.h"
#include "Manager.h"
#include <cassert>
#define RUN_TESTS  

using namespace std;

// для хранения данных
vector<Employee*> staff;    // Список всех сотрудников
vector<Project> projects;   // Список всех проектов

// Загрузка проектов из CSV-файла
void loadProjects(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Предупреждение: Не удалось открыть файл проектов " << filename << endl;
        return;
    }

    string line;
    getline(file, line);  // Пропуск заголовока

    // Читение файла построчно
    while (getline(file, line)) {
        istringstream iss(line);
        string name, budgetStr;

        // Разбитие строки на поля по разделителю ';'
        if (getline(iss, name, ';') && getline(iss, budgetStr)) {
            try {
                // Создание проекта и добавление в список
                projects.push_back({ name, stod(budgetStr) });
            }
            catch (const exception& e) {
                cerr << "Ошибка обработки проекта: " << line << " - " << e.what() << endl;
            }
        }
    }
}

// Сохранение проектов в CSV-файл
void saveProjects(const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Ошибка: Не удалось создать файл проектов " << filename << endl;
        return;
    }

    // Запись заголовков
    file << "name;budget\n";
    for (const auto& p : projects) {
        // Запись данных проекта
        file << p.name << ";" << p.budget << "\n";
    }
}

// Ввод рабочих данных для всех сотрудников
void inputWorkData() {
    for (Employee* emp : staff) {
        // Запрос отработанного времени
        cout << "Введите отработанное время для " << emp->getName() << " (" << emp->getPosition() << "): ";
        double hours;
        cin >> hours;
        emp->setWorkTime(hours);

        // Для водителей: запрос ночных часов
        if (auto driver = dynamic_cast<Driver*>(emp)) {
            cout << "Введите ночные часы: ";
            double nightHours;
            cin >> nightHours;
            driver->setNightHours(nightHours);
        }
        // Для программистов: досрочное завершения
        else if (auto programmer = dynamic_cast<Programmer*>(emp)) {
            cout << "Досрочное завершение (1-да, 0-нет): ";
            int flag;
            cin >> flag;
            programmer->setEarlyCompletion(flag == 1);
        }
        // Для тестировщиков: количество найденных ошибок
        else if (auto tester = dynamic_cast<Tester*>(emp)) {
            cout << "Введите количество найденных ошибок: ";
            int errors;
            cin >> errors;
            tester->setErrorCount(errors);
        }
    }
}

// Расчет ЗП для всех сотрудников
void calculateSalaries() {
    // Вызываем метод calc() для каждого сотрудника
    for (Employee* emp : staff) {
        emp->calc(projects, staff);
    }
    cout << "Зарплаты успешно рассчитаны!\n";
}

// Вывод всех сотрудников в виде таблицы
void printAllStaff() {
    cout << "\nID   Имя                Должность            Часы     Зарплата\n";
    cout << "----------------------------------------------------------------\n";
    for (const auto& emp : staff) {
        emp->printInfo();
    }
    cout << "----------------------------------------------------------------\n";
}

// Вывод сотрудников конкретного проекта
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

// Поиск сотрудников по должности
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

// Поиск сотрудников по имени (какое-либо совпадение)
void findByName(const string& name) {
    cout << "\nСотрудники с именем '" << name << "':\n";
    bool found = false;
    for (const auto& emp : staff) {
        // Поиск подстроки в имени
        if (emp->getName().find(name) != string::npos) {
            emp->printInfo();
            found = true;
        }
    }
    if (!found) {
        cout << "Сотрудники с указанным именем не найдены.\n";
    }
}

// Поиск сотрудников по зарплате (выше/ниже порога)
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

// Создание нового проекта
void createProject() {
    string name;
    double budget;

    cout << "Введите название проекта: ";
    cin.ignore();
    getline(cin, name);

    cout << "Введите бюджет проекта: ";
    cin >> budget;

    // Проверка корректности ввода
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Некорректное значение бюджета!\n";
        return;
    }

    // Добавление проекта и сохранение в файл
    projects.push_back({ name, budget });
    saveProjects("data/projects.txt");
    cout << "Проект успешно создан!\n";
}

// Добавление сотрудника на проект
void addToProject() {
    int id;
    string project;

    cout << "Введите ID сотрудника: ";
    cin >> id;

    cout << "Введите название проекта: ";
    cin.ignore();
    getline(cin, project);

    // Поиск сотрудника по ID
    vector<Employee*>::iterator it = staff.end();
    for (auto iter = staff.begin(); iter != staff.end(); ++iter) {
        if ((*iter)->getId() == id) {
            it = iter;
            break;
        }
    }

    if (it != staff.end()) {
        // Проверка
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

// Изменение проекта сотрудника
void changeProject() {
    int id;
    string newProject;

    cout << "Введите ID сотрудника: ";
    cin >> id;

    cout << "Введите новый проект: ";
    cin.ignore();
    getline(cin, newProject);

    // Поиск сотрудника по ID для назначения на новый проект
    vector<Employee*>::iterator it = staff.end();
    for (auto iter = staff.begin(); iter != staff.end(); ++iter) {
        if ((*iter)->getId() == id) {
            it = iter;
            break;
        }
    }

    if (it != staff.end()) {
        // Проверка
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

// Юнит-тесты для проверки расчетов зарплат
void runUnitTests() {
    setlocale(0, "");  

    cout << "\n=== Запуск юнит-тестов ===\n";

    // Тест 1: Расчет зарплаты уборщика
    Cleaner cleaner(999, "Test Cleaner", "cleaner", "-", 100);
    cleaner.setWorkTime(160);
    cleaner.calc({}, {});
    assert(cleaner.getPayment() == 16000);
    cout << "Тест 1 пройден: Cleaner salary\n";

    // Тест 2: Водитель с ночными часами
    Driver driver(998, "Test Driver", "driver", "-", 120);
    driver.setWorkTime(160);
    driver.setNightHours(40);
    driver.calc({}, {});
    assert(driver.getPayment() == 21600);
    cout << "Тест 2 пройден: Driver with night hours\n";

    // Тест 3: Программист с бонусом за досрочное завершение
    Programmer prog(997, "Test Programmer", "programmer", "TestProject", 150);
    prog.setWorkTime(160);
    prog.setEarlyCompletion(true);

    vector<Project> projects = { {"TestProject", 1000000} };
    vector<Employee*> staff = { &prog };

    prog.calc(projects, staff);
    assert(prog.getPayment() == 344000);
    cout << "Тест 3 пройден: Programmer with bonus\n";

    // Тест 4: Смена проекта программиста
    prog.setProject("NewProject");
    projects.push_back({ "NewProject", 500000 });
    prog.calc(projects, staff);
    assert(prog.getPayment() == 194000);
    cout << "Тест 4 пройден: Project change\n";

    // Тест 5: Тестировщик с найденными ошибками
    Tester tester(996, "Test Tester", "tester", "QualityProject", 140);
    tester.setWorkTime(160);
    tester.setErrorCount(25);

    projects.push_back({ "QualityProject", 800000 });
    staff.push_back(&tester);
    tester.calc(projects, staff);

    assert(tester.getPayment() == 22400 + 240000 + 12500);
    cout << "Тест 5 пройден: Tester with errors bonus\n";

    // Тест 6: Менеджер проекта с командой
    ProjectManager pm(995, "Test PM", "project_manager", "TeamProject");
    Programmer p1(994, "Dev 1", "programmer", "TeamProject", 150);
    Tester t1(993, "QA 1", "tester", "TeamProject", 140);

    projects.push_back({ "TeamProject", 1500000 });
    vector<Employee*> team = { &pm, &p1, &t1 };

    for (auto emp : team) {
        emp->calc(projects, team);
    }

    assert(pm.getPayment() == 225000 + 2000);
    cout << "Тест 6 пройден: Project manager salary\n";

    cout << "=== Все 6 тестов успешно пройдены ===\n\n";
}


int main() {
#ifdef RUN_TESTS
    runUnitTests();  // Запуск тестов 
#endif

    setlocale(0, "");  

    // Загрузка начальных данных
    cout << "Загрузка данных о сотрудниках...\n";
    staff = StaffFactory::makeStaff("data/staff.txt");

    cout << "Загрузка данных о проектах...\n";
    loadProjects("data/projects.txt");

    int choice;
    do {
        // Вывод главного меню
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

        // Обработка некорректного ввода
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
        }

        // Обработка выбора пользователя
        switch (choice) {
        case 1:
            inputWorkData();  // Ввод рабочих данных
            break;
        case 2:
            calculateSalaries();  // Расчет зарплат
            break;
        case 3:
            printAllStaff();  // Вывод всех сотрудников
            break;
        case 4: {
            string project;
            cout << "Введите название проекта: ";
            cin.ignore();
            getline(cin, project);
            printByProject(project);  // Сотрудники проекта
            break;
        }
        case 5: {
            string position;
            cout << "Введите должность: ";
            cin.ignore();
            getline(cin, position);
            findByPosition(position);  // Поиск по должности
            break;
        }
        case 6: {
            string name;
            cout << "Введите имя: ";
            cin.ignore();
            getline(cin, name);
            findByName(name);  // Поиск по имени
            break;
        }
        case 7: {
            double salary;
            cout << "Введите порог зарплаты: ";
            if (cin >> salary) {
                findBySalary(salary, true);  // Зарплата выше порога
            }
            else {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Некорректный ввод!\n";
            }
            break;
        }
        case 8: {
            double salary;
            cout << "Введите порог зарплаты: ";
            if (cin >> salary) {
                findBySalary(salary, false);  // Зарплата ниже порога
            }
            else {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Некорректный ввод!\n";
            }
            break;
        }
        case 9:
            createProject();  // Создание проекта
            break;
        case 10:
            addToProject();  // Добавление на проект
            break;
        case 11:
            changeProject();  // Изменение проекта
            break;
        case 12:
            // Сохранение данных перед выходом
            StaffFactory::saveStaff("data/staff_updated.txt", staff);
            cout << "Данные сохранены. Выход...\n";
            break;
        default:
            cout << "Некорректный выбор. Попробуйте снова.\n";
        }
    } while (choice != 12);  // Выход

    // Освобождение памяти
    for (auto emp : staff) {
        delete emp;
    }
    staff.clear();

    return 0;
}