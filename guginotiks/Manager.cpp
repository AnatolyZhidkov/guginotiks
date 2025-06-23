#include "Manager.h"
#include "Project.h"
using namespace std;

// Конструктор менеджера проекта
ProjectManager::ProjectManager(int id, const string& name,
    const string& position, const string& project)
    : Employee(id, name, position, project) {
}

// Доля от бюджета: 30% бюджета / количество работников
double ProjectManager::calcBudgetPart(double projectBudget, int totalWorkers) {
    if (totalWorkers == 0) return 0;
    return (projectBudget * 0.3) / totalWorkers;
}

// Доп выплаты не предусмотрены
double ProjectManager::calcProAdditions() {
    return 0;
}

// Доплата за подчиненных: 1000 за каждого
double ProjectManager::calcHeadingAdditions(int subordinateCount) {
    return 1000 * subordinateCount;
}

// Менеджеры не имеют фиксированной ставки
double ProjectManager::getSalary() const {
    return 0;
}

// Расчет зарплаты менеджера:
// Доля от бюджета + доплата за подчиненных
void ProjectManager::calc(const vector<Project>& projects,
    const vector<Employee*>& staff) {
    double budgetPart = 0;
    double headingAdditions = 0;

    if (!project.empty()) {
        // Поиск проекта по имени
        vector<Project>::const_iterator it;
        for (it = projects.begin(); it != projects.end(); ++it) {
            if (it->name == project) {
                break;
            }
        }

        if (it != projects.end()) {
            int workerCount = 0;      // Кол-во работников на проекте
            int subordinateCount = 0; // Кол-во подчиненных

            for (auto emp : staff) {
                if (emp->getProject() == project) {
                    // Подсчет персонала на проекте
                    if (emp->getPosition() == "programmer" ||
                        emp->getPosition() == "tester" ||
                        emp->getPosition() == "team_leader") {
                        workerCount++;
                    }

                    // Подсчет подчиненных (все кроме менеджера)
                    if (emp->getId() != id) {
                        subordinateCount++;
                    }
                }
            }

            // Расчет составляющих зарплаты
            budgetPart = calcBudgetPart(it->budget, workerCount);
            headingAdditions = calcHeadingAdditions(subordinateCount);
        }
    }

    payment = budgetPart + headingAdditions;
}

// Конструктор старшего менеджера (не привязан к проекту)
SeniorManager::SeniorManager(int id, const string& name,
    const string& position)
    : Employee(id, name, position, "") {
}

// Доля от бюджета: 15% от бюджета проекта
double SeniorManager::calcBudgetPart(double projectBudget, int totalWorkers) {
    return projectBudget * 0.15;
}

// Дополнительные выплаты не предусмотрены
double SeniorManager::calcProAdditions() {
    return 0;
}

// Доплата за подчиненных: 5000 за каждого менеджера
double SeniorManager::calcHeadingAdditions(int subordinateCount) {
    return 5000 * subordinateCount;
}

// Старший менеджер не имеет фиксированной ставки
double SeniorManager::getSalary() const {
    return 0;
}

// Расчет зарплаты старшего менеджера:
// Сумма по всем проектам (15% от бюджета) + доплата за подчиненных
void SeniorManager::calc(const vector<Project>& projects,
    const vector<Employee*>& staff) {
    double budgetTotal = 0;
    int subordinateCount = 0;

    // Суммирует доли от всех проектов
    for (const auto& p : projects) {
        budgetTotal += calcBudgetPart(p.budget, 0);
    }

    // Подсчитывает подчиненных (менеджеров и главного команд)
    for (auto emp : staff) {
        if (emp->getPosition() == "project_manager" ||
            emp->getPosition() == "team_leader") {
            subordinateCount++;
        }
    }

    payment = budgetTotal + calcHeadingAdditions(subordinateCount);
}

// Конструктор лидера команды
TeamLeader::TeamLeader(int id, const string& name,
    const string& position, const string& project, double salary)
    : Programmer(id, name, position, project, salary) {
}

// Доплата за подчиненных: 500 за каждого программиста
double TeamLeader::calcHeadingAdditions(int subordinateCount) {
    return 500 * subordinateCount;
}

// Расчет зарплаты лидера команды:
// Зарплата программиста + доплата за подчиненных
void TeamLeader::calc(const vector<Project>& projects,
    const vector<Employee*>& staff) {
    // Сначала рассчитывает зарплату как для программиста
    Programmer::calc(projects, staff);

    int subordinateCount = 0;
    // Подсчитывает подчиненных программистов (кроме самого лидера)
    for (auto emp : staff) {
        if (emp->getProject() == project &&
            emp->getPosition() == "programmer" &&
            emp->getId() != id) {
            subordinateCount++;
        }
    }

    // Добавляет доплату за подчиненных
    payment += calcHeadingAdditions(subordinateCount);
}