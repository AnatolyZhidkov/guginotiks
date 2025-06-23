#include "Engineer.h"
#include "Project.h"
using namespace std;

// Конструктор всех сотрудников инициализирует почасовую ставку
Engineer::Engineer(int id, const string& name,
    const string& position, const string& project, double salary)
    : Employee(id, name, position, project), salary(salary) {
}

// Базовая зарплата = ставка * часы
double Engineer::calcBase() {
    return salary * worktime;
}

// Базовая реализация бонуса - 0
double Engineer::calcBonus() {
    return 0;
}

// Возвращает почасовую ставку
double Engineer::getSalary() const {
    return salary;
}

// Расчет доли от бюджета проекта: 30% бюджета / количество работников
double Engineer::calcBudgetPart(double projectBudget, int totalWorkers) {
    return (projectBudget * 0.3) / totalWorkers;
}

// Конструктор программиста инициализирует досрочное завершение
Programmer::Programmer(int id, const string& name,
    const string& position, const string& project, double salary)
    : Engineer(id, name, position, project, salary), hasEarlyCompletion(false) {
}

// Устанавка флага досрочного завершения проекта
void Programmer::setEarlyCompletion(bool flag) {
    hasEarlyCompletion = flag;
}

// Доплата 20000 за досрочное завершение
double Programmer::calcProAdditions() {
    return hasEarlyCompletion ? 20000 : 0;
}

// Расчет зарплаты программиста:
// База + доля от бюджета + доплата за досрочное завершение
void Programmer::calc(const vector<Project>& projects,
    const vector<Employee*>& staff) {
    double base = calcBase();
    double budgetPart = 0;
    double additions = calcProAdditions();

    if (!project.empty()) {
        // Поиск проекта по имени
        vector<Project>::const_iterator it;
        for (it = projects.begin(); it != projects.end(); ++it) {
            if (it->name == project) {
                break;
            }
        }

        if (it != projects.end()) {
            // Подсчет работников на проекте
            int count = 0;
            for (auto emp : staff) {
                if (emp->getProject() == project &&
                    (emp->getPosition() == "programmer" ||
                        emp->getPosition() == "tester" ||
                        emp->getPosition() == "team_leader")) {
                    count++;
                }
            }
            // Расчет доли от бюджета
            budgetPart = calcBudgetPart(it->budget, count);
        }
    }

    payment = base + budgetPart + additions;
}

// Конструктор тестировщика инициализирует счетчик ошибок
Tester::Tester(int id, const string& name,
    const string& position, const string& project, double salary)
    : Engineer(id, name, position, project, salary), errorCount(0) {
}

// Устанавка кол-ва найденных ошибок
void Tester::setErrorCount(int count) {
    errorCount = count;
}

// Доплата за ошибки: 500 за каждую найденную ошибку
double Tester::calcProAdditions() {
    return 500 * errorCount;
}

// Расчет зарплаты тестировщика:
// База + доля от бюджета + доплата за ошибки
void Tester::calc(const vector<Project>& projects,
    const vector<Employee*>& staff) {
    double base = calcBase();
    double budgetPart = 0;
    double additions = calcProAdditions();

    if (!project.empty()) {
        // Поиск проекта по имени
        vector<Project>::const_iterator it;
        for (it = projects.begin(); it != projects.end(); ++it) {
            if (it->name == project) {
                break;
            }
        }

        if (it != projects.end()) {
            // Подсчет работников на проекте
            int count = 0;
            for (auto emp : staff) {
                if (emp->getProject() == project &&
                    (emp->getPosition() == "programmer" ||
                        emp->getPosition() == "tester" ||
                        emp->getPosition() == "team_leader")) {
                    count++;
                }
            }
            // Расчет доли от бюджета
            budgetPart = calcBudgetPart(it->budget, count);
        }
    }

    payment = base + budgetPart + additions;
}